/*
35_TS수식계산기2_user
*/
#define rint register int
const int LM = 5005;
const int MOD = 1 << 12;
const int MASK = MOD - 1;

struct Form {
    int F[10];
    void setter(int idx, int val) {
        for (rint i = 0; i < 10; ++i) F[i] = 0;
        F[idx] = val;
    }
    int get() {
        return (F[0] || F[3] || F[5] || F[6]) +
            (F[1] || F[3] || F[4] || F[7]) + (F[2] || F[4] || F[5] || F[8]);
    }
    int calcForm(int a, int b, int c) {
        return F[0] * a * a + F[1] * b * b + F[2] * c * c + F[3] * a * b +
            F[4] * b * c + F[5] * c * a + F[6] * a + F[7] * b + F[8] * c + F[9];
    }
    bool operator==(const Form& t)const {
        for (rint i = 0; i < 10; ++i) if (F[i] != t.F[i]) return 0;
        return 1;
    }
    void operator+=(const Form& t) {
        for (rint i = 0; i < 10; ++i) F[i] += t.F[i];
    }
    void operator-=(const Form& t) {
        for (rint i = 0; i < 10; ++i) F[i] -= t.F[i];
    }
    void operator*=(const Form& t) {
        F[0] = F[6] * t.F[6];
        F[1] = F[7] * t.F[7];
        F[2] = F[8] * t.F[8];
        F[3] = F[6] * t.F[7] + F[7] * t.F[6];
        F[4] = F[7] * t.F[8] + F[8] * t.F[7];
        F[5] = F[8] * t.F[6] + F[6] * t.F[8];
        F[6] = F[6] * t.F[9] + F[9] * t.F[6];
        F[7] = F[7] * t.F[9] + F[9] * t.F[7];
        F[8] = F[8] * t.F[9] + F[9] * t.F[8];
        F[9] = F[9] * t.F[9];
    }
}forms[LM], stk[200];

int N, fcnt, top, opTop;
char opStk[200];
int stp[MOD], link[LM], cnt[LM];
int probing() {
    rint i = stp[stk[top].F[9] & MASK];
    for (; i && !(forms[i] == stk[top]); i = link[i]);
    return i;
}

void calc() {
    if (opStk[opTop] == '+') stk[top - 1] += stk[top];
    else if (opStk[opTop] == '-') stk[top - 1] -= stk[top];
    else if (opStk[opTop] == '*') stk[top - 1] *= stk[top];
    else return;
    top--, opTop--;
}

void init() {
    for (rint i = 1; i <= N; ++i) cnt[i] = 0;
    for (rint i = 0; i < MOD; ++i) stp[i] = 0;
    fcnt = 0;
}

int addExpression(int eid, char exp[201]) {
    N = eid;
    top = opTop = 0;
    stk[top].setter(9, 0);
    char c;
    for (rint i = 0; (c = exp[i]); ++i) {
        if (c > 47 || c == ')') {
            if (c == ')') calc(), opTop--;
            else if (c < 65) stk[++top].setter(9, exp[i] - 48);
            else stk[++top].setter(exp[i] - 59, 1);
            if (opStk[opTop] == '*') calc();
        }
        else {
            if (exp[i] == '+' || exp[i] == '-') calc();
            opStk[++opTop] = exp[i];
        }
    }
    calc();

    forms[eid] = stk[top];
    int id = probing();
    if (id == 0) {
        int hidx = stk[top].F[9] & MASK;
        link[eid] = stp[hidx], stp[hidx] = id = eid;
    }
    cnt[id] ++;
    if (cnt[id] == 1) return -forms[eid].get();
    return cnt[id] - 1;
}

int calcExpression(int eid, int ma, int mb, int mc) {
    return forms[eid].calcForm(ma, mb, mc);
}