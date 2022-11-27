/*
35_TS주가변동_user
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
    LL key;                // 이름을 long long형 정수로 변환한 값.
    bool operator<(const Data& t) const {
        return key < t.key;
    }
    bool operator>(const Data& t) const {  // 같은 그룹내에서 우선순위 비교
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

LL getKey(char* s) {        // 문자열을 long long 형 정수로 변환하기
    rint i = 0;
    LL key = 0;
    for (; s[i]; ++i) key = key * 27 + s[i] - 96;
    for (; i < 10; ++i) key = key * 27;  // 사전편집상 비교이므로 모두 10자리로 맞춘다.
    return key;
}

int probing(LL key) {       // 같은 이름의 주식 찾기
    Node* p = htab[key & MASK];
    for (; p; p = p->next)
        if (stock[p->id].key == key)
            return p->id;
    return 0;
}

inline int min(int a, int b) { return a < b ? a : b; }
void mergeSort(Data* A, int s, int e) {  // 주식을 이름의 오름차순으로 정렬
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
    while ((SQR + 1) * (SQR + 1) <= N) SQR++;  // 제곱근 구하기
    // 주식 정보 id(i) 순으로 저장하기
    for (rint i = 0; i < N; ++i) {
        stock[i] = { i, mPrices[i], 0, getKey(mStocks[i]) };
    }
    // 이름순으로 정렬하기
    mergeSort(stock, 0, N);

    // 해시 테이블 초기화
    bcnt = 0;
    for (rint i = 0; i < MOD; ++i) htab[i] = nullptr;
    for (rint i = 0; i < N; ++i) {  // 이름을 해시 테이블에 저장하기
        int hidx = stock[i].key & MASK;
        htab[hidx] = buf[bcnt++].alloc(i, htab[hidx]);
    }

    // 각 그룹별 초기값 저장
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

void update(int s, int e) { // 그룹내에서 최대값 갱신
    int& gmx = groupMax[s / SQR];
    for (; s < e; ++s) if (stock[s] > stock[gmx])
        gmx = s;
}

void change(char mFromStock[], char mToStock[], int mPriceDiff) {
    rint st = probing(getKey(mFromStock)), ed = probing(getKey(mToStock));
    rint s = st, e = ed;
    for (; s % SQR && s <= ed; ++s)         // 앞쪽 자투리 가격 업데이트
        stock[s].delta += mPriceDiff;

    update(st / SQR * SQR, s); //앞쪽 자투리가 포함된 전체 구간의 주식 상승 최대값 업데이트

    for (; ((e + 1) % SQR) && s <= e; --e) // 그룹단위 가격 업데이트, 최대값을 변화가 없다.
        stock[e].delta += mPriceDiff;

    for (; s <= e; s += SQR)
        groupDelta[s / SQR] += mPriceDiff; // 뒤쪽 자투리 가격 업데이트

    // 뒤쪽 자투리가 포함된 전체 구간의 주식 상승 최대값 업데이트
    update(s, min(ed / SQR * SQR + SQR, N));
}

int getPrice(char mStock[]) {             // mStock[]주식 현재 가격 구하기
    int ridx = probing(getKey(mStock));
    // 초기가격 + 개별 변동 가격 + 그룹 변동 가격
    return stock[ridx].price + stock[ridx].delta + groupDelta[ridx / SQR];
}

int comp(int a, int b) {
    int aval = stock[a].delta + groupDelta[a / SQR];  // 개별 변동 가격 + 그룹 변동 가격
    int bval = stock[b].delta + groupDelta[b / SQR];
    if (aval != bval) return aval > bval;
    return (aval == bval && stock[a].id < stock[b].id); // 변동가격이 같다면 id비교
}

int getMostIncreased(char mFromStock[], char mToStock[]) {
    rint s = probing(getKey(mFromStock)), e = probing(getKey(mToStock));
    rint sidx = s, eidx = e;
    for (; s % SQR && s <= e; ++s) {        // 구간의 앞쪽 자투리에서 찾기
        if (stock[s] > stock[sidx])
            sidx = s;
    }

    for (; (e + 1) % SQR && s <= e; --e) {  // 구간의 뒤쪽 자투리에서 찾기
        if (stock[e] > stock[eidx])
            eidx = e;
    }

    int ridx = sidx;                        // 앞쪽 자투리에서 찾은 값을 임시 답으로
    if (comp(eidx, ridx)) ridx = eidx;      // 뒤쪽 자투리에서 찾은 값이 더 좋은 경우 갱신
    int rval = stock[ridx].delta + groupDelta[ridx / SQR];

    for (; s <= e; s += SQR) {              // 그룹 단위로 찾기
        int idx = groupMax[s / SQR];
        int val = stock[idx].delta + groupDelta[idx / SQR];
        if (val > rval) rval = val, ridx = idx;
        if (val == rval && stock[idx].id < stock[ridx].id)
            ridx = idx;
    }

    return stock[ridx].id;                  // 최종 결과
}