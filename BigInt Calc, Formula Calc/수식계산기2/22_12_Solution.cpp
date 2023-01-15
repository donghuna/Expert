#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
33_���İ���2
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
    else return;  // ��Ģ�����ڰ� �ƴ� ��� : ��) '('
    opTop--, numTop--;
}

int main() {
#ifdef _WIN32
    freopen("33.txt", "r", stdin);
#endif // _WIN32
    scanf("%s", exp);
    for (int i = 0; exp[i];) {
        if (exp[i] > 47) {  // �����
            LL d = 0;
            for (; exp[i] > 47; ++i)   // �� ����
                d = d * 10 + exp[i] - '0';

            numStk[++numTop] = d;
            if (opStk[opTop] == '*' || opStk[opTop] == '/')
                calc();
        }
        else {              // �����ڶ��
            if (exp[i] == '+' || exp[i] == '-') {
                calc();
                opStk[++opTop] = exp[i];  // *****
            }
            else if (exp[i] == ')') {
                calc();
                opTop--;  // '(' �����
                if (opStk[opTop] == '*' || opStk[opTop] == '/')
                    calc();
            }
            else {   // '(', '*', '/' �� �ܼ��� ������ ���ÿ� �߰��� �Ѵ�.
                opStk[++opTop] = exp[i];
            }
            i++;
        }
    }
    calc();  // ���� ����� �ִٸ� ����ϱ�

    printf("%lld\n", numStk[numTop]);
    return 0;
}