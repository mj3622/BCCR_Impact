#include "draw_tools.h"
#include "xil_para.h"
// #include "xil_io.h"
#include "..\sources\img_list.h"
unsigned int color, addr;
unsigned char *img16;
unsigned char *img48;

void draw_image(int image_id, int x, int y)
{
    unsigned char *temp_img;
    switch (image_id / 100)
    {
    case 1:
        temp_img = img_list_1[image_id % 100];
        break;
    case 2:
        temp_img = img_list_2[image_id % 100];
        break;
    case 3:
        temp_img = img_list_3[image_id % 100];
        break;
    case 4:
        temp_img = img_list_4[image_id % 100];
        break;
    case 7:
        temp_img = img_list_7[image_id % 100];
        break;
    default:
        return;
    }

    if (is_img_16(image_id) == 1)
    {
        img16 = temp_img;
        draw_16(x, y);
    }
    else
    {
        img48 = temp_img;
        draw_48(x, y);
    }
}

void clear_16(int x, int y)
{
    for (int i = y; i < y + 16; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + (x))), BACK_COLOR);
    for (int i = y; i < y + 16; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + (x + 16))), BACK_COLOR);
    for (int j = x; j < x + 16; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * ((y)*1024 + j)), BACK_COLOR);
    for (int j = x; j < x + 16; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * ((y + 16) * 1024 + j)), BACK_COLOR);
}

void clear_48(int x, int y)
{
    for (int i = y; i < y + 48; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + (x))), BACK_COLOR);
    for (int i = y; i < y + 48; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + (x + 48))), BACK_COLOR);
    for (int j = x; j < x + 48; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * ((y)*1024 + j)), BACK_COLOR);
    for (int j = x; j < x + 48; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * ((y + 48) * 1024 + j)), BACK_COLOR);
}

void draw_background()
{
    for (int i = 120; i < 480; i++)
        for (int j = 0; j < 640; j++)
        {
            Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
        }
}
void clear_screen()
{
    for (int i = 0; i < 480; i++)
        for (int j = 0; j < 640; j++)
            Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
}

void draw_48(int x, int y)
{
    for (int i = y; i < y + 48; i++)
        for (int j = x; j < x + 48; j++)
        {
            addr = (unsigned int)img48 + ((i - y) * 48 + (j - x)) * 4;
            color = Xil_In32(addr);
            Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), color);
        }
}
void draw_16(int x, int y)
{
    for (int i = y; i < y + 16; i++)
        for (int j = x; j < x + 16; j++)
        {
            addr = (unsigned int)img16 + ((i - y) * 16 + (j - x)) * 4;
            color = Xil_In32(addr);
            Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), color);
        }
}

int is_img_16(int tag)
{
    switch (tag)
    {
    case 116:
    case 117:
    case 122:
    case 123:
    case 126:
    case 127:
        return 1;
    }
    if (tag >= 401 && tag < 412)
    {
        return 1;
    }
    return 0;
}
void clear_img(int type, int x, int y)
{
    // type = 1 16*16  type = 0 48*48
    if (type == 1)
    {
        for (int i = y; i < y + 16; i++)
            for (int j = x; j < x + 16; j++)
            {
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
            }
    }
    else
    {
        for (int i = y; i < y + 48; i++)
            for (int j = x; j < x + 48; j++)
            {
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
            }
    }
}

void draw_bsaic_status()
{
    for (int i = 119; i < 120; i++)
        for (int j = 0; j < 640; j++)
            Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), 0x0);
    draw_image(701, 296, 40);
    draw_image(702, 0, 0);
    draw_image(703, 592, 0);

    // hp bar area
    for (int j = 49; j <= 250; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (54 * 1024 + j)), BLACK);
    for (int j = 49; j <= 250; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (61 * 1024 + j)), BLACK);

    for (int j = 389; j <= 590; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (54 * 1024 + j)), BLACK);
    for (int j = 389; j <= 590; j++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (61 * 1024 + j)), BLACK);

    for (int i = 54; i <= 61; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + 49)), BLACK);
    for (int i = 54; i <= 61; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + 250)), BLACK);

    for (int i = 54; i <= 61; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + 389)), BLACK);
    for (int i = 54; i <= 61; i++)
        Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + 590)), BLACK);
}
void draw_players_info(Player *players)
{
    Player p1;
    Player p2;
    if (players[0].playerName == 1)
    {
        p1.hp = players[0].hp;
        p1.skillNum = players[0].skillNum;
        p2.hp = players[1].hp;
        p2.skillNum = players[1].skillNum;
    }
    else
    {
        p2.hp = players[0].hp;
        p2.skillNum = players[0].skillNum;
        p1.hp = players[1].hp;
        p1.skillNum = players[1].skillNum;
    }

    // draw hp bar
    if (p1.hp != pre_players[0].hp || p2.hp != pre_players[1].hp)
    {
        for (int i = 55; i <= 60; i++)
            for (int j = 50 + 2 * p1.hp; j < 250; j++)
            {
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
            }
        for (int i = 55; i <= 60; i++)
            for (int j = 390; j < 590 - 2 * p2.hp; j++)
            {
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
            }

        for (int i = 55; i <= 60; i++)
            for (int j = 50; j < 50 + 2 * p1.hp; j++)
            {
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), RED);
            }
        for (int i = 55; i <= 60; i++)
            for (int j = 590 - 2 * p2.hp; j < 590; j++)
            {
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), RED);
            }
    }
    // draw skills
    if (p1.skillNum != pre_players[0].skillNum || p2.skillNum != players[1].skillNum)
    {

        for (int i = 80; i < 115; i++)
            for (int j = 0; j < 640; j++)
                Xil_Out32(TFT_FRAME_ADDR0 + (4 * (i * 1024 + j)), BACK_COLOR);
        for (int i = 0; i < p1.skillNum; i++)
            draw_image(402, 10 + 40 * i, 80);
        for (int i = 0; i < p2.skillNum; i++)
            draw_image(402, 620 - 40 * i, 80);
    }
    pre_players[0].hp = p1.hp;
    pre_players[1].hp = p2.hp;
    pre_players[0].skillNum = p1.skillNum;
    pre_players[1].skillNum = p2.skillNum;
}