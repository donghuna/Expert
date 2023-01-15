/*
22_EX메모장_user_ver03_journaling
*/
#define rint register int

const int LM = 110000;
const int HLM = 1 << 21;  // 2097152

int scnt;
char strDB[LM][1024];     // 100MB

int target;              // insert시 사용할 문장 번호
int hisLen;               // 명령 개수
int cmd[HLM];             // 명령 번호 append:0, insert:1, erase:-1
int memoLine[HLM];        // 함수의 매개변수로 주어진 삽입,삭제,추가한 문장의 index
int srcLine[HLM];         // insert시 사용한 문장 번호를 기록
int memoLen;              // 문장 개수: 100000개인지 확인하는 용도

void strcpy(char* dest, char* src) {
    for (rint i = 0; dest[i] = src[i]; ++i) {}
}

void append(char* str) {
    strcpy(strDB[scnt], str);
    cmd[++hisLen] = 0;         // append 명령 번호
    memoLine[hisLen] = scnt++; // 문장이 저장된 index
    ++memoLen;                 // 문장 개수 증가
}

void insert(int line, char* str) {
    cmd[++hisLen] = 1;           // insert 명령 번호
    memoLine[hisLen] = line;     // 명령으로 주어진 문장 삽입 위치 백업
    srcLine[hisLen] = target;   // linestring(int line) index
    ++memoLen;                   // 문장 개수 증가
}

void erase(int line) {
    cmd[++hisLen] = -1;          // erase 명령 번호
    memoLine[hisLen] = line;     // 명령으로 주어진 문장 삭제 위치 백업
    --memoLen;                   // 문장 개수 감소
}

char* linestring(int line) {
    if (memoLen < 100000)        // 10만 이전까지
        return strDB[target = line]; // line을 삭제된적이 없는 경우라 가정

    // 마지막에 한번만 실행
    for (rint i = hisLen; i > 1000; --i) {
        if (cmd[i] > 0) {          // insert의 경우
            if (memoLine[i] == line)
                line = srcLine[i]; // 원본 문장 번호
            else if (memoLine[i] < line)  // 삽입위치가 더 앞쪽이라면
                line--;            // 삽입한 문장을 제거
        }
        else {                     // append, erase
            if (memoLine[i] <= line)
                line -= cmd[i];    // 삭제한 경우 1증가, 추가의 경우 변화 없음
        }
    }
    return strDB[line];
}