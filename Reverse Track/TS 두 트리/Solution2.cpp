/*
37_��Ʈ��_ver02
non STL : not use DLL, DFS
*/
#define rint register int
const int LM = 10005;

// countNode()���� ����ϴ� �ڷ�
int used[LM], ucnt;  // ������� �ʱ�ȭ�� ucnt�� ������Ű�� �����ϱ�
int stk[LM], top;    // �������Ͽ� �ڷ� ������ ���
int par[LM];         // stk[]��� ����� �θ���

struct Order {
    // ��ɹ�ȣ, �ð�, Ʈ����ȣ, �θ��ȣ, �����ȣ, �����ð�
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
    int ret = uid == 0;              // uid�� ��Ʈ id�� ���
    int curTick = orders[ocnt].tick; // Ž�� ���۽ð�
    ++ucnt;    // ��������� ǥ���ϴ� �ܰ� ����
    top = 0;   // ���� �ʱ�ȭ
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
        for (i = stk[k]; i > 0 && i != uid; )  // ��Ʈ �Ǵ� uid�� ã��
            i = par[i];
        if (i == uid) {   // stk[k]�� �����߿� uid�� �ִ� ���
            // uid�� �ڼյ��� �θ� uid�� : union find ����
            // stk[k]�κ��� uid�� �ִ� ��� ����� �θ� uid�� ����
            for (j = stk[k]; par[j] != uid;) {
                rint t = par[j];
                par[j] = uid;
                j = t;
            }
        }
        else {           // stk[k]�� uid�� �ڼ��� �ƴ� ���       
            for (j = stk[k]; j >= 0 && j != i;) {
                rint t = par[j];
                par[j] = -1;   // uid�� �ڼ��� �ƴϸ� parent = -1
                j = t;
            }
            if (j > 0) par[j] = -1; /// ***** *****
        }
        k--;
    }
    for (i = 1; i <= top; ++i)  // uid�� uid �ڼ��� ����
        ret += par[stk[i]] == uid;

    return ret;
}