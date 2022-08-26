/*
장재욱(GGUJIBBONG)님 코드
SCORE: 1861504
PASS

entry 단어의 수 ecnt 는 800~900개 이므로 rcnt = 1023 - ecnt개는 여유분이다.
rcnt는 9비트 만을 할당하고 ecnt-rcnt개에는 10비트를 할당하는 전략을 사용할 수 있다.
빈도수를 기준으로 정렬한후 빈도수 높은 단어들(rcnt)에 9bit를 낮은 번호들(ecnt - rcnt)에 10bit를 할당하는 전략
낮은 비트를 먼저 읽어야 하므로 낮은비트순으로 기록하고 읽어올수 있어야 한다.
*/
#define rint register int
#define ll long long
//max 995 len 65535
void set_bit(char* enc_str, int &bit, int &idx, int val, int cnt) {
    while (cnt--) {
        enc_str[idx] |= ((val >> cnt) & 1) << bit;
        if (++bit == 8) {
            idx++; bit = 0;
        }
    }
}

int get_bit(char* enc_str, int &bit, int &idx, int cnt) {
    int key = 0;
    while (cnt--) {
        key = (key << 1) + ((enc_str[idx] >> bit) & 1);
        if (++bit == 8) {
            enc_str[idx++] = 0;
            bit = 0;
        }
    }
    return key;
}

int encode(char* enc_str, char* str, int STRN) {
    rint i, j;
    int len = 0, wr = 1, add = 0;
    int word_idx[18000];
    char tmp[8];
    char dict[996][8];
    int length[996];
    int id[996], pos[996], freq[996] = { 0, };
    ll hash[996];
    for (i = 0; i < STRN; i++) {
        if (str[i] == ' ') {
            ll key = 0;
            for (j = 0; j < len; j++) key = (key << 5) + tmp[j] - 'a' + 1;
            for (j = 1; j < wr && hash[j] != key; j++);
            word_idx[add++] = j;
            freq[j]++;
            if (j == wr) {
                for (j = 0; j < len; j++) dict[wr][j] = tmp[j];
                length[wr] = len;
                id[wr] = wr;
                hash[wr++] = key;
            }
            len = 0;
        }
        else tmp[len++] = str[i];
    }

    for (i = 1; i < wr; i++)
    {
        int Max = freq[id[i]], Maxi = i;
        for (j = i + 1; j < wr; j++)
        {
            if (Max < freq[id[j]])
            {
                Max = freq[id[j]];
                Maxi = j;
            }
        }
        int t = id[i];
        id[i] = id[Maxi];
        id[Maxi] = t;
        pos[id[i]] = i;
    }

    int bit = 0, idx = 0;
    set_bit(enc_str, bit, idx, wr, 10);
    for (i = 1; i < wr; i++) {
        set_bit(enc_str, bit, idx, length[id[i]], 3);
        for (j = 0; j < length[id[i]]; j++) set_bit(enc_str, bit, idx, dict[id[i]][j] - 'a', 5);
    }
    int W = 1024 - wr;
    for (i = 0; i < add; i++) {
        int v = pos[word_idx[i]];
        if (v < W) set_bit(enc_str, bit, idx, v, 9);
        else set_bit(enc_str, bit, idx, v + W, 10);
    }
    set_bit(enc_str, bit, idx, 0, 9);
    return idx;
}
void decode(char* dec_str, char* enc_str, int encn) {
    rint i, j;
    char dict[996][8];
    int length[996];
    int idx = 0, bit = 0, len = 0, pos;
    int wr = get_bit(enc_str, bit, idx, 10);
    for (i = 1; i < wr; i++) {
        length[i] = get_bit(enc_str, bit, idx, 3);
        for (j = 0; j < length[i]; j++) dict[i][j] = get_bit(enc_str, bit, idx, 5) + 'a';
    }
    int W = 1024 - wr;
    while (pos = get_bit(enc_str, bit, idx, 9)) {
        if (pos >= W) pos = (pos << 1) + get_bit(enc_str, bit, idx, 1) - W;
        for (i = 0; i < length[pos]; i++) dec_str[len++] = dict[pos][i];
        dec_str[len++] = ' ';
    }
}
