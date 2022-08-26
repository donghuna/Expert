/*
19_죄인의 숲
BFS
*/
const int LM = 50;
const int DLM = 11;
const int QLM = 50 * 50 * 250 * 4;  // queue size

extern int useDetector(int detectResult[DLM][DLM]);
struct Result { int r, c; };

using LL = unsigned long long;
struct Pair {
    LL first, second;
    bool operator ==(const Pair&t) const {
        return first == t.first && second == t.second;
    }
};

int N, D;
int Map[LM][LM];                // mForest[][] 백업
Pair htab[LM][LM];              // D*D단위로 bitset으로 묶기
int detectResult[DLM][DLM];     // useDetector() 결과
int dr[] = { -1, 0, 1, 0 }, dc[] = { 0, 1, 0, -1 };  // clockwise : 12시, 3시, 6시, 9시

struct Data {
    int r, c, d, g;             // row, column, dir, visit group
}que[QLM];
int fr, re, gcnt;
short visit[LM][LM][10000], vn; // 약 50 MB사용 (2500만 * 2Byte)

Pair getCode(int r, int c) {    // 숲을 bitset으로
    r = (r - D / 2 + N) % N, c = (c - D / 2 + N) % N;  // 시작점으로 변환
    LL acode = 0, bcode = 0;
    int i, j, k = 0;
    for (i = 0; i < D; ++i) for (j = 0; j < D; ++j, ++k) {
        if (k < 61) acode = acode * 2 + (Map[(r + i) % N][(c + j) % N] - 1);
        else bcode = bcode * 2 + +(Map[(r + i) % N][(c + j) % N] - 1);
    }
    return { acode, bcode };
}

Pair getCode() {                // detecting 결과를 bitset으로
    int i, j, k = 0;
    LL acode = 0, bcode = 0;
    for (i = 0; i < D; ++i)for (j = 0; j < D; ++j, ++k) {
        if (k < 61) acode = acode * 2 + detectResult[i][j] - 1;
        else bcode = bcode * 2 + detectResult[i][j] - 1;
    }
    return { acode, bcode };
}

void init(int N, int D, int mForest[LM][LM], int K) {
    ::N = N, ::D = D;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)  // 숲의 상태를 백업
        Map[i][j] = mForest[i][j];

    for (int i = 0; i < N; ++i)for (int j = 0; j < N; ++j) { // (i, j)를 중심으로 D*D영역을 bitset으로
        htab[i][j] = getCode(i, j);
    }
}

Result findCriminal() {
    Result ans = { -1, -1 };
    useDetector(detectResult); // 탐색을 일단 실행 : 죄인이 한 칸 이동한 상태
    Pair code = getCode();     // 죄인이 한칸 이동한 상태를 Pair 타입의 code로 구하기

    fr = re = gcnt = 0;
    ++vn;

    // 최초시점으로 가능한 후보 구하기
    // detectResult[][] (즉 Pair code) 는 죄수가 한 칸 이동한 후의 상태
    for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c) if (code == htab[r][c]) {
        for (int d = 0; d < 4; ++d) {
            int sr = (r - dr[d] + N) % N;      // 죄수의 출발지로 추측되는 지점
            int sc = (c - dc[d] + N) % N;
            visit[sr][sc][gcnt] = vn;          // 출발지를 방문체크
            visit[r][c][gcnt] = vn;            // 두번째 지점을 방문체크
            que[re++] = { r, c, d, gcnt };     // 두번째 지점부터 큐에 추가(detecting 결과이므로)
            gcnt++;
        }
    }

    if (re == 4) return { que[0].r, que[0].c };// 현시점에서 유일하게 결정된 경우

    bool answerFixed = false;                  // 답이 유일하게 결정되는 경우 true로 변경된다.
    while (answerFixed == false && fr < re) {
        useDetector(detectResult);
        code = getCode();

        ans = { -1, -1 };
        int ed = re;                           // 현재 detecting 결과를 반영해야 하는 구간의 끝
        while (fr < ed) {
            Data t = que[fr++];
            for (int i = 0; i < 4; ++i, t.d = (t.d + 1) & 3) { // t로부터 한칸 이동하기
                int nr = (t.r + dr[t.d] + N) % N;         // *****
                int nc = (t.c + dc[t.d] + N) % N;         // *****
                if (visit[nr][nc][t.g] == vn) continue;
                if (htab[nr][nc] == code) {
                    visit[nr][nc][t.g] = vn;
                    que[re++] = { nr, nc, t.d, t.g };
                    if (ans.r < 0) {                      // 답이 정해지지 않은 경우
                        ans = { nr, nc };
                        answerFixed = true;
                    }
                    else if (ans.r != nr || ans.c != nc)  // 답이 유일하지 않은 경우
                        answerFixed = false;
                }
                break;  // 방향전환이 필요없는 경우
            }
        }
    }
    return ans;
}
