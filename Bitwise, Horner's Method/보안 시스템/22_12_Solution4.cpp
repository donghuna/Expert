#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
11_보안시스템_user_ver04
Sperner's theorem
gcc builtin : https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
vs _BitScanForward : https://docs.microsoft.com/ko-kr/cpp/intrinsics/bitscanforward-bitscanforward64?view=msvc-170
*/
const int LM = 920;
int N, A[LM + 5];

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
        if (__builtin_popcount(i) == 6) A[++N] = i;
    }
    return __builtin_ffs((A[x] ^ A[y]) & A[x]);
}

char answer(int p, int k) {
    return ((A[p] >> (k - 1)) & 1) ? 'x' : 'y';
}