#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <cstdio>
//#include <cstdlib>
#include <string>
#include <sstream>

bool en_de_crypt_files(int should_encrypt, FILE *ifp, FILE *ofp,
                       unsigned char *ckey, unsigned char *ivec);
bool en_de_crypt(int should_encrypt, unsigned char *in, unsigned char **out,
                 int in_len, unsigned char *ckey, unsigned char *ivec);
std::wstring hash_str(std::wstring in);
//bool sha_256(void* input, unsigned long length, unsigned char* hash);
bool sha_256(std::wstring str, unsigned char* hash);

#endif
