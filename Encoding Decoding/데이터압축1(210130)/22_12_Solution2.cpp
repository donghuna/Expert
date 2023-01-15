/*
13 : 데이터 압축 1 : 20210131exp_compression
CKW's test
version01: 8*3=24비트를 한번에 읽어온 후, 180도 회전(상하좌우반전)하여 6bit 4개로 나누어 처리하기

[문제 개요]
일차원으로 된 6000x6000 크기의 bitmap을 6x6 단위로 sum 하여
2차원으로 볼때 180도 회전하여
일차원으로 된 1000x1000 FREQ 이미지를 만들고 각 셀에 'J'를 더한후
이를 70% 이하로 압축
복원 수행

[문제 분석]
: test(), compress(), decompress() 결과의 정확성과  실행시간의 빠른순으로 점수가 부여된다.
   따라서 정확성과 함께 신속성이 요구된다.
: build()하는 일은 다음과 같다.
   1. bitMap 6000*6000비트배열을 6*6으로 나누어 각 구역에서 1인 비트를 세어 freq 1000*1000에 기록한다.
   2. freq을 180도 (좌우반전, 상하반전)회전시킨다.
   3. freq의 각 셀에 'J'(74)를 더한다.

[해결 전략]
: test()함수가 하는 일은 build()함수가 하는 일과 같다.  _
  그렇다고 main() 프로세스를 그대로 따르는 것은 시간이 많이 걸린다 조금더 효율적인 구현이 필요하다.
   1. bitMap 6000*6000비트배열을 6*6으로 나누어 각 구역에서 1인 비트를 세어 freq 1000*1000에 기록한다.
   2. freq을 180도 (좌우반전, 상하반전)회전시킨다.
   3. freq의 각 셀에 'J'(74)를 더한다.

:  compress()에서는 freq[]를 70퍼센트 이하의 size로 압축해야 한다.
   1. freq[]의 모든 셀에서 'J'(74)를 빼준다. 그러면 남는수는 0~36이므로 6bit로 표현가능한다.
   _  36인경우 100100(2) 이다.  따라서 8비트를 6비트로 나타낼 수 있으므로 75퍼센트 size로 압축할 수 있다.
   2. 그런데 우리는 70퍼센트 이하의 size로 압축해야 하므로 압축률 75퍼센트로는 부족하다.
   _  어떤 방법을 사용할 수 있을까?
   3. 다루는 수의 종류가 37가지이므로 37진수를 적용해 본다.
      3개의 수를 3자리 37진수로 보는 경우 16bit면 표현이 된다.
      즉 24bit를 16비트로 압축할 수 있다.  이로써 67퍼센트 size로 압축할 수 있게 된다.

: decompress()에서는 compress() 역으로 수행한다.

*/
const int BLM = 4500000;
const int FLM = 1000000;
const int CLM = 666666;
#define rint register int

void test(unsigned char* freq, const unsigned char* bitMap) {
    rint i;   // i는 bitMap 인덱스
    rint j, k, r, c;
    int popcnt[64] = { 0 };   // popcnt[i]: i가 가진 1인 비트의 개수를 저장
    for (i = 1; i < 64; ++i) popcnt[i] = popcnt[i >> 1] + (i & 1);

    for (i = 0; i < FLM; ++i) freq[i] = 'J'; // freq2[] 생성

    for (i = j = 0; i < BLM; i += 3) {
        // 8*3=24비트를 한번에 읽어오기
        k = ((int)bitMap[i] << 16) | ((int)bitMap[i + 1] << 8) | bitMap[i + 2];

        // 180도 회전(상하좌우반전)하여 6bit 4개로 나누어 처리하기

        // 6000 * 6000으로 만들어 행번호, 열번호 구하기 r = (i * 8) / 6000, c = (i * 8) % 6000
        // 180도 회전하기 r = 5999 - r, c = 5999 - c
        // 1000 * 1000으로 만들기 r = r / 6, c = c / 6
        // 1000 * 1000을 일차원형식(1000000)으로 만들기 r * 1000 + c
        r = (5999 - (i * 8) / 6000) / 6 * 1000;
        c = (5999 - (i * 8) % 6000) / 6;

        // 180도 회전되었으므로 역순으로
        freq[r + c] += popcnt[(k >> 18) & 63];
        freq[r + c - 1] += popcnt[(k >> 12) & 63];
        freq[r + c - 2] += popcnt[(k >> 6) & 63];
        freq[r + c - 3] += popcnt[k & 63];
    }
}

void compress(unsigned char* comp, const unsigned char* freq) {
    rint i, j, k;
    unsigned short* cp = (unsigned short*)comp;
    for (i = j = 0; i < FLM - 1; i += 3) {
        // freq[i] 에서 'J'를 빼면 0 ~ 36 범위의 수가 된다.
        // 따라서 37진수로 볼수 있고 37^3 = 50653 으로 2byte로 표현가능하다.
        k = (freq[i] - 'J') * 1369 + (freq[i + 1] - 'J') * 37 + (freq[i + 2] - 'J');

        // k를 2byte로 표현하기
        comp[j++] = k >> 8, comp[j++] = k & 255; // k % 256
    }
    // 마지막 남은 1개는 그대로 담는다.
    comp[j] = freq[i];  // comp[CLM] = freq[FLM - 1]
}

void decompress(unsigned char* freq, const unsigned char* comp) {
    rint i, j, k, v;
    // compress()와 반대로 실행한다.
    for (i = j = 0; j < CLM; j += 2) {
        v = (comp[j] << 8) | comp[j + 1];
        freq[i++] = v / 1369 + 'J';
        freq[i++] = v % 1369 / 37 + 'J';
        freq[i++] = v % 37 + 'J';
    }
    // 마지막 남은 1개는 그대로 담는다.
    freq[i] = comp[j];
}