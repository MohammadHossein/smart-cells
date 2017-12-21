#define SI 10

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
void show_box_end(char* );
void save_map(block[SI][SI] ,char[SI][SI] ,char *);
void color_box();
void create_map();
