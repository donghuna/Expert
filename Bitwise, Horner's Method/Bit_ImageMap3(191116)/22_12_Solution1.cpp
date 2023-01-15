/*
12_Bit_image3_user_ver01

[문제 개요]
소문자로 구성된 단어(길이1~7)들로 주어진 길이 65535의 문장(공백으로 구분)이 주어질때,
encode(압축), decode(복원) 하는 문제.
(1) 압축한 크기가 작을수록 좋은 점수.
(2) 실행속도가 빠를수록 좋은 점수.

[문제 분석]
(1) - 등장하는 단어의 종류는 최대 1024(평균 800 ~900)개,
    - 한 문장에 등장하는 단어의 개수는 평균 13107개 내외(65535 / 5(단어의 평균길이4 + 공백1) = 13107)
    - 이 특징들을 이용할 수 있을까 ?
(2) 단어의 빈도수를 이용한 허프만코드 ???
(3) 한문자를 5bit로 줄여표현하기 : 65536 * 5 / 8 = 40960btye를 사용하므로 100개 TC에 대한 점수는 400만여 점이다.
    주어진 메모리 안에서 해결가능하나 좋은 점수를 받기 힘들다.
    적어도 20000점 미만으로 해결할 수 있어야 한다.

[해법 연구 : ]
등장 dicWords단어가 최대 1024라는 점에 착안,
등장하는 단어는 단어장을 만들어 저장하고
문장의 단어는 단어장의 단어번호로 표현하면 하나의 단어를 10bit로 표현할 수 있다.

(1) encode :
    사전단어수 : 문장단어수 : 사전 단어 기록 : 문장 단어 기록
    10bit : 14bit : (3bit(단어길이) + 5bit(한문자) * 4(단어길이평균)) * 1000(사전단어수) : 10bit * 문장단어수
    = (10) + (14) + (23 * 1000) + (10 * 13107) = 24 + 23000 + 131070 = 154094 bit
    * 하나의 TC당 점수 : 154094 / 8 = 19,261.75점
    (2) decode : endcode의 내용을(1)의 역으로 풀어 str완성.
    (3) 점수 예상치 : 19,261.75 * 100 + 2000(실행시간) = 약 1,926,175 예상
    (4) 고찰
    : 단어를 길이순으로 정렬하여 저장한다면 단어별 길이 3bit를 절약할 수 있다.

    SEED:5, SCORE : 193**** (실제 생성된 단어수가 약 13,300 전후이기 때문에 예상치를 넘는 결과가 나온다.)

(2) 정보를 비트단위로 저장할 수 있어야 한다.
    다음과 같은 함수를 사용할 수 있다.

    void write(char*str, int idx, int val) {
        *((UI*)(str + (idx / 8))) += val << (idx % 8);
    }
    int read(char*str, int idx, int bitLen) {
        UI tg = *((UI*)(str + (idx / 8))), mask = (1 << bitLen) - 1;
        return (tg >> (idx % 8)) & mask;
    }
*/
#define rint register int
using UI = unsigned int;
//using ULL = unsigned long long;
//void writeULL(char*str, int idx, ULL val) {
//  *((ULL*)(str + (idx >> 3))) |= val << (idx & 7);
//}
//ULL readULL(char*str, int idx, int bitLen) {
//  ULL tg = *((ULL*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
//  return (tg >> (idx & 7)) & mask;
//}

void write(char* str, int idx, int val) {
    *((UI*)(str + (idx >> 3))) |= val << (idx & 7);
}
int read(char* str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx & 7)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    // 1. dicWords 단어 고르기 & 문장의 단어를 번호로 치환하기
    long long dicWords[1025]; // dicWords 단어들 : 단어(최대35bit)를 하나의 정수로 저장
    int dwLen[1025];          // 각 단어의 길이
    int dcnt = 0;             // dicWords 단어 수(고유한 단어의 갯수)

    int sentenceWords[16384]; // 문장의 단어를 dicWords단어 번호로 치환하여 저장
    int swCnt = 0;            // 문장의 단어수

    // str[]을 parsing
    long long word = 0;
    rint i, j, wlen = 0;
    for (i = 0; str[i]; ++i) { // 문장을 순회하면서
        if (str[i] == ' ') {   // 단어라면
            for (j = 0; j < dcnt && dicWords[j] != word; ++j); // linear search
            if (j == dcnt) {   // 못찾은 경우 : word는 새로운 단어이므로 등록하기
                dicWords[dcnt] = word;
                dwLen[dcnt++] = wlen;
            }
            sentenceWords[swCnt++] = j;  // 문장의 swCnt번째단어는 단어장의 j번 단어
            word = 0, wlen = 0;// 새로운 단어를 저장하기 위하여 초기화
        }
        else {                 // 단어가 계속되는 중이라면
            //word = (word << 5) + str[i] - 96;  // Horner's method
            word = word * 32 + str[i] - 96;      // Horner's method : 32진수로 보기
            wlen++;
        }
    }

    // 2. enc_str에 dicWords단어수, 문장의 단어수 기록하기
    rint idx = 0;
    write(enc_str, idx, dcnt), idx += 10;   // 1024    dicWords단어수기록
    write(enc_str, idx, swCnt), idx += 14;  // 16384   문장의 단어수 기록

    // 3. enc_str에 dicWords단어 기록하기
    for (i = 0; i < dcnt; ++i) {
        long long w = dicWords[i];
        write(enc_str, idx, dwLen[i]), idx += 3;      // 단어의 길이 기록
        for (j = 0; j < dwLen[i]; ++j) {              // 단어 기록
            write(enc_str, idx, w % 32), idx += 5;    // 문자단위로 기록 : 마지막 문자부터 역순으로 기록됨
            w /= 32;                                  // 다음문자를 위하여
        }
    }

    // 4. enc_str에 문장의 단어 번호 기록하기
    for (i = 0; i < swCnt; ++i) {
        write(enc_str, idx, sentenceWords[i]), idx += 10;
    }

    int sentenceLength = (idx + 7) / 8;           // 올림식
    return sentenceLength;                        // 압축된 길이 반환
}

void decode(char* dec_str, char* enc_str, int encn) {
    // 1. dicWords 단어수 구하기, 문장의 단어수 구하기
    rint idx = 0;
    int dcnt = read(enc_str, idx, 10); idx += 10;    // dicWords 단어수
    int swCnt = read(enc_str, idx, 14); idx += 14;   // 문장 단어수

    // 2. dicWords 단어 복원하여 기록하기
    char dicWords[1025][8] = { 0 };
    rint i, j, t = 0;
    for (i = 0; i < dcnt; ++i) {
        int len = read(enc_str, idx, 3); idx += 3;   // 길이 구하기
        for (j = len - 1; j >= 0; --j) {             // 낮은 자리부터 저장하였으므로 역순으로 
            int k = read(enc_str, idx, 5); idx += 5; // 단어 복원하기
            dicWords[i][j] = k + 96;
        }
    }

    // 3. dec_str에 문장 복원하기
    for (i = 0; i < swCnt; ++i) {
        int k = read(enc_str, idx, 10); idx += 10;
        for (j = 0; dicWords[k][j]; ++j)
            dec_str[t++] = dicWords[k][j];
        dec_str[t++] = ' ';
    }
}