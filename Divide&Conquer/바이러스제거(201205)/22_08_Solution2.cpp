/*
24_���̷�������_user_ver02
binary search : recursive
*/
#define rint register int

static const int LM = 50'000'000;
const int SECTOR = 512;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);

int bisearch(int st, int ed) {
    if (st >= ed) return st;
    int m = (st + ed) / 2;
    if (virus_checkup(LM + m))
        return bisearch(st, m);
    return bisearch(m + 1, ed);
}

void test()
{
    for (rint st = 0; st < LM;) {
        rint ed = st + SECTOR;
        if (ed > LM) ed = LM;

        // ���̺� ����
        culture(st + LM, st, st);
        for (rint i = st + 1; i < ed; ++i) {
            culture(i + LM, i + LM - 1, i);
        }

        if (virus_checkup(LM + ed - 1)) {  // ������ ���̷����� �ִٸ�
            int tg = bisearch(st, ed - 1); // ���� ó�� �����ϴ� 1 ��ġ ã��
            clear(tg);
            st = tg + 1;                   // ���� ������ ������ġ
        }
        else st = ed;                      // ������ ���̷����� ���� ���
    }
}