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
#include "game.h"

position random_pos(){
    position p;
    p.w=rand()%width;
    p.h=rand()%height;
    return p;
}
int print(int f_c,int b_c,const char *__format,...){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),f_c | b_c<<4);
register int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vprintf( __format, __local_argv );
  __builtin_va_end( __local_argv );
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
  return __retval;
}
int type_diag(char t){
switch(t){
case '1':
    return source;
case '2':
    return split;
case '3':
    return wall;
case '4':
    return normal;
}
}
char type_diag_rev(int t){
switch(t){
case 1:
    return '1';
case 14:
    return '2';
case 6:
    return '4';
case 8:
    return '3';
}
}
//Read map
void map(block map[height][width],FILE *f){
    int i,j;
    char tmp;
    for(j=height-1;j>=0;j--)
        for(i=width-1;i>=0;i--){
            fread(&map[j][i].energy,sizeof(int),1,f);
            fread(&tmp,sizeof(char),1,f);
            map[j][i].type=type_diag(tmp);
            if(tmp=='3')
                walls++;
        }
}
void print_one_block(int color,int x,int y){
    int i;

    for(i=0;i<3;i++){
        print(0,color,"      ");
        gotoxy(x,++y);
    }
   color(0,15)
    for(i=0;i<4;i++){
        gotoxy(x+6,y--);
        printf(" ");
    }
    gotoxy(x,y+4);
    printf("       ");
    def_color
}
void print_map(block arr_map[height][width]){
    int i=0,j=0;
    x=1,y=1;
    gotoxy(x,0);
    for(i=0;i<width;i++){
    printf("  ");
    print(11,0,"%d",i);
    printf("    ");
    }
    for(i=0;i<height;i++){
        gotoxy(0,4*i+3);
        print(11,0,"%d",height-1-i);
    }
    for(j=0;j<width;j++){
        for(i=0;i<height;i++){
            gotoxy(x,y);
            print_one_block(arr_map[i][j].type,x,y);
            y+=4;
        }
        y=1;
        x+=7;
        if(j%2 == 0)
            y+=2;
    }
    show_block_energy(arr_map);
    gotoxy(0,height * 4 + 3);
}
void clear_text(){
    gotoxy(0,height * 4 + 2);
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<25;j++)
            printf("   ");
        printf("\n");
    }
    gotoxy(0,height * 4 + 3);
}
void print_cell(position p){
    if(p.w%2 == 0)
         x=p.w * 7 + 3,y=p.h *4 + 2;
    else
        x=p.w * 7 + 3,y=p.h *4 + 4;
    gotoxy(x,y);
    printf("%c%c",198,181);
}
void remove_cell(position p,block arr_map[height][width]){
    color(0,arr_map[p.h][p.w].type)
    if(p.w%2 == 0)
         x=p.w * 7 + 3,y=p.h *4 + 2;
    else
        x=p.w * 7 + 3,y=p.h *4 + 4;
    gotoxy(x,y);
    printf("  ");
    def_color
}
void cell_add(position p,int energy,cell_inf **cell_arr){
    cell_inf new_cell;
    new_cell.p=p;
    new_cell.energy=energy;
    cell_num++;
    cell_inf_add(new_cell,cell_arr);
}
void select_cell(position p){
    if(p.w%2 == 0)
         x=p.w * 7 + 3,y=p.h *4 + 2;
    else
        x=p.w * 7 + 3,y=p.h *4 + 4;
    gotoxy(x,y);
    print(0,5,"%c%c",198,181);
}
void show_move_hint(){
    gotoxy(0,height * 4 + 2);
    printf("[1] North\n[2] South\n[3] Northeast\n[4] Northwest\n[5] Southeast\n[6] Southwest\n");
}
int find_cell_pos(position pos,cell_inf* cell_arr){
    int i;
    for(i=0;i<cell_num;i++)
        if((cell_arr+i)->p.h == pos.h && (cell_arr+i)->p.w == pos.w)
            return i;
    return -1;
}
int check_block_empty(int h,int w,cell_inf *cell_arr){
    int i;
    for(i=0;i<cell_num;i++){
        if((cell_arr+i)->p.h == h && (cell_arr+i)->p.w == w)
            return 1;
    }
    return 0;
}
void move(cell_inf* cell_arr,block arr_map[height][width],position p,int cell_number,int dir){
    int q=dir,d=cell_number;
    remove_cell(p,arr_map);Sleep(500);
    if(p.w % 2 == 1)

    switch(q){
        case 1:
            if(((cell_arr+d)->p).h-1 >= 0 && arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w,cell_arr)==0)
            ((cell_arr+d)->p).h --;
            break;
        case 2:
            if(((cell_arr+d)->p).h+1 <height && arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w,cell_arr)==0)
            ((cell_arr+d)->p).h ++;
            break;
        case 3:
            if(((cell_arr+d)->p).w+1 <width && arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w+1,cell_arr)==0)
            ((cell_arr+d)->p).w ++;
            break;
        case 4:
            if(((cell_arr+d)->p).w-1 >=0  && arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w-1,cell_arr)==0)
            ((cell_arr+d)->p).w --;
            break;
        case 5:
            if(((cell_arr+d)->p).h+1 <height && ((cell_arr+d)->p).w+1 <width  && arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w+1,cell_arr)==0)
            ((cell_arr+d)->p).h ++,((cell_arr+d)->p).w ++;
            break;
        case 6:
            if(((cell_arr+d)->p).h+1 <height && ((cell_arr+d)->p).w-1 >=0  &&  arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w-1,cell_arr)==0)
            ((cell_arr+d)->p).h ++,((cell_arr+d)->p).w --;
            break;
    }
    else
        switch(q){
            case 1:
                if(((cell_arr+d)->p).h-1 >= 0  &&  arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w,cell_arr)==0)
                ((cell_arr+d)->p).h --;
                break;
            case 2:
                if(((cell_arr+d)->p).h+1 <height  &&  arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w,cell_arr)==0)
                ((cell_arr+d)->p).h ++;
                break;
            case 3:
                if(((cell_arr+d)->p).h-1 >=0 && ((cell_arr+d)->p).w+1 <width  &&  arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w+1,cell_arr)==0)
                ((cell_arr+d)->p).h --,((cell_arr+d)->p).w ++;
                break;
            case 4:
                 if(((cell_arr+d)->p).h-1 >=0 && ((cell_arr+d)->p).w-1 >=0  &&  arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w-1,cell_arr)==0)
                ((cell_arr+d)->p).h --,((cell_arr+d)->p).w --;
                break;
            case 5:
                if(((cell_arr+d)->p).w+1 <width  &&  arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w+1,cell_arr)==0)
                ((cell_arr+d)->p).w ++;
                break;
            case 6:
                if(((cell_arr+d)->p).w-1 >=0  &&  arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w-1,cell_arr)==0)
                ((cell_arr+d)->p).w --;
                break;
    }

    print_cell((cell_arr+d)->p);


}
void cell_inf_add(cell_inf c,cell_inf **cell_arr){
    *cell_arr=(cell_inf*)realloc(*cell_arr,cell_num * sizeof(cell_inf));
    *((*cell_arr)+cell_num-1)=c;
}
void print_cells(cell_inf * cell_arr){
    int i;
    for(i=0;i<cell_num;i++)
        print_cell((cell_arr+i)->p);
}
char* show_text_box(char* s){
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
    gotoxy(x+3,y++);
    print(12,11,s);
    gotoxy(x+3,y);
    char *a=(char*)malloc(40*sizeof(char));
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12 |11<<4);
    char c;i=0;x+=3;
    while((c=getch())!=13 && i<30){
        if(c==8){
            i-=2;
            gotoxy(x-1,y);
            print(12,11," ");
            gotoxy(x-1,y);
            x--;
        }
        if(c!=8)
        print(12,11,"%c",c),x++,a[i]=c;

        i++;
    }
    if(i==30)   Sleep(500);
    a[i]='\0';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
    return a;
}
void play(cell_inf *cell_arr,block arr_map[height][width]){
    char *s;
    system("cls");
    print_map(arr_map);
    show_inf();
    print_cells(cell_arr);
    while(1){
    clear_text();
    print(3,0,"[1] Select a cell\n[2] Save\n[3] Exit\n");
    //"[1] Move\n[2] Split a cell\n[3] Boost energy\n
    int s;
    char qwerty[50];scanf("%s",qwerty);s=atoi(qwerty);
    switch(s){
        case 1:
            clear_text();

            printf("Select one Cell with Coordinate: ");
            position p;int d,q,dir;
            char qwerty[50];scanf("%s",qwerty);p.h=atoi(qwerty);
            scanf("%s",qwerty);p.w=atoi(qwerty);
            p.h=height-p.h-1;
            d=find_cell_pos(p,cell_arr);
            if(d == -1)
                break;
            select_cell(p);
            clear_text();
            show_energy(cell_arr,d);
            switch(arr_map[p.h][p.w].type){
                case 1:
                    print(3,0,"[1] Move\n");
                    print(8,0,"[2] Split a cell\n");
                    print(3,0,"[3] Boost energy\n");
                    char qwerty[50];scanf("%s",qwerty);q=atoi(qwerty);
                switch(q){
                    case 1:
                        clear_text();
                        show_move_hint();
                        char qwerty[50];scanf("%s",qwerty);dir=atoi(qwerty);
                        move(cell_arr,arr_map,p,d,dir);
                        break;
                    case 3:
                        boost_energy(arr_map,cell_arr,d,p);
                        show_energy(cell_arr,d);Sleep(500);
                        remove_show_energy();
                        break;
                    default:
                        print_cell(p);
                }
                    break;
                case 6:
                    print(3,0,"[1] Move\n");
                    print(8,0,"[2] Split a cell\n");
                    print(8,0,"[3] Boost energy\n");
                    scanf("%s",qwerty);q=atoi(qwerty);
                switch(q){
                    case 1:
                        clear_text();
                        show_move_hint();
                        char qwerty[50];scanf("%s",qwerty);dir=atoi(qwerty);
                        move(cell_arr,arr_map,p,d,dir);
                        break;
                    default:
                        print_cell(p);
                }
                    break;
                case 14:
                    print(3,0,"[1] Move\n");
                    print(3,0,"[2] Split a cell\n");
                    print(8,0,"[3] Boost energy\n");
                    scanf("%s",qwerty);q=atoi(qwerty);
                switch(q){
                    case 1:
                        clear_text();
                        show_move_hint();
                        char qwerty[50];scanf("%s",qwerty);dir=atoi(qwerty);
                        move(cell_arr,arr_map,p,d,dir);
                        break;
                    case 2:
                        split_cell(arr_map,cell_arr,d,p);
                        remove_show_energy();
                        break;
                    default:
                        print_cell(p);
                }
                    break;
            }

            break;
        case 2:
            clear_text();
            print(3,0,"[1] Text\n[2] Binary\n[3] Both above\n");
            scanf("%s",qwerty);q=atoi(qwerty);
            switch(q){
                case 1:
                    s=show_text_box("Enter file name(with format):");
                    save_text(arr_map,cell_arr,s);
                    break;
                case 2:
                    s=show_text_box("Enter file name(with format):");                    save_bin(arr_map,cell_arr,s);
                    break;
                case 3:
                    s=show_text_box("Enter file name(binary file):");                    save_bin(arr_map,cell_arr,s);
                    s=show_text_box("Enter file name(text file):");
                    save_text(arr_map,cell_arr,s);

            }
            system("cls");
            print_map(arr_map);
            print_cells(cell_arr);
            break;

        case 3:
                system("cls");
                return;
            break;
    }
    }
}
void insert_cell(cell_inf* cell_arr,block arr_map[height][width]){
first:
    system("cls");
    int n,i,j,k,t=1;
    char qwerty[50];
    position q;
    printf("How many Cells you want to add?\n");
    scanf("%s",qwerty);n=atoi(qwerty);
    if(n<=0 || n>height *width - walls)
        goto first;
    for(i=0;i<n;i++){
            while(t==1){
                q=random_pos();
                if(arr_map[q.h][q.w].type!=wall){
                    if(cell_num == 0)
                        t=0;
                    for(j=0;j<cell_num;j++){
                        if((cell_arr+j)->p.h == q.h && (cell_arr+j)->p.w == q.w){
                            t=1;
                            break;
                        }
                        t=0;
                    }
                }
            }
            t=1;
        cell_add(q,0,&cell_arr);
    }
}
void show_energy(cell_inf * cell_arr,int cell_number){
    gotoxy(0,4 * height +2);
    print(12,11,"Cell energy is:%d\n",(cell_arr+cell_number)->energy);
}
void remove_show_energy(){
    gotoxy(0,4 * height +2);
    printf("                     \n");
}
void show_inf(){
        x=width * 7 + 5;
        y=1;int i;
        gotoxy(x,y);
        for(i=0;i<3;i++){
            print(0,source,"      ");
            gotoxy(x,++y);
        }
        gotoxy(x,y);
        printf("Source");
        x+=7;
        y=1;
        gotoxy(x,y);
        for(i=0;i<3;i++){
            print(0,wall,"      ");
            gotoxy(x,++y);
        }
        gotoxy(x,y);
        printf("Wall");
        x+=7;
        y=1;
        gotoxy(x,y);
        for(i=0;i<3;i++){
            print(0,split,"      ");
            gotoxy(x,++y);
        }
        gotoxy(x,y);
        printf("Split");
        x+=7;
        y=1;
        gotoxy(x,y);
        for(i=0;i<3;i++){
            print(0,normal,"      ");
            gotoxy(x,++y);
        }
        gotoxy(x,y);
        printf("Normal");
}
void show_block_energy(block arr_map[height][width]){
    int i,j,x=1,y=1;
    for(i=0;i<width;i++){
        for(j=0;j<height;j++){
            gotoxy(x,y+2);
            if(arr_map[j][i].type==1)
            print(12,arr_map[j][i].type,"%d ",arr_map[j][i].energy);
            y+=4;
        }
        y=1;
        x+=7;
        if(i%2 == 0)
            y+=2;
    }
}
void split_cell(block arr_map[height][width],cell_inf * cell_arr,int cell_number,position p){
int d=cell_number,dir[6]={0};
//[0] North  [1] South  [2] Northeast  [3] Northwest  [4] Southeast  [5] Southwest
if((cell_arr+d)->energy >= 80){
    if(p.w % 2 == 1){
        if(((cell_arr+d)->p).h-1 >= 0 && arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w,cell_arr)==0)
            dir[0]=1;
        if(((cell_arr+d)->p).h+1 <height && arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w,cell_arr)==0)
            dir[1]=1;
        if(((cell_arr+d)->p).w+1 <width && arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w+1,cell_arr)==0)
            dir[2]=1;
        if(((cell_arr+d)->p).w-1 >=0  && arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w-1,cell_arr)==0)
            dir[3]=1;
        if(((cell_arr+d)->p).h+1 <height && ((cell_arr+d)->p).w+1 <width  && arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w+1,cell_arr)==0)
            dir[4]=1;
        if(((cell_arr+d)->p).h+1 <height && ((cell_arr+d)->p).w-1 >=0  &&  arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w-1,cell_arr)==0)
            dir[5]=1;
    }
    else{
        if(((cell_arr+d)->p).h-1 >= 0  &&  arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w,cell_arr)==0)
            dir[0]=1;
        if(((cell_arr+d)->p).h+1 <height  &&  arr_map[((cell_arr+d)->p).h+1][((cell_arr+d)->p).w].type!=wall && check_block_empty(((cell_arr+d)->p).h+1,((cell_arr+d)->p).w,cell_arr)==0)
            dir[1]=1;
        if(((cell_arr+d)->p).h-1 >=0 && ((cell_arr+d)->p).w+1 <width  &&  arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w+1,cell_arr)==0)
            dir[2]=1;
        if(((cell_arr+d)->p).h-1 >=0 && ((cell_arr+d)->p).w-1 >=0  &&  arr_map[((cell_arr+d)->p).h-1][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h-1,((cell_arr+d)->p).w-1,cell_arr)==0)
            dir[3]=1;
        if(((cell_arr+d)->p).w+1 <width  &&  arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w+1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w+1,cell_arr)==0)
            dir[4]=1;
        if(((cell_arr+d)->p).w-1 >=0  &&  arr_map[((cell_arr+d)->p).h][((cell_arr+d)->p).w-1].type!=wall && check_block_empty(((cell_arr+d)->p).h,((cell_arr+d)->p).w-1,cell_arr)==0)
            dir[5]=1;
    }
    int i,h=1;
    for(i=0;i<6;i++)
    if(dir[i]==1){
        h=0;
        break;
    }
    if(h!=0)
        print_cell(p);
    while(h==0){
        int w=rand()%6;
        if(dir[w]==1){
            move(cell_arr,arr_map,p,d,w+1);
            print_cell(p);
            cell_add(p,40,&cell_arr);
            (cell_arr+d)->energy=40;
            break;
        }
    }

}
else
    print_cell(p);
}
void boost_energy(block arr_map[height][width],cell_inf *cell_arr,int cell_number,position p){
    if(arr_map[p.h][p.w].energy>=15){
            if((cell_arr+cell_number)->energy+15>100){
                arr_map[p.h][p.w].energy-=100-(cell_arr+cell_number)->energy;
                (cell_arr+cell_number)->energy=100;
            }
            else{
                arr_map[p.h][p.w].energy-=15;
                (cell_arr+cell_number)->energy+=15;
            }
    }
    else{
            if((cell_arr+cell_number)->energy+arr_map[p.h][p.w].energy>100){
                arr_map[p.h][p.w].energy -= 100-(cell_arr+cell_number)->energy;
               (cell_arr+cell_number)->energy=100;
            }
            else{
                (cell_arr+cell_number)->energy+=arr_map[p.h][p.w].energy;
                arr_map[p.h][p.w].energy=0;
            }
    }
    print_cell(p);
    show_block_energy(arr_map);
}
void save_bin(block arr_map[height][width],cell_inf *cell_arr,char* s){
    FILE *f=fopen(s,"wb");
    if(f==NULL){
        gotoxy(0,0);
        print(12,11,"Can`t create file");
        return;
    }
    int i,j;
    char c;
    fwrite(&width,sizeof(int),1,f);
    fwrite(&height,sizeof(int),1,f);
    for(j=height-1;j>=0;j--)
        for(i=width-1;i>=0;i-- ){
            fwrite(&arr_map[j][i].energy,sizeof(int),1,f);
            c=type_diag_rev(arr_map[j][i].type);
            fwrite(&c,sizeof(char),1,f);
        }
    fwrite(&cell_num,sizeof(int),1,f);
    fwrite(cell_arr,sizeof(cell_inf),cell_num,f);
    fclose(f);
}
char* type_s(int a){
if(a==source)
    return "Source";
if(a==split)
    return "Split";
if(a==normal)
    return "Normal";
if(a==wall)
    return "Wall";
}
int type_s_rev(char *s){
    if(!strcmp(s,"Source"))
        return source;
    if(!strcmp(s,"Split"))
        return split;
    if(!strcmp(s,"Normal"))
        return normal;
    if(!strcmp(s,"Wall"))
        return wall;

}
void save_text(block arr_map[height][width],cell_inf *cell_arr,char *s){
    FILE *f=fopen(s,"w+");
    if(f==NULL){
        gotoxy(0,0);
        print(12,11,"Can`t create file");
        return;
    }
    int i,j;
    fprintf(f,"Map:\nWidth:%d Height:%d\n",width,height);
    for(j=height-1;j>=0;j--)
        for(i=0;i<width;i++)
            fprintf(f,"(%d,%d):\n\tEnergy:%d\n\tType:%s\n",i,j,arr_map[j][i].energy,type_s(arr_map[j][i].type));
    fprintf(f,"Cell:\nCell number:%d\n",cell_num);
    for(i=0;i<cell_num;i++)
        fprintf(f,"Cell(%d):\n\tEnergy:%d\n\tPosition:(%d,%d)\n",i+1,(cell_arr+i)->energy,(cell_arr+i)->p.w,(cell_arr+i)->p.h);
    fclose(f);
}
void cell_load(cell_inf *cell_arr,FILE* f){
    int i,t;
    cell_inf tmp;
    cell_num=0;
    fread(&t,sizeof(int),1,f);
    for(i=0;i<t;i++){
        fread(&tmp,sizeof(cell_inf),1,f);
        cell_add(tmp.p,tmp.energy,&cell_arr);
    }
}
void load_text(block arr_map[height][width],cell_inf **cell_arr,char *s,FILE* f){
    free(cell_arr);
    *cell_arr=(cell_inf *)malloc(sizeof(cell_inf));
    char *type;
    int i,j,t;
    for(j=height-1;j>=0;j--)
        for(i=width -1;i>=0;i--){
            fscanf(f,"(%d,%d):\n\tEnergy:%d\n\tType:%s\n",&t,&t,&arr_map[j][i].energy,type);
            arr_map[j][i].type=type_s_rev(type);
        }

    int e,h;
    fscanf(f,"Cell:\nCell number:%d\n",&h);
    cell_num=0;
    position p;
    for(i=0;i<h;i++){
        fscanf(f,"Cell(%d):\n\tEnergy:%d\n\tPosition:(%d,%d)\n",&t,&e,&p.w,&p.h);
        cell_add(p,e,cell_arr);
    }
    fclose(f);
}
