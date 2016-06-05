/**
 * lab_sec
 * Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#include "crypto.hpp"
#include "functions.hpp"

const std::string PUBLIC_KEY = PUBKEY;

/**
 * Шифрование или дешифрование файла алгоритмом AES в режиме сцепления блоков
 * шифротекста. Действие  зависит от флага 'should_encrypt'
 */
bool en_de_crypt_files(int should_encrypt, FILE *ifp, FILE *ofp, unsigned char *ckey,
                 unsigned char *ivec)
{
    const unsigned int BUFSIZE = 4096;  // размер буфера чтения
    unsigned char *read_buf = (unsigned char*)malloc(BUFSIZE);  // создание буфера чтения
    unsigned char *cipher_buf;  // указатель на буфер шифрования
    unsigned int blocksize;  // размер блока шифрования
    int out_len;  // размер обработанных данных
    EVP_CIPHER_CTX ctx;  // указатель на контекст шифрования

    // инициализация контекста шифрования алгоритмом AES с режимом
    // сцепления блоков шифротекста, ключем ckey длины 256 бит,
    // начальным вектором ivec размера 128 бит
    if (!EVP_CipherInit(&ctx, EVP_aes_256_cbc(), ckey, ivec, should_encrypt)) {
        free(read_buf);
        return false;
    }
    // получение размера блока для выбранного алгоритма
    blocksize = EVP_CIPHER_CTX_block_size(&ctx);
    // выделение места под буфер шифрования
    cipher_buf = (unsigned char*)malloc(BUFSIZE + blocksize);

    while (1) {
        // Чтение данных до достижения конца файла. Обработка данных при каждом чтении.
        int numRead = fread(read_buf, sizeof(unsigned char), BUFSIZE, ifp);
        if (!EVP_CipherUpdate(&ctx, cipher_buf, &out_len, read_buf, numRead)) {  // обработка блока
            free(cipher_buf);
            free(read_buf);
            return false;
        }
        fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);
        if (numRead < BUFSIZE) { // Условие достижения конца файла
            break;
        }
    }

    // Обработка последнего блока файла и запись его в файл.
    if (!EVP_CipherFinal(&ctx, cipher_buf, &out_len)) {
        free(cipher_buf);
        free(read_buf);
        return false;
    }

    fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);

    // Освобождение памяти
    free(cipher_buf);
    free(read_buf);

    return true;
}


/**
 * Шифрование или дешифрование алгоритмом AES в режиме сцепления блоков
 * шифротекста. Действие  зависит от флага 'should_encrypt'
 */
bool en_de_crypt(int should_encrypt, unsigned char *in, unsigned char **out,
                 int in_len, unsigned char *ckey, unsigned char *ivec)
{
    unsigned int blocksize;  // размер блока шифрования
    int out_len;  // размер обработанных данных
    EVP_CIPHER_CTX ctx;  // контекст шифрования

    // инициализация контекста шифрования алгоритмом AES с режимом
    // сцепления блоков шифротекста, ключем ckey длины 256 бит,
    // начальным вектором ivec размера 128 бит
    if (!EVP_CipherInit(&ctx, EVP_aes_256_cbc(), ckey, ivec, should_encrypt)) {
        return false;
    }
    // получение размера блока для выбранного алгоритма
    blocksize = EVP_CIPHER_CTX_block_size(&ctx);
    // выделение места под буфер шифрования
    *out = (unsigned char*)malloc(in_len + blocksize);
    // обработка буфера шифрования
    if (!EVP_CipherUpdate(&ctx, *out, &out_len, in, in_len)) {
        return false;
    }
    // завершение шифрования
    if (!EVP_CipherFinal(&ctx, *out, &out_len)) {
        return false;
    }

    return true;
}

std::wstring hash_str(std::wstring in)  // хеширование гаммированием строки 12345678
{
    std::string str = "12345678";  // исходная строка
    std::string p = wstring_to_string(in);  // преобразование входной строки
    char G = p[2];  // G (исходная гамма) равен третьему символу входной строки
    char A = p[0];  // A равен первому символу входной строки
    char C = p[1];  // C равен второму символу входной строки
    std::wstringstream out;  // сюда будет идти запись хеша
    out << std::hex;  // запись будет производиться в шестнадцатиричном виде
    for (auto i: str) {  // цикл, проходящий по всем символам строки str
        out << (i ^ G);  // вычисление символа шифротекста и его запись
        G = (G*A + C) % 256;  // вычисление следующей гаммы
    }
    return out.str();  // возврат хеша
}

bool sha_256(std::wstring str, unsigned char* hash)
{
    SHA256_CTX context;  // контекст хеширования
    if(!SHA256_Init(&context)) {  // инициализация контекста хеширования
        return false;
    }

    // хеширование входной строки
    if(!SHA256_Update(&context, (unsigned char*)str.c_str(),
                      str.size() * sizeof(wchar_t))) {
        return false;
    }

    // завершение хеширования
    if(!SHA256_Final(hash, &context)) {
        return false;
    }

    return true;
}
