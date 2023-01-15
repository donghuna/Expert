#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/**
31_���İ���2
stack
[problem]
��ȣ�� ��Ģ�����ڸ� ������ ���� �־����� ����� ����϶�.
������ ������ ���� ���Ѵ�.
����� �߰���� �� ��������� int�� �ʰ��� �� ������ long long ������ ����� �ʴ´�.

[analysis]
0. ���ڿ��� �Է¹ް� �����ڿ� ���ڷ� ������ ���� �ʿ��ϴ�.
     ���� �������� ���� ���� �� Horner's method�� ���� �� �ִ�.
1. ������ �߰� ����� int�� ���� �� �����Ƿ� long long���� ó���Ѵ�.
2. �������� ����� ���� ���Ѵ�.
3. '( )'�� �ֿ켱�Ͽ� ����Ѵ�.
4. '*', '/'������ '+', '-'���� �켱�Ѵ�.

[solution sketch]
0. ��ȣ�� �����ڿ� �켱������ �����Ƿ� ������ �����Ǵ� ��찡 �߻��Ѵ�.
   ���� ������ ����� ���ÿ� ��Ƶ� �ʿ䰡 �ִ�.
1. �����ΰ�� :
   1) ���� ����� �� ���ÿ� ���� ���
   2) ������ ������ top�� '*', '/'��� ����Ѵ�.
2. ������ ���
   1) '+', '-' ���
    : ���� ���� ���ÿ� ���� 2�� �̻��̰� ������ ��� ���� ����� �� �ִ� ��� ����Ѵ�.
      (�����ڰ� '('�� �ƴϰ� '+', '-'��� ����Ѵ�.)
    : ������ ���ÿ� '+', '-' �� �߰��Ѵ�.
   2) ')'�� ���
       �� ����Ѵ�.(���� ������ '+', '-'�� �ϳ��̴�.)
       �� '('�� �����.
       �� ������ ������ top�� '*', '/'��� ����Ų��.
   3) ������ : '(', '*', '/' �� ���
      : ������ ���ÿ� �߰��Ѵ�.
3. ���������� ������ ���ÿ� ���� ���� �ִٸ� ����Ѵ�.
   (���� ������ '+', '-'�� �ϳ��̴�.)

*/
#include <stdio.h>

using LL = long long;
const int LM = 210;
char str[LM], opStk[LM];
LL numStk[LM];
int opTop, numTop;  // 1_base�� ó���ȴ�.

void calc() {
    int sign = opStk[opTop];
    if (sign == '+') numStk[numTop - 1] += numStk[numTop];
    else if (sign == '-') numStk[numTop - 1] -= numStk[numTop];
    else if (sign == '*') numStk[numTop - 1] *= numStk[numTop];
    else if (sign == '/') numStk[numTop - 1] /= numStk[numTop];
    else return;
    opTop--, numTop--;
}

int main() {
    scanf("%s", str);
    for (int i = 0; str[i];) {
        if (str[i] >= '0' && str[i] <= '9') {  // ���ڶ��
            LL d = 0;
            while (str[i] >= '0' && str[i] <= '9') {
                d = d * 10 + str[i] - '0';
                i++;
            }
            // 1. ���ڽ��ÿ� ���
            numStk[++numTop] = d;
            // 2. ������ ������ top�� ���� �Ǵ� �������̶�� ����Ѵ�.
            if (opStk[opTop] == '*' || opStk[opTop] == '/') calc();
        }
        else { // �����ڶ��
            // 1. ����, �����̶�� 
            if (str[i] == '+' || str[i] == '-') {
                if (numTop > 1) calc();  // �������� ����ϱ� : ���� ������ '+', '-'�� �ϳ��̴�
                opStk[++opTop] = str[i]; // ������ ���ÿ� ���
            }
            else if (str[i] == ')') {
                calc();   // �������� ����ϱ� : ���� ������ '+', '-'�� �ϳ��̴�
                opTop--;  // delete '('
                if (opStk[opTop] == '*' ||
                    opStk[opTop] == '/') calc();
            }
            else {   // '(', '*', '/'
                opStk[++opTop] = str[i];
            }
            i++;
        }
    }
    if (numTop > 1) calc();
    printf("%lld \n", numStk[1]);
    return 0;
}