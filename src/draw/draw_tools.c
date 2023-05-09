#include "draw_tools.h"
#include "xil_para.h"
#include "../sources/img_list.h"
unsigned int color, addr;
unsigned char* img16;
unsigned char* img48;
void draw_image(int image_id, int x, int y){
    unsigned char* temp_img;
    switch (image_id / 100)
    {
    case 1: temp_img = img_list_1[image_id%100]; break;
    case 2: temp_img = img_list_2[image_id%100]; break;
    case 3: temp_img = img_list_3[image_id%100]; break;
    case 4: temp_img = img_list_4[image_id%100]; break;
    default: return;
    }

    if(is_img_16(image_id) == 1){
        img16 = temp_img;
        draw_16(x, y);
    }else{
        img48 = temp_img;
        draw_48(x, y);
    }
}

void clear_16(int x, int y){
	for(int i=y; i<y+16; i++) Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+(x))), 0x00808080);
	for(int i=y; i<y+16; i++) Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+(x+16))), 0x00808080);
	for(int j=x; j<x+16; j++) Xil_Out32(TFT_FRAME_ADDR0+(4*((y)*1024+j)), 0x00808080);
	for(int j=x; j<x+16; j++) Xil_Out32(TFT_FRAME_ADDR0+(4*((y+16)*1024+j)), 0x00808080);
}

void clear_48(int x, int y){
	for(int i=y; i<y+48; i++) Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+(x))), 0x00808080);
	for(int i=y; i<y+48; i++) Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+(x+48))), 0x00808080);
	for(int j=x; j<x+48; j++) Xil_Out32(TFT_FRAME_ADDR0+(4*((y)*1024+j)), 0x00808080);
	for(int j=x; j<x+48; j++) Xil_Out32(TFT_FRAME_ADDR0+(4*((y+48)*1024+j)), 0x00808080);
}

void draw_background(){
    for(int i=120; i<480; i++)
		for(int j=0; j<640; j++){
			Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+j)), 0x00808080);
		}
}
void clear_screen(){
    for(int i=0; i<480; i++)
		for(int j=0; j<640; j++)
			Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+j)), 0x00FFFFFF);
}

void draw_48(int x, int y){
	for(int i=y; i<y+48; i++)
		for(int j=x; j<x+48; j++){
			addr = (unsigned int)img48 +((i-y)*48+(j-x))*4;
			color = Xil_In32(addr);
			Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+j)), color);
		}
}
void draw_16(int x, int y){
	for(int i=y; i<y+16; i++)
		for(int j=x; j<x+16; j++){
			addr = (unsigned int)img16 +((i-y)*16+(j-x))*4;
			color = Xil_In32(addr);
			Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+j)), color);
		}
}

int is_img_16(int tag){
    switch(tag){
        case 116:
        case 117:
        case 122:
        case 123:
        case 126:
        case 127:
        return 1;
    }
    if(tag >= 401 && tag < 412){
        return 1;
    }
    return 0;
}
void clear_img(int type, int x, int y){
    //type = 1 16*16  type = 0 48*48
    if(type == 1){
    for(int i=x; i<x+16; i++)
		for(int j=y; j<y+16; j++){
			Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+j)), 0x00E0E0E0);
		}
    }else{
    for(int i=x; i<x+48; i++)
		for(int j=y; j<y+48; j++){
			Xil_Out32(TFT_FRAME_ADDR0+(4*(i*1024+j)), 0x00E0E0E0);
		}
    }
}