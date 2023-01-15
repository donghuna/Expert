/*
19_FAST_SORT_user_ver01
 hw_sort()�� ������� �ʴ� version
 score : 2**
1. ���� ���:
    (1) 16bit(0~65535)�� 2048���� ���� ���� ����(�Ϻ� ������ ����)
    (2) 2048���� ���� �̿��Ͽ� 32bit(����16bit, ���� 16bit)���� 1048576���� ����
    (3) ����ڴ� 1M �ѵ��� �����޸𸮸� �̿��Ͽ� �����ؾ� ��.
        ����ڴ� main.cpp �� hw_sort(short data[1024])�Լ��� ����� �� ����.
        [hw_sort]
        �� hw_sort()���ð��� ������ �ݿ����� �ʴ´�.
        �� hw_sort()�� signed_short�� �����Ѵ�.
        �� hw_sort()�� ��Ȯ�� 1024���� �����Ѵ�.
        �� hw_sort()�� �����������θ� �����Ѵ�.
2. ���� �м�:
  (1) ������ ������ 2048���� 16bit������ �̿��Ͽ� ���������.
        ���� 16��Ʈ ������ ���� ���ƾ� 2048���� ���δٸ� ������ �ִ�.
    (2) test()�Լ��� �־����� �����ʹ� unsigned int Ÿ��������
        hw_sort()�� ������ �� �ִ� ������ short Ÿ���̴�.
    (3) 1M������ �����޸𸮸��� ����ϹǷ� �޸� ���� ����� ����ȭ�� �ʿ䰡 �ִ�.
    (4) ������ ���� �ð��� ���Ͽ� üũ�ǹǷ� ������ �����ӵ��� �����ؾ� �Ѵ�.
    (5) � ������ ����Ҽ� ������?
3. solution sketch
   : �پ��� �ع��� �ְ����� hw_sort()�� ������� �ʴ� ����� �����غ���.
  (1) �� 2048���� ������ ��� �̸� �̿��Ͽ� 32bit������ 22bit������ �ٲܼ� �ִ�.
        advanced_hash�� ���� �ִ�.
    (2) 22bit �������� ���� 11bit�� counting sort �Ѵ�.
    (3) ���� 11bit������ ���� 11bit�� counting sort �Ѵ�.
    (4) 11bit������ ������ 32bit������ �ٲ۴�.
    (5) �������⵵ : 65536 * 2 + 2048 * 4 + 2048 * 4 = 131072 + 16384 = 147456
        �ð����⵵ : �ι��� counting sort�� �����ϹǷ� O(1048576)
*/
#define LM (1048576)
#define MASK (65535)
#define rint register int

const unsigned int MSB = 1 << 31;
const int CLM = 1 << 11;
const int MK = CLM - 1;  // mask

extern void hw_sort(short data[1024]);

// ��͹��� self radix sort(right_bit_shift_size, ���� ���� ������, ���� ũ��, ������ �� �迭)
void rSort(int lev, unsigned int* p, int n, int* cnt) {
    rint i, j, k;
    for (i = 0; i < CLM; ++i) cnt[i] = 0;
    for (i = 0; i < n; ++i) cnt[(p[i] >> lev) & MK] ++;
    for (i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1];
    for (i = n - 1; i >= 0; --i) {
        if (p[i] & MSB) p[i] ^= MSB;   // �̹����ĵ� ����� MSB�� �����
        else {
            for (j = --cnt[(p[i] >> lev) & MK]; i != j; j = --cnt[(p[i] >> lev) & MK]) {
                k = p[j];
                p[j] = p[i] | MSB;
                p[i] = k;
            }
        }
    }
    if (lev <= 0) return;
    for (i = j = 0; i < n; i = j) {  // ���� 11bit�� ���� ������ ���Ͽ� ���� 11bit �����ϱ�
        int tg = (p[i] >> lev);      // ���� �ĺ��� : ���� 11bit
        for (; j < n && tg == (p[j] >> lev); ++j); // i: ���� ������ġ, j:���� ��
        rSort(0, p + i, j - i, cnt);  // rSort(right_bit_shift_size, ���� ���� ������, ���� ũ��, ������ �� �迭)
    }
}

void test(unsigned int data[LM]) {
    int origin[2050] = { 0 }, cnt[2050] = { 0 };
    unsigned int entry[65536] = { 0 }; // ���ڼ��� index�� ǥ���Ͽ� renumbering
    rint i, j, k, n = 0;
    // extract entry value
    for (i = 0; i < LM; ++i)  // O(1048576): ������ 16bit�� ǥ���ϱ�
        entry[(data[i] >> 16) & MASK] = entry[data[i] & MASK] = 1;

    // descending order renumbering
    for (i = 65535; i >= 0; --i) if (entry[i]) {
        origin[n] = i;   // 16��Ʈ�� ���Ͽ� �������� ����
        entry[i] = n++;  // �������� ������ ���Ͽ� �������� renumberng
    }

    // 32bit --> 22bit compressing
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 16) & MASK;  // ���� 16��Ʈ �̱�
        k = data[i] & MASK;          // ���� 16��Ʈ �̱�
        data[i] = (entry[j] << 11) | entry[k];  // 22��Ʈ�� �ٲٱ�
    }

    rSort(11, data, LM, cnt);

    // original value�� �����ϱ�.
    for (i = 0; i < LM; ++i) {
        j = (data[i] >> 11) & MK, k = data[i] & MK;
        data[i] = ((unsigned int)origin[j] << 16) | origin[k];
    }
}