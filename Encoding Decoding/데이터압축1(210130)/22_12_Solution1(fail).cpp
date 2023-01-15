/*
13_데이터압축1_user_ver01_FAIL
*/
const int LM = 1000000;
#define rint register int

// 2차원좌표(y행, x열)은 1차원좌표로 바꾸면 y행*1000 + x 가 된다. 
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

    // 2차원 좌표를 1차원좌표로 변환하기
    int x2 = x;
    x = x / 8;
    y = y * (6000 / 8);

    // int t = ((bitMap[y + x] >> (7 - (x2 % 8))) & 1);
    if ((bitMap[y + x] & mask) == mask)
        return 1;   // (y행, x열) 비트가 1이라면
    else
        return 0;
}

static void add(unsigned char* freq, int x, int y)
{
    if (((0 <= x) && (x <= 5999)) == 0) return;
    if (((0 <= y) && (y <= 5999)) == 0) return;

    // 6000*6000 을 1000*1000 으로 압축하기
    x = x / 6;          // 열번호
    y = y / 6 * 1000;   // y/6(행번호) * 1000(열크기)

    freq[y + x]++;      // 1차원 좌표로 변경하여 개수 업데이트
}

static void count(unsigned char* freq, const unsigned char* bitMap)
{
    for (int y = 0; y < 6000; y++)
        for (int x = 0; x < 6000; x++)
            if (sample(bitMap, x, y) == 1) add(freq, x, y);
}

static void process1(unsigned char* freq)      // 좌우 flip
{
    for (int y = 0; y < 1000; y++)      // 행좌표
        for (int x = 0; x < 500; x++)   // 열좌표
        {
            unsigned char tmp = freq[y * 1000 + x];           // tmp = f[y][x]
            freq[y * 1000 + x] = freq[y * 1000 + (999 - x)];  // f[y][x] = f[y][999-x]
            freq[y * 1000 + (999 - x)] = tmp;                 // f[y][999-x] = tmp;
        }
}

static void process2(unsigned char* freq)
{
    for (int y = 0; y < 500; y++)             // 상하 flip
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
    rint i = 0;  // freq의 인덱스
    rint j = 0;  // comp의 인덱스
    for (; i < LM - 1; i += 3) {
        // 연속한 3개의 freq[]를 하나의 묶음으로 만들기
        rint code = (freq[i] - 74) * 37 * 37 + (freq[i + 1] - 74) * 37 + (freq[i + 2] - 74);

        // 8비트씩 나누어 저장하기
        comp[j++] = code >> 8;
        comp[j++] = code % 256;
    }
    // 마지막 남은 1개는 그대로 담는다.
    comp[j] = freq[i];
}

void decompress(unsigned char* freq, const unsigned char* comp) {
    rint i = 0; // freq의 인덱스
    rint j = 0; // comp의 인덱스

    // compress와 역순으로 수행한다.
    for (; j < 666666; j += 2) {
        rint code = (comp[j] << 8) | (comp[j + 1]);
        freq[i + 2] = code % 37 + 74, code /= 37;
        freq[i + 1] = code % 37 + 74, code /= 37;
        freq[i] = code + 74;
        i += 3;
    }
    // 마지막 남은 1개는 그대로 담는다.
    freq[i] = comp[j];
}
