#pragma once
#include "draw.h"
#define BACK_COLOR 0x00E0E0E0
#define RED 0x00FF0000
#define BLACK 0x0

Player pre_players[2];

void draw_image(int image_id, int x, int y);
void draw_background();
void clear_screen();
void clear_16(int x, int y);
void clear_48(int x, int y);

void draw_48(int x, int y);
void draw_16(int x, int y);

int is_img_16(int tag);
void clear_img(int type, int x, int y);

void draw_bsaic_status();
void draw_players_info(Player *players);