/*
39_EX8퍼즐B_user_AdHoc
*/
extern void move(int);

#define rint register int
#define U move(0)
#define D move(1)
#define L move(2)
#define R move(3)

void test(const int srcPuz[][3], const int destPuz[][3])
{
    rint i, type = 0, renumID[9] = { 0 };
    for (type = 0; type < 9; ++type) {  // type 찾기
        if (destPuz[type / 3][type % 3] == 0) break;
    }

    for (i = 0; i < 9; ++i) {
        renumID[destPuz[i / 3][i % 3]] = i <= type ? i < type ? i + 1 : 0 : i;
    }

    // process0
    U, U, L, L, D, R;

    // process1
    if (renumID[srcPuz[0][1]] == 1) L, U, R, D;
    else if (renumID[srcPuz[0][2]] == 1) U, R, D, L, L, U, R, D;
    else if (renumID[srcPuz[1][0]] == 1) U, L, D, R;
    else if (renumID[srcPuz[1][2]] == 1) R, U, L, L, D, R, U, L, D, R;
    else if (renumID[srcPuz[2][0]] == 1) L, D, R, U, U, L, D, R;
    else if (renumID[srcPuz[2][1]] == 1) D, L, U, U, R, D, L, U, R, D;
    else if (renumID[srcPuz[2][2]] == 1) D, R, U, L, D, L, U, U, R, D, L, U, R, D;

    // process2
    if (renumID[srcPuz[0][2]] == 2) U, R, D, L;
    else if (renumID[srcPuz[1][0]] == 2) L, D, R, R, U, U, L, D;
    else if (renumID[srcPuz[1][2]] == 2) R, U, L, D;
    else if (renumID[srcPuz[2][0]] == 2) D, L, U, R, D, R, U, U, L, D;
    else if (renumID[srcPuz[2][1]] == 2) D, R, U, U, L, D;
    else if (renumID[srcPuz[2][2]] == 2) R, D, L, U, R, U, L, D;

    // process3
    if (renumID[srcPuz[1][0]] == 3) L, U, R, D, R, U, L, L, D, R;
    else if (renumID[srcPuz[1][2]] == 3) L, U, R, R, D, L, U, L, D, R;
    else if (renumID[srcPuz[2][0]] == 3) L, D, R, U, L, U, R, D, R, U, L, L, D, R;
    else if (renumID[srcPuz[2][1]] == 3) D, L, U, U, R, D, R, U, L, L, D, R;
    else if (renumID[srcPuz[2][2]] == 3) R, D, L, U, L, U, R, R, D, L, U, L, D, R;

    // process4
    if (renumID[srcPuz[1][2]] == 4) R, D, L, L, U, R;
    else if (renumID[srcPuz[2][0]] == 4) L, D, R, U;
    else if (renumID[srcPuz[2][1]] == 4) D, L, U, R;
    else if (renumID[srcPuz[2][2]] == 4) D, R, U, L, D, L, U, R;

    // process7
    if (renumID[srcPuz[1][2]] == 7) D, L, U, R, R, D, L, U, L, D, R;
    else if (renumID[srcPuz[2][0]] == 7) D;
    else if (renumID[srcPuz[2][1]] == 7) R, D, L, L, U, R, D, R, U, L, L, D, R;
    else if (renumID[srcPuz[2][2]] == 7) D, L, U, R, D, R, U, L, L, D, R;

    // process568
    if (renumID[srcPuz[1][1]] == 5) R;
    else if (renumID[srcPuz[1][2]] == 5) U, R, D;
    else if (renumID[srcPuz[2][1]] == 5) D, R;
    else if (renumID[srcPuz[2][2]] == 5) R, U, L, D, R;


    // destPuz[][]의 유형(type)으로 바꾸기
    if (type == 0) L, L, U, R, R, D, L, U, L, D, R, R, U, L, L, U, R, R, D, L, U, L, D, R, R, U, L, L;
    else if (type == 1) L, L, U, R, R, D, L, U, L, D, R, R, U, L, L, U, R, R, D, L, U, L, D, R, R, U, L;
    else if (type == 2) L, L, U, R, R, D, L, U, L, D, R, R, U, L, L, U, R, R, D, L, U, L, D, R, R, U;
    else if (type == 3) L, L, U, R, R, D, L, U, L, D, R, R, U, L, L;
    else if (type == 4) L, L, U, R, R, D, L, U, L, D, R, R, U, L;
    else if (type == 5) L, L, U, R, R, D, L, U, L, D, R, R, U;
    else if (type == 6) L, L;
    else if (type == 7) L;
}