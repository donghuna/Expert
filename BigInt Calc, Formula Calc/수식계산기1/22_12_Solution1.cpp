#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
32_���İ���1
[��, ������] ������ ó���ϱ�
*/
#include <cstdio>

int main() {
#ifdef _WIN32
    freopen("32.txt", "r", stdin);
#endif // _WIN32
    int ret = 0, a;
    char ch, op = '+';
    while (true) {
        ch = 0;
        scanf("%d", &a);
        ret += op == '+' ? a : -a;

        op = 0;
        scanf("%c", &op);
        if (op != '+' && op != '-')
            break;
    }
    printf("%d\n", ret);
    return 0;
}