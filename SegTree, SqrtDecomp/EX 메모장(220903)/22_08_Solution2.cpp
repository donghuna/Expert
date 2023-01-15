#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
j5296_EX¸Þ¸ðÀå_user version 02
comkiwer's test
Sqrt Decomposition
*/
#define rint register int

const int LM = 1 << 17;     // 131072
const int HLM = 1 << 21;    // 2097152

int curLine;
int bn, srrLen, len;
char srr[LM][1024];         // 128MB
struct Sect {
    int arr[1000], an;
    void push(int sidx) {
        arr[an++] = sidx;
    }
    void insert(int aidx) {
        for (rint i = an; i > aidx; --i) arr[i] = arr[i - 1];
        arr[aidx] = curLine;
        an++;
    }
    void del(int aidx) {
        for (rint i = aidx; i < an; ++i) arr[i] = arr[i + 1];
        an--;
    }
    char* getLine(int aidx) {
        return srr[curLine = arr[aidx]];
    }
}B[1024];

void strcpy(char* dest, char* src) {
    for (rint i = 0; dest[i] = src[i]; ++i) {}
}

void append(char* str) {
    strcpy(srr[srrLen], str);
    if (B[bn].an < 256) B[bn].push(srrLen++);
    else B[++bn].push(srrLen++);
    len++;
}

void insert(int line, char* str) {
    rint i = 0;
    for (; i <= bn && B[i].an <= line; ++i) line -= B[i].an;
    B[i].insert(line);
    if (i > bn)
        bn++;
    len++;
}

void erase(int line) {
    rint i = 0;
    for (; B[i].an <= line; ++i) line -= B[i].an;
    B[i].del(line);
    len--;
}

char* linestring(int line) {
    rint i = 0;
    for (; B[i].an <= line; ++i) line -= B[i].an;
    return B[i].getLine(line);
}