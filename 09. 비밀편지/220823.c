#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define rint register int

int code[8] = {0b000000, 0b001111, 0b010011, 0b011100, 0b100110, 0b101001, 0b110101, 0b111010 };
int N;
int d, a, idx;
char ans[15];

int check(int d)
{
  for (rint i=0; i < 8; ++i)
  {
    /*
    XOR = code[i] ^ d;
    if ((XOR & (XOR - 1)) == 0) return i;
    */
    if (((code[i] ^ d) & ((code[i] ^ d) - 1)) == 0) return i;   // speed good
  }
  return -1;
}

int main() {
  scanf("%d", &N);
  
  rint i, j;
  for (i = 0; i < N; ++i)
  {
    d = 0;
    for (j = 0; j < 6; ++j) {
      scanf("%1d", &a);
      d = d * 2 + a;    // ^2.. so multiple 2.
    }
    
    idx = check(d); // 0~7
    if (idx == -1) {  // not matched
      printf("%d", i+1);
      return 0;
    }
    ans[i] = idx + 'A'; // make char
    // at first time, I saved ans as integer and trans it to char at last time. it is not gooot at performance.
  }
  printf("%s", ans);
  
  return 0;
}
    
