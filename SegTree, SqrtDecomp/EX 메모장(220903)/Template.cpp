////////// ***** main.cpp ***** //////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>

extern void append(char* str);
extern void insert(int line, char* str);
extern void erase(int line);
extern char* linestring(int line);

static inline int psuedo_rand(void)
{
    static unsigned long long seed = 55;
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x7fffffff;
}

static char* rndstr(void)
{
    static char str[1024] = { 0 };
    if (str[0] == 0) {
        for (int c = 0; c < 1023; c++) {
            str[c] = 'A' + psuedo_rand() % 26;
        }
    }
    char c = 'A' + psuedo_rand() % 26;
    str[psuedo_rand() % 1023] = c;
    str[512 + psuedo_rand() % 512] = 0;
    return str;
}

int main()
{
    static const int MAX = 100000;
    int SCORE;
    int size;

    SCORE = clock() / (CLOCKS_PER_SEC / 1000);

    for (int c = 0; c < 1000; c++) {
        append(rndstr());
    }
    size = 1000;

    while (size < MAX) {
        if (psuedo_rand() % 10 == 0) {
            append(rndstr());
            size++;
        }

        if (psuedo_rand() % 2 == 0) {
            insert(psuedo_rand() % size, linestring(psuedo_rand() % size));
            size++;
        }
        else {
            erase(psuedo_rand() % size);
            size--;
        }
    }
    SCORE = clock() / (CLOCKS_PER_SEC / 1000) - SCORE;

    if (strcmp(linestring(psuedo_rand() % MAX), \
        "YCASELNZOBUPSTVOXYKSGQRIOQDWSOBGZRQWIWMZZOFYYTDBZFYXOTKPWILNKDMQSNAYELAMAJ\
VOIOODQDIVWKYOGDPUCMULUJNUTSBGRAPZCDDQQNAXAKPAERAHIWARBXMSCJOCLIBAENAGLFISH\
SMPIJJFTCNEOWBPMYQGOECHUCWGZUNVZXUONDVRAXNURNBFAPMUGZBYGCDXVQKSYIBYGFGPAPUK\
IJZYPEQMSRVDKCAFOBSXTUQNHVNVOFLOXPPKLYFHDPNPXGVLVOCCSINCWVOOVFQZKBAUHPGBUUF\
QOAJVONLWBPDHBOHVTQIARYKPIROVWONZQVMNGIMLKPTLVSXXFXGTGMTXNNPCJFCDSBFIHEOJSW\
LHWPOGOMKJZVDTKDPHUBFBDSAZYAYGHHBBUEOPKSKFOWWQQRTJEZJFEKUZWXVGLAVYYGVRAUCQR\
QVNJWDQGSDWQERQKSQCRICBTLPKAZEKNXLCTEZHJQBJFBBJBSHOETZETHQAKNSMUB") != 0) {
        SCORE += 100000000;
    }

    printf("SCORE: %d\n", SCORE);
    if (SCORE > 500) puts("FAIL");
    else puts("PASS");
    return 0;
}



////////// ***** user.cpp ***** //////////
char* document[1000000];
int  size = 0;

int strlen(char* str, int i = 0) {
    for (; str[i]; ++i) {}
    return i;
}

void strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}


void append(char* str) {
    document[size] = new char[strlen(str) + 1];
    strcpy(document[size], str);
    size++;
}

void insert(int line, char* str) {
    for (int c = size; c > line; c--) {
        delete[] document[c];
        document[c] = new char[strlen(document[c - 1]) + 1];
        strcpy(document[c], document[c - 1]);
    }
    delete[] document[line];
    document[line] = new char[strlen(str) + 1];
    strcpy(document[line], str);
    size++;
}

void erase(int line) {
    for (int c = line; c < size - 1; c++) {
        delete[] document[c];
        document[c] = new char[strlen(document[c + 1]) + 1];
        strcpy(document[c], document[c + 1]);
    }
    size--;
}

char* linestring(int line) {
    return document[line];
}