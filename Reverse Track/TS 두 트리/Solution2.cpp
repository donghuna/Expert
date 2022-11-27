/*
37_두트리_ver02
non STL : not use DLL, DFS
*/
#define rint register int
const int LM = 10005;

// countNode()에서 사용하는 자료
int used[LM], ucnt;  // 사용유무 초기화를 ucnt를 증가시키며 결정하기
int stk[LM], top;    // 역추적하여 자료 얻을때 사용
int par[LM];         // stk[]담긴 노드의 부모노드

struct Order {
    // 명령번호, 시각, 트리번호, 부모번호, 현재번호, 이전시각
    int cmd, tick, treeNum, pid, uid, prevTick;
}orders[LM * 5];
int ocnt;

void init(int n) {
    ocnt = 0;
}
void addNode(int tick, int treeNum, int pid, int uid) {
    orders[++ocnt] = { 2, tick, treeNum, pid, uid, 0 };
}
void removeNode(int tick, int treeNum, int uid) {
    orders[++ocnt] = { 3, tick, treeNum, 0, uid, 0 };
}
void moveNode(int tick, int treeNum, int pid, int uid) {
    orders[++ocnt] = { 4, tick, treeNum, pid, uid, 0 };
}
void restore(int tick, int treeNum, int prevTick) {
    orders[++ocnt] = { 5, tick, treeNum, 0, 0, prevTick };
}
void synchronize(int tick, int treeNum, int prevTick) {
    orders[++ocnt] = { 6, tick, treeNum, 0, 0, prevTick };
}

int countNode(int treeNum, int uid) {
    int ret = uid == 0;              // uid가 루트 id인 경우
    int curTick = orders[ocnt].tick; // 탐색 시작시각
    ++ucnt;    // 사용했음을 표시하는 단계 증가
    top = 0;   // 스택 초기화
    rint i, j, k;
    for (i = ocnt; i > 0; --i) {
        Order& t = orders[i];
        if (t.tick > curTick || treeNum != t.treeNum) continue;
        if (t.cmd == 5)       // restore
            curTick = t.prevTick;
        else if (t.cmd == 6)  // synchronize
            treeNum ^= 1, curTick = t.prevTick;
        else {
            if (t.cmd == 3) { // remove
                if (used[t.uid] < ucnt) {
                    used[t.uid] = ucnt;
                    par[t.uid] = -1;
                }
            }
            else {            // add, move
                if (used[t.uid] < ucnt) {
                    used[t.uid] = ucnt;
                    par[t.uid] = t.pid;
                    stk[++top] = t.uid;
                }
            }
        }
    }

    k = top;
    par[uid] = uid;
    while (k) {
        for (i = stk[k]; i > 0 && i != uid; )  // 루트 또는 uid를 찾기
            i = par[i];
        if (i == uid) {   // stk[k]의 조상중에 uid가 있는 경우
            // uid의 자손들의 부모를 uid로 : union find 응용
            // stk[k]로부터 uid에 있는 모든 노드의 부모를 uid로 설정
            for (j = stk[k]; par[j] != uid;) {
                rint t = par[j];
                par[j] = uid;
                j = t;
            }
        }
        else {           // stk[k]가 uid의 자손이 아닌 경우       
            for (j = stk[k]; j >= 0 && j != i;) {
                rint t = par[j];
                par[j] = -1;   // uid의 자손이 아니면 parent = -1
                j = t;
            }
            if (j > 0) par[j] = -1; /// ***** *****
        }
        k--;
    }
    for (i = 1; i <= top; ++i)  // uid와 uid 자손의 개수
        ret += par[stk[i]] == uid;

    return ret;
}