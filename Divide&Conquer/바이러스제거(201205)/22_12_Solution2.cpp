/*
29_바이러스제거_user_ver02
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
    if (s + 1 >= e) {              // 2개이하가 남은 경우
        culture(now + LM, s, e);   // leaf node의 경우 전반부 인접 두 노드의 or연산결과를 저장
        return;
    }
    int lch = now * 2, rch = lch + 1, m = (s + e) / 2;
    build(lch, s, m);
    build(rch, m + 1, e);
    culture(now + LM, lch + LM, rch + LM);
}

int cleanup(int now, int s, int e) {
    if (s + 1 >= e) { // 단 2개 또는 1개가 남은 경우
        if (virus_checkup(s)) {  // 왼쪽이 1인 경우
            clear(s);
            return s + 1;        // 새로운 검사구간의 시작위치
        }
        clear(e);                // 오른쪽이 1인 경우
        return e + 1;            // 새로운 검사구간의 시작위치
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
        if (virus_checkup(LM + 1)) {  // 구간에 1이 있다면
            s = cleanup(1, s, e);
        }
        else s = e + 1;
    }
}