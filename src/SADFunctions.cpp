
#include "SADFunctions.h"


#ifdef _WIN32
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif


static inline unsigned int SADABS(int x) {
    return (x < 0) ? -x : x;
}


#define DEFINE_SAD(width, height, bits) \
unsigned int mvtools_sad_##width##x##height##_u##bits##_c(const uint8_t *pSrc8, intptr_t nSrcPitch, const uint8_t *pRef8, intptr_t nRefPitch) { \
    unsigned int sum = 0;                                                       \
    for (int y = 0; y < height; y++) {                                          \
        for (int x = 0; x < width; x++) {                                       \
            const uint##bits##_t *pSrc = (const uint##bits##_t *)pSrc8;         \
            const uint##bits##_t *pRef = (const uint##bits##_t *)pRef8;         \
            sum += SADABS(pSrc[x] - pRef[x]);                                   \
        }                                                                       \
        pSrc8 += nSrcPitch;                                                     \
        pRef8 += nRefPitch;                                                     \
    }                                                                           \
    return sum;                                                                 \
}

DEFINE_SAD(2, 2, 8)
DEFINE_SAD(2, 4, 8)
DEFINE_SAD(4, 2, 8)
DEFINE_SAD(4, 4, 8)
DEFINE_SAD(4, 8, 8)
DEFINE_SAD(8, 1, 8)
DEFINE_SAD(8, 2, 8)
DEFINE_SAD(8, 4, 8)
DEFINE_SAD(8, 8, 8)
DEFINE_SAD(8, 16, 8)
DEFINE_SAD(16, 1, 8)
DEFINE_SAD(16, 2, 8)
DEFINE_SAD(16, 4, 8)
DEFINE_SAD(16, 8, 8)
DEFINE_SAD(16, 16, 8)
DEFINE_SAD(16, 32, 8)
DEFINE_SAD(32, 8, 8)
DEFINE_SAD(32, 16, 8)
DEFINE_SAD(32, 32, 8)

DEFINE_SAD(2, 2, 16)
DEFINE_SAD(2, 4, 16)
DEFINE_SAD(4, 2, 16)
DEFINE_SAD(4, 4, 16)
DEFINE_SAD(4, 8, 16)
DEFINE_SAD(8, 1, 16)
DEFINE_SAD(8, 2, 16)
DEFINE_SAD(8, 4, 16)
DEFINE_SAD(8, 8, 16)
DEFINE_SAD(8, 16, 16)
DEFINE_SAD(16, 1, 16)
DEFINE_SAD(16, 2, 16)
DEFINE_SAD(16, 4, 16)
DEFINE_SAD(16, 8, 16)
DEFINE_SAD(16, 16, 16)
DEFINE_SAD(16, 32, 16)
DEFINE_SAD(32, 8, 16)
DEFINE_SAD(32, 16, 16)
DEFINE_SAD(32, 32, 16)


#define HADAMARD4(d0, d1, d2, d3, s0, s1, s2, s3) \
    {                                             \
        SumType2 t0 = s0 + s1;                    \
        SumType2 t1 = s0 - s1;                    \
        SumType2 t2 = s2 + s3;                    \
        SumType2 t3 = s2 - s3;                    \
        d0 = t0 + t2;                             \
        d2 = t0 - t2;                             \
        d1 = t1 + t3;                             \
        d3 = t1 - t3;                             \
    }

#define HADAMARD8(d0, d1, d2, d3, d4, d5, d6, d7, s0, s1, s2, s3, s4, s5, s6, s7) \
    {                                                                             \
        SumType2 t0 = s0 + s1;                                                    \
        SumType2 t1 = s0 - s1;                                                    \
        SumType2 t2 = s2 + s3;                                                    \
        SumType2 t3 = s2 - s3;                                                    \
        SumType2 t4 = s4 + s5;                                                    \
        SumType2 t5 = s4 - s5;                                                    \
        SumType2 t6 = s6 + s7;                                                    \
        SumType2 t7 = s6 - s7;                                                    \
        d0 = t0 + t4;                                                             \
        d2 = t0 - t4;                                                             \
        d1 = t1 + t5;                                                             \
        d3 = t1 - t5;                                                             \
        d4 = t2 + t6;                                                             \
        d5 = t2 - t6;                                                             \
        d6 = t3 + t7;                                                             \
        d7 = t3 - t7;                                                             \
    }

#define HADAMARD16(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15) \
    {                                                                                                                                                          \
        SumType2 t0 = s0 + s1;                                                                                                                                 \
        SumType2 t1 = s0 - s1;                                                                                                                                 \
        SumType2 t2 = s2 + s3;                                                                                                                                 \
        SumType2 t3 = s2 - s3;                                                                                                                                 \
        SumType2 t4 = s4 + s5;                                                                                                                                 \
        SumType2 t5 = s4 - s5;                                                                                                                                 \
        SumType2 t6 = s6 + s7;                                                                                                                                 \
        SumType2 t7 = s6 - s7;                                                                                                                                 \
        SumType2 t8 = s8 + s9;                                                                                                                                 \
        SumType2 t9 = s8 - s9;                                                                                                                                 \
        SumType2 t10 = s10 + s11;                                                                                                                              \
        SumType2 t11 = s10 - s11;                                                                                                                              \
        SumType2 t12 = s12 + s13;                                                                                                                              \
        SumType2 t13 = s12 - s13;                                                                                                                              \
        SumType2 t14 = s14 + s15;                                                                                                                              \
        SumType2 t15 = s14 - s15;                                                                                                                              \
        d0 = t0 + t8;                                                                                                                                          \
        d2 = t0 - t8;                                                                                                                                          \
        d1 = t1 + t9;                                                                                                                                          \
        d3 = t1 - t9;                                                                                                                                          \
        d4 = t2 + t10;                                                                                                                                         \
        d5 = t2 - t10;                                                                                                                                         \
        d6 = t3 + t11;                                                                                                                                         \
        d7 = t3 - t11;                                                                                                                                         \
        d8 = t4 + t12;                                                                                                                                         \
        d9 = t4 - t12;                                                                                                                                         \
        d10 = t5 + t13;                                                                                                                                        \
        d11 = t5 - t13;                                                                                                                                        \
        d12 = t6 + t14;                                                                                                                                        \
        d13 = t6 - t14;                                                                                                                                        \
        d14 = t7 + t15;                                                                                                                                        \
        d15 = t7 - t15;                                                                                                                                        \
    }


// in: a pseudo-simd number of the form x+(y<<16)
// return: abs(x)+(abs(y)<<16)
template <typename SumType, typename SumType2>
static FORCE_INLINE SumType2 abs2(SumType2 a) {
    int bitsPerSum = 8 * sizeof(SumType);

    SumType2 s = ((a >> (bitsPerSum - 1)) & (((SumType2)1 << bitsPerSum) + 1)) * ((SumType)-1);
    return (a + s) ^ s;
}


template <typename PixelType, typename SumType, typename SumType2>
static FORCE_INLINE unsigned int Real_Satd_4x4_C(const uint8_t *pSrc8, intptr_t nSrcPitch, const uint8_t *pRef8, intptr_t nRefPitch) {
    int bitsPerSum = 8 * sizeof(SumType);

    SumType2 tmp[4][2];
    SumType2 a0, a1, a2, a3, b0, b1;
    SumType2 sum = 0;

    for (int i = 0; i < 4; i++) {
        const PixelType *pSrc = (const PixelType *)pSrc8;
        const PixelType *pRef = (const PixelType *)pRef8;

        a0 = pSrc[0] - pRef[0];
        a1 = pSrc[1] - pRef[1];
        b0 = (a0 + a1) + ((a0 - a1) << bitsPerSum);
        a2 = pSrc[2] - pRef[2];
        a3 = pSrc[3] - pRef[3];
        b1 = (a2 + a3) + ((a2 - a3) << bitsPerSum);
        tmp[i][0] = b0 + b1;
        tmp[i][1] = b0 - b1;

        pSrc8 += nSrcPitch;
        pRef8 += nRefPitch;
    }

    for (int i = 0; i < 2; i++) {
        HADAMARD4(a0, a1, a2, a3, tmp[0][i], tmp[1][i], tmp[2][i], tmp[3][i]);
        a0 = abs2<SumType, SumType2>(a0) + abs2<SumType, SumType2>(a1) + abs2<SumType, SumType2>(a2) + abs2<SumType, SumType2>(a3);
        sum += ((SumType)a0) + (a0 >> bitsPerSum);
    }

    return (unsigned int)(sum >> 1);
}


template <typename PixelType>
static FORCE_INLINE unsigned int Satd_4x4_C(const uint8_t *pSrc, intptr_t nSrcPitch, const uint8_t *pRef, intptr_t nRefPitch) {
    if (sizeof(PixelType) == 1)
        return Real_Satd_4x4_C<PixelType, uint16_t, uint32_t>(pSrc, nSrcPitch, pRef, nRefPitch);
    else
        return Real_Satd_4x4_C<PixelType, uint32_t, uint64_t>(pSrc, nSrcPitch, pRef, nRefPitch);
}


template <typename PixelType, typename SumType, typename SumType2>
static FORCE_INLINE unsigned int Real_Satd_8x4_C(const uint8_t *pSrc8, intptr_t nSrcPitch, const uint8_t *pRef8, intptr_t nRefPitch) {
    int bitsPerSum = 8 * sizeof(SumType);

    SumType2 tmp[4][4];
    SumType2 a0, a1, a2, a3;
    SumType2 sum = 0;

    for (int i = 0; i < 4; i++) {
        const PixelType *pSrc = (const PixelType *)pSrc8;
        const PixelType *pRef = (const PixelType *)pRef8;

        a0 = (pSrc[0] - pRef[0]) + ((SumType2)(pSrc[4] - pRef[4]) << bitsPerSum);
        a1 = (pSrc[1] - pRef[1]) + ((SumType2)(pSrc[5] - pRef[5]) << bitsPerSum);
        a2 = (pSrc[2] - pRef[2]) + ((SumType2)(pSrc[6] - pRef[6]) << bitsPerSum);
        a3 = (pSrc[3] - pRef[3]) + ((SumType2)(pSrc[7] - pRef[7]) << bitsPerSum);
        HADAMARD4(tmp[i][0], tmp[i][1], tmp[i][2], tmp[i][3], a0, a1, a2, a3);

        pSrc8 += nSrcPitch;
        pRef8 += nRefPitch;
    }
    for (int i = 0; i < 4; i++) {
        HADAMARD4(a0, a1, a2, a3, tmp[0][i], tmp[1][i], tmp[2][i], tmp[3][i]);
        sum += abs2<SumType, SumType2>(a0) + abs2<SumType, SumType2>(a1) + abs2<SumType, SumType2>(a2) + abs2<SumType, SumType2>(a3);
    }

    return (unsigned int)((((SumType)sum) + (sum >> bitsPerSum)) >> 1);
}

template <typename PixelType>
static FORCE_INLINE unsigned int Satd_8x4_C(const uint8_t *pSrc, intptr_t nSrcPitch, const uint8_t *pRef, intptr_t nRefPitch) {
    if (sizeof(PixelType) == 1)
        return Real_Satd_8x4_C<PixelType, uint16_t, uint32_t>(pSrc, nSrcPitch, pRef, nRefPitch);
    else
        return Real_Satd_8x4_C<PixelType, uint32_t, uint64_t>(pSrc, nSrcPitch, pRef, nRefPitch);
}

template <typename PixelType, typename SumType, typename SumType2>
static FORCE_INLINE unsigned int Real_Satd_8x8_C(const uint8_t *pSrc8, intptr_t nSrcPitch, const uint8_t *pRef8, intptr_t nRefPitch) {
    int bitsPerSum = 8 * sizeof(SumType);

    SumType2 tmp[8][4];
    SumType2 a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3;
    SumType2 sum = 0;

    for (int i = 0; i < 8; i++) {
        const PixelType *pSrc = (const PixelType *)pSrc8;
        const PixelType *pRef = (const PixelType *)pRef8;

        a0 = pSrc[0] - pRef[0];
        a1 = pSrc[1] - pRef[1];
        b0 = (a0 + a1) + ((a0 - a1) << bitsPerSum);
        a2 = pSrc[2] - pRef[2];
        a3 = pSrc[3] - pRef[3];
        b1 = (a2 + a3) + ((a2 - a3) << bitsPerSum);
        a4 = pSrc[4] - pRef[4];
        a5 = pSrc[5] - pRef[5];
        b2 = (a4 + a5) + ((a4 - a5) << bitsPerSum);
        a6 = pSrc[6] - pRef[6];
        a7 = pSrc[7] - pRef[7];
        b3 = (a6 + a7) + ((a6 - a7) << bitsPerSum);
        tmp[i][0] = b0 + b2;
        tmp[i][1] = b0 - b2;
        tmp[i][2] = b1 + b3;
        tmp[i][3] = b1 - b3;

        pSrc8 += nSrcPitch;
        pRef8 += nRefPitch;
    }

    for (int i = 0; i < 4; i++) {
        HADAMARD8(a0, a1, a2, a3, a4, a5, a6, a7, tmp[0][i], tmp[1][i], tmp[2][i], tmp[3][i], tmp[4][i], tmp[5][i], tmp[6][i], tmp[7][i]);
        a0 = abs2<SumType, SumType2>(a0) + abs2<SumType, SumType2>(a1) + abs2<SumType, SumType2>(a2) + abs2<SumType, SumType2>(a3) + abs2<SumType, SumType2>(a4) + abs2<SumType, SumType2>(a5) + abs2<SumType, SumType2>(a6) + abs2<SumType, SumType2>(a7);
        sum += ((SumType)a0) + (a0 >> bitsPerSum);
    }

    return (unsigned int)(sum >> 1);
}

template <typename PixelType>
static FORCE_INLINE unsigned int Satd_8x8_C(const uint8_t *pSrc, intptr_t nSrcPitch, const uint8_t *pRef, intptr_t nRefPitch) {
    if (sizeof(PixelType) == 1)
        return Real_Satd_8x8_C<PixelType, uint16_t, uint32_t>(pSrc, nSrcPitch, pRef, nRefPitch);
    else
        return Real_Satd_8x8_C<PixelType, uint32_t, uint64_t>(pSrc, nSrcPitch, pRef, nRefPitch);
}

template <typename PixelType, typename SumType, typename SumType2>
static FORCE_INLINE unsigned int Real_Satd_16x16_C(const uint8_t *pSrc8, intptr_t nSrcPitch, const uint8_t *pRef8, intptr_t nRefPitch) {
    int bitsPerSum = 8 * sizeof(SumType);

    SumType2 tmp[16][8];
    SumType2 a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, b0, b1, b2, b3, b4, b5, b6, b7;
    SumType2 sum = 0;

    for (int i = 0; i < 16; i++) {
        const PixelType *pSrc = (const PixelType *)pSrc8;
        const PixelType *pRef = (const PixelType *)pRef8;

        a0 = pSrc[0] - pRef[0];
        a1 = pSrc[1] - pRef[1];
        b0 = (a0 + a1) + ((a0 - a1) << bitsPerSum);
        a2 = pSrc[2] - pRef[2];
        a3 = pSrc[3] - pRef[3];
        b1 = (a2 + a3) + ((a2 - a3) << bitsPerSum);
        a4 = pSrc[4] - pRef[4];
        a5 = pSrc[5] - pRef[5];
        b2 = (a4 + a5) + ((a4 - a5) << bitsPerSum);
        a6 = pSrc[6] - pRef[6];
        a7 = pSrc[7] - pRef[7];
        b3 = (a6 + a7) + ((a6 - a7) << bitsPerSum);
        a8 = pSrc[8] - pRef[8];
        a9 = pSrc[9] - pRef[9];
        b4 = (a8 + a9) + ((a8 - a9) << bitsPerSum);
        a10 = pSrc[10] - pRef[10];
        a11 = pSrc[11] - pRef[11];
        b5 = (a10 + a11) + ((a10 - a11) << bitsPerSum);
        a12 = pSrc[12] - pRef[12];
        a13 = pSrc[13] - pRef[13];
        b6 = (a12 + a13) + ((a12 - a13) << bitsPerSum);
        a14 = pSrc[14] - pRef[14];
        a15 = pSrc[15] - pRef[15];
        b7 = (a14 + a15) + ((a14 - a15) << bitsPerSum);
        tmp[i][0] = b0 + b4;
        tmp[i][1] = b0 - b4;
        tmp[i][2] = b1 + b5;
        tmp[i][3] = b1 - b5;
        tmp[i][4] = b2 + b6;
        tmp[i][5] = b2 - b6;
        tmp[i][6] = b3 + b7;
        tmp[i][7] = b3 - b7;

        pSrc8 += nSrcPitch;
        pRef8 += nRefPitch;
    }

    for (int i = 0; i < 8; i++) {
        HADAMARD16(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, tmp[0][i], tmp[1][i], tmp[2][i], tmp[3][i], tmp[4][i], tmp[5][i], tmp[6][i], tmp[7][i], tmp[8][i], tmp[9][i], tmp[10][i], tmp[11][i], tmp[12][i], tmp[13][i], tmp[14][i], tmp[15][i]);
        a0 = abs2<SumType, SumType2>(a0) + abs2<SumType, SumType2>(a1) + abs2<SumType, SumType2>(a2) + abs2<SumType, SumType2>(a3) + abs2<SumType, SumType2>(a4) + abs2<SumType, SumType2>(a5) + abs2<SumType, SumType2>(a6) + abs2<SumType, SumType2>(a7) + abs2<SumType, SumType2>(a8) + abs2<SumType, SumType2>(a9) + abs2<SumType, SumType2>(a10) + abs2<SumType, SumType2>(a11) + abs2<SumType, SumType2>(a12) + abs2<SumType, SumType2>(a13) + abs2<SumType, SumType2>(a14) + abs2<SumType, SumType2>(a15);
        sum += ((SumType)a0) + (a0 >> bitsPerSum);
    }

    return (unsigned int)(sum >> 1);
}

template <typename PixelType>
static FORCE_INLINE unsigned int Satd_16x16_C(const uint8_t *pSrc, intptr_t nSrcPitch, const uint8_t *pRef, intptr_t nRefPitch) {
    if (sizeof(PixelType) == 1)
        return Real_Satd_16x16_C<PixelType, uint16_t, uint32_t>(pSrc, nSrcPitch, pRef, nRefPitch);
    else
        return Real_Satd_16x16_C<PixelType, uint32_t, uint64_t>(pSrc, nSrcPitch, pRef, nRefPitch);
}

// Only handles 4x4, 8x4, 8x8, 8x16, 16x8, and 16x16.
template <int nBlkWidth, int nBlkHeight, typename PixelType>
static FORCE_INLINE unsigned int Satd_C(const uint8_t *pSrc, intptr_t nSrcPitch, const uint8_t *pRef, intptr_t nRefPitch) {
    if (nBlkWidth == 4 && nBlkHeight == 4)
        return Satd_4x4_C<PixelType>(pSrc, nSrcPitch, pRef, nRefPitch);
    else if (nBlkWidth == 8 && nBlkHeight == 4)
        return Satd_8x4_C<PixelType>(pSrc, nSrcPitch, pRef, nRefPitch);
    else if (nBlkWidth == 8 && nBlkHeight == 8)
        return Satd_8x8_C<PixelType>(pSrc, nSrcPitch, pRef, nRefPitch);
    else if (nBlkWidth == 16 && nBlkHeight == 16)
        return Satd_16x16_C<PixelType>(pSrc, nSrcPitch, pRef, nRefPitch);
    else {
        int bytesPerSample = sizeof(PixelType);

        unsigned int sum = Satd_8x4_C<PixelType>(pSrc, nSrcPitch, pRef, nRefPitch) + Satd_8x4_C<PixelType>(pSrc + 4 * nSrcPitch, nSrcPitch, pRef + 4 * nRefPitch, nRefPitch);

        if (nBlkWidth == 16)
            sum += Satd_8x4_C<PixelType>(pSrc + 8 * bytesPerSample, nSrcPitch, pRef + 8 * bytesPerSample, nRefPitch) + Satd_8x4_C<PixelType>(pSrc + 8 * bytesPerSample + 4 * nSrcPitch, nSrcPitch, pRef + 8 * bytesPerSample + 4 * nSrcPitch, nRefPitch);

        if (nBlkHeight == 16)
            sum += Satd_8x4_C<PixelType>(pSrc + 8 * nSrcPitch, nSrcPitch, pRef + 8 * nRefPitch, nRefPitch) + Satd_8x4_C<PixelType>(pSrc + 12 * nSrcPitch, nSrcPitch, pRef + 12 * nRefPitch, nRefPitch);

        return sum;
    }
}

#define DEFINE_SATD(width, height, bits) \
unsigned int mvtools_satd_##width##x##height##_u##bits##_c(const uint8_t *pSrc8, intptr_t nSrcPitch, const uint8_t *pRef8, intptr_t nRefPitch) { \
    return Satd_C<width, height, uint##bits##_t>(pSrc8, nSrcPitch, pRef8, nRefPitch); \
}

DEFINE_SATD(4, 4, 8)
DEFINE_SATD(8, 4, 8)
DEFINE_SATD(8, 8, 8)
DEFINE_SATD(16, 8, 8)
DEFINE_SATD(16, 16, 8)

DEFINE_SATD(4, 4, 16)
DEFINE_SATD(8, 4, 16)
DEFINE_SATD(8, 8, 16)
DEFINE_SATD(16, 8, 16)
DEFINE_SATD(16, 16, 16)
