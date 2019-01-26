#define MAX_TOKENSIZE 10
#define GROWNUM 2

void test_interpreter_all()
{
   printf("---- TESTING FD RT LT INTERPRETER ----\n");
   test_interpre_FD_RT_LT();
   printf("---- PASS ---- \n");
   printf("-----TESTING DO LOOP INTERPRETER -----------\n");
   test_interpre_DO_LOOP();
   printf("---PASS---- \n");
   printf("-----TESTING SET INTERPRETER -----------\n");
   test_interpret_SET();
   printf("---PASS---- \n");
   printf("-----TESTING VAR or NUM  -----------\n");
   test_is_num();
   printf("---PASS---- \n");
}

/*intepreter */
void test_is_num()
{
   Prog *p;
   p = intialise_program(MAX_TOKENSIZE);
   test_varnum();
   strcpy(p->tokenlist[0].token,"10");
   assert(IS_NUM(p)==True);
   strcpy(p->variable->name,"A");
   p->variable->value = 10;
   strcpy(p->tokenlist[1].token,"A");
   p->cw = 1;
   assert(IS_NUM(p)==True);
   strcpy(p->tokenlist[1].token,"C");
   assert(IS_NUM(p)==False);
   program_free(&p);
   assert(p==NULL);    
}

void test_varnum()
{
   assert(ISVARNUM("1")==NUM);
   assert(ISVARNUM("num")==VAR);
}

void test_interpre_FD_RT_LT()
{
   Prog *p;
   Var *tmp;
   SDL_Simplewin sw;
   Neill_SDL_Init(&sw);
   p = intialise_program(MAX_TOKENSIZE);
   strcpy(p->tokenlist[0].token,"LT");
   strcpy(p->tokenlist[1].token,"1");
   printf(" TESTING LT ....... \n");
   p->cw = 1;
   go_LT(p);
   assert(p->loc->degree ==1);
   printf(" PASS ...... \n" );
   strcpy(p->tokenlist[2].token,"RT");
   strcpy(p->tokenlist[3].token,"1");
   p->cw = 3;
   printf(" TESTING RT ....... \n");
   go_RT(p);
   assert(p->loc->degree ==0);
   printf(" PASS ...... \n" );
   strcpy(p->tokenlist[4].token,"FD");
   strcpy(p->tokenlist[5].token,"1");
   printf(" TESTING FD ....... \n");
   p->cw = 5;
   go_FD(p, &sw);
   assert(p->loc->x ==401.0);
   assert(p->loc->y ==300.0);
   assert(p->loc->degree ==0);
   printf(" PASS ...... \n" );
   printf(" TESTING VAR HAS BEEN ASSIGNED ....... \n");
   Declare_Var(p->variable, "C");
   tmp = Var_isin(p->variable, "C");
   tmp->value = 10;
   strcpy(p->tokenlist[6].token,"LT");
   strcpy(p->tokenlist[7].token,"C");
   p->cw = 7;
   go_LT(p);
   assert(p->loc->degree ==10);
   printf(" PASS ...... \n" );
   printf("---- Error Test ----\n\n");
   printf("---- unassigned value testing ---- \n");
   strcpy(p->tokenlist[6].token,"LT");
   strcpy(p->tokenlist[7].token,"D");
   p->cw = 7;
   go_LT(p);
   printf("\n\n--------\n");
   SDL_Quit();
   atexit(SDL_Quit);  
   program_free(&p);
   assert(p==NULL);    
}

void test_interpre_DO_LOOP ()
{
   Var *tmp;
   Var *C, *D;
   Prog *p;
   p = intialise_program(MAX_TOKENSIZE);
   strcpy(p->tokenlist[0].token,"DO");
   strcpy(p->tokenlist[1].token,"A");
   printf(" TESTING LOAD VAR ....... \n");
   p->cw = 1;
   tmp = load_Var(p);
   assert(tmp!=NULL);
   printf(" PASS ...... \n" );
   strcpy(p->tokenlist[2].token,"FROM");
   strcpy(p->tokenlist[3].token,"1");
   printf(" TESTING GET START NUMBER ....... \n");
   p->cw = 2;
   assert(get_start_num(p)==1);
   printf(" PASS ...... \n" );
   printf(" TESTING GET END NUMBER ....... \n");
   strcpy(p->tokenlist[4].token,"TO");
   strcpy(p->tokenlist[5].token,"10");
   p->cw = 4;
   assert(get_End_num(p)==10);
   printf(" PASS ...... \n" );
   printf(" TESTING GET START VARIABLE NUMBER ....... \n");
   printf(" DECLARE C ....... \n");
   Declare_Var(p->variable, "C");
   C = Var_isin(p->variable, "C");
   printf(" ASSIGNED 10 INTO  C ....... \n");
   C->value = 10;
   printf(" DECLARE D ....... \n");
   Declare_Var(p->variable, "D");
   D = Var_isin(p->variable, "D");
   printf(" ASSIGNED 20 INTO  C ....... \n");
   D->value = 20;
   strcpy(p->tokenlist[3].token,"C");
   printf(" TESTING GET START VARIABLE NUMBER ....... \n");
   p->cw = 2;
   assert(get_start_num(p)==10);
   printf(" PASS ...... \n" );
   printf(" TESTING GET END VARIABLE NUMBER ....... \n");
   strcpy(p->tokenlist[5].token,"D");
   p->cw = 4;
   assert(get_End_num(p)==20);
   printf(" PASS ...... \n" );

   printf("---- Error Test ----\n\n");
   printf("---- unassigned value testing ---- \n");
   strcpy(p->tokenlist[2].token,"FROM");
   strcpy(p->tokenlist[3].token,"E");
   printf(" TESTING GET START NUMBER ....... \n");
   p->cw = 2;
   get_start_num(p);
   strcpy(p->tokenlist[4].token,"TO");
   strcpy(p->tokenlist[5].token,"E");
   printf(" TESTING GET START NUMBER ....... \n");
   p->cw = 2;
   get_End_num(p);
   printf("\n\n--------\n");
   program_free(&p);
   assert(p==NULL);          
}

void test_interpret_SET ()
{
   Prog *p;
   Var *tmp;
   p = intialise_program(MAX_TOKENSIZE);
   Declare_Var(p->variable, "C");
   tmp = Var_isin(p->variable, "C");
   tmp->value = 10;
   strcpy(p->tokenlist[0].token,"SET");
   strcpy(p->tokenlist[1].token,"A");
   strcpy(p->tokenlist[2].token,":=");
   strcpy(p->tokenlist[3].token,"2");
   strcpy(p->tokenlist[4].token,"C");
   strcpy(p->tokenlist[5].token,"*");
   strcpy(p->tokenlist[6].token,";");
   printf(" TESTING RPN ....... \n");
   p->cw = 3;
   assert(do_Reverse_polish(p)==True);
   printf(" PASS ...... \n" );
   assert(Pop(p)==20.0);
   printf(" A := 20 ...... \n" );
   printf("---- SEMANTIC ERROR TEST (PASS IN PASRER NOT IN INTERPRETER)  ----- \n");
   printf("SET A := 2 + * ; \n");
   strcpy(p->tokenlist[0].token,"SET");
   strcpy(p->tokenlist[1].token,"A");
   strcpy(p->tokenlist[2].token,":=");
   strcpy(p->tokenlist[3].token,"2");
   printf("Push %s  in to Stack \n",p->tokenlist[3].token);
   Push(p,2);
   strcpy(p->tokenlist[4].token,"+");
   printf("DO %s \n",p->tokenlist[4].token);
   printf("POP first Value %0.1f \n",Pop(p));
   assert(p->s->top==0);
   printf("GO TO THE BOTTOM \n");
   printf("No value in stack \n");
   strcpy(p->tokenlist[5].token,"*");
   strcpy(p->tokenlist[6].token,";");
   printf("INVALID EXPRESSION \n");
   printf("\n\n--------\n");
   program_free(&p);
   assert(p==NULL);       

}

/*---- EXTENSION TESTING ----*/
void test_extension_all()
{
   printf("-----TESTING COLOR ----- \n");
   test_INTERPR_Color();
   printf("----PASS---- \n");
   printf("-----TESTING RESET ----- \n");
   test_INTERPR_RESET ();
   printf("----PASS---- \n");
   printf("---- TESTING LIBRARY FUNCTION----\n");
   test_load_library();
   printf("----PASS--- \n");
   printf("---- FIND LIBRARY ----\n");
   test_find_library();
   printf("----PASS--- \n");
   printf("-----TESTING Strip WORD ----- \n");
   test_strip_word ();
   printf("----PASS---- \n");

}

void test_INTERPR_Color ()
{
   Prog *p;
   SDL_Simplewin sw;
   Neill_SDL_Init(&sw);
   p = intialise_program(MAX_TOKENSIZE);
   strcpy(p->tokenlist[0].token,"COLOR");
   strcpy(p->tokenlist[1].token,"255");
   strcpy(p->tokenlist[2].token,"255");
   strcpy(p->tokenlist[3].token,"255");
   p->cw = 1;
   go_COLOR(p,&sw);
   printf("---- ERROR TEST  ----- \n");
   printf("---- INVALID 8 BIT COLOUR NUMBER  ----- \n");
   strcpy(p->tokenlist[0].token,"COLOR");
   strcpy(p->tokenlist[1].token,"266");
   strcpy(p->tokenlist[2].token,"266");
   strcpy(p->tokenlist[3].token,"266");
   p->cw = 1;
   go_COLOR(p,&sw);
   printf("---- UNASSIGNED VARIABLE   ----- \n");
   strcpy(p->tokenlist[0].token,"COLOR");
   strcpy(p->tokenlist[1].token,"C");
   strcpy(p->tokenlist[2].token,"A");
   strcpy(p->tokenlist[3].token,"266");
   p->cw = 1;
   go_COLOR(p,&sw);
   printf("\n\n--------\n");
   SDL_Quit();
   atexit(SDL_Quit); 
   program_free(&p);
   assert(p==NULL);  
}

void test_INTERPR_RESET ()
{
   Prog *p;
   p = intialise_program(MAX_TOKENSIZE);
   strcpy(p->tokenlist[0].token,"RESET");
   strcpy(p->tokenlist[1].token,"255");
   strcpy(p->tokenlist[2].token,"255");
   strcpy(p->tokenlist[3].token,"255");
   p->cw = 1;
   printf(" TESTING RESET X ....... \n");
   go_RESET_X(p);
   assert(p->loc->x==255.0);
   printf(" PASS ...... \n" );
   p->cw = 2;
   printf(" TESTING RESET Y ....... \n");
   go_RESET_Y(p);
   assert(p->loc->y==255.0);
   printf(" PASS ...... \n" );
   p->cw = 3;
   printf(" TESTING RESET DEGREE ....... \n");
   go_RESET_degree(p);
   assert(p->loc->degree==255.0);
   printf(" PASS ...... \n" );
   printf("---- ERROR TEST  ----- \n");
   strcpy(p->tokenlist[0].token,"RESET");
   strcpy(p->tokenlist[1].token,"20");
   strcpy(p->tokenlist[2].token,"A");
   strcpy(p->tokenlist[3].token,"10");
   p->cw = 1;
   go_RESET_X(p);
   assert(p->loc->x==20.0);
   p->cw = 2;
   go_RESET_Y(p);
   p->cw = 3;
   go_RESET_degree(p);
   assert(p->loc->degree==10.0);
   printf("\n\n--------\n");
   program_free(&p);
   assert(p==NULL);    
}
void test_load_library ()
{
   Prog *p;
   p = intialise_program(MAX_TOKENSIZE);
   strcpy(p->tokenlist[0].token,"extension_function");
   assert(Load_lib_into_prog(p)!=NULL);
   printf("%s \n",string_process(p->tokenlist[0].token));
   assert(STRSAME(string_process(p->tokenlist[0].token),"extension_function.txt"));
   program_free(&p);
   assert(p==NULL); 
}
void test_find_library ()
{
   Prog *p;
   p = intialise_program(MAX_TOKENSIZE*GROWNUM);
   strcpy(p->tokenlist[0].token,"IMPORT");
   strcpy(p->tokenlist[1].token,"extension_function");
   p->cw = 1;
   parser_lib(p);
   program_free(&p);
   assert(p==NULL);  
}
