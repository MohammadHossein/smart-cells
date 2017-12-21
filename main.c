#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//#include <mf.h>
#include <time.h>
#include "mapeditor.h"
#include "game.h"
#define endl getCursorXY(&x,&y);gotoxy(x-3,y+1);
#define color(f_c,b_c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),f_c | b_c<<4);
#define ps printf("   ");
#define def_color SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
/*const int source=1,split=14,wall=8,normal=6;     // source: Blue     split:Yellow       wall: Gray      normal:Ajori
int x,y,cell_num,walls;
const int width,height;
enum select_{selected=13};      //Selected: Pink
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
*/

const int source=1,split=14,wall=8,normal=6;     // source: Blue     split:Yellow       wall: Gray      normal:Ajori
int x,y,cell_num,walls;
const int width,height;
 // H

int main(void)
{
    FILE *f;
    while(1){
    srand(time(NULL));
    system("cls");
    printf("[1] Load\n[2] New Single player game\n[3] New Multi player game\n[4] Map editor\n[5] Exit\n");
    int q;
    char *s;
    char qwerty[50];scanf("%s",qwerty);q=atoi(qwerty);
    system("cls");
    if(q==1){

            s=show_text_box("Enter file name to load:");
            if(strstr(s,".bin")){
                f=fopen(s,"rb");
                if(f==NULL){
                    gotoxy(0,0);
                    show_box_end("Cant open file");Sleep(1500);
                }
                else{
                    cell_inf *cell_arr=(cell_inf*)malloc(sizeof(cell_inf));
                    fread(&width,sizeof(int),1,f);
                    fread(&height,sizeof(int),1,f);
                    block arr_map[height][width];
                    map(arr_map,f);
                    cell_load(cell_arr,f);
                    play(cell_arr,arr_map);
                    free(cell_arr);
                }
                fclose(f);
            }
            else if(strstr(s,".txt")){
                f=fopen(s,"r");
                if(f==NULL){
                    gotoxy(0,0);
                    show_box_end("Cant open file");Sleep(1500);
                }
                else{
                    cell_inf *cell_arr=(cell_inf*)malloc(sizeof(cell_inf));
                    fscanf(f,"Map:\nWidth:%d Height:%d\n",&width,&height);
                    block arr_map[height][width];
                    load_text(arr_map,&cell_arr,s,f);
                    play(cell_arr,arr_map);
                    free(cell_arr);
                }
                fclose(f);
            }
            else{
                    gotoxy(0,0);
                    show_box_end("Can`t open file!!\t:(");Sleep(1500);
            }

    }
    else if(q==2){
            s=show_text_box("Enter Map file name(just 'bin' files):");
            f=fopen(s,"rb");
            if(f==NULL){
                show_box_end("Cant open file");Sleep(1500);

            }
            else{
                cell_inf *cell_arr=(cell_inf*)malloc(sizeof(cell_inf));
                fread(&width,sizeof(int),1,f);
                fread(&height,sizeof(int),1,f);
                block arr_map[height][width];
                map(arr_map,f);
                fclose(f);
                insert_cell(cell_arr,arr_map);
                play(cell_arr,arr_map);
                free(cell_arr);
            }
    }
     else if(q==3){

     }
    else if(q==4)
        create_map();
    else if(q==5){
            system("cls");
            show_box_end("Have a nice day!!\t:-p");
            Sleep(2000);
            exit(1);
    }

    free(s);
    }
    gotoxy(0,60);
    return 0;
}
