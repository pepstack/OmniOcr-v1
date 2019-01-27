/**
 * RC4.H
 */
#ifndef ___RC4_H___
#define ___RC4_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#define  RC4_DEFAULT_KEY		"should NOT use rc4 default key"

int RC4_encrypt_string(char *source, size_t sourcelen, char* key, size_t keylen);
int RC4_encrypt_file(char *source, char* dest, char* key, size_t keylen, char *buffer, size_t buffer_size);
int RC4_encrypt_file_w(wchar_t *source, wchar_t* dest, char* key, size_t keylen, char *buffer, size_t buffer_size);

int RC4_hex_encode(const unsigned char *source, size_t sourceSize, char* dest, size_t destSize);
int RC4_hex_decode(const char *source, size_t sourceLen, char* dest, size_t destSize);

#if defined(__cplusplus)
}
#endif

#endif
