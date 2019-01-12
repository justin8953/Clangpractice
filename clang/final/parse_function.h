#ifndef __PARSEFUNC__H__
#define __PARSEFUNC__H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include <math.h>
#define STRSAME(A,B) (strcmp(A,B)==0)
#define NUM(TEXT) atoi(TEXT)
#define MAX_SIZE 100
#define MAXTOKEN 10
#define GROWFACT 0.7

enum bool {False, True};
typedef enum bool bool;

struct position{
   float x;
   float y; 
   int degree;
};
typedef struct position Pos;

struct tokenEle{
   char *token;
};
typedef struct tokenEle Ele;

struct var{
   char *name;
   int value;
   struct var *left;
   struct var *right;
};
typedef struct var Var;

struct stk
{
   float data[MAX_SIZE];
   int top;
};
typedef struct stk STK;

struct colour{
   int R;
   int G;
   int B;
   int color_default;
};
typedef struct colour Colour;

struct program{
   Ele *tokenlist;
   Var *variable ;
   Colour * colour_display;
   Pos *loc;
   STK *s; 
   int cw;
   int sz;
};
typedef struct program Prog;

Prog *intialise_program(int size);
Pos * intialise_location(void);
void program_Start(Prog *p,SDL_Simplewin *sw);
void Code (Prog *p,SDL_Simplewin *sw);
void Statement(Prog *p,SDL_Simplewin *sw);


void check_for_loop(Prog *p,SDL_Simplewin *sw);
void check_Instruction(Prog *p,SDL_Simplewin *sw);
void set_var(Prog *p);
int check_Varnum(Prog *p);
int load_varnum(Prog *p);
int get_start_num(Prog *p);
int get_End_num(Prog *p);
Var *load_Var(Prog *p);


float assign_value(Prog *p);

Var *intialise_var (char *v);
void Declare_Var(Var *p, char *v);
Var *Var_isin(Var *p, char *v);
void program_free(Prog **s);
void var_free(Var **s);
void draw_line (Prog *p, int x_start, int y_start, int x_end, int y_end, SDL_Simplewin *sw);
void set_color(Prog *p,SDL_Simplewin *sw);
void Reset_loc(Prog *p);
void delay (Prog *p);

void grow (Prog *s,int size);
void old_program_free(Prog **s);

float Pop (Prog *p);
void Push (Prog *p, float num);
void postfix_cal (Prog *p);

#endif
