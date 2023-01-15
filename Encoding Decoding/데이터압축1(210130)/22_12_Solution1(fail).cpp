/*
13_�����;���1_user_ver01_FAIL
*/
const int LM = 1000000;
#define rint register int

// 2������ǥ(y��, x��)�� 1������ǥ�� �ٲٸ� y��*1000 + x �� �ȴ�. 
static void clear(unsigned char* freq)
{
    for (int y = 0; y < 1000; y++)
        for (int x = 0; x < 1000; x++)
            freq[y * 1000 + x] = 0;
}

static int sample(const unsigned char* bitMap, int x, int y)
{
    unsigned char mask;

    if (((0 <= x) && (x <= 5999)) == 0) return -1;
    if (((0 <= y) && (y <= 5999)) == 0) return -1;

    //mask = 0x80 >> (x % 8);
    mask = 0b10000000 >> (x % 8);

    // 2���� ��ǥ�� 1������ǥ�� ��ȯ�ϱ�
    int x2 = x;
    x = x / 8;
    y = y * (6000 / 8);

    // int t = ((bitMap[y + x] >> (7 - (x2 % 8))) & 1);
    if ((bitMap[y + x] & mask) == mask)
        return 1;   // (y��, x��) ��Ʈ�� 1�̶��
    else
        return 0;
}

static void add(unsigned char* freq, int x, int y)
{
    if (((0 <= x) && (x <= 5999)) == 0) return;
    if (((0 <= y) && (y <= 5999)) == 0) return;

    // 6000*6000 �� 1000*1000 ���� �����ϱ�
    x = x / 6;          // ����ȣ
    y = y / 6 * 1000;   // y/6(���ȣ) * 1000(��ũ��)

    freq[y + x]++;      // 1���� ��ǥ�� �����Ͽ� ���� ������Ʈ
}

static void count(unsigned char* freq, const unsigned char* bitMap)
{
    for (int y = 0; y < 6000; y++)
        for (int x = 0; x < 6000; x++)
            if (sample(bitMap, x, y) == 1) add(freq, x, y);
}

static void process1(unsigned char* freq)      // �¿� flip
{
    for (int y = 0; y < 1000; y++)      // ����ǥ
        for (int x = 0; x < 500; x++)   // ����ǥ
        {
            unsigned char tmp = freq[y * 1000 + x];           // tmp = f[y][x]
            freq[y * 1000 + x] = freq[y * 1000 + (999 - x)];  // f[y][x] = f[y][999-x]
            freq[y * 1000 + (999 - x)] = tmp;                 // f[y][999-x] = tmp;
        }
}

static void process2(unsigned char* freq)
{
    for (int y = 0; y < 500; y++)             // ���� flip
        for (int x = 0; x < 1000; x++)
        {
            unsigned char tmp = freq[y * 1000 + x];           // tmp = f[y][x]
            freq[y * 1000 + x] = freq[(999 - y) * 1000 + x];  // f[y][x] = f[999-y][x]
            freq[(999 - y) * 1000 + x] = tmp;                 // f[999-y][x] = tmp
        }
}

static void process3(unsigned char* freq)
{
    for (int y = 0; y < 1000; y++)
        for (int x = 0; x < 1000; x++)
            freq[y * 1000 + x] += 'J';   //'J' = 74
}

void test(unsigned char* freq, const unsigned char* bitMap) {
    clear(freq);
    count(freq, bitMap);
    process1(freq);
    process2(freq);
    process3(freq);
}

void compress(unsigned char* comp, const unsigned char* freq) {
    rint i = 0;  // freq�� �ε���
    rint j = 0;  // comp�� �ε���
    for (; i < LM - 1; i += 3) {
        // ������ 3���� freq[]�� �ϳ��� �������� �����
        rint code = (freq[i] - 74) * 37 * 37 + (freq[i + 1] - 74) * 37 + (freq[i + 2] - 74);

        // 8��Ʈ�� ������ �����ϱ�
        comp[j++] = code >> 8;
        comp[j++] = code % 256;
    }
    // ������ ���� 1���� �״�� ��´�.
    comp[j] = freq[i];
}

void decompress(unsigned char* freq, const unsigned char* comp) {
    rint i = 0; // freq�� �ε���
    rint j = 0; // comp�� �ε���

    // compress�� �������� �����Ѵ�.
    for (; j < 666666; j += 2) {
        rint code = (comp[j] << 8) | (comp[j + 1]);
        freq[i + 2] = code % 37 + 74, code /= 37;
        freq[i + 1] = code % 37 + 74, code /= 37;
        freq[i] = code + 74;
        i += 3;
    }
    // ������ ���� 1���� �״�� ��´�.
    freq[i] = comp[j];
}
