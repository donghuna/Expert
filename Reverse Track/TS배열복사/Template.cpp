// *** user.cpp ***
void init() {

}
void makeArray(char name[], int len, int arr[]) {

}
void copyArray(char to[], char from[], bool flag) {

}
void updateData(char name[], int index, int newData) {

}
int getData(char name[], int index) {

}

// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT 100
#define MAKE_ARRAY 200
#define CMD_COPY_LIST 300
#define UPDATE_DATA 400
#define GET_DATA 500

extern void init();
extern void makeArray(char name[], int len, int arr[]);
extern void copyArray(char to[], char from[], bool flag);
extern void updateData(char name[], int index, int newData);
extern int getData(char name[], int index);

/////////////////////////////////////////////////////////////////////////

static unsigned int Jseed;
static unsigned int pseudo_rand(void)
{
    Jseed = Jseed * 214013 + 2531011;
    return (Jseed >> 16) & 0x7FFF;
}

static char name[21];
static char to[21];
static char from[21];
static int arr[200000];

static void generateName(char* name, int seed)
{
    Jseed = seed;
    int name_len = pseudo_rand() % 20 + 1;
    for (int i = 0; i < name_len; ++i)
    {
        name[i] = pseudo_rand() % 26 + 'a';
    }
    name[name_len] = '\0';
}

static int generateList(int* listValue, int seed) {
    Jseed = seed;
    int length = pseudo_rand() << 15;
    length = (length + pseudo_rand()) % 200000 + 1;
    for (int i = 0; i < length; ++i) {
        listValue[i] = pseudo_rand();
    }
    return length;
}

static bool run() {
    int numQuery;

    int seed;
    int index, newData, flag, len;
    int userAns, ans;
    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i) {
        int cmd;
        scanf("%d", &cmd);

        switch (cmd)
        {
        case INIT:
            init();
            isCorrect = true;
            break;
        case MAKE_ARRAY:
            scanf("%d", &seed);
            generateName(name, seed);
            scanf("%d", &seed);
            len = generateList(arr, seed);
            makeArray(name, len, arr);
            break;
        case CMD_COPY_LIST:
            scanf("%d", &seed);
            generateName(to, seed);
            scanf("%d", &seed);
            generateName(from, seed);
            scanf("%d", &flag);
            copyArray(to, from, (flag != 0));
            break;
        case UPDATE_DATA:
            scanf("%d", &seed);
            generateName(name, seed);
            scanf("%d %d", &index, &newData);
            updateData(name, index, newData);
            break;
        case GET_DATA:
            scanf("%d", &seed);
            generateName(name, seed);
            scanf("%d", &index);
            userAns = getData(name, index);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }
    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
