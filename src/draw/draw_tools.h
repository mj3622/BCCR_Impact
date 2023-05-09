#pragma once

void draw_image(int image_id, int x, int y);
void draw_background();
void clear_screen();
void clear_16(int x, int y);
void clear_48(int x, int y);

void draw_48(int x, int y);
void draw_16(int x, int y);

int is_img_16(int tag);
void clear_img(int type, int x, int y);
