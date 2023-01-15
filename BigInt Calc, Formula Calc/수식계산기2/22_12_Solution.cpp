#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
33_수식계산기2
*/
#include <cstdio>

using LL = long long;
const int LM = 210;
char exp[LM], opStk[LM];
int opTop, numTop;
LL numStk[LM];

void calc() {
    char op = opStk[opTop];
    if (op == '+') numStk[numTop - 1] += numStk[numTop];
    else if (op == '-') numStk[numTop - 1] -= numStk[numTop];
    else if (op == '*') numStk[numTop - 1] *= numStk[numTop];
    else if (op == '/') numStk[numTop - 1] /= numStk[numTop];
    else return;  // 사칙연산자가 아닌 경우 : 예) '('
    opTop--, numTop--;
}

int main() {
#ifdef _WIN32
    freopen("33.txt", "r", stdin);
#endif // _WIN32
    scanf("%s", exp);
    for (int i = 0; exp[i];) {
        if (exp[i] > 47) {  // 수라면
            LL d = 0;
            for (; exp[i] > 47; ++i)   // 수 추출
                d = d * 10 + exp[i] - '0';

            numStk[++numTop] = d;
            if (opStk[opTop] == '*' || opStk[opTop] == '/')
                calc();
        }
        else {              // 연산자라면
            if (exp[i] == '+' || exp[i] == '-') {
                calc();
                opStk[++opTop] = exp[i];  // *****
            }
            else if (exp[i] == ')') {
                calc();
                opTop--;  // '(' 지우기
                if (opStk[opTop] == '*' || opStk[opTop] == '/')
                    calc();
            }
            else {   // '(', '*', '/' 는 단순히 연산자 스택에 추가만 한다.
                opStk[++opTop] = exp[i];
            }
            i++;
        }
    }
    calc();  // 남은 계산이 있다면 계산하기

    printf("%lld\n", numStk[numTop]);
    return 0;
}