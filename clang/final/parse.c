#define ERROR(STR) {fprintf(stderr, "Fatal Error %s occured in %s, line %d \n", STR, __FILE__, __LINE__); exit(2);}
#define MILLISECONDDELAY 1
#define ARC 180.0
#define GROWNUM 2
/* ---- Intialise ---- */

/* Intialise Program */
Prog *intialise_program(int size)
{
   Prog *p;
   int i;
   p = (Prog*)malloc(sizeof(Prog));
   if (p==NULL)
   {
      ERROR("Create Program Failed \n"); 
   }
   p->tokenlist = (Ele *)malloc(sizeof(Ele)*size);
   for(i=0;i<size;i++)
   {
      p->tokenlist[i].token = (char *)malloc(sizeof(char));
   }
   p->variable = (Var *)malloc(sizeof(Var));
   p->colour_display = (Colour *)malloc(sizeof(Colour));
   p->colour_display->color_default= False;
   p->s = (STK *)malloc(sizeof(STK));
   p->s->top = 0;
   p->cw = 0;
   p->sz = size;
   p-> loc = intialise_location();
   return p;
}
void grow (Prog *s, int size)
{
      Prog *New_prog, tmp;
      int  i;
      New_prog = intialise_program(s->sz * GROWNUM);
      for (i=0; i<size;i++)
      {
            strcpy(New_prog->tokenlist[i].token,s->tokenlist[i].token);
      }
      tmp  = *s;
      *s = *New_prog;
      *New_prog = tmp;
      old_program_free(&New_prog);
}
/* Intialise Variable Table */
Var *intialise_var (char *v)
{
      Var *p;
      p = (Var *)malloc(sizeof(Var));
      p->name = (char *)malloc(sizeof(char)*(strlen(v)+1));
      p->left = NULL;
      p->right = NULL;
      return p;
}
/* Intialise Location */
Pos * intialise_location(void)
{
      Pos *p;
      p = malloc(sizeof(Pos));
      p->x = 400;
      p->y = 300;
      p->degree = 0;
      return p ;
}
/* ---- Variable Function ---- */

/* Create new variable */
void Declare_Var(Var *p, char *v)
{
   Var *New_Var;
   if (p->name == NULL)
   {
         p->name = (char *)malloc(sizeof(char)*(strlen(v)+1));
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
/* Return existed variable */
Var *Var_isin(Var *p, char *v)
{
      if (p!=NULL)
      {
         if(p->name !=NULL)
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
      }
   return NULL;
}
Var *load_Var(Prog *p)
{
      int tmp;
      Declare_Var(p->variable,p->tokenlist[p->cw].token);
      tmp = p->cw;
      p->cw ++;
      return Var_isin(p->variable,p->tokenlist[tmp].token);
}
void set_var(Prog *p)
{
      int num; 
      Var *new; 
      if (STRSAME(p->tokenlist[p->cw].token,SET))
      {
            p->cw++;
            new = load_Var(p);
            num = assign_value(p);
            new -> value = num;
            p->cw++;
      }
      
}
float assign_value(Prog *p)
{
      float num,result=0;
      if (STRSAME(p->tokenlist[p->cw].token,ASSIGN))
      {
            /*printf("%s ",ASSIGN);*/
            p->cw++;
            while (!STRSAME(p->tokenlist[p->cw].token,SEMI))
            {
                  if (check_Varnum(p))
                  {
                        num = load_varnum(p);
                        Push(p,num);
                  }else{
                        postfix_cal(p); 
                  }
            }
            result = Pop(p);
      }else{
            ERROR("No Assign Symbol\n");
      }
      return result;
}
int load_varnum(Prog *p)
{
   int num;
   Var *tmp;
   if (!NUM(p->tokenlist[p->cw].token)&&Var_isin(p->variable,p->tokenlist[p->cw].token)!=NULL)
   {
         tmp = Var_isin(p->variable, p->tokenlist[p->cw].token);
         num = tmp->value;
         p->cw = p->cw +1;
         return num;
   }   
   if (!NUM(p->tokenlist[p->cw].token))
   {
      ERROR("Not number");
   }
   num = NUM(p->tokenlist[p->cw].token);
   p->cw = p->cw +1;
   return num;
}
int check_Varnum(Prog *p)
{
      if (!NUM(p->tokenlist[p->cw].token)&&Var_isin(p->variable,p->tokenlist[p->cw].token)!=NULL)
      {             
         return 1;
      }   
      if (!NUM(p->tokenlist[p->cw].token))
      {
         return 0;
      }
      return 1;
}
/* ---- Program Start ---- */
void program_Start(Prog *p, SDL_Simplewin *sw)
{
      if (!STRSAME(p->tokenlist[p->cw].token,START))
      {
            ERROR("NO BEGIN STATEMENT \n");
      }
      /*printf("Start PASS \n");*/
      p->cw ++;
      Code(p, sw);
      
}

void Code (Prog *p, SDL_Simplewin *sw)
{
      if(STRSAME(p->tokenlist[p->cw].token, END))
      {
          /*  printf("\nEND\n");*/
          return;
      }
      Statement(p,sw);
      Code(p, sw);
}

void Statement(Prog *p,SDL_Simplewin *sw)
{
   check_Instruction(p,sw);
   check_for_loop(p,sw);
   set_var(p);
   set_color(p,sw);
   Reset_loc(p);
   delay(p);
}
/* ---- LOOP ---- */
void check_for_loop(Prog *p, SDL_Simplewin *sw)
{     
      Var *tmp_var;
      int start, end, tmp;
      if (STRSAME(p->tokenlist[p->cw].token, DO))
      {
            /*printf("%s ",p->tokenlist[p->cw].token);  */
            p->cw ++;
            tmp_var = load_Var(p);
            start = get_start_num(p);
            end = get_End_num(p);
            tmp = p->cw;
            /*printf("\n ");*/
            while(start!=end)
            {
                  tmp_var->value = start;
                  p->cw = tmp;
                  program_Start(p,sw);
                  start++;
            }
            p->cw++;
      }
}
int get_start_num(Prog *p)
{
      int start;
      if(!STRSAME(p->tokenlist[p->cw].token, FROM))
      {
            ERROR("No Start number");
      }
      /*printf("FROM ");*/
      p->cw ++;
      start = load_varnum(p);
      return start;
}
int get_End_num(Prog *p)
{
      int end;
      if(!STRSAME(p->tokenlist[p->cw].token, TO))
      {
            ERROR("No End number");
      }
      /*printf("TO ");*/
      p->cw ++;
      end = load_varnum(p);
      return end;
}
/*----- COLOR SET ---- */
void set_color(Prog *p,SDL_Simplewin *sw)
{
      int R;
      int G;
      int B;
      if (STRSAME(p->tokenlist[p->cw].token, COLOR))
      {
            p->cw ++;
            R = load_varnum(p);
            if(R>SDL_8BITCOLOUR||R<0)
            {
                  ERROR("Failed to Set COLOUR ");
            }
            G = load_varnum(p);
            if(G >SDL_8BITCOLOUR ||R<0)
            {
                  ERROR("Failed to Set COLOUR ");
            }
            B = load_varnum(p);
            if(B >SDL_8BITCOLOUR ||R <0)
            {
                  ERROR("Failed to Set COLOUR ");
            }
            Neill_SDL_SetDrawColour(sw, R,G,B);
            p->colour_display->color_default = True;

      }   

}
/* --- Reset loc ---- */
void Reset_loc(Prog *p)
{
      if(STRSAME(p->tokenlist[p->cw].token,RESET)){
            p->loc->x = 400;
            p->loc->y = 300;
            p->loc->degree = 0;
            p->cw++;
      }
}
/*--- DRAW LINE ---- */
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
/* ---- Instruction ---- */
void check_Instruction(Prog *p,SDL_Simplewin *sw)
{
      int num;
      float arc;
      float x_start, x_end, y_start,y_end;
      if(STRSAME(p->tokenlist[p->cw].token,LT))
      {
         /*printf("LT ");*/
         p->cw = p->cw +1;
         num = load_varnum(p);
         p->loc->degree += num;
      }
      if (STRSAME(p->tokenlist[p->cw].token,FD)) {  
         /*printf("FD ");*/
         p->cw = p->cw +1;
         num = load_varnum(p);
         x_start = p->loc->x;
         y_start = p->loc->y;
         arc = p->loc->degree / ARC * M_PI;
         x_end = x_start + num * cos(arc);
         y_end = y_start + num * sin(arc);
         p->loc->x = x_end;
         p->loc->y = y_end;
         /*printf("(%d, %d) to (%d,%d)",x_start,y_start,x_end,y_end);*/
         draw_line(p,x_start,y_start,x_end,y_end,sw);
      }
      if (STRSAME(p->tokenlist[p->cw].token,RT)) {
         /*printf("RT ");*/
         p->cw = p->cw +1;
         num = load_varnum(p);         
         p->loc->degree -= num;
      }
}
/* Delay  */
void delay (Prog *p)
{
      int time;
      if (STRSAME(p->tokenlist[p->cw].token,DELAY))
      {
            p->cw++;
            time = load_varnum(p);
            SDL_Delay(time);
      }
}
/* ---- Operator ---- */
void postfix_cal (Prog *p)
{
      float result = 0;
      float op1, op2 ;
      if (STRSAME(p->tokenlist[p->cw].token,MULT))
      {
            op1 = Pop(p);
            op2 = Pop(p);
            result = op1 * op2;
      }
      else if (STRSAME(p->tokenlist[p->cw].token,PLUS))
      {
            op1 = Pop(p);
            op2 = Pop(p);
            result = op1 + op2;
      }
      else if (STRSAME(p->tokenlist[p->cw].token,DEVIDE))
      {
            op1 = Pop(p);
            op2 = Pop(p);
            result = op2 / op1;
      }
      else if (STRSAME(p->tokenlist[p->cw].token,MINUS))
      {
            op1 = Pop(p);
            op2 = Pop(p);
            result = op2 - op1;
            
      }
      p->cw++;
      Push(p,result);    
}
/*--- Stack Function --- */
void Push (Prog *p, float num)
{
      assert(p->s->top < MAX_SIZE);
      p->s->data[p->s->top] = num; 
      p->s->top = p->s->top + 1;
}
float Pop (Prog *p)
{
      assert(p->s->top > 0);
      p->s->top = p->s->top - 1;
      return p->s->data[p->s->top];
}
/*----free memory---- */
void program_free(Prog **q)
{
      int i; 
      Prog *p = *q;
      for (i=0; i<p->sz;i++)
      {
            free(p->tokenlist[i].token);
      }
      var_free(&(p->variable));
      free(p->loc);
      free(p->tokenlist);
      free(p->s);
      free(p);
      *q = NULL;
}
void old_program_free(Prog **s)
{
      int i; 
      Prog *p = *s;
      for (i=0; i<p->sz;i++)
      {
            free(p->tokenlist[i].token);
      }
      free(p->variable);
      free(p->loc);
      free(p->tokenlist);
      free(p);
      *s = NULL;
}
void var_free(Var **s)
{   
	if ((*s)==NULL && s==NULL)
	{
		return ;
	}
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

