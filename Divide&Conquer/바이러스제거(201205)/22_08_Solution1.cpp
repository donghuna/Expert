/*
24_���̷�������_user_ver01
binary search : Loop
*/
#define rint register int

static const int LM = 50'000'000;
const int SECTOR = 512;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);
int biSearchLoop(rint low, rint high) {
    rint mid, ret = -1;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (low == high && ret < 0) // ��ġ�� �̰����ε� ���� ������ 1��
            return low;             // low(high)�� ���̷����� �ִ� ��ġ
        if (virus_checkup(LM + mid)) {
            ret = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return ret;
}

void test()
{
    for (int st = 0; st < LM;) {
        int ed = st + SECTOR;
        if (ed > LM) ed = LM;

        // ���̺� ����
        culture(st + LM, st, st);
        for (rint i = st + 1; i < ed; ++i) {
            culture(i + LM, i + LM - 1, i);
        }

        if (virus_checkup(LM + ed - 1)) {      // ������ ���̷����� �ִٸ�
            int tg = biSearchLoop(st, ed - 1); // �������� ���� ó�� �����ϴ� 1 ��ġ ã��
            clear(tg);
            st = tg + 1;                       // ���� ������ ������ġ
        }
        else st = ed;                          // ������ ���̷����� ���� ���
    }
}