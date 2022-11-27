/*
35_TS�ְ�����_user
non stl
*/
#define MAX_STOCK_LEN 10
#define rint register int
using LL = long long;
const int LM = 100005;
const int MOD = 1 << 14;  // chaining hash slot size
const int MASK = MOD - 1;

int N;
int SQR;
int groupDelta[LM];
int groupMax[LM];

struct Data {
    int id, price, delta;
    LL key;                // �̸��� long long�� ������ ��ȯ�� ��.
    bool operator<(const Data& t) const {
        return key < t.key;
    }
    bool operator>(const Data& t) const {  // ���� �׷쳻���� �켱���� ��
        if (delta != t.delta) return delta > t.delta;
        return id < t.id;
    }
}stock[LM], T[LM];

struct Node {              // chaining hash
    int id;
    Node* next;
    Node* alloc(int nid, Node* nn) {
        id = nid, next = nn;
        return this;
    }
}buf[LM * 2], * htab[MOD];  // buf[]: memory pool, *htab[]: chaining hash slot
int bcnt;

LL getKey(char* s) {        // ���ڿ��� long long �� ������ ��ȯ�ϱ�
    rint i = 0;
    LL key = 0;
    for (; s[i]; ++i) key = key * 27 + s[i] - 96;
    for (; i < 10; ++i) key = key * 27;  // ���������� ���̹Ƿ� ��� 10�ڸ��� �����.
    return key;
}

int probing(LL key) {       // ���� �̸��� �ֽ� ã��
    Node* p = htab[key & MASK];
    for (; p; p = p->next)
        if (stock[p->id].key == key)
            return p->id;
    return 0;
}

inline int min(int a, int b) { return a < b ? a : b; }
void mergeSort(Data* A, int s, int e) {  // �ֽ��� �̸��� ������������ ����
    if (s + 1 >= e) return;
    int m = (s + e) / 2, i = s, j = m, k = s;
    mergeSort(A, s, m), mergeSort(A, m, e);
    while (i < m && j < e) {
        if (A[j] < A[i]) T[k++] = A[j++];
        else T[k++] = A[i++];
    }
    while (i < m) T[k++] = A[i++];
    while (j < e) T[k++] = A[j++];
    for (i = s; i < e; ++i) A[i] = T[i];
}

void init(int N, char mStocks[][MAX_STOCK_LEN + 1], int mPrices[]) {
    ::N = N, SQR = 1;
    while ((SQR + 1) * (SQR + 1) <= N) SQR++;  // ������ ���ϱ�
    // �ֽ� ���� id(i) ������ �����ϱ�
    for (rint i = 0; i < N; ++i) {
        stock[i] = { i, mPrices[i], 0, getKey(mStocks[i]) };
    }
    // �̸������� �����ϱ�
    mergeSort(stock, 0, N);

    // �ؽ� ���̺� �ʱ�ȭ
    bcnt = 0;
    for (rint i = 0; i < MOD; ++i) htab[i] = nullptr;
    for (rint i = 0; i < N; ++i) {  // �̸��� �ؽ� ���̺� �����ϱ�
        int hidx = stock[i].key & MASK;
        htab[hidx] = buf[bcnt++].alloc(i, htab[hidx]);
    }

    // �� �׷캰 �ʱⰪ ����
    for (rint i = 0; i < N; i += SQR) {
        int gn = i / SQR, ridx = i;
        int ed = min(N, i + SQR);
        for (int j = i; j < ed; ++j) {
            if (stock[j].id < stock[ridx].id)
                ridx = j;
        }
        groupDelta[gn] = 0;
        groupMax[gn] = ridx;
    }
}

void update(int s, int e) { // �׷쳻���� �ִ밪 ����
    int& gmx = groupMax[s / SQR];
    for (; s < e; ++s) if (stock[s] > stock[gmx])
        gmx = s;
}

void change(char mFromStock[], char mToStock[], int mPriceDiff) {
    rint st = probing(getKey(mFromStock)), ed = probing(getKey(mToStock));
    rint s = st, e = ed;
    for (; s % SQR && s <= ed; ++s)         // ���� ������ ���� ������Ʈ
        stock[s].delta += mPriceDiff;

    update(st / SQR * SQR, s); //���� �������� ���Ե� ��ü ������ �ֽ� ��� �ִ밪 ������Ʈ

    for (; ((e + 1) % SQR) && s <= e; --e) // �׷���� ���� ������Ʈ, �ִ밪�� ��ȭ�� ����.
        stock[e].delta += mPriceDiff;

    for (; s <= e; s += SQR)
        groupDelta[s / SQR] += mPriceDiff; // ���� ������ ���� ������Ʈ

    // ���� �������� ���Ե� ��ü ������ �ֽ� ��� �ִ밪 ������Ʈ
    update(s, min(ed / SQR * SQR + SQR, N));
}

int getPrice(char mStock[]) {             // mStock[]�ֽ� ���� ���� ���ϱ�
    int ridx = probing(getKey(mStock));
    // �ʱⰡ�� + ���� ���� ���� + �׷� ���� ����
    return stock[ridx].price + stock[ridx].delta + groupDelta[ridx / SQR];
}

int comp(int a, int b) {
    int aval = stock[a].delta + groupDelta[a / SQR];  // ���� ���� ���� + �׷� ���� ����
    int bval = stock[b].delta + groupDelta[b / SQR];
    if (aval != bval) return aval > bval;
    return (aval == bval && stock[a].id < stock[b].id); // ���������� ���ٸ� id��
}

int getMostIncreased(char mFromStock[], char mToStock[]) {
    rint s = probing(getKey(mFromStock)), e = probing(getKey(mToStock));
    rint sidx = s, eidx = e;
    for (; s % SQR && s <= e; ++s) {        // ������ ���� ���������� ã��
        if (stock[s] > stock[sidx])
            sidx = s;
    }

    for (; (e + 1) % SQR && s <= e; --e) {  // ������ ���� ���������� ã��
        if (stock[e] > stock[eidx])
            eidx = e;
    }

    int ridx = sidx;                        // ���� ���������� ã�� ���� �ӽ� ������
    if (comp(eidx, ridx)) ridx = eidx;      // ���� ���������� ã�� ���� �� ���� ��� ����
    int rval = stock[ridx].delta + groupDelta[ridx / SQR];

    for (; s <= e; s += SQR) {              // �׷� ������ ã��
        int idx = groupMax[s / SQR];
        int val = stock[idx].delta + groupDelta[idx / SQR];
        if (val > rval) rval = val, ridx = idx;
        if (val == rval && stock[idx].id < stock[ridx].id)
            ridx = idx;
    }

    return stock[ridx].id;                  // ���� ���
}