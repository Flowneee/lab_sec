#ifndef __CRYPTO_H__
#define __CRYPTO_H__

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

#include <cstdio>
//#include <cstdlib>
#include <string>
#include <sstream>

extern const std::string PUBLIC_KEY;

bool en_de_crypt_files(int should_encrypt, FILE *ifp, FILE *ofp,
                       unsigned char *ckey, unsigned char *ivec);
bool en_de_crypt(int should_encrypt, unsigned char *in, unsigned char **out,
                 int in_len, unsigned char *ckey, unsigned char *ivec);
std::wstring hash_str(std::wstring in);
bool sha_256(std::wstring str, unsigned char* hash);

#endif
