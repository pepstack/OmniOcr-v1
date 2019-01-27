/**
 * RC4.C
 */
#include "rc4.h"
#include <assert.h>

int RC4_encrypt_string( char *source, size_t sourcelen, char* key, size_t keylen)
{
    /* we will consider size of sbox 256 bytes
       (extra byte are only to prevent any mishep just in case) */
    char Sbox[257], Sbox2[257];
    unsigned long i, j, t, x;

    /* this unsecured key is to be used only when there is no source key from user */
    static const char OurUnSecuredKey[] = RC4_DEFAULT_KEY;
    size_t OurKeyLen = strlen( OurUnSecuredKey );
    char temp , k = 0;
    i = j = t = x = 0;
    temp = 0;

    /* always initialize the arrays with zero */
    memset(Sbox, 0, sizeof( Sbox ) );
	memset(Sbox2, 0, sizeof( Sbox2 ) );
    
    /* initialize sbox i */
    for( i = 0; i < 256U; i++ )
    {
        Sbox[i] = ( char )i;
    }

    j = 0;

    /* whether user has sent any sourceur key */
    if( keylen )
    {
        /* initialize the sbox2 with user key */
        for( i = 0; i < 256U ; i++ )
        {
            if( j == keylen )
            {
                j = 0;
            }
            Sbox2[i] = key[j++];
        }
    }
    else
    {
        /* initialize the sbox2 with our key */
        for( i = 0; i < 256U ; i++ )
        {
            if( j == OurKeyLen )
            {
                j = 0;
            }
            Sbox2[i] = OurUnSecuredKey[j++];
        }
    }


    j = 0 ; /* Initialize j */
    
	/* scramble sbox1 with sbox2 */
    for( i = 0; i < 256; i++ )
    {
        j = ( j + ( unsigned long ) Sbox[i] + ( unsigned long ) Sbox2[i] ) % 256U ;
        temp =  Sbox[i];                    
        Sbox[i] = Sbox[j];
        Sbox[j] =  temp;
    }

    i = j = 0;
    for( x = 0; x < sourcelen; x++ )
    {
        /* increment i */
        i = (i + 1U) % 256U;
        
		/*increment j */
        j = (j + ( unsigned long ) Sbox[i] ) % 256U;

        /* Scramble SBox #1 further so encryption routine will
           will repeat itself at great interval */
        temp = Sbox[i];
        Sbox[i] = Sbox[j] ;
        Sbox[j] = temp;

        /* Get ready to create pseudo random  byte for encryption key */
        t = ( ( unsigned long ) Sbox[i] + ( unsigned long ) Sbox[j] ) %  256U ;

        /* get the random byte */
        k = Sbox[t];

        /* xor with the data and done */
        source[x] = ( source[x] ^ k );
    }

	return (int) sourcelen;
}

int RC4_encrypt_file( char *source, char* dest, char* key, size_t keylen, char *buffer, size_t buffer_size )
{
	size_t totalWrite = 0;
	size_t totalRead = 0;
    size_t sizeRead = 1;

	/* Reading crypted file and decrypt content */
	if (source==dest){

#ifndef WINCE
		FILE  *fp = 0;
		if (0 != fopen_s(&fp, source, "rb+"))
			return 0;
#else
		FILE  *fp = fopen(source, "rb+");
		if (!fp)
			return 0;
#endif

		while (sizeRead){
			if (0 != fseek(fp, (long)totalRead, SEEK_SET)){
				fclose(fp);
				return 0;
			}

			sizeRead = fread( buffer, sizeof(char), buffer_size, fp );
			if (sizeRead==0)
				break;
			totalRead += sizeRead;

			RC4_encrypt_string(buffer, sizeRead, key, keylen);
			
			if (0 != fseek(fp, (long)totalWrite, SEEK_SET)){
				fclose(fp);
				return 0;
			}

			totalWrite += fwrite(buffer, sizeof(char), sizeRead, fp);
		}
		fclose(fp);
	}
	else{
		FILE *fpr = 0;
		FILE *fpw = 0;

	#ifndef WINCE
		if (0 != fopen_s(&fpr, source, "rb" ))
			return 0;

		if (0 != fopen_s(&fpw, dest, "rb" )){
			fclose(fpr);
			return 0;
		}
	#else
		fpr = fopen( source, "rb" );
		if (!fpr)
			return 0;

		fpw = fopen( dest, "wb" );
		if (!fpw){
			fclose(fpr);
			return 0;
		}
	#endif
		
		while (!feof(fpr)){
			sizeRead = fread( buffer, sizeof(char), buffer_size, fpr );
			RC4_encrypt_string(buffer, sizeRead, key, keylen);
			totalRead += sizeRead;
			totalWrite += fwrite(buffer, sizeof(char), sizeRead, fpw);
		}
		fclose(fpr);
		fclose(fpw);
	}

	if (totalRead==totalWrite)
		return (int) totalWrite;
	assert(0);
	return 0;
}

int RC4_encrypt_file_w(wchar_t *source, wchar_t* dest, char* key, size_t keylen, char *buffer, size_t buffer_size)
{
	size_t totalWrite = 0;
	size_t totalRead = 0;
    size_t sizeRead = 1;

	/* Reading crypted file and decrypt content */
	if (source==dest){

#ifndef WINCE
		FILE  *fp = 0;
		if (0 != _wfopen_s(&fp, source, L"rb+"))
			return 0;
#else
		FILE  *fp = _wfopen(source, L"rb+");
		if (!fp)
			return 0;
#endif

		while (sizeRead){
			if (0 != fseek(fp, (long)totalRead, SEEK_SET)){
				fclose(fp);
				return 0;
			}

			sizeRead = fread( buffer, sizeof(char), buffer_size, fp );
			if (sizeRead==0)
				break;
			totalRead += sizeRead;

			RC4_encrypt_string(buffer, sizeRead, key, keylen);
			
			if (0 != fseek(fp, (long)totalWrite, SEEK_SET)){
				fclose(fp);
				return 0;
			}

			totalWrite += fwrite(buffer, sizeof(char), sizeRead, fp);
		}
		fclose(fp);
	}
	else{
		FILE *fpr = 0;
		FILE *fpw = 0;

	#ifndef WINCE
		if (0 != _wfopen_s(&fpr, source, L"rb" ))
			return 0;

		if (0 != _wfopen_s(&fpw, dest, L"rb" )){
			fclose(fpr);
			return 0;
		}
	#else
		fpr = _wfopen( source, L"rb" );
		if (!fpr)
			return 0;

		fpw = _wfopen( dest, L"wb" );
		if (!fpw){
			fclose(fpr);
			return 0;
		}
	#endif
		
		while (!feof(fpr)){
			sizeRead = fread( buffer, sizeof(char), buffer_size, fpr );
			RC4_encrypt_string(buffer, sizeRead, key, keylen);
			totalRead += sizeRead;
			totalWrite += fwrite(buffer, sizeof(char), sizeRead, fpw);
		}
		fclose(fpr);
		fclose(fpw);
	}

	if (totalRead==totalWrite)
		return (int) totalWrite;
	assert(0);
	return 0;
}


// Define the function ByteToStr.
void static Bytes2String(const unsigned char* pv, int cb, char *sz)
{
	unsigned char* pb = (unsigned char*) pv; // Local pointer to a BYTE in the BYTE array
	int i;                // Local loop counter
	int b;                  // Local variable

	//  Begin processing loop.
	for (i = 0; i<cb; i++)
	{
	   b = (*pb & 0xF0) >> 4;
	   *sz++ = (b <= 9) ? b + '0' : (b - 10) + 'A';
	   b = *pb & 0x0F;
	   *sz++ = (b <= 9) ? b + '0' : (b - 10) + 'A';
	   pb++;
	}
	*sz++ = 0;
} // End of Bytes2String


int RC4_hex_encode(const unsigned char *source, size_t sourceSize, char* dest, size_t destSize)
{
	assert(destSize >= sourceSize*2+1);

	Bytes2String(source, (int)sourceSize, dest);

	return (int)(sourceSize*2);
}

int RC4_hex_decode(const char *source, size_t sourcelen, char* dest, size_t destSize)
{
	size_t  i;
	char    tmp[3];
	assert(destSize > sourcelen/2);
	*dest = 0;

	tmp[2] = 0;
	destSize = 0;

	for ( i = 0 ; i < sourcelen ; i++ ){
		if (i%2 == 0){
			tmp[0] = source[i];
			tmp[1] = source[i+1];
			dest[destSize++] = (unsigned char) strtol(tmp, 0, 16);
		}
	}

	return (int)destSize;
}
