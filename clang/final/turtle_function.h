#ifndef __TESTTURTLEFUNC__H__
#define __TESTTURTLEFUNC__H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include <math.h>

#define STRSAME(A,B) (strcmp(A,B)==0)
/* Check IS NUM OR STRING */
#define ISVARNUM(TEXT) (TONUM(TEXT)?NUM:VAR)

/* TRANSFER STRING TO NUM */
#define TONUM(TEXT) atoi(TEXT)
#define FLOATNUM(TEXT) atof(TEXT)


/*STRING LENGTH*/
#define LEN(STR) (int)strlen(STR)
/*DOT IS IN*/
#define DOISIN(A) (A == '.')

/*MAX STACK SIZE*/
#define MAX_SIZE 100
/*MAX WORD SIZE*/
#define MAXWORD_SIZE 100

/*MAX TOKEN LIST SIZE*/
#define MAXTOKEN 10
/*MAX TOKEN LIST SIZE IN LIBRARY */
#define MAX_LIBTOKENSIZE 10

/*ERROR */
#define ERROR(STR) {fprintf(stderr, "Fatal Error %s occured in %s, line %d \n", STR, __FILE__, __LINE__);}

/*DELAY TIME 1ms */
#define MILLISECONDDELAY 1

/* FOR CALCULATE RADIAN */
#define ARC 180.0

/* GROWING NUMBER */
#define GROWNUM 2
/* GROWING CONDITION */
#define GROWFACT 0.7

/* FOR FILE NAME PROCESSING */
#define TXT ".txt"

/* FOR SDL GROUP CIRCEL SET*/
#define MAXCIRCLESET 10

/* FOR MAXIMUM CIRCLE RADIUS */
#define MAXRADIUS 30

enum bool {False, True};
typedef enum bool bool;

/* INSTRUCTION */
enum INSTR {NoInstr, GOFD, GORT, GOLT, GODO, GOSET, GODEF, GORESET, GODELAY, GOSTART, GOCIRCLE, GOMULTICIRCLE, GOCOLOR, GOTEXT, GOEND, GOCLEAN};
typedef enum INSTR INSTR;

enum VARNUM {VAR, NUM};
typedef enum VARNUM VARNUM;

/* POLISH AND VARNUM */
enum POLISH {INVALID, DOVAR, DONUM, DOPLUS, DOMULTI, DODEVIDE, DOSUB, CLOSEPARENTHESE, SEMIEND, COMMAEND};
typedef enum POLISH POLISH;


/* FOR SDL SCREEN POSITION AND DEGREE */
struct position{
   float x;
   float y; 
   int degree;
};
typedef struct position Pos;

/* TOKEN */
struct tokenEle{
   char *token;
};
typedef struct tokenEle Ele;

/* VARIABLE TABLE BY USING BST TABLE */
struct var{
   char *name;
   int value;
   struct var *left;
   struct var *right;
};
typedef struct var Var;

/* DO REVERSE POLISH NOTATION BY USING STACK */

struct stk
{
   float data[MAX_SIZE];
   int top;
};
typedef struct stk STK;

/* FOR SDL COLOR -- IF COLOR DEFAULT IS 0, SET COLOR
   TO RANDOM.
*/
struct colour{
   int R;
   int G;
   int B;
   int color_default;
};
typedef struct colour Colour;

/* LIBRARY TABLE BY USING BST TABLE 
   WITH TOKEN LIST,  TOKEN SIZE, TOKEN COUNTER 
   AND LIBRARY NAME
*/
struct Library {
   char *name;
   Ele *lib_tokenlist;
   int lib_cw;
   int token_sz;
   struct Library *left;
   struct Library *right;
};
typedef struct Library Lib;

/* PROGRAM STRUCTURE BY USING LINKED LIST 
   WITH TOKEN LIST, VARIABLE TABLE, LIBRARY NAME, 
   TOKEN SIZE, TOKEN COUNTER, SDL COLOR, POSITION, 
   AND STACK FOR RPN
*/
struct program{
   Ele *tokenlist;
   Var *variable ;
   Lib *lib;
   Colour * colour_display;
   Pos *loc;
   STK *s; 
   struct program *next; 
   int cw;
   int sz;
};
typedef struct program Prog;



/*---- INTIALISE FUNCTION ----*/

Prog *intialise_program(int size);
Ele * intialise_tokenlist (int size);
Var *intialise_var (char *v);
/* INTIALISE THE STACK FOR RPN*/
STK * intialise_STK ();
Pos * intialise_location(void);



/*---- EXTENSION IN INTIALISE FUNCTION ----*/
Colour * intialise_colour ();
Lib *intialise_lib(char *v, int size);

/* DYNAMTIC MEMORY FOR PROGRAM*/
void Prog_grow (Prog *s,int size);
void var_copy(Var *Old_table, Var *New_table);

/*----EXTENSION IN DYNAMTIC MEMORY FOR LIBRARY ----*/
void lib_grow (Lib *s, int size);

/*---- FREE FUNCTION ----*/
void program_free(Prog **s);
void var_free(Var **s);

/*---- EXTEINSION IN LIBRARY FREE FUNCTION ----*/
void lib_element_free(Lib **q);
void lib_free(Lib **s);

/*---- STACK FUNCTION ----*/

/* FOR STACK PUSH AND POP */
float Pop (Prog *p);
void Push (Prog *p, float num);

/* ---- VARNUM ISVARNUM (char *s) ----*/
bool IS_NUM(Prog *p);

/*---- PARSER TESTING---- */

/* START FUNCTION */
void parserstart(Prog *p);

/* CHECK TO END (BY CHECKING "") ELSE DO INSTRUCTION */
void parser_code(Prog *p);

/* CHECK VARIABLE NOT USING THE WORD IN GRAMMAR*/
bool invalid_token (Prog *p);

/* FOR INSTURCTION*/
INSTR instruction (char *s);
void check_instruction(Prog *p);

/* FOR DO LOOP FUNCTION */
bool do_loop (Prog *p);
bool do_loop_start (Prog *p);
bool do_loop_end (Prog *p);

/* FOR CHECK SET FUNCTION*/
bool do_set (Prog *p);
/* FOR REVERSE POLISH NOTATION */
POLISH check_polish(char *s);
void do_polish(Prog *p);

/*--- EXTENSION IN PARSER TESTING ----*/
/* COLOR FUNCTION */
bool do_color(Prog *p);
bool color_R (Prog *p);
bool color_G (Prog *p);
bool color_B (Prog *p);
/* RESET POSITION AND DEGREE */
bool do_reset(Prog *p);
bool reset_x (Prog *p);
bool reset_y (Prog *p);
bool reset_degree (Prog *p);

/* DO FUNCTION */
void do_function(Prog *p);
bool do_assign_local_value (Prog *p);


/*---- INTERPRETER TESTING ----*/

/* START FUNCTION */
void Block_start(Prog *p,SDL_Simplewin *sw);

/* CHECK TO END (BY CHECKING "") ELSE DO INSTRUCTION */
void Code (Prog *p,SDL_Simplewin *sw);

/* FOR INSTURCTION*/
void check_instruct(Prog *p, SDL_Simplewin *sw);

/* DO FOWORAD, LEFT TURN, AND RIGHT TURN*/
void go_FD (Prog *p,SDL_Simplewin *sw);
void go_RT (Prog *p);
void go_LT (Prog *p);


/* FOR DO LOOP */
void go_for_loop (Prog *p, SDL_Simplewin *sw);
void check_for_loop(Prog *p,SDL_Simplewin *sw);
int get_start_num(Prog *p);
int get_End_num(Prog *p);

/* INSERT NEW VARIABLE */
void Declare_Var(Var *p, char *v);
/* CHECK VARIABLE IS IN */
Var *Var_isin(Var *p, char *v);

/* SET NEW VARIABLE*/
void go_set(Prog *p);

/* DO REVERSE POLISH NOTATION */
bool do_Reverse_polish(Prog *p);

/* POINT TO VARIABLE */
Var *load_Var(Prog *p);

/* GET NUMBER */
int load_varnum(Prog *p);


/* FOR SDL DRAWING */
void draw_line (Prog *p, int x_start, int y_start, int x_end, int y_end, SDL_Simplewin *sw);
float x_end_postition(float x, int degree, int r);
float y_end_postition(float y, int degree, int r);

/*---- EXTENSION IN LIBRARY ----*/
void parser_lib(Prog *p);

/* FOR LOAD FILE NAME STRUCTUREING PROCESSING */
char * string_process (char *v);

/* ADD LIBRARY NAME INTO LIBRARY TABLE */
void insert_lib_name(Lib *p, char *v);
Lib *Load_lib_into_prog (Prog *p);


/* CHECK LIBRARY IS IN*/
Lib *Lib_isin(Lib *p, char *v);

/* LOAD FILE INTO LIBRARY TOKEN LIST*/
void Load_tokenlist_into_lib (Lib *p, char *v);

/* FIND FUNCTION IS IN LIBRARY*/
bool find_function (char *v, Lib *p);

/* FOR DO FUNCTION STRING PROCESSING */
int dot_isin (char *v);
void test_strip_word ();

char *get_lib_name (char *v);
char *get_function_name (char *v);

/* DOING FUNCTION */
void load_function (Prog *p,SDL_Simplewin *sw);

/* COPY TOKENLIST INTO NEXT PROGRAM TOKENLIST */
void copy_functon (Prog *s, Lib *tmp,SDL_Simplewin *sw);

/* FOR STORING FUNCTION INPUT */
void get_open_parenthese (Prog *p, Prog *s);
void declare_local_var (Lib *p, Prog *s);
float assign_local_value (Prog *p);


/* ---- EXTENSION IN SET COLOR ----- */
void go_COLOR (Prog *p,SDL_Simplewin *sw );

/* ---- EXTENSION IN DRAW CIRCLE AND CIRCLE SETS ----  */
int go_CIRECLE_radius (Prog *p);
void draw_circle (Prog *p, int radius, SDL_Simplewin *sw);
int go_num_circles (Prog *p);
void random_circle (int num , SDL_Simplewin * sw);

/* ---- EXTENSION IN RESET POSITION ---- */
void go_RESET_X (Prog *p);
void go_RESET_Y (Prog *p);
void go_RESET_degree (Prog *p);

/* ---- EXTENSION IN DELAY TIME ---- */
void go_delay (Prog *p);


#endif
