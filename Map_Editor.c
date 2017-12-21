#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define endl getCursorXY(&x,&y);gotoxy(x-3,y+1);
#define color(f_c,b_c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),f_c | b_c<<4);
#define ps printf("   ");
#define def_color SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
extern const int source,split,wall,normal;     // source: Blue     split:Yellow       wall: Gray      normal:Ajori
extern int x,y,cell_num,walls;
extern const int width,height;


#include "mapeditor.h"
void show_box_end(char* s){
    int i,j;
    x=width * 3 + 2;
    y=height *3 + 2;
    gotoxy(x,y);
    print(12,11,"%c",201);
    for(i=0;i<50;i++)
    print(12,11,"%c",205);
    print(12,11,"%c",187);
    for(i=0;i<7;i++){
        gotoxy(x,++y);
        print(12,11,"%c",186);
        for(j=0;j<50;j++)
            print(12,11," ");
        print(12,11,"%c",186);
    }
    gotoxy(x,y++);
    print(12,11,"%c",200);
    for(i=0;i<50;i++)
    print(12,11,"%c",205);
    print(12,11,"%c",188);
    y-=7;
    gotoxy(x+4,y++);
    print(12,11,s);

}
void save_map(block arr_map[height][width],char arr_map_type[height][width],char *s){
    FILE *f=fopen(s,"wb");
    if(f==NULL){
        gotoxy(0,0);
        print(12,11,"Can`t create file");
        return;
    }
    int i,j;
    fwrite(&width,sizeof(int),1,f);
    fwrite(&height,sizeof(int),1,f);
    for(j=height-1;j>=0;j--)
        for(i=0;i<width;i++){
            fwrite(&arr_map[j][i].energy,sizeof(int),1,f);
            fwrite(&arr_map_type[j][i],sizeof(char),1,f);
        }
}
void color_box(){
    int i;
    for(i=0;i<10;i++){
        printf("%d:  ",i);
        print(0,i,"          \n");
    }
    for(i=10;i<16;i++){
        printf("%d: ",i);
        print(0,i,"          \n");
    }
}
void create_map(){
    int i=0,j,source,split,wall,normal;
enter_width_height:
    system("cls");
    print(2,0,"Please enter Width & Height:\n");
    scanf("%d %d",&width,&height);
    system("cls");
    print(2,0,"Enter the Number of Source block\n");
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    scanf("%d",&source);
    i+=source;
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    system("cls");
    print(2,0,"Enter the Number of Split block\n");
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    scanf("%d",&split);
    i+=split;
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    system("cls");
    print(2,0,"Enter the Number of Wall block\n");
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    scanf("%d",&wall);
    i+=wall;
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    system("cls");
    print(2,0,"Enter the Number of Normal block\n");
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    scanf("%d",&normal);
    i+=normal;
    gotoxy(40,0);
    print(2,0,"Block remaining:%d\n",width * height - i);
    system("cls");
    if( i!= width * height){
        system("cls");
        print(2,0,"Please enter the amounts correctly!!");Sleep(1000);
        i=0;
        goto enter_width_height;
    }
    //----------------------------ENTER POSITIONS----------------------------//
    block arr_map[height][width];
    char arr_map_type[height][width];
    for(i=0;i<height;i++)
        for(j=0;j<width;j++){
            arr_map[i][j].energy=0;
            arr_map[i][j].type=8;
        }
    print_map(arr_map);
    int source_c,wall_c,split_c,normal_c,e;
    clear_text();
    print(0,3,"Now Set the color of blocks.\n");
    color_box();
    print(0,3,"Source:");
    scanf("%d",&source_c);
    print(0,3,"Split:");
    scanf("%d",&split_c);
    print(0,3,"Wall:");
    scanf("%d",&wall_c);
    print(0,3,"Normal:");
    scanf("%d",&normal_c);
    system("cls");
    print_map(arr_map);
    clear_text();
    position p;
    print(0,3,"Now select source blocks\n");
    for(i=0;i<source;i++){
        print(0,3,"%d-th block position: ",i+1);
        scanf("%d%d",&p.h,&p.w);
        print(0,3,"%d-th block energy: ",i+1);
        scanf("%d",&e);
        arr_map[height-1-p.h][p.w].type=source_c;
        arr_map[height-1-p.h][p.w].energy=e;
        arr_map_type[height-1-p.h][p.w]='1';
        print_map(arr_map);
        clear_text();
    }
    print(0,3,"Now select split blocks\n");
    for(i=0;i<source;i++){
        print(0,3,"%d-th block position: ",i+1);
        scanf("%d%d",&p.h,&p.w);
        arr_map[height-1-p.h][p.w].type=split_c;
        arr_map_type[height-1-p.h][p.w]='2';
        print_map(arr_map);
        clear_text();
    }
    print(0,3,"Now select wall blocks\n");
    for(i=0;i<source;i++){
        print(0,3,"%d-th block position: ",i+1);
        scanf("%d%d",&p.h,&p.w);
        arr_map[height-1-p.h][p.w].type=wall_c;
        arr_map_type[height-1-p.h][p.w]='3';
        print_map(arr_map);
        clear_text();
    }
    print(0,3,"Now select normal blocks\n");
    for(i=0;i<source;i++){
        print(0,3,"%d-th block position: ",i+1);
        scanf("%d%d",&p.h,&p.w);
        arr_map[height-1-p.h][p.w].type=normal_c;
        arr_map_type[height-1-p.h][p.w]='4';
        print_map(arr_map);
        clear_text();
    }
    Sleep(500);
    char *s;
    s=show_text_box("Now choose a name for your map:\n");
    save_map(arr_map,arr_map_type,s);
    show_box_end("Congratulation!! you have created a map.");
}

