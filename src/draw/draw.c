#include "draw.h"
#include "xil_para.h"
#include "draw_tools.h"
#include "xil_io.h"
#include <stdlib.h>

Info pre_info;

Info *init_draw()
{
    clear_screen();
    // active VGA
    Xil_Out32(TFT_0_BASEADDR + TFT_AR_OFFSET, TFT_FRAME_ADDR0);

    pre_info.lengthEffect = 0;
    pre_info.lengthMove = 0;

    Player p1 = {1, 0, NULL, 0, 0};
    Player p2 = {2, 0, NULL, 0, 0};
    pre_players[0] = p1;
    pre_players[1] = p2;

    Info *p = (Info *)malloc(sizeof(Info));
    p->infoeffect = NULL;
    p->infomove = NULL;
    p->lengthEffect = 0;
    p->lengthMove = 0;
    return p;
};
void renew_backgrounds(int **obstacles, int length)
{
    for (int i = 0; i < length; i++)
    {
        draw_image(obstacles[i][0], obstacles[i][1], obstacles[i][2]);
    }
    draw_background();
};
void renew_status(Player players[2])
{
    draw_bsaic_status();
    draw_players_info(players);
};

void import_info(Info *info, InfoMove *infomove, int lengthMove, InfoEffect *infoeffect, int lengthEffect)
{
    pre_info = *info;
    info->lengthEffect = lengthEffect;
    info->lengthMove = lengthMove;
    info->infoeffect = infoeffect;
    info->infomove = infomove;
};
void refresh(Info info, int cnt)
{
    // effect
    for (int j = 0; j < pre_info.lengthEffect; j++)
    {
        int flag = 1;
        for (int i = 0; i < info.lengthEffect; i++)
        {
            if (pre_info.infoeffect[j].tag == info.infoeffect[i].tag &&
                pre_info.infoeffect[j].x == info.infoeffect[i].x &&
                pre_info.infoeffect[j].y == info.infoeffect[i].y)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            clear_img(is_img_16(pre_info.infoeffect[j].tag), pre_info.infoeffect[j].x, pre_info.infoeffect[j].y);
    }
    for (int i = 0; i < info.lengthEffect; i++)
        draw_effect(info.infoeffect[i]);

    // move
    for (int j = 0; j < pre_info.lengthMove; j++)
    {
        int flag = 1;
        for (int i = 0; i < info.lengthMove; i++)
        {
            if (pre_info.infomove[j].tag == info.infomove[i].tag &&
                pre_info.infomove[j].x_dest == info.infomove[i].x_start &&
                pre_info.infomove[j].y_dest == info.infomove[i].y_start)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            clear_img(is_img_16(pre_info.infomove[j].tag), pre_info.infomove[j].x_dest, pre_info.infomove[j].y_dest);
    }

    for (int i = 0; i < info.lengthMove; i++)
        draw_move(info.infomove[i], cnt);
};
void draw_move(InfoMove infoMove, int time)
{
    int x = (infoMove.x_start + (infoMove.x_dest - infoMove.x_start) * time / REFRESH_CNT);
    int y = (infoMove.y_start + (infoMove.y_dest - infoMove.y_start) * time / REFRESH_CNT);
    draw_image(infoMove.tag, x, y);

    // erase the shadow
    if (infoMove.x_dest - infoMove.x_start == REFRESH_CNT ||
        infoMove.x_dest - infoMove.x_start == -REFRESH_CNT ||
        infoMove.y_dest - infoMove.y_start == REFRESH_CNT ||
        infoMove.y_dest - infoMove.y_start == -REFRESH_CNT)
        is_img_16(infoMove.tag) == 1 ? clear_16(x, y) : clear_48(x, y);
    else
        clear_img(infoMove.tag, x, y); // 可能会导致移动中的物体显示时间太短了
};
void draw_effect(InfoEffect infoEffect)
{
    draw_image(infoEffect.tag, infoEffect.x, infoEffect.y);
};

