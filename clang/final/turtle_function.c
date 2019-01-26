/* ---- INTIALISE FUNCTION ---- */

/* INTIALISE PROGRAM 
   BASIC:
   1. INITIALISE TOKEN LIST WITH SIZE
   2. INITIALISE VARIABLE WITH NONE STRING
   3. INITIALISE LOCATION 
   4. INITIALISE STACK
   5. SET TOKEN COUNT 0 AND TOKEN LIST SIZE
   EXTENSION:
   1. INITIALISE COLOUR DISPLAY
   2. INITIALISE LIBRARY TABLE WITH NONE STRING 
      AND TOKEN LIST SIZe
   3. SET NEXT PROGRAM NULL 
*/

Prog *intialise_program(int size)
{
   Prog *p;
   p = (Prog*)malloc(sizeof(Prog));
   if (p==NULL)
   {
      ERROR("Create Program Failed \n"); 
   }
   p->tokenlist = intialise_tokenlist(size);
   p->variable =intialise_var (NULL);
   p->s = intialise_STK();
   p-> loc = intialise_location();
   p->colour_display = intialise_colour();
   p->next = NULL;
   p->lib = intialise_lib(NULL, size);
   p->cw = 0;
   p->sz = size;
   return p;
}

/* INTITIALISE TOKEN LIST */
Ele * intialise_tokenlist (int size)
{
   Ele *p;
   int i ;
   p = (Ele *)malloc(sizeof(Ele)*size);
   assert(p!=NULL);
   for(i=0;i<size;i++)
   {
      p[i].token = (char *)malloc(sizeof(char)*MAXWORD_SIZE);
      assert(p[i].token!=NULL);
   }
   return p;
}

/* 
   INITIALISE VARIABLE TABLE WITH STRING SIZE
   IN BEGIN SET STRING TO NULL
*/
Var *intialise_var (char *v)
{
   Var *p;
   p = (Var *)malloc(sizeof(Var));
   assert(p!=NULL);
   if (v == NULL)
   {
      p->name = (char *)malloc(sizeof(char));
   }else{
      p->name = (char *)malloc(sizeof(char)*(strlen(v)+1));
   }
   assert(p->name!=NULL);
   p->left = NULL;
   p->right = NULL;
   return p;
}

/* INITIALISE STACK  */
STK * intialise_STK ()
{
   STK *p;
   p = (STK *)malloc(sizeof(STK));
   assert(p!=NULL);
   p->top = 0;
   return p;
}

/* INITIALISE LOCATION TO WINDOW CENTER */
Pos * intialise_location(void)
{
   Pos *p;
   p = malloc(sizeof(Pos));
   assert(p!=NULL);
   p->x = 400;
   p->y = 300;
   p->degree = 0;
   return p ;
}


/*---- EXTENSION IN INTIALISE FUNCTION ----*/


/* INITIALISE COLOUR DISPLAY */
Colour * intialise_colour ()
{
   Colour *p;
   p = (Colour *)malloc(sizeof(Colour));
   p->color_default= False;
   return p;
}


/* 
   1.INITIALISE LIBRARY TABLE BY USING BST TABLE
   2.IN BEGIN SET STRING TO NULL
   3.SET LIBRARY TOKEN COUNTER TO 0
   4.SET TOKEN LIST SIZE TO SIZE
   5.SET LEFT AND RIGHT NODE TO NULL
*/
Lib *intialise_lib(char *v, int size)
{
   Lib *p;
   int i;
   p = (Lib *)malloc(sizeof(Lib));
   assert(p!=NULL);
   if (v == NULL)
   {
      p->name = (char *)malloc(sizeof(char)*MAXWORD_SIZE);   
   }else{
      p->name = (char *)malloc(sizeof(char)*(strlen(v)+1));      
   }
   assert(p->name!=NULL);
   p->lib_tokenlist = (Ele *)malloc(sizeof(Ele)*size);
   assert(p->lib_tokenlist!=NULL);
   for(i=0;i<size;i++)
   {
      p->lib_tokenlist[i].token = (char *)malloc(sizeof(char));
      assert(p->lib_tokenlist[i].token!=NULL);
   }
   p->left = NULL;
   p->right = NULL;
   p->lib_cw = 0;
   p->token_sz = size;
   return p;    
}


/* DYNAMTIC MEMORY FOR PROGRAM*/

/* PROGRAM GROW*/

void Prog_grow (Prog *s, int size)
{
   Prog *New_prog, tmp;
   int  i;
   New_prog = intialise_program(s->sz * GROWNUM);
   assert(New_prog!=NULL);
   for (i=0; i<size;i++)
   {
      strcpy(New_prog->tokenlist[i].token,s->tokenlist[i].token);
   }
   var_copy(s->variable,New_prog->variable);
   tmp  = *s;
   *s = *New_prog;
   *New_prog = tmp;
   program_free(&New_prog);
   assert(New_prog==NULL);
}

/* COPY ELEMENT IN OLD VARIABLE TABLE TO NEW ONE  */

void var_copy(Var *Old_table, Var *New_table)
{   
   
   if (Old_table->name != NULL)
   {
      Declare_Var(New_table, Old_table->name);
   }
   if (Old_table->left!=NULL)
   {
      var_copy(Old_table->left,New_table);
   }
   if (Old_table->right!=NULL)
   {
      var_copy(Old_table->right,New_table);
   } 
}

/*----EXTENSION IN DYNAMTIC MEMORY FOR LIBRARY ----*/
void lib_grow (Lib *s, int size)
{
   Lib *New_lib, tmp;
   Lib *oldlib_left, *oldlib_right;
   int  i;
   New_lib = intialise_lib(s->name, s->token_sz * GROWNUM);
   assert(New_lib!=NULL);
   oldlib_left = s->left; 
   oldlib_right = s->right; 
   for (i=0; i<size;i++)
   {
      strcpy(New_lib->lib_tokenlist[i].token,s->lib_tokenlist[i].token);
   }
   memcpy(New_lib->name, s->name, strlen(s->name)+1);
   New_lib->left = oldlib_left;
   New_lib->right = oldlib_right; 
   tmp  = *s;
   *s = *New_lib;
   *New_lib = tmp;
   lib_element_free(&New_lib);
   assert(New_lib==NULL);
}


/*---- FREE FUNCTION ----*/

void program_free(Prog **q)
{
   int i; 
   Prog *p = *q;
   if (p!=NULL)
   {
      for (i=0; i<p->sz;i++)
      {
            free(p->tokenlist[i].token);
      }
      var_free(&(p->variable));
      lib_free(&(p->lib));
      free(p->colour_display);
      free(p->loc);
      free(p->tokenlist);
      free(p->s);
      program_free(&(p->next));
      free(p);
      *q = NULL;
   }
}
void var_free(Var **s)
{   
   if ((*s)->right!=NULL) 
   {      
      var_free(&(*s)->right);  
   } 
   if ((*s)->left!=NULL) 
   {     
      var_free(&(*s)->left);  
   }         
   free((*s)->name);  
   free(*s);   
   *s = NULL;
}

/*---- EXTEINSION IN LIBRARY FREE FUNCTION ----*/

void lib_element_free(Lib **q)
{
   int i; 
   Lib *p = *q;
   if (q!=NULL)
   {
      for (i=0; i<p->token_sz;i++)
      {
            free(p->lib_tokenlist[i].token);
      }
      free(p->name);
      free(p->left);
      free(p->right);
      free(p->lib_tokenlist);
      free(p);
      *q = NULL;
   }
}
void lib_free(Lib **s)
{   
   if ((*s)==NULL && s==NULL)
   {
      return ;
   }
   if ((*s)->right!=NULL) 
   {      
      lib_free(&(*s)->right);  
   } 
   if ((*s)->left!=NULL) 
   {     
      lib_free(&(*s)->left);  
   }
      lib_element_free(s);          
   *s = NULL;
}


/*---- STACK FUNCTION ----*/

/*
   PUSH NUMBER INTO STACK 
   CHECK ELEMENT IS NOT EXCESS STACK MAXIMUM SIZE
*/
void Push (Prog *p, float num)
{
   assert(p->s->top < MAX_SIZE);
   p->s->data[p->s->top] = num; 
   p->s->top = p->s->top + 1;
}
/*
   POP NUMBER
   CHECK IS GONE BOTTOM
*/
float Pop (Prog *p)
{
   assert(p->s->top > 0);
   p->s->top = p->s->top - 1;
   return p->s->data[p->s->top];
}

/* ---- VARNUM ISVARNUM (char *s) ----*/

bool IS_NUM(Prog *p)
{
   if (!TONUM(p->tokenlist[p->cw].token)&&Var_isin(p->variable,p->tokenlist[p->cw].token)!=NULL)
   {             
      return True;
   }   
   if (!TONUM(p->tokenlist[p->cw].token))
   {
      return False;
   }
   return True;
}
/*---- PARSER TESTING ----*/

/*
   BASIC: 
   1. CHECK START "{"
   EXTENSION: 
   1.CHECK IMPORT FIRST "IMPORT" 
   2.CEHCK START "{"
   NOTE: LIBRARY NAME CANT USING WORDS 
   IN GRAMMAR 
*/
void parserstart(Prog *p)
{
   if (STRSAME(p->tokenlist[p->cw].token,IMPORT))
   {
      printf(" %s  \t",p->tokenlist[p->cw++].token);           
      if (invalid_token(p))
      {
         printf(" %s  \t",p->tokenlist[p->cw++].token);
      }
   }
   printf(" %s  \n",p->tokenlist[p->cw].token);
   if (STRSAME(p->tokenlist[p->cw++].token,START))
   {
      parser_code(p);
   }
}

/* 
   1.CHECK THE FILE END IS "" PROGRAM STOP
   2.GO INTO INSTRUCTION
*/
void parser_code(Prog *p)
{
   if(STRSAME(p->tokenlist[p->cw].token, "")){return;}
   check_instruction(p);
   parser_code(p);
}

/* CHECK VARIABLE NOT USING THE WORD IN GRAMMAR */
bool invalid_token (Prog *p)
{
   if (instruction(p->tokenlist[p->cw].token)!=NoInstr)
   {
      printf("%d token is invalid -- variable name %s is the same as name in grammar \n", p->cw,p->tokenlist[p->cw].token);
      return False;
   }
   return True;
}
/* 
   CHECK INSTRUCTION RETURN ENUMERATE NUMBER 
   BASIC:
   1. GOFD, GOLT, GODO, GOSET
   EXTENSION:
   1. GO DEF, GOCOLOR, GORESET, GOTEXT, GOCIRCLE, GOMUTICIRCLE 
*/

INSTR instruction (char *s)
{
   if (STRSAME(s,FD)){return GOFD;}
   else if (STRSAME(s,LT)){return GOLT;}
   else if (STRSAME(s,RT)){return GORT;}
   else if (STRSAME(s,DO)){return GODO;}
   else if (STRSAME(s,SET)){return GOSET;}
   else if (STRSAME(s,DEF)){return GODEF;}
   else if (STRSAME(s,COLOR)){return GOCOLOR;}
   else if (STRSAME(s,RESET)){return GORESET;}
   else if (STRSAME(s,MESSAGE)){return GOTEXT;}
   else if (STRSAME(s,CIRCLE)){return GOCIRCLE;}
   else if (STRSAME(s,CIRCLES)){return GOMULTICIRCLE;}
   else if (STRSAME(s,DELAY)){return GODELAY;}
   else if (STRSAME(s,CLEAN)){return GOCLEAN;}
   else if (STRSAME(s,START)){return GOSTART;}
   else if (STRSAME(s,END)){return GOEND;}
   return NoInstr;
}

/* CHECK INSTRUCTION AND MAKE SURE FOLLOW GRAMMAR */
void check_instruction(Prog *p)
{
   switch (instruction(p->tokenlist[p->cw].token))
   {
      case GOFD:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (invalid_token(p))
         {
            printf(" %s  \n",p->tokenlist[p->cw++].token);
            check_instruction(p);
            break;
         }
      case GORT:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (invalid_token(p)){
            printf(" %s  \n",p->tokenlist[p->cw++].token);
            check_instruction(p);
            break;
         }
      case GOLT:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (invalid_token(p)){
            printf(" %s  \n",p->tokenlist[p->cw++].token);
            check_instruction(p);
            break;
         }
      case GODO:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (invalid_token(p)){
            printf(" %s  \t",p->tokenlist[p->cw].token);
            if (ISVARNUM(p->tokenlist[p->cw++].token)!=VAR)
            {
               printf("%d token is invalid --- it's not variable \n", p->cw);
            }
            if (do_loop(p)){parserstart(p);};
            break;
         }
      case GOSET:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (invalid_token(p)){
            printf(" %s  \t",p->tokenlist[p->cw].token);
            if (ISVARNUM(p->tokenlist[p->cw++].token)!=VAR)
            {
               printf("%d token is invalid --- it's not variable \n", p->cw);
            }
            if (do_set(p)){do_polish(p);}
            check_instruction(p);
            break;
         }
      case GORESET:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (do_reset(p)){
            check_instruction(p);
            break;
         }
      case GOCOLOR:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (do_reset(p)){
            check_instruction(p);
            break;
         }
      case GODELAY:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         if (invalid_token(p)){
            printf(" %s  \n",p->tokenlist[p->cw++].token);
            check_instruction(p);
            break;
         }
      case GOEND:
         printf(" %s  \n",p->tokenlist[p->cw++].token);
         break;      
      default:
         if (dot_isin(p->tokenlist[p->cw].token))
         {
            printf("FUNCTION %s \n", p->tokenlist[p->cw++].token);
            do_function(p);
            check_instruction(p);
         }
         p->cw++;
         break;
   }
}


/* DO LOOP FUNCTION  */
bool do_loop(Prog *p)
{
   if (do_loop_start(p))
   {
      p->cw++;
      if (do_loop_end(p))
      {
         p->cw++;
         return True;
      }
   }
   return False;
}

/* 
   CHECK "FROM" IS IN,  THEN CHECK FROM VARNUM ISNT 
   WORDS IN GRAMMAR
*/

bool do_loop_start (Prog *p)
{
   printf(" %s  \t",p->tokenlist[p->cw].token);
   if (STRSAME(p->tokenlist[p->cw++].token,FROM))
   {
      printf(" %s  \t",p->tokenlist[p->cw].token);
      if (!invalid_token(p))
      {
         return False;
      }
      return True;
   }
   return False;
}

/* 
   CHECK "END" IS IN,  THEN CHECK END VARNUM ISNT 
   WORDS IN GRAMMAR
*/

bool do_loop_end (Prog *p)
{
   printf(" %s  \t",p->tokenlist[p->cw].token);
   if (STRSAME(p->tokenlist[p->cw++].token,TO))
   {
      printf(" %s  \t",p->tokenlist[p->cw].token);
      if (!invalid_token(p))
      {
         return False;
      }
      return True;
   }
   return False;
}

/* CHECK SET VARIBLE GRAMMAR HAS  ":= */

bool do_set (Prog *p)
{
   printf(" %s  \t",p->tokenlist[p->cw].token);
   if (STRSAME(p->tokenlist[p->cw++].token,ASSIGN))
   {
      return True;
   }
   return False;
}

/* CHECK OPERATOR AND VARIABLE OR NUMBER RETURN ENUMERATE NUMBER*/

POLISH check_polish(char *s)
{
   if (STRSAME(s,PLUS)){return DOPLUS;}
   else if (STRSAME(s,MINUS)){return DOSUB;}
   else if (STRSAME(s,MULT)){return DOMULTI;}
   else if (STRSAME(s,DEVIDE)){return DODEVIDE;}
   else if (STRSAME(s,SEMI)){return SEMIEND;}
   else if (STRSAME(s,COMMA)){return COMMAEND;}
   else if (STRSAME(s,PARENTHESE_CLOSE)){return CLOSEPARENTHESE;}
   else if (instruction(s)==NoInstr)
   {
      if(ISVARNUM(s)==VAR){return DOVAR;}
      else { return DONUM;}
   } 
   return INVALID;
}

/* DO POLISH
   BASIC:
   1. FOR SET NUMBER IN TO VARIABLE 
   2. ENDING USING ";"
   EXTENSION:
   1. FOR SET NUMBER INTO FUNCTION INPUT 
   2. ENDING USING "," AND " )"
*/
void do_polish(Prog *p)
{
   switch(check_polish(p->tokenlist[p->cw].token))
   {
      case DOPLUS:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         do_polish(p);
         break;
      case DOSUB:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         do_polish(p);
         break;
      case DOMULTI:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         do_polish(p);
         break;
      case DODEVIDE:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         do_polish(p);
         break;
      case DOVAR:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         do_polish(p);
         break;
      case DONUM:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         do_polish(p);
         break;
      case SEMIEND:
         printf(" %s  \n",p->tokenlist[p->cw++].token);
         break;
      case COMMAEND:
         printf(" %s  \t",p->tokenlist[p->cw++].token);
         break;
      case CLOSEPARENTHESE:
         printf(" %s  \n",p->tokenlist[p->cw++].token);
         break;
      default:
         printf("%d token %s is invalid \n",p->cw,p->tokenlist[p->cw].token);
         break;
   }
}

/* ---- EXTENSION IN COLOR ----*/

bool do_color(Prog *p)
{
   if(color_R(p))
   {
      if (color_G(p))
      {
         if(color_B(p))
         {
            printf("\n");
            return True;
         }
      }
   }
   return False;
}

/* CHECK COLOR NUMBER OR VARIABLE IS NOT WORDS IN GRAMMAR */
bool color_R (Prog *p)
{
   if (invalid_token(p)){
      printf(" %s  \t",p->tokenlist[p->cw++].token);
      return True;
   } 
   return False;
}
bool color_G (Prog *p)
{
   if (invalid_token(p)){
      printf(" %s  \t",p->tokenlist[p->cw++].token);
      return True;
   } 
   return False;
}
bool color_B (Prog *p)
{
   if (invalid_token(p)){
      printf(" %s  \t",p->tokenlist[p->cw++].token);
      return True;
   } 
   return False;
}

/*---- EXTENSION IN RESET POSITION ----*/

/* CHECK POSITION NUMBER OR VARIABLE IS NOT WORDS IN GRAMMAR */

bool do_reset(Prog *p)
{
   if(reset_x(p))
   {
      if (reset_y(p))
      {
         if(reset_degree(p))
         {
            printf("\n");
            return True;
         }
      }
   }
   return False;
}

bool reset_x (Prog *p)
{
   if (invalid_token(p)){
      printf(" %s  \t",p->tokenlist[p->cw++].token);
      return True;
   } 
   return False;
}
bool reset_y (Prog *p)
{
   if (invalid_token(p)){
      printf(" %s  \t",p->tokenlist[p->cw++].token);
      return True;
   } 
   return False;
}
bool reset_degree (Prog *p)
{
   if (invalid_token(p)){
      printf(" %s  \t",p->tokenlist[p->cw++].token);
      return True;
   } 
   return False;
}

/*---- EXTENSION IN DOING FUNCTION ----*/

/*
   1. CHECK OPEN PARENTHESE
   2. CHECK VOID FUNCTION OR NOT 
   3. IF NOT VOID FUNCTION CHECK VARIABLE NAME IS NOT IN GAMMAR
   4. CHECK ASSIGN LOCAL VALUE FUNCTION
*/
void do_function(Prog *p)
{
   printf(" %s \t", p->tokenlist[p->cw].token);
   if (STRSAME(p->tokenlist[p->cw].token,PARENTHESE_OPEN))
   {
      p->cw ++;
      while (!STRSAME(p->tokenlist[p->cw].token,PARENTHESE_CLOSE))
      {
         printf("%s \t", p->tokenlist[p->cw].token);
         if (!STRSAME(p->tokenlist[p->cw].token,VOID)&&ISVARNUM(p->tokenlist[p->cw].token)==VAR)
         {
            p->cw ++;
            if (!do_assign_local_value(p)){
                  printf(" %s ERROR \n", p->tokenlist[p->cw].token);
            }
         }else{
            p->cw++;
         }
      }
      printf(" %s  \n", p->tokenlist[p->cw++].token);
   }
}

/*
   1. CHECK ASSIGN ":=" IS IN
   2. DO POLISH FUNCTION
*/
bool do_assign_local_value (Prog *p)
{
   if (STRSAME(p->tokenlist[p->cw].token,ASSIGN))
   {
      p->cw++;
      do_polish(p);
      return True;
   }
   return False;
}

/*---- INTERPRETER TESTING ----*/


/* START FUNCTION 
   BASIC: GO INTO CODE FUNCTION
   EXTENSION: IMPORT LIBRARY 
*/

void Block_start(Prog *p, SDL_Simplewin *sw)
{
   if (STRSAME(p->tokenlist[p->cw].token,IMPORT)){
      p->cw++;
      if (invalid_token(p))
      {
            parser_lib(p);
      }
   }
   if (!STRSAME(p->tokenlist[p->cw].token,START))
   {
      ERROR("NO BEGIN TOKEN \n");
   }
   p->cw ++;
   Code(p, sw);     
}

/* CHECK TO END (BY CHECKING "") ELSE DO INSTRUCTION */
void Code (Prog *p, SDL_Simplewin *sw)
{
   if(STRSAME(p->tokenlist[p->cw].token, ""))
   {
      return;
   }
   check_instruct(p,sw);
   Code(p, sw);
}

/* FOR INSTURCTION */
void check_instruct(Prog *p, SDL_Simplewin *sw)
{
   int R,G,B;
   switch (instruction(p->tokenlist[p->cw].token))
   {
      case GOFD:
         p->cw++;
         if (invalid_token(p))
         {
            go_FD(p,sw);
            check_instruct(p,sw);
            break;
         }
      case GORT:
         p->cw++;
         if (invalid_token(p)){
            go_RT(p);
            check_instruct(p,sw);
            break;
         }
      case GOLT:
         p->cw++;
         if (invalid_token(p)){
            go_LT(p);
            check_instruct(p,sw);
            break;
         }
      case GOTEXT:
         p->cw ++;
         R = load_varnum(p);
         G = load_varnum(p);
         B = load_varnum(p);
         LOAD_FONT(sw, p->tokenlist[p->cw].token,R,G,B);
         p->cw++;
         check_instruct(p,sw);
         break;
      case GOCIRCLE :
         p->cw ++ ;
         draw_circle(p,go_CIRECLE_radius(p) ,sw); 
         check_instruct(p,sw);
         break;
      case GODO:
         p->cw++;
         if (invalid_token(p)){
            if (ISVARNUM(p->tokenlist[p->cw].token)!=VAR)
            {
               printf("%d  token is invalid --- it's not variable \n", p->cw);
            }
            go_for_loop(p,sw);
            break;
         }
      case GOSET:
         p->cw++;
         if (invalid_token(p)){
            if (ISVARNUM(p->tokenlist[p->cw].token)!=VAR)
            {
               printf("%d token is invalid --- it's not variable \n", p->cw);
            }
            go_set(p);                  
            check_instruct(p,sw);
            break;
         }
      case GOMULTICIRCLE:
         p->cw++;
         random_circle(go_num_circles(p),sw);
         check_instruct(p,sw);
         break;
      case GORESET:
         p->cw++;
         go_RESET_X(p);
         go_RESET_Y(p);
         go_RESET_degree(p);
         check_instruct(p,sw);
         break;
      case GOCOLOR:
         p->cw++;
         go_COLOR(p,sw);
         check_instruct(p,sw);
         break;
      case GODELAY:
         p->cw++;
         if (invalid_token(p)){
            go_delay(p);
            check_instruct(p,sw);
            break;
         }
      case GOCLEAN:
         p->cw++;
         Neill_SDL_Init(sw);
         check_instruct(p,sw);
         break;
      case GOEND:
         p->cw++;
         check_instruct(p,sw);
         break;      
      default:
         if (STRSAME(p->tokenlist[p->cw].token,IMPORT))
         {
            ERROR("import Library First \n");
         }           
         if (dot_isin(p->tokenlist[p->cw].token))
         {
            load_function(p,sw);
            check_instruct(p,sw);
         }
         p->cw++;
         break;
   }
}
/* GO FORWORD
   1. LOAD NUMBER 
   2. GET X AND Y END POSITION BY USING SIN AND COS FUNCTION
   3. DRAW LINE 
*/
void go_FD (Prog *p,SDL_Simplewin *sw)
{
   float x_start, x_end, y_start,y_end;
   int num;
   num = load_varnum(p);
   x_start = p->loc->x;
   y_start = p->loc->y;
   x_end = x_end_postition(x_start,p->loc->degree, num);
   y_end = y_end_postition(y_start,p->loc->degree, num);
   p->loc->x = x_end;
   p->loc->y = y_end;
   draw_line(p,x_start,y_start,x_end,y_end,sw);
}
/* 
   GO LEFT TURN
   CLOCKWISE ROTATE 
*/
void go_LT (Prog *p)
{
   int num; 
   num = load_varnum(p);
   p->loc->degree += num;
}
/* 
   GO LEFT TURN
   COUNTER-CLOCKWISE ROTATE 
*/
void go_RT (Prog *p)
{
   int num; 
   num = load_varnum(p);
   p->loc->degree -= num;      
}

/*
   1.GET START NUMBER AND END NUMBER 
   2.COUNT UNTIL START NUMBER EQUAL END NUMBER
   3.GO BACK TO BLOCK START
*/
void go_for_loop (Prog *p, SDL_Simplewin *sw)
{
   Var *tmp_var;
   int start, end, tmp;
   tmp_var = load_Var(p);
   assert(tmp_var!=NULL);
   start = get_start_num(p);
   end = get_End_num(p);
   tmp = p->cw;
   while(start!=end)
   {        
   tmp_var->value = start;
   p->cw = tmp;
   Block_start(p,sw);
   start++;
   }
   p->cw++;        
}


/* GET START NUMBER */

int get_start_num(Prog *p)
{
   int start;
   if (!STRSAME(p->tokenlist[p->cw].token,FROM))
   {
         ERROR("NO START NUM");
   }
   p->cw++;
   if (!invalid_token(p))
   {
      ERROR("Invalid TOKEN");
   }
   start = load_varnum(p);
   return start;
}

/* GET END NUMBER */

int get_End_num(Prog *p)
{
   int end;
   if (!STRSAME(p->tokenlist[p->cw].token,TO))
   {
         ERROR("NO END NUM");
   }
   p->cw++;
   if (!invalid_token(p))
   {
      ERROR("Invalid TOKEN");
   }
   end = load_varnum(p);
   return end;
}


/* ---- VARIABLE FUNCTION ---- */

/* INSERT NEW VARIABLE */
void Declare_Var(Var *p, char *v)
{
   Var *New_Var;
   if (p->left == NULL && p->right == NULL && p->name == NULL)
   {
      p->name = (char *)malloc(sizeof(char)*(strlen(v)+1));
      assert(p->name!=NULL);
      strcpy(p->name, v);
   }
   else if (p!=NULL || strcmp(v, p->name)!=0)
   {
      if (strcmp(v,p->name)>0)
      {
         if(p->right ==NULL)
         {
            New_Var = intialise_var(v);
            strcpy(New_Var->name, v);
            p->right = New_Var;
         }else {
            Declare_Var(p->right,v);
         }
      }else{
         if (p->left==NULL)
         {
            New_Var = intialise_var(v);
            strcpy(New_Var->name, v);
            p->left = New_Var;
         }else{
            Declare_Var(p->left,v);
         }
      }
   }
}

/* CHECK VARIABLE IS IN AND RETURN  */
Var *Var_isin(Var *p, char *v)
{
   if (p!=NULL && p->name!=NULL)
   {
      if (strcmp(p->name,v)==0)
      {
         return p;
      }
      if (strcmp(v,p->name)>0)
      {
         return Var_isin(p->right,v);
      }else{
         return Var_isin(p->left,v);
      }
   }
   return NULL;
}

/* 
   1.STORE NEW VARIABLE INTO TEMPORARY SPACE
   2.DO RPN AND RETURN VALUE
   3.ASSIGN NEW VALUE INTO NEW VARIABLE
*/
void go_set(Prog *p)
{
   float num; 
   Var *new; 
   new = load_Var(p);
   assert(new!= NULL);
   if (STRSAME(p->tokenlist[p->cw].token,ASSIGN))
   {
      p->cw++;
      assert(do_Reverse_polish(p)==True);
      num = Pop(p);
      new -> value = num;
   }else{
      ERROR("NO ASSIGNED  \n")
   }
}

/* 
   DO REVERSE POLISH NOTATION
   BASIC 
   1. POP TWO NUMBER AND DO OPERATION
      THEN PUSH RESULT BACK
   2. IF GET ";" RETURN TRUE
   EXTENSION
   1. IF GET "," AND ")" RETURN TRUE
*/

bool do_Reverse_polish(Prog *p)
{
   float result = 0 ;
   float num;
   float op1 , op2; 
   switch(check_polish(p->tokenlist[p->cw].token))
   {
      case DOPLUS:
         op1 = Pop(p);
         op2 = Pop(p);
         result  = op1 + op2;
         Push(p, result);
         p->cw++;
         do_Reverse_polish(p);
         break;
      case DOSUB:
         op1 = Pop(p);
         op2 = Pop(p);
         result  = op2 - op1;
         Push(p, result);
         p->cw++;
         do_Reverse_polish(p);
         break;
      case DOMULTI:
         op1 = Pop(p);
         op2 = Pop(p);
         result  = op1 * op2;
         Push(p, result);
         p->cw++;
         do_Reverse_polish(p);
         break;
      case DODEVIDE:
         op1 = Pop(p);
         op2 = Pop(p);
         result  = op2 / op1;
         Push(p, result);
         p->cw++;
         do_Reverse_polish(p);
         break;
      case DOVAR:
         num = load_varnum(p);
         Push(p,num);
         do_Reverse_polish(p);
         break;
      case DONUM:
         num = load_varnum(p);
         Push(p,num);
         do_Reverse_polish(p);
         break;
      case SEMIEND:
         p->cw++;
         return True;
      case COMMAEND:
         p->cw++;
         return True;
      case CLOSEPARENTHESE:
         p->cw++;
         return True;
      default:
         printf("%d token %s is invalid no end\n",p->cw,p->tokenlist[p->cw].token);
         return False;
   }
   return True;
}
/* POINT TO VARIABLE */
Var *load_Var(Prog *p)
{
   int tmp;
   Declare_Var(p->variable,p->tokenlist[p->cw].token);
   tmp = p->cw;
   p->cw ++;
   return Var_isin(p->variable,p->tokenlist[tmp].token);
}

/* 
   GET NUMBER
   1. IF TOKEN IS NUMBER THEN RETURN NUMBER
   2. IF IT IS VARIABLE,  CHECK IT HAS BEEN 
      ASSIGNED AND RETURN NUMBER OR GET ERROR
*/

int load_varnum(Prog *p)
{
   int num;
   Var *tmp;
   if (!TONUM(p->tokenlist[p->cw].token)&&Var_isin(p->variable,p->tokenlist[p->cw].token)!=NULL)
   {
      tmp = Var_isin(p->variable, p->tokenlist[p->cw].token);
      assert(tmp!=NULL);
      num = tmp->value;
      p->cw = p->cw +1;
      return num;
   }   
   if (!TONUM(p->tokenlist[p->cw].token)&&!STRSAME(p->tokenlist[p->cw].token,"0"))
   {
      printf("%d token-- %s -- is not num  \n",p->cw, p->tokenlist[p->cw].token);
      ERROR("Not number");
   }
   num = TONUM(p->tokenlist[p->cw].token);
   p->cw = p->cw +1;
   return num;
}


/* DRAW LINE */
void draw_line (Prog *p,int x_start, int y_start, int x_end, int y_end, SDL_Simplewin *sw)
{
   SDL_Delay(MILLISECONDDELAY);
   if (!p->colour_display->color_default){
      Neill_SDL_SetDrawColour(sw, rand()%SDL_8BITCOLOUR,rand()%SDL_8BITCOLOUR,rand()%SDL_8BITCOLOUR);
   }
   /* Choose a random colour, a mixture of red, green and blue. */
   SDL_RenderDrawLine(sw->renderer,x_start,y_start,x_end,y_end);
   Neill_SDL_UpdateScreen(sw);
   Neill_SDL_Events(sw);
}
/* GET X END POSITION  */

float x_end_postition(float x, int degree, int r)
{
   float arc ; 
   float end; 
   arc = degree / ARC * M_PI;
   end = x + r * cos(arc);
   return end ; 
}
/* GET Y END POSITION  */

float y_end_postition(float y, int degree, int r)
{
   float arc ; 
   float end; 
   arc = degree / ARC * M_PI;
   end = y + r * sin(arc);
   return end ; 
}
/*---- EXTENSION IN LIBRARY ----*/

/* 
   IMPORT LIBRARY
   1. LOAD FILE NAME INTO PROGRAM LIBRARY NAME
   2. LOAD TOKEN INTO LIBRARY TOKEN LIST
*/
void parser_lib(Prog *p)
{
   Lib *tmp; 
   printf("import library \n");
   tmp = Load_lib_into_prog(p);
   printf("Load %s into Program \n", tmp->name);
   Load_tokenlist_into_lib(tmp, tmp->name);
   printf( "Load success \n");
}

/* TRANSFER NAME TO NAME.TXT TO LOAD FILE */
char * string_process (char *v)
{
   char *new_v;
   int i , word_count,txt_count;
   word_count = strlen(v);
   txt_count = strlen(TXT);
   new_v = (char *)calloc( (strlen(v)+strlen(TXT)+1),sizeof(char) );
   for (i = 0; i< word_count;i++ )
   {
      new_v[i] = v[i];
   }
   for (i = 0; i< txt_count; i++)
   {
      new_v[i+word_count] = TXT[i];
   }
   return new_v;

}
/* ADD LIBRARY NAME INTO LIBRARY TABLE */

void insert_lib_name(Lib *p, char *v)
{
   Lib *New_lib;
   if (p->left == NULL && p->right ==NULL && p->name == NULL)
   {
      p->name = (char *)malloc (sizeof(char)*(strlen(v)+1));
      assert(p->name != NULL);
      strcpy(p->name, v);
   }
   else if (p!=NULL || strcmp(v, p->name)!=0)
   {
      if (strcmp(v,p->name)>0)
      {
         if(p->right ==NULL)
         {
            New_lib = intialise_lib(v,MAX_LIBTOKENSIZE);
            strcpy(New_lib->name, v);
            p->right = New_lib;
         }else {
            insert_lib_name(p->right,v);
         }
      }else{
         if (p->left==NULL)
         {
            New_lib = intialise_lib(v,MAX_LIBTOKENSIZE);
            strcpy(New_lib->name, v);
            p->left = New_lib;
         }else{
            insert_lib_name(p->left,v);
         }
      }
   }   
}
/* RETURN  LIBRARY */
Lib *Load_lib_into_prog (Prog *p)
{
   int tmp;
   insert_lib_name(p->lib, p->tokenlist[p->cw].token);
   assert(Lib_isin(p->lib,p->tokenlist[p->cw].token)!=NULL);
   tmp = p->cw;
   p->cw++;
   return Lib_isin(p->lib,p->tokenlist[tmp].token); 
}
/* FIND LIBRARY NAME IS IN LIBRARY TABLE */
Lib *Lib_isin(Lib *p, char *v)
{
   if (p!=NULL && p->name !=NULL)
   {
   
      if (strcmp(p->name,v)==0)
      {
         return p;
      }
      if (strcmp(v,p->name)>0)
      {
         return Lib_isin(p->right,v);
      }else{
         return Lib_isin(p->left,v);
      }
   }
   return NULL;
}


/* LOAD TOKEN INTO TOKEN LIST IN LIBRARY */
void Load_tokenlist_into_lib (Lib *p, char *v)
{
   FILE *fp;
   char *filename;
   int i; 
   filename = (char *)malloc(sizeof(char)*(LEN(string_process(v))+1) );
   strcpy (filename,string_process(v));
   if(!(fp = fopen(filename,"r")))
   {
      fprintf(stderr, "Cannot open %s \n", filename);
      exit(2);
   }
   i=0;
   while(fscanf(fp, "%s",p->lib_tokenlist[i++].token)==1)
   {
      if(i > p->token_sz*GROWFACT)
      {
         lib_grow(p,i);
      }
   }
   fclose(fp);   
}


/* FIND FUNCTION IS IN LIBRARY */
bool find_function (char *v, Lib *p)
{
   if (STRSAME(p->lib_tokenlist[p->lib_cw].token,DEF)||!STRSAME(p->lib_tokenlist[p->lib_cw].token,""))
   {
      p->lib_cw++;
      while (!STRSAME(p->lib_tokenlist[p->lib_cw].token,DEF))
      {
         if (STRSAME(p->lib_tokenlist[p->lib_cw].token,""))
         {
            break;
         }
         if (STRSAME(p->lib_tokenlist[p->lib_cw].token,v))
         {
            p->lib_cw++;
            return True;
         }
         p->lib_cw++; 
      } 
      return find_function(v,p);     
   }
   return False;
}

/* CHECK DOT IS IN THE STRING */
int dot_isin (char *v)
{
   int i;
   int len; 
   len = strlen(v);
   for (i=0 ; i<len;i++)
   {
      if (DOISIN(v[i]))
      {
         return i;
      }
   }
   return 0 ;
}

/* TESTING TO GET LIBRARY NAME AND FUNCTION NAME IN A STRING */
void test_strip_word ()
{
   char * lib_name = get_lib_name("extension_function.triangle");
   char * function_name = get_function_name("extension_function.triangle");
   printf("library is %s function is %s \n" ,lib_name , function_name);
}

/*BEFORE DOT IS LIBRARY NAME */
char *get_lib_name (char *v)
{
   int dot_count;
   int i ;
   char *lib_name; 
   
   dot_count = dot_isin (v);
   
   lib_name  = (char *)calloc (dot_count,sizeof(char) );
   for (i = 0 ; i< dot_count; i++)
   {
      lib_name[i] = v[i];
   }
   return lib_name;
}
/*AFTER  DOT IS FUNCTION NAME */
char *get_function_name (char *v)
{
   int dot_count;
   int funlen;
   int i;
   char *fun_name; 
   dot_count = dot_isin (v);
   funlen = LEN(v) - dot_count;
   fun_name  = (char *)malloc (sizeof(char) * (funlen+1));
   for (i = 0 ; i<=funlen; i++)
   { 
      fun_name[i] = v[dot_count+i+1];
   }
   return fun_name;
}

/* 
   1.LOAD FUNCTION INTO NEXT PROGRAM
   2.GET THE TOKEN LIST IN LIBRARY
   3.GET THE FUNCTION IN TOKEN LIST
*/
void load_function (Prog *p,SDL_Simplewin *sw)
{
   char *lib_name;
   char * function_name ;
   Lib * tmp = NULL;
   if (dot_isin(p->tokenlist[p->cw].token)==0 && !FLOATNUM(p->tokenlist[p->cw].token) )
   {
      return;
   }
   lib_name = get_lib_name(p->tokenlist[p->cw].token);
   if (Lib_isin(p->lib,lib_name)!=NULL)
   {
      tmp = Lib_isin(p->lib,lib_name);
   }
   function_name = get_function_name(p->tokenlist[p->cw].token);
   p->cw++;
   assert(tmp!=NULL);
   tmp->lib_cw = 0 ;
   assert(find_function(function_name,tmp)==True);
   
   copy_functon(p,tmp,sw);
}

/* 
   COPY FUNCTION INTO TOKEN LIST NEXT PROGRAM
   1. DECLARE THE INPUT IN FUNCTION FIRST
   2. COPY FUNCTION INTO TOEKN LIST
   3. GET OPEN PARENTHESE IN THE MAIN PROGRAM
   4. ASSIGN THE VALUE INTO THE VARIABLE
   5. START THE BLOCK
   6. FREE THE PROGRAM AFTER THE END 
*/
void copy_functon (Prog *s, Lib *tmp,SDL_Simplewin *sw)
{
   Prog *p, *New_Prog;
   int i ;
   p = s->next;
   New_Prog = intialise_program(tmp->lib_cw);
   while(p != NULL)
   {
      p= p->next;
   }
   p  = New_Prog;
   i = 0;
   declare_local_var(tmp, p);
   while (!STRSAME(tmp->lib_tokenlist[tmp->lib_cw].token,DEF))
   {
      if (STRSAME(tmp->lib_tokenlist[tmp->lib_cw].token,""))
      {
            break;
      }
      strcpy(p->tokenlist[i++].token,tmp->lib_tokenlist[tmp->lib_cw++].token);
      if(i > p->sz*0.6)
      {

         Prog_grow(p,i);
      }
      
   }
   get_open_parenthese(s, p);
   Block_start(p,sw);
   program_free(&p);
   assert(p==NULL);
}
/*
   ASSIGN LOCAL VALUE INTO VARIABLE BY DOING POLISH
 
*/
void get_open_parenthese (Prog *p, Prog *s)
{
   Var *tmp;
   if (STRSAME(p->tokenlist[p->cw].token,PARENTHESE_OPEN))
   {
      p->cw ++;
      while (!STRSAME(p->tokenlist[p->cw].token,PARENTHESE_CLOSE))
      {
         tmp = Var_isin(s->variable,p->tokenlist[p->cw].token);
         assert(tmp != NULL);
         if (!STRSAME(p->tokenlist[p->cw].token,VOID)&&ISVARNUM(p->tokenlist[p->cw].token)==VAR)
         {
            p->cw ++;
            tmp->value = assign_local_value(p);
         }else{
               p->cw++;
         }
      }
      
      p->cw++;
   }
}
void declare_local_var (Lib *p, Prog *s)
{
   if (STRSAME(p->lib_tokenlist[p->lib_cw].token,PARENTHESE_OPEN))
   {
      p->lib_cw ++;
      while (!STRSAME(p->lib_tokenlist[p->lib_cw].token,PARENTHESE_CLOSE))
      {
         Declare_Var(s->variable, p->lib_tokenlist[p->lib_cw].token);
         assert(Var_isin(s->variable,  p->lib_tokenlist[p->lib_cw].token)!=NULL);
         p->lib_cw++;
      }
      p->lib_cw++;
   }
}
float assign_local_value (Prog *p)
{
   float result=0;
   if (STRSAME(p->tokenlist[p->cw].token,ASSIGN))
   {
      p->cw++;
      assert(do_Reverse_polish(p)==True);
      result = Pop(p);
   }
   return result;
}

/* ---- EXTENSION IN SET COLOR ----- */

/* 
   SET COLOR 
   CHECK THE NUMBER IS LESS THAN AND EQUAL 255 AND MORE THAN AND EQUAL 0
*/
void go_COLOR (Prog *p,SDL_Simplewin *sw )
{
   int R , G, B ;
   if (invalid_token(p)){ 
      R = load_varnum(p);
      if (invalid_token(p)){
         G = load_varnum(p);
         if (invalid_token(p)){
            B = load_varnum(p);
            if (R>SDL_8BITCOLOUR||R<0||G >SDL_8BITCOLOUR ||R<0||G >SDL_8BITCOLOUR ||R<0)
            {
               ERROR("Failed to Set COLOUR --- More than 255 or Less than 0 ");
            }
            Neill_SDL_SetDrawColour(sw, R,G,B);
            p->colour_display->color_default = True;
         }else{
            ERROR ("INVALID TOKEN \n");
         }
      }else{
         ERROR ("INVALID TOKEN \n");
      }
   }else{
      ERROR ("INVALID TOKEN \n");
   }        
}


/* ---- EXTENSION IN DRAW CIRCLE AND CIRCLE SETS ----  */

/* GET CIRCLE RADIUS */
int go_CIRECLE_radius (Prog *p)
{
   int num ;
   if (invalid_token(p)){
      num = load_varnum(p);
      return num;
   }else{
      ERROR ("INVALID TOKEN \n");
   }
   return 0; 
}
/* DRAW  CIRCLE  */
void draw_circle (Prog *p, int radius, SDL_Simplewin *sw)
{
   Neill_SDL_RenderFillCircle(sw->renderer, p->loc->x, p->loc->y, radius);
   SDL_Delay(10);
   Neill_SDL_UpdateScreen(sw);
   Neill_SDL_Events(sw);

}

/* GET NUMBER OF CIRCLE SETS */
int go_num_circles (Prog *p)
{
   int num ;
   if (invalid_token(p)){
      num = load_varnum(p);
      return num;
   }else{
      ERROR ("INVALID TOKEN \n");
   }
   return 0; 
}

/* DRAW CIRCLE SETS */
void random_circle (int num , SDL_Simplewin * sw)
{
   int i ;
   float x,y , radius;
   float tmp_x , tmp_y ;
      srand(time(0));
      do {
      x = rand()%(WWIDTH);
      y = rand()%(WHEIGHT);
      for (i  = 0; i< MAXCIRCLESET ; i ++)
      {
         SDL_SetRenderDrawColor(sw->renderer, rand()%SDL_8BITCOLOUR, rand()%SDL_8BITCOLOUR, rand()%SDL_8BITCOLOUR, rand()%SDL_ALPHA_OPAQUE);
         while ((tmp_x = (int)pow(-1.0,i ) * rand()%MAXRADIUS + x)>WWIDTH 
               || tmp_x <0 
               ||(tmp_y = (int)pow(-1.0,i ) * rand()%MAXRADIUS + y)> WHEIGHT 
               || tmp_y < 0 );  
         radius = i % MAXRADIUS;
         Neill_SDL_RenderFillCircle(sw->renderer, tmp_x, tmp_y, radius);
         SDL_Delay(10);
         Neill_SDL_UpdateScreen(sw);
         Neill_SDL_Events(sw);
      }
      num--;
   }while(num != 0);
}


/* ---- EXTENSION IN RESET POSITION ---- */
void go_RESET_X (Prog *p)
{
   int num ;
   if (invalid_token(p)){
      num = load_varnum(p);
      p->loc->x = num; 
   }else{
      ERROR ("INVALID TOKEN \n");
   }  
}
void go_RESET_Y (Prog *p)
{
   int num ;
   if (invalid_token(p)){
      num = load_varnum(p);
      p->loc->y = num; 
   }else{
      ERROR ("INVALID TOKEN \n");
   }     
}
void go_RESET_degree (Prog *p)
{
   int num ;
   if (invalid_token(p)){
      num = load_varnum(p);
      p->loc->degree = num; 
   }else{
      ERROR ("INVALID TOKEN \n");
   }     
}

/* ---- EXTENSION IN DELAY TIME ---- */
void go_delay (Prog *p)
{
   int time; 
   time = load_varnum(p);
   SDL_Delay(time);     
}






