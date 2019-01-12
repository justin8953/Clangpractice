
void test_all(Prog *s)
{
      assert(test_start(s)==True);
      test_code(s);

}
bool test_start (Prog *s)
{
   if (!STRSAME(s->tokenlist[s->cw].token,START))
   {
            return False;
   }
   s->cw ++;
   return True;
}
void test_code(Prog *p)
{
      if(STRSAME(p->tokenlist[p->cw].token, END))
      {
          return;
      }
      test_statement(p);
      test_code(p);
}
void test_statement(Prog *p)
{
      test_instruction(p);
      test_for_loop(p);
      test_set_var(p);

}
void test_for_loop(Prog *p)
{
      Var *tmp_var;
      if (STRSAME(p->tokenlist[p->cw].token, DO))
      {
            p->cw++;
            tmp_var = load_Var(p);
            assert(tmp_var!=NULL);
            assert(test_start_num(p)==True);
            assert(test_end_num(p)==True);
            test_all(p);
      }
}
void test_set_var(Prog *p)
{     
      Var *new;
      if (STRSAME(p->tokenlist[p->cw].token,SET))
      {
            p->cw ++;
            new = load_Var(p);
            assert(new!=NULL);
            test_assign_value(p);
            p->cw++;
      }
}
bool test_assign_value(Prog *p)
{
      float num;
      if (STRSAME(p->tokenlist[p->cw].token,ASSIGN))
      {
            /*printf("%s ",ASSIGN);*/
            p->cw++;
            while (!STRSAME(p->tokenlist[p->cw].token,SEMI))
            {
                  if (check_Varnum(p))
                  {
                        num  = load_varnum(p);
                        Push(p,num);
                  }else{
                        postfix_cal(p); 
                  }
            }
            Pop(p);
      }else{
            return False;
      }
      return True;
}
void test_instruction(Prog *p)
{
      if(STRSAME(p->tokenlist[p->cw].token,LT))
      {
            p->cw++;
            assert(test_load_varnum(p)==True);
      }
      if (STRSAME(p->tokenlist[p->cw].token,FD)) { 
            p->cw++;
            assert(test_load_varnum(p)==True);
      }
      if (STRSAME(p->tokenlist[p->cw].token,RT)) {
            p->cw++;
            assert(test_load_varnum(p)==True);
      }
}
bool test_start_num (Prog *p)
{
      if(!STRSAME(p->tokenlist[p->cw].token, FROM))
      {
            return False;
      }
      p->cw++;
      assert(test_load_varnum(p)==True);
      return True;
}
bool test_end_num (Prog *p)
{
      if(!STRSAME(p->tokenlist[p->cw].token, TO))
      {
            return False;
      }
      p->cw++;
      assert(test_load_varnum(p)==True);
      return True;
}
bool test_load_varnum(Prog *p)
{ 
   if (!NUM(p->tokenlist[p->cw].token)&&Var_isin(p->variable,p->tokenlist[p->cw].token)!=NULL)
   {
         p->cw ++;
         return True;
   }
   if (!NUM(p->tokenlist[p->cw].token))
   {
      return False;
   }
   p-> cw++;
   return True;
}
