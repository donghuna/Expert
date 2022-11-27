/// *** user.cpp ***
void init(int n) {

}
void addNode(int tick, int treeNum, int pid, int uid) {

}
void removeNode(int tick, int treeNum, int uid) {

}
void moveNode(int tick, int treeNum, int pid, int uid) {

}
void restore(int tick, int treeNum, int prevTick) {

}
void synchronize(int tick, int treeNum, int prevTick) {

}
int countNode(int treeNum, int uid) {
    return 0;
}

/// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int n);
extern void addNode(int tick, int treeNum, int pid, int uid);
extern void removeNode(int tick, int treeNum, int uid);
extern void moveNode(int tick, int treeNum, int pid, int uid);
extern void restore(int tick, int treeNum, int prevTick);
extern void synchronize(int tick, int treeNum, int prevTick);
extern int countNode(int treeNum, int uid);

#define INIT     100
#define ADD      200
#define REMOVE   300
#define MOVE     400
#define RESTORE  500
#define SYNC     600
#define COUNT    700

static bool run()
{
    int Q;
    scanf("%d", &Q);

    int n = 0;
    bool correct = false;
    int curTick, treeNum, pid, uid, prevTick, ans;

    for (int i = 0; i < Q; i++)
    {
        int cmd;
        scanf("%d", &cmd);
        //printf("%d\n", cmd);
        if (cmd == INIT) {
            scanf("%d", &n);
            init(n);
            correct = true;
        }
        else if (cmd == ADD) {
            scanf("%d%d%d%d", &curTick, &treeNum, &pid, &uid);
            addNode(curTick, treeNum, pid, uid);
        }
        else if (cmd == REMOVE) {
            scanf("%d%d%d", &curTick, &treeNum, &uid);
            removeNode(curTick, treeNum, uid);
        }
        else if (cmd == MOVE) {
            scanf("%d%d%d%d", &curTick, &treeNum, &pid, &uid);
            moveNode(curTick, treeNum, pid, uid);
        }
        else if (cmd == RESTORE) {
            scanf("%d%d%d", &curTick, &treeNum, &prevTick);
            restore(curTick, treeNum, prevTick);
        }
        else if (cmd == SYNC) {
            scanf("%d%d%d", &curTick, &treeNum, &prevTick);
            synchronize(curTick, treeNum, prevTick);
        }
        else if (cmd == COUNT) {
            scanf("%d%d", &treeNum, &uid);
            int ret = 0;
            ret = countNode(treeNum, uid);
            scanf("%d", &ans);
            if (ans != ret)
                correct = false;
        }
    }
    return correct;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    int T, success;
    scanf("%d%d", &T, &success);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? success : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
