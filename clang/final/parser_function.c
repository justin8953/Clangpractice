#define MAXTOKENSIZE 10
#define GROWNUM 2
void test_Prog_intialise ()
{
   Prog *s;
   s = intialise_program(MAXTOKENSIZE);
   assert(s!=NULL);
   assert(s->tokenlist!=NULL);
   assert(s->variable!=NULL);
   assert(s->colour_display!=NULL);
   assert(s->lib!=NULL);
   assert(s->s!=NULL);
   assert(s->loc!=NULL);
   assert(s->next==NULL);
   assert(s->cw==0);
   assert(s->sz==MAXTOKENSIZE);
   program_free(&s);
   assert(s==NULL);   
}
void test_Prog_and_Lib_grow()
{
   Prog *Old_prog;
   Lib *Old_lib;
   int Old_prog_size, Old_lib_size;
   Old_prog  = intialise_program(MAXTOKENSIZE);
   Old_prog_size = Old_prog->sz;
   Prog_grow(Old_prog, Old_prog->sz);
   assert(Old_prog->sz = GROWNUM * Old_prog_size);
   Old_lib = intialise_lib(NULL, MAXTOKENSIZE);
   Old_lib_size = Old_lib->token_sz;
   lib_grow(Old_lib, Old_lib->token_sz);
   assert(Old_lib->token_sz = GROWNUM * Old_lib_size);
   program_free(&Old_prog);
   assert(Old_prog==NULL);    
   lib_free(&Old_lib);
   assert(Old_lib==NULL);
}
void test_FD_RT_LT()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE);
   printf("\n TESTING FD ...... \n" );
   strcpy(p->tokenlist[0].token,"FD");
   strcpy(p->tokenlist[1].token,"1");
   p->cw = 1;
   assert(invalid_token(p)==True);
   p->cw = 0;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("\n TESTING RT ...... \n" );
   strcpy(p->tokenlist[2].token,"RT");
   strcpy(p->tokenlist[3].token,"C");
   p->cw = 3;
   assert(invalid_token(p)==True);
   p->cw = 2;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("\n TESTING LT ...... \n" );
   strcpy(p->tokenlist[4].token,"LT");
   strcpy(p->tokenlist[5].token,"2");
   p->cw = 5;
   assert(invalid_token(p)==True);
   p->cw = 4;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("\n ---- Error Test ----\n\n");
   strcpy(p->tokenlist[6].token,"LT");
   strcpy(p->tokenlist[7].token,"LT");
   p->cw = 7;
   assert(invalid_token(p)==False);
   p->cw = 6;
   check_instruction(p);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL);    
}
void test_DO_LOOP ()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE);
   strcpy(p->tokenlist[0].token,"DO");
   strcpy(p->tokenlist[1].token,"A");
   strcpy(p->tokenlist[2].token,"FROM");
   strcpy(p->tokenlist[3].token,"1");
   printf("\n TESTING START NUMBER  ...... \n" );
   p->cw = 2;
   assert(do_loop_start(p)==True);
   printf(" PASS ...... \n" );
   strcpy(p->tokenlist[4].token,"TO");
   strcpy(p->tokenlist[5].token,"10");
   printf("\n TESTING END NUMBER  ...... \n" );
   p->cw = 4;
   assert(do_loop_end(p)==True);
   printf(" PASS ...... \n" );
   p->cw = 2;
   printf("\n TESTING DO LOOP  ...... \n" );
   assert(do_loop(p)==True);
   assert(p->cw == 6);
   printf(" PASS ...... \n" );
   printf("---- ERROR TEST ----- \n");
   strcpy(p->tokenlist[0].token,"DO");
   strcpy(p->tokenlist[1].token,"FD");
   strcpy(p->tokenlist[2].token,"FROM");
   strcpy(p->tokenlist[3].token,"DO");
   p->cw = 2;
   assert(do_loop_start(p)==False);
   strcpy(p->tokenlist[4].token,"TO");
   strcpy(p->tokenlist[5].token,"DO"); 
   p->cw = 4;
   assert(do_loop_end(p)==False);
   p->cw = 2;
   assert(do_loop(p)==False);
   p->cw = 0;
   check_instruction(p);
   assert(p->cw == 5);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL);          
}

void test_SET ()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE);
   strcpy(p->tokenlist[0].token,"SET");
   strcpy(p->tokenlist[1].token,"A");
   strcpy(p->tokenlist[2].token,":=");
   printf("\n TESTING ASSIGNED ...... \n" );
   p->cw = 2;
   assert(do_set(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING POLISH VARNUM ...... \n" );
   strcpy(p->tokenlist[3].token,"2");
   assert(check_polish(p->tokenlist[3].token)==DONUM);
   printf(" PASS ...... \n" );
   printf("\n TESTING POLISH VARNUM ...... \n" );
   strcpy(p->tokenlist[4].token,"C");
   assert(check_polish(p->tokenlist[4].token)==DOVAR);
   printf(" PASS ...... \n" );
   printf("\n TESTING POLISH OPERATOR ...... \n" );
   strcpy(p->tokenlist[5].token,"*");
   assert(check_polish(p->tokenlist[5].token)==DOMULTI);
   printf(" PASS ...... \n" );
   printf("\n TESTING SEMI END  ...... \n" );
   strcpy(p->tokenlist[6].token,";");
   assert(check_polish(p->tokenlist[6].token)==SEMIEND);
   printf(" PASS ...... \n" );
   p->cw = 2;
   printf("\n TESTING POLISH ...... \n" );
   do_polish(p);
   printf(" PASS ...... \n" );
   p->cw = 0;
   check_instruction(p);
   printf("---- SEMANTIC ERROR TEST (PASS IN PASRER NOT IN INTERPRETER)  ----- \n");
   p->cw = 2;
   strcpy(p->tokenlist[0].token,"SET");
   strcpy(p->tokenlist[1].token,"A");
   strcpy(p->tokenlist[2].token,":=");
   strcpy(p->tokenlist[3].token,"2");
   strcpy(p->tokenlist[4].token,"+");
   strcpy(p->tokenlist[5].token,"*");
   strcpy(p->tokenlist[6].token,";");
   do_polish(p);
   p->cw = 0;
   check_instruction(p);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL);          
}
void test_Color ()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE);
   strcpy(p->tokenlist[0].token,"COLOR");
   strcpy(p->tokenlist[1].token,"255");
   strcpy(p->tokenlist[2].token,"255");
   strcpy(p->tokenlist[3].token,"255");
   printf("\n TESTING COLOUR RED NUMBER VALID ...... \n" );
   p->cw = 1;
   assert(color_R(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING COLOUR GREEN NUMBER VALID ...... \n" );
   p->cw = 2;
   assert(color_G(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING COLOUR BLUE NUMBER VALID ...... \n" );
   p->cw = 3;
   assert(color_B(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING COLOUR  ...... \n" );
   p->cw = 1;
   assert(do_color(p)==True);
   p->cw =0;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("---- ERROR TEST  ----- \n");
   strcpy(p->tokenlist[0].token,"COLOR");
   strcpy(p->tokenlist[1].token,"FD");
   strcpy(p->tokenlist[2].token,"A");
   strcpy(p->tokenlist[3].token,"LT");
   p->cw = 1;
   assert(color_R(p)==False);
   p->cw = 2;
   assert(color_G(p)==True);
   p->cw = 3;
   assert(color_B(p)==False);
   p->cw = 1;
   assert(do_color(p)==False);
   p->cw =0;
   check_instruction(p);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL);  
}
void test_RESET ()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE);
   strcpy(p->tokenlist[0].token,"RESET");
   strcpy(p->tokenlist[1].token,"255");
   strcpy(p->tokenlist[2].token,"255");
   strcpy(p->tokenlist[3].token,"255");
   printf("\n TESTING RESET X NUMBER VALID ...... \n" );
   p->cw = 1;
   assert(reset_x(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING RESET Y NUMBER VALID ...... \n" );
   p->cw = 2;
   assert(reset_y(p)==True);
   printf(" PASS ...... \n" );
   p->cw = 3;
   printf("\n TESTING RESET DEGREE NUMBER VALID ...... \n" );
   assert(reset_degree(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING RESET ...... \n" );
   p->cw = 1;
   assert(do_reset(p)==True);
   p->cw =0;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("---- ERROR TEST  ----- \n");
   strcpy(p->tokenlist[0].token,"RESET");
   strcpy(p->tokenlist[1].token,"FD");
   strcpy(p->tokenlist[2].token,"A");
   strcpy(p->tokenlist[3].token,"LT");
   p->cw = 1;
   assert(reset_x(p)==False);
   p->cw = 2;
   assert(reset_y(p)==True);
   p->cw = 3;
   assert(reset_degree(p)==False);
   p->cw = 1;
   assert(do_reset(p)==False);
   p->cw =0;
   check_instruction(p);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL);    
}
void test_delay ()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE);
   strcpy(p->tokenlist[0].token,"DELAY");
   strcpy(p->tokenlist[1].token,"100");
   printf("\n TESTING DELAY TIME NUMBER VALID ...... \n" );
   p->cw = 1;
   assert(invalid_token(p)==True);
   printf(" PASS ...... \n" );
   printf("\n TESTING DELAY  ...... \n" );
   p->cw = 0;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("---- Error Test ---- \n\n");
   strcpy(p->tokenlist[2].token,"DELAY");
   strcpy(p->tokenlist[3].token,"LT");
   p->cw = 3;
   assert(invalid_token(p)==False);
   p->cw = 2;
   check_instruction(p);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL); 
}
void test_do_function ()
{
   Prog *p;
   p = intialise_program(MAXTOKENSIZE*GROWNUM);
   printf("\n TESTING USING FUNCTION ...... \n" );
   strcpy(p->tokenlist[0].token,"activate.run");
   assert(dot_isin(p->tokenlist[0].token)!=0);
   printf(" PASS ...... \n" );
   strcpy(p->tokenlist[1].token,"(");
   strcpy(p->tokenlist[2].token,"length");
   strcpy(p->tokenlist[3].token,":=");
   strcpy(p->tokenlist[4].token,"50");
   printf("\n TESTING POLISH NUMVAR ...... \n" );
   assert(check_polish(p->tokenlist[4].token)==DONUM);
   printf(" PASS ...... \n" );
   printf("\n TESTING POLISH COMMA ...... \n" );
   strcpy(p->tokenlist[5].token,",");
   assert(check_polish(p->tokenlist[5].token)==COMMAEND);
   printf(" PASS ...... \n" );
   strcpy(p->tokenlist[6].token,")");
   p->cw = 3;
   printf("\n TESTING ASSIGNED VALUE  ...... \n" );
   assert(do_assign_local_value(p)==True);
   assert(check_polish(p->tokenlist[6].token)==CLOSEPARENTHESE);
   p->cw =0;
   check_instruction(p);
   printf(" PASS ...... \n" );
   printf("\n ---Testing VOID function  ----- \n");
   strcpy(p->tokenlist[7].token,"activate.run");
   assert(dot_isin(p->tokenlist[7].token)!=0);
   strcpy(p->tokenlist[8].token,"(");
   strcpy(p->tokenlist[9].token,"VOID");
   strcpy(p->tokenlist[10].token,")");
   p->cw =7;
   check_instruction(p);
   printf("\n\n -------------------- \n");
   program_free(&p);
   assert(p==NULL); 
}
void test_all()
{ 
   printf("\n ---- Testing Initialise Function ---- \n");
   test_Prog_intialise ();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing Program and Library growing ---- \n");
   test_Prog_and_Lib_grow();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING FD & RT & LT ---- \n ");
   test_FD_RT_LT();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING DO LOOP ---- \n ");
   test_DO_LOOP();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING SET and POLISH ---- \n ");
   test_SET ();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING COLOR ---- \n ");
   test_Color();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING RESET ---- \n ");
   test_RESET();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING DELAY ---- \n ");
   test_delay();
   printf("\n Pass ......\n ");

   printf("\n ---- Testing PARSING DO FUNCTION ---- \n ");
   test_do_function();
   printf("\n Pass ......\n ");

}
