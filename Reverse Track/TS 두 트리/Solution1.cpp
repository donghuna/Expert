/*
37_twoTree_ver01
journaling + DLL + dfs
*/
const int LM = 10001;
int N;
int tcnt;
struct Node {
    int cid;
    Node* prev, * next, * child;
    void alloc(int nid, Node* np, Node* nn, Node* nc) {
        cid = nid, child = nc, child->init();
        insert(np, nn);
    }
    void insert(Node* np, Node* nn) {
        prev = np, next = nn;
        if (prev) prev->next = this;
        if (next) next->prev = this;
    }
    void init() {
        prev = next = child = nullptr;
    }
    void erase() {
        if (prev) prev->next = next;
        if (next) next->prev = prev;
    }
    int dfs(int cnt = 1) {
        if (child == nullptr) cnt = 0;
        if (child) cnt += child->dfs();
        if (next) cnt += next->dfs();
        return cnt;
    }
}tree[LM * 2];

int ocnt;                  // orders' count
struct Order {             // orders' list
    int cmd, tick, tnum, pid, uid;
}orders[LM * 5];

void init(int n) {
    N = n, ocnt = 0;
}
void addNode(int tick, int treeNum, int pid, int uid) {
    orders[++ocnt] = { 2, tick, treeNum, pid, uid };
}
void removeNode(int tick, int treeNum, int uid) {
    orders[++ocnt] = { 3, tick, treeNum, 0, uid };
}
void moveNode(int tick, int treeNum, int pid, int uid) {
    orders[++ocnt] = { 4, tick, treeNum, pid, uid };
}
void restore(int tick, int treeNum, int prevTick) {
    orders[++ocnt] = { 5, tick, treeNum, prevTick, 0 };
}
void synchronize(int tick, int treeNum, int prevTick) {
    orders[++ocnt] = { 6, tick, treeNum, prevTick, 0 };
}

int stk[LM], scnt;
int countNode(int treeNum, int uid) {
    if (ocnt == 0) return 0;

    for (int i = 0; i <= N; ++i) tree[i].init();   // init tree
    tcnt = LM;
    tree[0].alloc(0, nullptr, nullptr, &tree[tcnt++]);
    int tgTreeNum = treeNum;
    int tgTick = orders[ocnt].tick;
    for (int i = ocnt; i > 0; --i) {
        Order& t = orders[i];
        if (t.tick > tgTick || t.tnum != tgTreeNum) continue;
        if (t.cmd == 5) tgTick = t.pid;
        else if (t.cmd == 6) tgTreeNum ^= 1, tgTick = t.pid;
        else stk[++scnt] = i;
    }
    while (scnt) {
        Order& t = orders[stk[scnt--]];
        if (t.cmd == 2) {
            Node* p = tree[t.pid].child;
            tree[t.uid].alloc(t.uid, p, p->next, &tree[tcnt++]);
        }
        else if (t.cmd == 3) {
            tree[t.uid].erase();
        }
        else if (t.cmd == 4) {               // tree update
            tree[t.uid].erase();
            Node* p = tree[t.pid].child;
            tree[t.uid].insert(p, p->next);
        }
    }
    int ret = tree[uid].child->dfs() + 1;
    return ret;
}