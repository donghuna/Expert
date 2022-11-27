/*
36_TS�迭����_user
non STL :
�����̷��� ��ũ�� ����Ʈ�� ���
����Ʈ�� ������ �����Ͱ� �θ���� �б����� ����Ű���� �Ѵ�.
��������
���� ����� �����̷� ->
�θ��� �����̷� ->
�θ��� �θ� �����̷� ->
... ->
root �������� �̷��� �ִٸ� ��ȯ�Ѵ�.
�׷��� �ʴٸ� root�迭�� ���� ��ȯ�Ѵ�.
*/
#define rint register int
using LL = long long;
const int LM = 200005;    // Array length
const int NLM = 5020;     // Node size
const int MOD = 1 << 12;
const int MASK = MOD - 1;

int arr[11][LM];
int* idArr[NLM];  // id�� ��Ʈarr�� �����͸� ���� 
int arrcnt, idcnt, hcnt, bcnt;

struct Hash {     // chaining hash
    LL key;       // ���ڿ��� LL Ÿ���� ������ ó��
    int renumID;  // idcnt�� ���������� �ο��ϱ�
    Hash* next;
    Hash* alloc(LL nk, int nid, Hash* nn) {
        key = nk, renumID = nid, next = nn;
        return this;
    }
}hbuf[NLM], * htab[MOD];

struct Node {       // ���泻���� id���� ��ũ�� ����Ʈ�� �����ϱ�
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
    LL key = getKey(Name);  // ���ڿ��� LLŸ���� ������ �ٲٱ�
    int hidx = key & MASK;  // hash ���̺��� slot��ȣ ����
    Hash* p = htab[hidx];    // ���� Ű ã��
    for (; p; p = p->next) if (p->key == key)
        return p->renumID;  // ���� Ű(���ڿ�)�� ã�� ���

    // ���ο� ���ڿ��̶�� ����ϱ�
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
    rint* ap = idArr[id] = arr[arrcnt++];                // ��Ʈ �迭�� �ּҰ��� idArr[id]�� ����
    for (rint i = 0; i < Len; ++i) ap[i] = Values[i];    // �״�� ����
    updateList[id] = buf[bcnt++].alloc(-1, -1, nullptr); // root node
}

void copyArray(char to[], char from[], bool flag)
{
    int fid = getID(from);
    if (flag) { // deep copy : ���������� fid�� �̷��� �������� �� �ֵ����Ѵ�.
        int tid = getID(to);
        idArr[tid] = idArr[fid];
        updateList[tid] = buf[bcnt++].alloc(-1, -1, updateList[fid]);
    }
    else {      // shallow copy : hash���̺��� renum id�� fid�� �����Ѵ�.
        LL key = getKey(to);
        int hidx = key & MASK;
        htab[hidx] = hbuf[hcnt++].alloc(key, fid, htab[hidx]);
    }
}

void updateData(char Name[], int Index, int Value)
{
    int id = getID(Name);  // ���泻���� ��ũ�� ����Ʈ�� ����
    updateList[id] = buf[bcnt++].alloc(Index, Value, updateList[id]);
}

int getData(char Name[], int Index)
{
    int id = getID(Name); // ���泻���� ���� Ž���ϱ�
    register Node* p = updateList[id];
    for (; p; p = p->next) // �������� ���泻��->�θ�-> �θ��� �θ� ...->root���� ����
        if (p->idx == Index)
            return p->val;

    return idArr[id][Index];  // root array�� �� ��ȯ
}