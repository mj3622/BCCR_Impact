#pragma once
#define REFRESH_CNT 8
typedef struct Player{
    int playerName;     // only 1 & 2
    int hp;             // 0~100 convert to percentage
    int* skills;        // the tag of skill
    int skillNum;       // the num of skill player has
    int selectSkill;    // the select skill, if -1 means no skill setected
} Player;

typedef struct InfoMove{
    int tag;

    // provide the start and destination information
    int x_start, y_start;
    int x_dest, y_dest;
}InfoMove;

typedef struct InfoEffect{
    int tag;

    //the effect area
    int x, y;
}InfoEffect;

typedef struct Info{
    InfoMove *infomove;
    int lengthMove;
    
    InfoEffect *infoeffect;
    int lengthEffect;
} Info;

Info* init_draw();

void renew_backgrounds(int **obstacles, int length);
void renew_status(Player players[2]);

void import_info(Info *info,InfoMove *infomove, int lengthMove, InfoEffect *infoeffect, int lengthEffect);
void refresh(Info info, int cnt);

void draw_move(InfoMove infoMove, int time);
void draw_effect(InfoEffect infoEffect);
