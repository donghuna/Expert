/*
29_���̷�������_user_ver02
segment tree version
*/
#define rint register int
static const int LM = 50000000;
const int SECT = 512;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);

void build(int now, int s, int e) {// [s, e]
    // base condition
    if (s + 1 >= e) {              // 2�����ϰ� ���� ���
        culture(now + LM, s, e);   // leaf node�� ��� ���ݺ� ���� �� ����� or�������� ����
        return;
    }
    int lch = now * 2, rch = lch + 1, m = (s + e) / 2;
    build(lch, s, m);
    build(rch, m + 1, e);
    culture(now + LM, lch + LM, rch + LM);
}

int cleanup(int now, int s, int e) {
    if (s + 1 >= e) { // �� 2�� �Ǵ� 1���� ���� ���
        if (virus_checkup(s)) {  // ������ 1�� ���
            clear(s);
            return s + 1;        // ���ο� �˻籸���� ������ġ
        }
        clear(e);                // �������� 1�� ���
        return e + 1;            // ���ο� �˻籸���� ������ġ
    }
    int lch = now * 2, rch = lch + 1, m = (s + e) / 2;
    if (virus_checkup(lch + LM))
        return cleanup(lch, s, m);
    return cleanup(rch, m + 1, e);
}

void test()
{
    int s = 0, e;
    while (s < LM) {
        e = s + SECT - 1;
        if (e >= LM) e = LM - 1;

        build(1, s, e); // build(root index, rangeStart, rangeEnd);
        if (virus_checkup(LM + 1)) {  // ������ 1�� �ִٸ�
            s = cleanup(1, s, e);
        }
        else s = e + 1;
    }
}