#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/**
31_수식계산기2
stack
[problem]
괄호와 사칙연산자를 포함한 식이 주어지면 결과를 계산하라.
나누기 연산은 몫만을 취한다.
계산의 중간결과 및 최종결과는 int를 초과할 수 있으나 long long 범위를 벗어나지 않는다.

[analysis]
0. 문자열로 입력받고 연산자와 숫자로 나누는 것이 필요하다.
     숫자 여러개를 수로 만들 때 Horner's method가 사용될 수 있다.
1. 연산의 중간 결과가 int를 넘을 수 있으므로 long long으로 처리한다.
2. 나눗셈의 결과는 몫만을 취한다.
3. '( )'는 최우선하여 계산한다.
4. '*', '/'연산은 '+', '-'보다 우선한다.

[solution sketch]
0. 괄호와 연산자에 우선순위가 있으므로 연산이 유보되는 경우가 발생한다.
   따라서 유보된 계산은 스택에 담아둘 필요가 있다.
1. 숫자인경우 :
   1) 수를 만들어 수 스택에 수를 담고
   2) 연산자 스택의 top이 '*', '/'라면 계산한다.
2. 문자인 경우
   1) '+', '-' 경우
    : 먼저 숫자 스택에 수가 2개 이상이고 이전에 담긴 수를 계산할 수 있는 경우 계산한다.
      (연산자가 '('이 아니고 '+', '-'라면 계산한다.)
    : 연산자 스택에 '+', '-' 를 추가한다.
   2) ')'인 경우
       ① 계산한다.(남은 연산은 '+', '-'중 하나이다.)
       ② '('를 지운다.
       ③ 연산자 스택의 top이 '*', '/'라면 계산시킨다.
   3) 나머지 : '(', '*', '/' 인 경우
      : 연산자 스택에 추가한다.
3. 마지막으로 연산자 스택에 남은 것이 있다면 계산한다.
   (남은 연산은 '+', '-'중 하나이다.)

*/
#include <stdio.h>

using LL = long long;
const int LM = 210;
char str[LM], opStk[LM];
LL numStk[LM];
int opTop, numTop;  // 1_base로 처리된다.

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
        if (str[i] >= '0' && str[i] <= '9') {  // 숫자라면
            LL d = 0;
            while (str[i] >= '0' && str[i] <= '9') {
                d = d * 10 + str[i] - '0';
                i++;
            }
            // 1. 숫자스택에 담고
            numStk[++numTop] = d;
            // 2. 연산자 스택의 top이 곱셈 또는 나눗셈이라면 계산한다.
            if (opStk[opTop] == '*' || opStk[opTop] == '/') calc();
        }
        else { // 연산자라면
            // 1. 덧셈, 뺄셈이라면 
            if (str[i] == '+' || str[i] == '-') {
                if (numTop > 1) calc();  // 이전까지 계산하기 : 남은 연산은 '+', '-'중 하나이다
                opStk[++opTop] = str[i]; // 연산자 스택에 담기
            }
            else if (str[i] == ')') {
                calc();   // 이전까지 계산하기 : 남은 연산은 '+', '-'중 하나이다
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