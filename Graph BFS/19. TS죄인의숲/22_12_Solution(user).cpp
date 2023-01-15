/*
24_������ ��_user
BFS
*/
extern int useDetector(int detectResult[DLM][DLM]);

const int LM = 50;
const int DLM = 11;
const int QLM = 50 * 50 * 4 * 250;  // queue size

struct Result { int r, c; };

using LL = unsigned long long;
struct Pair {
    LL first, second;  // 121bit�� 61bit, 60bit�� ������ ����
    bool operator ==(const Pair& t) const {
        return first == t.first && second == t.second;
    }
};

int N, D;
int Map[LM][LM];                 // mForest[][] ���
Pair codeTable[LM][LM];          // D*D������ 64bit���� 2���� ���� ����
int detectResult[DLM][DLM];      // useDetector() ���
int dr[] = { -1, 0, 1, 0 };      // clockwise : 12��, 3��, 6��, 9��
int dc[] = { 0, 1, 0, -1 };

struct Data {
    int r, c, d, g;              // row, column, dir, visit group
}que[QLM];
int fr, re, gcnt;
short visit[LM][LM][10000], vn;  // �� 50 MB��� (2500�� * 2Byte)

Pair getCode(int r, int c) {     // ���� bitset���� : (r, c)�� ������ �ִٰ� �� ��,
    r = (r - D / 2 + N) % N, c = (c - D / 2 + N) % N;  // ���������� ��ȯ
    LL acode = 0, bcode = 0;
    int i, j, k = 0;
    for (i = 0; i < D; ++i) for (j = 0; j < D; ++j, ++k) {
        if (k < 61) acode = acode * 2 + (Map[(r + i) % N][(c + j) % N] - 1);  // Horner's method
        else bcode = bcode * 2 + +(Map[(r + i) % N][(c + j) % N] - 1);        // Horner's method
    }
    return { acode, bcode };
}

Pair getCode() {                 // detecting ����� bitset����
    int i, j, k = 0;
    LL acode = 0, bcode = 0;
    for (i = 0; i < D; ++i)for (j = 0; j < D; ++j, ++k) {
        if (k < 61) acode = acode * 2 + detectResult[i][j] - 1; // Horner's method
        else bcode = bcode * 2 + detectResult[i][j] - 1;        // Horner's method
    }
    return { acode, bcode };
}

void init(int N, int D, int mForest[LM][LM], int K) {
    ::N = N, ::D = D;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)     // ���� ���¸� ���
        Map[i][j] = mForest[i][j];

    for (int i = 0; i < N; ++i)for (int j = 0; j < N; ++j) {    // (i, j)�� �߽����� D*D������ 64bit 2���� ������
        codeTable[i][j] = getCode(i, j);
    }
}

Result findCriminal() {
    Result ans = { -1, -1 };
    useDetector(detectResult); // Ž���� �ϴ� ���� : ������ �� ĭ �̵��� ����
    Pair code = getCode();     // ������ ��ĭ �̵��� ���¸� Pair Ÿ���� code�� ���ϱ�

    // que�� visited[][] �ʱ�ȭ, �˼� ��ȣ �ʱ�ȭ
    fr = re = gcnt = 0;
    ++vn;

    // ���ʽ������� ������ �ĺ� ���ϱ�
    // detectResult[][] (�� Pair code) �� �˼��� �� ĭ �̵��� ���� ����
    for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c) if (code == codeTable[r][c]) {
        for (int d = 0; d < 4; ++d) {
            int sr = (r - dr[d] + N) % N;        // �˼��� ������� �����Ǵ� ����
            int sc = (c - dc[d] + N) % N;
            visit[sr][sc][gcnt] = vn;            // ������� �湮üũ
            visit[r][c][gcnt] = vn;              // �ι�° ������ �湮üũ
            que[re++] = { r, c, d, gcnt };       // �ι�° �������� ť�� �߰�(detecting ����̹Ƿ�)
            gcnt++;
        }
    }

    if (re == 4) return { que[0].r, que[0].c };  // ���������� �����ϰ� ������ ���

    bool answerFixed = false;                    // ���� �����ϰ� �����Ǵ� ��� true�� ����ȴ�.
    while (answerFixed == false && fr < re) {
        useDetector(detectResult);
        code = getCode();

        ans = { -1, -1 };
        int ed = re;                             // ���� detecting ����� �ݿ��ؾ� �ϴ� ������ ��
        while (fr < ed) {
            Data t = que[fr++];
            for (int i = 0; i < 4; ++i, t.d = (t.d + 1) & 3) { // t.d = (t.d + 1) % 4 : �ð�������� 90�� ȸ��
                // t�κ��� ���� �������� ��ĭ �̵��ϱ�
                int nr = (t.r + dr[t.d] + N) % N;         // *****
                int nc = (t.c + dc[t.d] + N) % N;         // *****
                if (visit[nr][nc][t.g] == vn) continue;
                if (codeTable[nr][nc] == code) {
                    visit[nr][nc][t.g] = vn;
                    que[re++] = { nr, nc, t.d, t.g };
                    if (ans.r < 0) {                      // ���� �������� ���� ���
                        ans = { nr, nc };
                        answerFixed = true;
                    }
                    else if (ans.r != nr || ans.c != nc)  // ���� �������� ���� ���
                        answerFixed = false;
                }
                break;                                    // ������ȯ�� �ʿ���� ���
            }
        }
    }
    return ans;
}