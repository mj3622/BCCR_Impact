#include "draw.h"
#include <stdlib.h>
Info* init_draw(){
    Info* p = (Info*)malloc(sizeof(Info));
    p->infoeffect = NULL;
    p->infomove = NULL;
    p->lengthEffect = 0;
    p->lengthMove = 0;
    return p;
};
void renew_backgrounds(int **obstacles, int length){

};
void renew_status(Player players[2]){

};

void import_info(Info *info,InfoMove *infomove, int lengthMove, InfoEffect *infoeffect, int lengthEffect){
    info->lengthEffect = lengthEffect;
    info->lengthMove = lengthMove;
    info->infoeffect = infoeffect;
    info->infomove = infomove;
};
void refresh(Info info, int cnt){

};

void draw_move(InfoMove infoMove){

};
void draw_effect(InfoEffect infoEffect){

};
void draw_image(int image_id, int x, int y){

}
void clear_screen(){
    
}