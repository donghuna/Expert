/*
14_�����;���2_user_ver02
[�������� �ڷḦ ǥ�� + �밢�� ��ǥ���� FLIP]
    ������������, ������������, (���������� : ������, ����(sr, sc, n)), (����������: ������, ����(sr, sc, n))
    ���α��̰� TH�̻��� ���� ���� ������ ǥ���ϰ�, �������� ���������� ǥ���Ѵ�.

    14bit * 3(��������) * 4(�� �簢���� ���м�) * 10000(�簢����) = 1,680,000bit�̹Ƿ�210,000�� byte�� ��Ÿ�� �� �ִ�.
    ���� �����ְ� 16(short) * 3 * 40000 = 1,920,000 �̰� 240000 �� byte�� ��Ÿ�� �� �ִ�.
    ����ġ�� �־��� 15������ ������ �ʰ������� �����Ͱ� random�����Ǹ� �������� �簢���� ��ġ�� ���
    �����ͼ��� 24���� ���� ���� ���ɼ��� �ſ����.

[�밢�� flip ���� �ڷ�]
Why is iterating 2D array row major faster than column major ?
https://stackoverflow.com/questions/33722520/why-is-iterating-2d-array-row-major-faster-than-column-major
*/
#define rint register int
const int LM = 10000;
const int TH = 40;

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

    // �밢�� flip
    for (i = 0; i < LM; ++i) {
        for (j = i + 1; j < LM; ++j) {
            rint t = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = t;
        }
    }

    // ���η� ���� ����ϱ�
    for (i = 0; i < LM; ++i) {
        for (j = 0; j < LM; ++j) if (map[i][j] == 1) {  // ������ġ
            for (k = j + 1; k < LM && map[i][k] > 0; ++k);
            ap[dataIndex++] = j; // �����
            ap[dataIndex++] = k; // �ೡ
            ap[dataIndex++] = i; // ����ȣ
            j = k;
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