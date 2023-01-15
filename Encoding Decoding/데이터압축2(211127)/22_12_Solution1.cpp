/*
14_�����;���2_user_ver01
*/
#define rint register int
const int LM = 10000;
const int TH = 30;

void comp(char map[10000][10000], char data[150000]) {
    rint i, j, k;
    rint dataIndex = 4;       // data[]�� �ε���, data[0]: ���� ������ ����, data[1]: ��ü ������ ����
    short* ap = (short*)data;  // data�迭�� 2����Ʈ ������ ����ϰڴٴ� �ǹ�.
    int* bp = (int*)data;

    // ���η� ���� ����ϱ�
    for (i = 0; i < LM; ++i) {
        for (j = 0; j < LM; ++j) if (map[i][j] == 1) {
            for (k = j + 1; k < LM && map[i][k] == 1; ++k);
            rint len = k - j + 1;  // ���μ��� ����
            if (len > TH) {
                ap[dataIndex++] = i;  // ���ȣ
                ap[dataIndex++] = j;  // ������
                ap[dataIndex++] = k;  // ����

                // ���η� ������ ǥ���ϱ�: ���η� ���� �����ϰ� �����ϱ� ���Ͽ�
                for (; j < k; ++j) map[i][j] = 2;
            }
            j = k;
        }
    }
    bp[0] = dataIndex;

    // ���η� ���� ����ϱ�
    for (j = 0; j < LM; ++j) {
        for (i = 0; i < LM; ++i) if (map[i][j] == 1) {  // ������ġ
            for (k = i + 1; k < LM && map[k][j] > 0; ++k);
            ap[dataIndex++] = i; // �����
            ap[dataIndex++] = k; // �ೡ
            ap[dataIndex++] = j; // ����ȣ
            i = k;
        }
    }
    bp[1] = dataIndex;
}

void decomp(char map[10000][10000], char data[150000]) {
    rint i, j, k;
    rint dataIndex = 4;       // data[]�� �ε���, data[0]: ���� ������ ����, data[1]: ��ü ������ ����
    short* ap = (short*)data;  // data�迭�� 2����Ʈ ������ ����ϰڴٴ� �ǹ�.
    int* bp = (int*)data;
    rint an = bp[0], bn = bp[1];

    // ���μ� �߱�
    for (; dataIndex < an;) {
        rint i = ap[dataIndex++]; // ���ȣ
        rint j = ap[dataIndex++]; // ������
        rint k = ap[dataIndex++]; // ����
        for (; j < k; ++j) map[i][j] = 1;
    }

    while (dataIndex < bn) {
        rint i = ap[dataIndex++]; // �����
        rint k = ap[dataIndex++]; // �ೡ
        rint j = ap[dataIndex++]; // ����ȣ
        for (; i < k; ++i) map[i][j] = 1;
    }
}