#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mf.h>
#include <time.h>
#define endl getCursorXY(&x,&y);gotoxy(x-3,y+1);
#define color(f_c,b_c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),f_c | b_c<<4);
#define ps printf("   ");
#define def_color SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
extern const int source,split,wall,normal;     // source: Blue     split:Yellow       wall: Gray      normal:Ajori
extern int x,y,cell_num,walls;
extern const int width,height;

typedef struct{
    int energy;
    int type;
}block;
typedef struct{
int w,h;
}position;
typedef struct{
position p;
int energy;
}cell_inf;
#include "multiplayer.h"

void print_cell(position p){
    if(p.w%2 == 0)
         x=p.w * 7 + 3,y=p.h *4 + 2;
    else
        x=p.w * 7 + 3,y=p.h *4 + 4;
    gotoxy(x,y);
        printf("%c%c",198,181);
}
void print_opp_cell(position p){
    if(p.w%2 == 0)
         x=p.w * 7 + 3,y=p.h *4 + 2;
    else
        x=p.w * 7 + 3,y=p.h *4 + 4;
    gotoxy(x,y);
        printf("%c%c",181,198);
}
int multi_check_block_empty(int h,int w,cell_inf cell){
        if(cell.p.h == h && cell.p.w == w)
            return 1;
    return 0;
}
void multi_move(block arr_map[height][width],position p,int dir,cell_inf *cell,cell_inf opp){
    int q=dir;
    remove_cell(p,arr_map);Sleep(500);
    if(p.w % 2 == 1)

    switch(q){
        case 1:
            if((cell->p).h-1 >= 0 && arr_map[(cell->p).h-1][(cell->p).w].type!=wall && check_block_empty((cell->p).h-1,(cell->p).w,opp)==0)
            (cell->p).h --;
            break;
        case 2:
            if((cell->p).h+1 <height && arr_map[(cell->p).h+1][(cell->p).w].type!=wall && multi_check_block_empty((cell->p).h+1,(cell->p).w,opp)==0)
            (cell->p).h ++;
            break;
        case 3:
            if((cell->p).w+1 <width && arr_map[(cell->p).h][(cell->p).w+1].type!=wall && multi_check_block_empty((cell->p).h,(cell->p).w+1,opp)==0)
            (cell->p).w ++;
            break;
        case 4:
            if((cell->p).w-1 >=0  && arr_map[(cell->p).h][(cell->p).w-1].type!=wall && multi_check_block_empty((cell->p).h,(cell->p).w-1,opp)==0)
            (cell->p).w --;
            break;
        case 5:
            if((cell->p).h+1 <height && (cell->p).w+1 <width  && arr_map[(cell->p).h+1][(cell->p).w+1].type!=wall && multi_check_block_empty((cell->p).h+1,(cell->p).w+1,opp)==0)
            (cell->p).h ++,(cell->p).w ++;
            break;
        case 6:
            if((cell->p).h+1 <height && (cell->p).w-1 >=0  &&  arr_map[(cell->p).h+1][(cell->p).w-1].type!=wall && multi_check_block_empty((cell->p).h+1,(cell->p).w-1,opp)==0)
            (cell->p).h ++,(cell->p).w --;
            break;
    }
    else
        switch(q){
            case 1:
                if((cell->p).h-1 >= 0  &&  arr_map[(cell->p).h-1][(cell->p).w].type!=wall && multi_check_block_empty((cell->p).h-1,(cell->p).w,opp)==0)
                (cell->p).h --;
                break;
            case 2:
                if((cell->p).h+1 <height  &&  arr_map[(cell->p).h+1][(cell->p).w].type!=wall && multi_check_block_empty((cell->p).h+1,(cell->p).w,opp)==0)
                (cell->p).h ++;
                break;
            case 3:
                if((cell->p).h-1 >=0 && (cell->p).w+1 <width  &&  arr_map[(cell->p).h-1][(cell->p).w+1].type!=wall && multi_check_block_empty((cell->p).h-1,(cell->p).w+1,opp)==0)
                (cell->p).h --,(cell->p).w ++;
                break;
            case 4:
                 if((cell->p).h-1 >=0 && (cell->p).w-1 >=0  &&  arr_map[(cell->p).h-1][(cell->p).w-1].type!=wall && multi_check_block_empty((cell->p).h-1,(cell->p).w-1,opp)==0)
                (cell->p).h --,(cell->p).w --;
                break;
            case 5:
                if((cell->p).w+1 <width  &&  arr_map[(cell->p).h][(cell->p).w+1].type!=wall && multi_check_block_empty((cell->p).h,(cell->p).w+1,opp)==0)
                (cell->p).w ++;
                break;
            case 6:
                if((cell->p).w-1 >=0  &&  arr_map[(cell->p).h][(cell->p).w-1].type!=wall && multi_check_block_empty((cell->p).h,(cell->p).w-1,opp)==0)
                (cell->p).w --;
                break;
    }
}

void multi_boost_energy(block arr_map[height][width],cell_inf *cell,position p){
    if(arr_map[p.h][p.w].energy==0)
        return;
    if(arr_map[p.h][p.w].energy>=15){
            if(cell->energy+15>100){
                arr_map[p.h][p.w].energy-=100 - cell->energy;



                cell->energy=100;
            }
            else{
                arr_map[p.h][p.w].energy-=15;
                cell->energy+=15;
            }
    }
    else{
            if(cell->energy+arr_map[p.h][p.w].energy>100){
                arr_map[p.h][p.w].energy -= 100- cell->energy;
               cell->energy=100;
            }
            else{
                cell->energy+=arr_map[p.h][p.w].energy;
                arr_map[p.h][p.w].energy=0;
            }
    }
    print_cell(p);
    show_block_energy(arr_map);
}
void multiplay(){
    /*---------Map load------*/
    FILE *f;
    char *zxc;
    zxc=show_text_box("Enter Map file name(just 'bin' files):");
    f=fopen(zxc,"rb");
    if(f==NULL){
        show_box_end("Cant open file");Sleep(1500);
        return;
    }
    fread(&width,sizeof(int),1,f);
    fread(&height,sizeof(int),1,f);
    block arr_map[height][width];
    map(arr_map,f);
    fclose(f);
    /*--------------------*/

    /*create random position for my cell*/
    struct cell_position my_pos,opp_pos;
     while(1){
        position tu;
        tu=random_pos();
        if(arr_map[tu.h][tu.w].type!=wall){
            my_pos.y=tu.h;
            my_pos.x=tu.w;
            break;
        }
    }
    /*-----------------------*/

    opp_pos=cell_new(my_pos);

    cell_inf my,opp;
    my.p.w=my_pos.x;
    my.p.h=my_pos.y;
    my.energy=0;
    opp.p.w=opp_pos.x;
    opp.p.h=opp_pos.y;
    opp.energy=0;

    print_cell(my.p);
    print_opp_cell(opp.p);

    position p;int d,q,dir;
    system("cls");
    print_map(arr_map);
    while(1){
turn:    clear_text();
    print(3,0,"[1] Select a cell\n[2] Save\n[3] Exit\n");
    int s;
    char qwerty[50];scanf("%s",qwerty);s=atoi(qwerty);
    switch(s){
        case 1:
            clear_text();
            printf("Select one Cell with Coordinate: ");
            char qwerty[50];scanf("%s",qwerty);p.w=atoi(qwerty);
            scanf("%s",qwerty);p.h=atoi(qwerty);
            if(p.h != my_pos.y || p.w != my_pos.x)
                goto turn;
            p.h=height-p.h-1;
            select_cell(p);
            clear_text();
            /*-----show energy----*/
            gotoxy(0,4 * height +2);
            print(12,11,"Cell energy is:%d\n",my.energy);
            /*-------------------*/
            switch(arr_map[p.h][p.w].type){
                case 1:
                    print(3,0,"[1] Move\n");
                    print(3,0,"[2] Boost energy\n");
                    char qwerty[50];scanf("%s",qwerty);q=atoi(qwerty);
                switch(q){
                    case 1:
                        clear_text();
                        show_move_hint();
                        char qwerty[50];scanf("%s",qwerty);dir=atoi(qwerty);
                        multi_move(arr_map,my.p,dir,&my,opp);
                        print_cell(my.p);
                        break;
                    case 2:
                       multi_boost_energy(arr_map,&my,my.p);
                        /*-----show energy----*/
                        gotoxy(0,4 * height +2);
                        print(12,11,"Cell energy is:%d\n",my.energy);
                        Sleep(500);
                        /*-------------------*/
                        remove_show_energy();
                        break;
                    default:
                        print_cell(p);
                }
                    break;
                case 6:
                    print(3,0,"[1] Move\n");
                    print(8,0,"[2] Boost energy\n");
                    scanf("%s",qwerty);q=atoi(qwerty);
                switch(q){
                    case 1:
                        clear_text();
                        show_move_hint();
                        char qwerty[50];scanf("%s",qwerty);dir=atoi(qwerty);
                        multi_move(arr_map,my.p,dir,&my,opp);
                        print_cell(my.p);
                        break;
                    default:
                        print_cell(p);
                }
                    break;

            }
            break;
        case 2:
            clear_text();
            cell_inf cell_arr[2];
            cell_arr[0]=my;
            cell_arr[1]=opp;
            cell_num=2;
            print(3,0,"[1] Text\n[2] Binary\n[3] Both above\n");
            scanf("%s",qwerty);q=atoi(qwerty);
            switch(q){
                case 1:
                    zxc=show_text_box("Enter file name(with format):");
                    save_text(arr_map,cell_arr,zxc);
                    break;
                case 2:
                    zxc=show_text_box("Enter file name(with format):");                    save_bin(arr_map,cell_arr,zxc);
                    break;
                case 3:
                    zxc=show_text_box("Enter file name(binary file):");                    save_bin(arr_map,cell_arr,zxc);
                    zxc=show_text_box("Enter file name(text file):");
                    save_text(arr_map,cell_arr,zxc);

            }
            system("cls");
            print_map(arr_map);
            print_cells(cell_arr);
            goto turn;
            break;

        case 3:
                system("cls");
                return;
            break;
    }
    struct cell_move_data data;
    data.cell_energy=my.energy;
    data.move_direction=dir;
    data=cell_move(data);
    opp.energy=data.cell_energy;
    multi_move(arr_map,opp.p,data.move_direction,&opp,my);
    print_opp_cell(opp.p);
    }
    }
