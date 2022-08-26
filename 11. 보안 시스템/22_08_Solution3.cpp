#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
3_보안시스템_user
ver03
gcc builtin : https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
vs _BitScanForward : https://docs.microsoft.com/ko-kr/cpp/intrinsics/bitscanforward-bitscanforward64?view=msvc-170

*/
const int LM = 921;
int N = 1, A[LM];

#ifdef _WIN32
#include <intrin.h>
int __builtin_popcount(int n) {
    return __popcnt(n);
}
int __builtin_ffs(int n) {
    unsigned long idx = 0;
    _BitScanForward(&idx, n);
    return idx + 1;
}
#endif

int encoding(int x, int y) {
    for (int i = 63; i < 4096 && N < LM; ++i) {
        if (__builtin_popcount(i) == 6) A[N++] = i;
    }
    int k = __builtin_ffs((A[x] ^ A[y]) & A[x]);
    return k;
}

char answer(int p, int k) {
    return (A[p] & (1 << (k - 1))) ? 'x' : 'y';
}
