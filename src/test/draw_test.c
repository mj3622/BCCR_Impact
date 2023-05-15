#include "..\draw\draw.h"
#include <stdlib.h>
Info *info;
int main()
{
    info = init_draw();

    // creat data
    InfoEffect e1 = {108, 40, 140};
    InfoEffect e2 = {129, 80, 240};
    InfoEffect eArr[2] = {e1, e2};

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

    while (1)
    {
        import_info(info, mArr, 2, eArr, 2);
        for (size_t i = 0; i < REFRESH_CNT; i++)
        {
            renew_backgrounds(matrix, 4);
            refresh(*info, i);
        }

        renew_status(NULL);
        mArr[0].x_start = mArr[0].x_dest;
        mArr[0].x_dest = ((mArr[0].x_dest + REFRESH_CNT) > 640) ? 0 : (mArr[0].x_dest + REFRESH_CNT);

        mArr[1].y_start = mArr[1].y_dest;
        mArr[1].y_start = ((mArr[1].y_dest + REFRESH_CNT) > 480) ? 120 : (mArr[1].y_dest + REFRESH_CNT);
    }
}