/*
19_FASTSort_user_ver02
self counting sort + hw_sort
SCORE : 1**

[hw_sort�� ���� �̿��ϱ�]
1. hw_sort()���ð��� ������ �ݿ����� �ʴ´�.
2. hw_sort()�� signed_short�� �����Ѵ�.
3. hw_sort()�� ��Ȯ�� 1024���� �����Ѵ�.
4. hw_sort()�� �����������θ� �����Ѵ�.
*/
extern void hw_sort(short data[1024]);

#define LM (1048576)
#define MASK (65535)
#define rint register int

using UI = unsigned int;
const unsigned int MSB = 1 << 31;
const int CLM = 1 << 11; // 2048
const int MK = CLM - 1;  // 2047 : bitmask

// ***** ���� 11��Ʈ�� ���Ͽ� �������� �����ϱ�(���� 11bit�� �׷�����) *****
void selfCountingSort(int lev, unsigned int* p, int n, int* cnt) {
    rint i, j, k;
    for (i = 0; i < CLM; ++i) cnt[i] = 0;
    for (i = 0; i < n; ++i) cnt[(p[i] >> lev) & MK] ++;  // ���� ����
    for (i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1];      // ������ ���ϱ�
    for (i = n - 1; i >= 0; --i) {
        if (p[i] & MSB) p[i] ^= MSB;  // MSB�� ǥ�õ� ���� �̹� �ڱ� �ڸ� ã�� ���̹Ƿ� MSB�� �����ϱ�
        else {  // ���������� �����ϰ� ���ĵ� ���� MSB�� ǥ���ϸ鼭 ��ü �迭�� �����ϱ�
            for (j = --cnt[(p[i] >> lev) & MK]; i != j; j = --cnt[(p[i] >> lev) & MK]) {
                // ��ġ�� ��ȯ�ϱ�
                k = p[j];
                p[j] = p[i] | MSB;   // �ڱ� �ڸ� ã�� ���� MSB�� ǥ���ϱ�
                p[i] = k;
            }
        }
    }
}

void test(unsigned int data[LM]) {
    int origin[2050] = { 0 }, cnt[2050] = { 0 };
    int entry[65538] = { 0 }; // ������ ���� ǥ��
    unsigned short A[2050], trr[2050];
    rint i, j, k, n = 0, m, t;

    // extract entry value
    for (i = 0; i < LM; ++i) {
        // a: ���� 16bit����, b: ���� 16bit����
        int a = (data[i] >> 16) & MASK, b = data[i] & MASK;

        // ó�� ������ ����� ��ȣ bit�� ��������(hw_sort�� signed short�� ���İ�����) trr�� ����
        if (entry[a] == 0) entry[a] = 1, trr[n++] = a ^ 32768;
        if (entry[b] == 0) entry[b] = 1, trr[n++] = b ^ 32768;
    }

    // �ִ� 2048���� �� �� �����Ƿ� 2�� ������ ����(hw_sort�� ��Ȯ�� 1024���� ���İ�����)
    hw_sort((short*)trr), hw_sort((short*)(trr + n - 1024));

    for (i = 0; i < n; ++i) trr[i] ^= 32768;      // ��ȣ bit�� ������� ����

    // �ѷ� ������ ���ĵ� trr�迭�� merge��Ű�� : O(n)
    m = n - 1024, i = 0, j = m, k = 0;
    while (i < m && j < n) {
        if (trr[i] < trr[j]) A[k++] = trr[i++];
        else A[k++] = trr[j++];
    }
    while (i < m) A[k++] = trr[i++];
    while (j < n) A[k++] = trr[j++];

    // desc renumbering
    for (i = n - 1, j = 0; i >= 0; --i) { // �������� ��ȣ�ű��(hw_sort()�� �����������θ� �����Ѵ�.)
        origin[j] = A[i];   // ������ �� ���
        entry[A[i]] = j++;  // ������ ���� renumbering id�ο��ϱ� (16bit���� 11bit��ȣ�� �ο��ȴ�)
    }

    // 32bit --> 22bit�� �����ϱ�
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 16) & MASK, k = data[i] & MASK;
        data[i] = ((unsigned int)entry[j] << 11) | entry[k];
    }

    selfCountingSort(11, data, LM, cnt);  // ���� 11��Ʈ�� ���Ͽ� �������(����11��Ʈ�� �׷�����)

    // ���� 11bit�� �׷����� ���ִ� ���� 11bit�� �׷쳻���� �����ϱ�
    for (i = 0; i < LM; i = j) {
        // �׷��� ����ã��
        t = (data[i] >> 11) & MASK;                    // ���� �ĺ���(���� 11bit)            
        j = i;                                         // i: ������ ����
        for (; j < LM && (data[j] >> 11) == t; ++j);   // j: ������ ��
        n = j - i;                                     // n: ������ ũ��
        if (n < 1025) {                                // ���� ũ�Ⱑ 1024������ ���
            for (k = 0; k < n; ++k) A[k] = data[i + k] & MK;  // �ӽ÷� A[]�� ���
            for (; k < 1024; ++k) A[k] = 2050;         // 1024�̸��̶�� ������ ������ ū������ ä���
            hw_sort((short*)A);
            for (k = 0; k < n; ++k) data[i + k] = (t << 11) | A[k]; // ���� �迭�� ����
        }
        else if (n < 2049) {                           // ���� ũ�Ⱑ 1025 ~ 2048�� ���
            for (k = 0; k < n; ++k) trr[k] = data[i + k] & MK;  // �ӽ÷� A[]�� ���

            hw_sort((short*)trr), hw_sort((short*)(trr + n - 1024));
            {
                // �ѷ� ������ ���ĵ� trr�迭�� merge��Ű�� : O(n)
                rint m = n - 1024, i = 0, j = m, k = 0;
                while (i < m && j < n) {
                    if (trr[i] < trr[j]) A[k++] = trr[i++];
                    else A[k++] = trr[j++];
                }
                while (i < m) A[k++] = trr[i++];
                while (j < n) A[k++] = trr[j++];
            }

            for (k = 0; k < n; ++k) data[i + k] = (t << 11) | A[k];  // ���� �迭�� ����
        }
        else    // ������ ũ�Ⱑ 2048�� �ʰ��ϴ� ��� : �̰��� ����(����� ���� ����) ������ �ʴ´�.
            selfCountingSort(0, data + i, n, cnt);     // ���� 11��Ʈ�� ���Ͽ� ��������ϱ�
    }

    // original value�� �����ϱ�.
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 11) & MK;                      // ���� 11bit����
        k = data[i] & MK;                              // ���� 11bit����
        data[i] = ((unsigned int)origin[j] << 16) | origin[k];
    }
}