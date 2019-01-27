/**
 * byteorder.h
 * @brief
 *  Byte Converter for 2, 4, 8 bytes numeric types
 *---------------------------------------------------------------------
 *  Big Endian: XDR (big endian) encoding of numeric types
 *
 *                   Register
 *                  0x0A0B0C0D
 *      Memory         | | | |
 *       |..|          | | | |
 *  a+0: |0A|<---------+ | | |
 *  a+1: |0B|<-----------+ | |
 *  a+2: |0C|<-------------+ |
 *  a+3: |0D|<---------------+
 *       |..|
 *
 *---------------------------------------------------------------------
 *  Little Endian: NDR (little endian) encoding of numeric types
 *
 *   Register
 *  0x0A0B0C0D
 *     | | | |              Memory
 *     | | | |               |..|
 *     | | | +--------> a+0: |0D|
 *     | | +----------> a+1: |0C|
 *     | +------------> a+2: |0B|
 *     +--------------> a+3: |0A|
 *                           |..|
 *---------------------------------------------------------------------
 *
 * @author cheungmine
 * @since 2012
 * @date Jun. 19, 2013
 */
#ifndef _BYTEORDER_H_
#define _BYTEORDER_H_

#if defined(__cplusplus)
extern "C"
{
#endif

#include <memory.h>

#ifdef _MSC_VER
    #define __INLINE static __forceinline
    #define __INLINE_ALL __INLINE
#else
    #define __INLINE static inline
    #if (defined(__APPLE__) && defined(__ppc__))
        /* static inline __attribute__ here breaks osx ppc gcc42 build */
        #define __INLINE_ALL static __attribute__((always_inline))
    #else
        #define __INLINE_ALL static inline __attribute__((always_inline))
    #endif
#endif

#if defined (_SVR4) || defined (SVR4) || defined (__OpenBSD__) ||\
    defined (_sgi) || defined (__sun) || defined (sun) || \
    defined (__digital__) || defined (__HP_cc)
    #include <inttypes.h>
#elif defined (_MSC_VER) && _MSC_VER < 1600
    /* VS 2010 (_MSC_VER 1600) has stdint.h */
    typedef __int8 int8_t;
    typedef unsigned __int8 uint8_t;
    typedef __int16 int16_t;
    typedef unsigned __int16 uint16_t;
    typedef __int32 int32_t;
    typedef unsigned __int32 uint32_t;
    typedef __int64 int64_t;
    typedef unsigned __int64 uint64_t;
#elif defined (_AIX)
    #include <sys/inttypes.h>
#else
    #include <stdint.h>
#endif

#ifndef byte_t
    typedef unsigned char byte_t;
#endif

static union {
    char c[4];
    uint8_t f;
} __endianess = {{'l','0','0','b'}};

#define __little_endian (((char)__endianess.f) == 'l')
#define __big_endian (((char)__endianess.f) == 'b')

__INLINE void swap_bytes(void *value, int size)
{
    int i = 0;
    uint8_t t;
    uint8_t *b = (uint8_t*) value;

    for (; i < size/2; ++i) {
        t = b[i];
        b[i] = b[size-i-1];
        b[size-i-1] = t;
    }
}

/**
 * 2 bytes numeric converter: int16_t, uint16_t
 */
__INLINE int16_t int16_htole (int16_t val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int16_t int16_htobe (int16_t val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int16_t int16_letoh (int16_t val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int16_t int16_betoh (int16_t val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

/**
 * 4 bytes numeric converter:
 *  int32_t, uint32_t
 *  float
 */
__INLINE int32_t int32_htole (int32_t val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int32_t int32_htobe (int32_t val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int32_t int32_letoh (int32_t val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int32_t int32_betoh (int32_t val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE float float32_htole (float val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE float float32_htobe (float val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE float float32_letoh (float val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE float float32_betoh (float val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

/**
 * 8 bytes numeric converter
 */
__INLINE double float64_htole (double val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE double float64_htobe (double val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE double float64_letoh (double val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE double float64_betoh (double val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int64_t int64_htole (int64_t val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int64_t int64_htobe (int64_t val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int64_t int64_letoh (int64_t val)
{
    if (__big_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

__INLINE int64_t int64_betoh (int64_t val)
{
    if (__little_endian) {
        swap_bytes(&val, sizeof(val));
    }
    return val;
}

/**
 * read bytes to host
 */
__INLINE int16_t bytes_betoh_int16 (void *b2)
{
    int16_t val = *(int16_t*) b2;
    if (__little_endian) {
        val = int16_betoh (val);
    }
    return val;
}

__INLINE int16_t bytes_letoh_int16 (void *b2)
{
    int16_t val = *(int16_t*) b2;
    if (__big_endian) {
        val = int16_betoh (val);
    }
    return val;
}

__INLINE int32_t bytes_betoh_int32 (void *b4)
{
    int32_t val = *(int32_t*) b4;
    if (__little_endian) {
        val = int32_betoh (val);
    }
    return val;
}

__INLINE int32_t bytes_letoh_int32 (void *b4)
{
    int32_t val = *(int32_t*) b4;
    if (__big_endian) {
        val = int32_betoh (val);
    }
    return val;
}

__INLINE float bytes_betoh_float32 (void *b4)
{
    float val = *(float*) b4;
    if (__little_endian) {
        val = float32_betoh (val);
    }
    return val;
}

__INLINE float bytes_letoh_float32 (void *b4)
{
    float val = *(float*) b4;
    if (__big_endian) {
        val = float32_betoh (val);
    }
    return val;
}

__INLINE int64_t bytes_betoh_int64 (void *b8)
{
    int64_t val = *(int64_t*) b8;
    if (__little_endian) {
        val = int64_betoh (val);
    }
    return val;
}

__INLINE int64_t bytes_letoh_int64 (void *b8)
{
    int64_t val = *(int64_t*) b8;
    if (__big_endian) {
        val = int64_betoh (val);
    }
    return val;
}

__INLINE double bytes_betoh_float64 (void *b8)
{
    double val = *(double*) b8;
    if (__little_endian) {
        val = float64_betoh (val);
    }
    return val;
}

__INLINE double bytes_letoh_float64 (void *b8)
{
    double val = *(double*) b8;
    if (__big_endian) {
        val = float64_betoh (val);
    }
    return val;
}

#ifdef BYTEORDER_TEST
#include <assert.h>
#include <string.h>

static void byteorder_test_int16 (int16_t val)
{
    int16_t a, b;
    char b2[2];

    a = b = val;

    swap_bytes(&a, sizeof(a));
    swap_bytes(&a, sizeof(a));
    assert(a == b);

    b = int16_htole(a);
    b = int16_letoh(b);
    assert(a == b);

    b = int16_htobe(a);
    b = int16_betoh(b);
    assert(a == b);

    /* write as big endian to bytes */
    b = int16_htobe(a);
    memcpy(b2, &b, sizeof(b));

    /* read bytes */
    b = * (int16_t*) b2;
    b = int16_betoh(b);
    assert(a == b);

    b = bytes_betoh_int16 (b2);
    assert(a == b);
}

static void byteorder_test_int32 (int val)
{
    int a, b;
    char b4[4];

    a = b = val;

    swap_bytes(&a, sizeof(a));
    swap_bytes(&a, sizeof(a));
    assert(a == b);

    b = int32_htole(a);
    b = int32_letoh(b);
    assert(a == b);

    b = int32_htobe(a);
    b = int32_betoh(b);
    assert(a == b);

    /* read bytes */
    b = int32_htobe(a);
    memcpy(b4, &b, sizeof(b));
    b = bytes_betoh_int32 (b4);
    assert(a == b);
}

static void byteorder_test_float32 (float val)
{
    float a, b;
    char b4[4];

    a = b = val;

    swap_bytes(&a, sizeof(a));
    swap_bytes(&a, sizeof(a));
    assert(a == b);

    b = float32_htole(a);
    b = float32_letoh(b);
    assert(a == b);

    b = float32_htobe(a);
    b = float32_betoh(b);
    assert(a == b);

    b = float32_htobe(a);
    memcpy(b4, &b, sizeof(b));
    b = bytes_betoh_float32 (b4);
    assert(a == b);
}

static void byteorder_test_float64 (double val)
{
    double a, b;
    char b8[8];

    a = b = val;

    swap_bytes(&a, sizeof(a));
    swap_bytes(&a, sizeof(a));
    assert(a == b);

    b = float64_htole(a);
    b = float64_letoh(b);
    assert(a == b);

    b = float64_htobe(a);
    b = float64_betoh(b);
    assert(a == b);

    b = float64_htobe(a);
    memcpy(b8, &b, sizeof(b));
    b = bytes_betoh_float64 (b8);
    assert(a == b);
}

#endif

#if defined(__cplusplus)
}
#endif

#endif /* _BYTEORDER_H_ */
