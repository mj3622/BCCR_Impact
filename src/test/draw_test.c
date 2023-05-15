#include "..\draw\draw.h"
#include <stdlib.h>
#include "xil_io.h"
#include "..\draw\xil_para.h"
#include "..\draw\draw_tools.h"
Info *info;
Player *players;
void test_1();
void test_2();
int main()
{
    test_2();
}

void test_1()
{
    info = init_draw();
    clear_screen();
    int cnt = 0;
    // creat data
    InfoEffect e1 = {108, 40, 140};
    InfoEffect e2 = {129, 80, 240};
    InfoEffect es1[2] = {e1, e2};
    InfoEffect *eArr = es1;

    Player p1 = {1, 100, NULL, 3, 0};
    Player p2 = {2, 40, NULL, 3, 0};
    Player ps[2] = {p1, p2};
    players = ps;
    // xil_printf("ps[1].hp = %d\n", ps[1].hp);

    InfoEffect e3 = {402, 300, 300};
    InfoEffect es2[1] = {e3};
    int **matrix;
    matrix = (int **)malloc(sizeof(int *) * 4);
    for (int i = 0; i < 4; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * 3);
    }
    matrix[0][0] = 101;
    matrix[0][1] = 0;
    matrix[0][2] = 120;
    matrix[1][0] = 102;
    matrix[1][1] = 600;
    matrix[1][2] = 120;
    matrix[2][0] = 103;
    matrix[2][1] = 400;
    matrix[2][2] = 320;
    matrix[3][0] = 104;
    matrix[3][1] = 20;
    matrix[3][2] = 400;

    InfoMove m1 = {206, 0, 160, 8, 160};
    InfoMove m2 = {211, 330, 120, 330, 128};
    InfoMove mArr[2] = {m1, m2};
    int el = 2;
    while (1)
    {
        cnt++;
        // xil_printf("get in!\n");
        import_info(info, mArr, 2, eArr, el);
        for (size_t i = 0; i < REFRESH_CNT; i++)
        {
            // renew_backgrounds(matrix,4);
            refresh(*info, i);
            for (int i = 0; i < 10000; i++)
                ;
        }

        mArr[0].x_start = mArr[0].x_dest;
        mArr[0].x_dest = ((mArr[0].x_dest + REFRESH_CNT) > 640) ? 0 : (mArr[0].x_dest + REFRESH_CNT);

        mArr[1].y_start = mArr[1].y_dest;
        mArr[1].y_dest = ((mArr[1].y_dest + REFRESH_CNT) > 480) ? 120 : (mArr[1].y_dest + REFRESH_CNT);
        for (int i = 0; i < 100000; i++)
            ;
        if (cnt > 50)
        {
            eArr = es2;
            el = 1;
        }
        renew_status(players);
        if (cnt % 10 == 0)
        {
            players[0].hp -= 10;
            players[1].hp /= 2;
            if (players[0].hp < 0)
                players[0].hp = 0;
            if (players[1].hp < 0)
                players[1].hp = 0;

            players[0].skillNum = 6;
        }
    }
}
void test_2()
{
    draw_main_page();
    for (int i = 0; i < 100000; i++)
        ;
    draw_gameover(1);
    for (int i = 0; i < 100000; i++)
        ;
    draw_gameover(2);
    for (int i = 0; i < 100000; i++)
        ;
}