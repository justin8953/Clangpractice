

int main (int argc, char const *argv[])
{
   FILE *fn;
   int i;
   Prog *prog;
   if (argc !=2)
   {
      fprintf(stderr, "Usage : i%s <parse file>", argv[0]);
   }
   prog = intialise_program(MAXTOKEN);
   if(!(fn = fopen(argv[1],"r")))
   {
      fprintf(stderr, "Cannot open test.txt \n");
      exit(2);
   }
   i = 0;
   while(fscanf(fn, "%s",prog->tokenlist[i++].token)==1)
   {
      if(i > prog->sz*GROWFACT)
      {
         grow(prog,i);
      }
   }
   test_all(prog);
   program_free(&prog);
   assert(prog==NULL);
}
