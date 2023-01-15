/*
29_���̷�������_user_ver01
binary search version
*/
#define rint register int

const int LM = 50'000'000;
const int SECT = 512;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);

int bisearchLoop1(int low, int high) {
    while (low < high) {
        rint mid = (low + high) / 2;
        if (virus_checkup(LM + mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

int bisearchLoop2(int low, int high) {
    rint mid, ans = -1;
    while (low <= high) {
        if (low == high && ans < 0) return low;
        mid = (low + high) / 2;
        if (virus_checkup(LM + mid))
            ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    return ans;
}

int bisearchRecur(int low, int high) {
    if (low == high) return low;
    rint mid = (low + high) / 2;
    if (virus_checkup(LM + mid))
        return bisearchRecur(low, mid);
    return bisearchRecur(mid + 1, high);
}

void test()
{
    for (rint s = 0; s < LM;) {
        rint e = s + SECT;
        if (e > LM) e = LM;

        // 1. culturing
        culture(LM + s, s, s);
        for (rint i = s + 1; i < e; ++i)
            culture(LM + i, LM + i - 1, i);

        // 2. find & erase
        if (virus_checkup(LM + e - 1)) {  // (s, e-1) �������� ã�� ���
            //int tg = bisearchLoop1(s, e - 1);  // ã��
            //int tg = bisearchLoop2(s, e - 1);  // ã��
            int tg = bisearchRecur(s, e - 1);  // ã��
            clear(tg);                         // �����
            s = tg + 1;
        }
        else s = e;                       // (s, e-1) �������� ��ã�� ���
    }
}