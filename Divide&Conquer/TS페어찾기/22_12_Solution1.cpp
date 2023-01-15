/*** user.cpp ***/
extern bool checkCards(int indexA, int indexB, int diff);

const int LM = 50005;
int NN, listOfDiff[LM][4], listLen[LM];

void playGame(int N)
{
    // 0. init
    for (int i = 0; i < N; ++i) listLen[i] = 0;
    NN = N + N;
    // 1. �����͸� ���̷� �з��ϱ�
    listOfDiff[0][listLen[0]++] = 0;
    int i;
    for (i = 1; i < NN; ++i) {
        int s = 0, e = N - 1, m, ans = 0;
        while (s <= e) {
            m = (s + e) / 2;                 // ������ ����
            bool ret = checkCards(0, i, m);  // ������ ���� m�������� �����
            if (ret) ans = m, e = m - 1;
            else s = m + 1;
        }
        listOfDiff[ans][listLen[ans]++] = i;
    }

    // 2. ¦�� Ȯ���ϱ�

    for (i = 1; listLen[i] == 4; ++i) {
        if (checkCards(listOfDiff[i][0], listOfDiff[i][1], 0))
            checkCards(listOfDiff[i][2], listOfDiff[i][3], 0);
        else if (checkCards(listOfDiff[i][0], listOfDiff[i][2], 0))
            checkCards(listOfDiff[i][1], listOfDiff[i][3], 0);
        else if (checkCards(listOfDiff[i][0], listOfDiff[i][3], 0))
            checkCards(listOfDiff[i][1], listOfDiff[i][2], 0);
    }

    for (; listLen[i] == 2; ++i)
        checkCards(listOfDiff[i][0], listOfDiff[i][1], 0);
}