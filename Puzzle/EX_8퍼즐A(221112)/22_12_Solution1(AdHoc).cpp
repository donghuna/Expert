#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
38_EX8ÆÛÁñA_user_ver01_AdHoc
***    1**    12*    123    123    123    123
*0* => *0* => *0* => *0* => 40* => 4** => 456
***    ***    ***    ***    ***    70*    780
*/
extern void move(int);

#define U move(0)
#define D move(1)
#define L move(2)
#define R move(3)
const int(*puzzle)[3];
void process1() {
    if (puzzle[0][0] == 1) return;
    if (puzzle[0][1] == 1)
        L, U, R, D;
    else if (puzzle[0][2] == 1)
        U, R, D, L, L, U, R, D;
    else if (puzzle[1][0] == 1)
        U, L, D, R;
    else if (puzzle[1][2] == 1)
        R, U, L, D, L, U, R, D;
    else if (puzzle[2][0] == 1)
        L, D, R, U, U, L, D, R;
    else if (puzzle[2][1] == 1)
        D, L, U, R, U, L, D, R;
    else if (puzzle[2][2] == 1)
        D, R, U, L, D, L, U, R, U, L, D, R;
}

void process2() {
    if (puzzle[0][1] == 2) return;
    if (puzzle[0][2] == 2)
        U, R, D, L;
    else if (puzzle[1][0] == 2)
        L, D, R, R, U, U, L, D;
    else if (puzzle[1][2] == 2)
        R, U, L, D;
    else if (puzzle[2][0] == 2)
        D, L, U, R, D, R, U, U, L, D;
    else if (puzzle[2][1] == 2)
        D, R, U, U, L, D;
    else if (puzzle[2][2] == 2)
        R, D, L, U, R, U, L, D;
}

void process3() {
    if (puzzle[0][2] == 3) return;
    if (puzzle[1][0] == 3)
        L, U, R, D, R, U, L, L, D, R;
    else if (puzzle[1][2] == 3)
        L, U, R, R, D, L, U, L, D, R;
    else if (puzzle[2][0] == 3)
        L, D, R, U, L, U, R, D, R, U, L, L, D, R;
    else if (puzzle[2][1] == 3)
        D, L, U, U, R, D, R, U, L, L, D, R;
    else if (puzzle[2][2] == 3)
        R, D, L, U, L, U, R, R, D, L, U, L, D, R;
}

void process4() {
    if (puzzle[1][0] == 4) return;
    if (puzzle[1][2] == 4)
        R, D, L, L, U, R;
    else if (puzzle[2][0] == 4)
        L, D, R, U;
    else if (puzzle[2][1] == 4)
        D, L, U, R;
    else if (puzzle[2][2] == 4)
        D, R, U, L, D, L, U, R;
}

void process7() {
    if (puzzle[2][0] == 7)
        D;
    if (puzzle[1][2] == 7)
        D, L, U, R, R, D, L, U, L, D, R;
    else if (puzzle[2][1] == 7)
        R, D, L, L, U, R, D, R, U, L, L, D, R;
    else if (puzzle[2][2] == 7)
        D, L, U, R, D, R, U, L, L, D, R;
}

void process568() {
    if (puzzle[1][1] == 5) R;
    else if (puzzle[1][2] == 5) U, R, D;
    else if (puzzle[2][2] == 5) R, U, L, D, R;
}

void test(const int puzzle[][3])
{
    ::puzzle = puzzle;
    U, U, L, L, D, R;
    process1();
    process2();
    process3();
    process4();
    process7();
    process568();
}