/*
36_TS배열복사_user
non STL :
변경이력을 링크드 리스트에 담고
리스트의 마지막 포인터가 부모와의 분기점을 가리키도록 한다.
역추적시
현재 노드의 변경이력 ->
부모의 변경이력 ->
부모의 부모 변경이력 ->
... ->
root 이전까지 이력이 있다면 반환한다.
그렇지 않다면 root배열의 값을 반환한다.
*/
#define rint register int
using LL = long long;
const int LM = 200005;    // Array length
const int NLM = 5020;     // Node size
const int MOD = 1 << 12;
const int MASK = MOD - 1;

int arr[11][LM];
int* idArr[NLM];  // id별 루트arr의 포인터를 저장 
int arrcnt, idcnt, hcnt, bcnt;

struct Hash {     // chaining hash
    LL key;       // 문자열을 LL 타입의 정수로 처리
    int renumID;  // idcnt를 순차적으로 부여하기
    Hash* next;
    Hash* alloc(LL nk, int nid, Hash* nn) {
        key = nk, renumID = nid, next = nn;
        return this;
    }
}hbuf[NLM], * htab[MOD];

struct Node {       // 변경내역을 id별로 링크드 리스트로 저장하기
    int idx, val;   // update info
    Node* next;     // next or parent pointer
    Node* alloc(int ni, int nv, Node* nn) {
        idx = ni, val = nv, next = nn;
        return this;
    }
}buf[LM], * updateList[NLM];

inline LL getKey(char Name[], LL key = 0) {
    for (rint i = 0; Name[i]; ++i)  // Horner's method
        key = key * 27 + Name[i] - 'a' + 1;
    return key;
}

inline int getID(char Name[]) {
    LL key = getKey(Name);  // 문자열을 LL타입의 정수로 바꾸기
    int hidx = key & MASK;  // hash 테이블의 slot번호 생성
    Hash* p = htab[hidx];    // 같은 키 찾기
    for (; p; p = p->next) if (p->key == key)
        return p->renumID;  // 같은 키(문자열)을 찾은 경우

    // 새로운 문자열이라면 등록하기
    htab[hidx] = hbuf[hcnt++].alloc(key, ++idcnt, htab[hidx]);
    return idcnt;
}

void init()
{
    idcnt = arrcnt = bcnt = hcnt = 0;
    for (rint i = 0; i < MOD; ++i)
        htab[i] = nullptr;
}

void makeArray(char Name[], int Len, int Values[])
{
    int id = getID(Name);
    rint* ap = idArr[id] = arr[arrcnt++];                // 루트 배열의 주소값을 idArr[id]에 복사
    for (rint i = 0; i < Len; ++i) ap[i] = Values[i];    // 그대로 복사
    updateList[id] = buf[bcnt++].alloc(-1, -1, nullptr); // root node
}

void copyArray(char to[], char from[], bool flag)
{
    int fid = getID(from);
    if (flag) { // deep copy : 현시점까지 fid의 이력을 역추적할 수 있도록한다.
        int tid = getID(to);
        idArr[tid] = idArr[fid];
        updateList[tid] = buf[bcnt++].alloc(-1, -1, updateList[fid]);
    }
    else {      // shallow copy : hash테이블의 renum id를 fid로 지정한다.
        LL key = getKey(to);
        int hidx = key & MASK;
        htab[hidx] = hbuf[hcnt++].alloc(key, fid, htab[hidx]);
    }
}

void updateData(char Name[], int Index, int Value)
{
    int id = getID(Name);  // 변경내역을 링크드 리스트로 저장
    updateList[id] = buf[bcnt++].alloc(Index, Value, updateList[id]);
}

int getData(char Name[], int Index)
{
    int id = getID(Name); // 변경내역을 순차 탐색하기
    register Node* p = updateList[id];
    for (; p; p = p->next) // 현재노드의 변경내역->부모-> 부모의 부모 ...->root직전 종료
        if (p->idx == Index)
            return p->val;

    return idArr[id][Index];  // root array의 값 반환
}