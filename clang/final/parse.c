
int main(int argc, char const *argv[])
{
   FILE *fn;
   int i;
   Prog *prog;
   printf( "START TESTING ..........  \n");
   test_all();
   printf( "ALL PASS ...... \n");
   printf( "-----TESTING FILES ----- \n");
   if (argc !=2)
   {
      fprintf(stderr, "Usage : i%s <parse file>", argv[0]);
   }
   prog = intialise_program(MAXTOKEN);
   printf("Intilise ..... \n");
   if(!(fn = fopen(argv[1],"r")))
   {
      fprintf(stderr, "Cannot open %s \n",argv[1]);
      exit(2);
   }
   printf("File open ..... \n");
   i = 0;
   while(fscanf(fn, "%s",prog->tokenlist[i++].token)==1)
   {
      if(i > prog->sz*GROWFACT)
      {
         Prog_grow(prog,i);
      }
   }
   printf("File Loaded ..... \n");
   printf("Program Start ..... \n");
   parserstart(prog);
   printf("Program End ..... \n");
   /* Clear up graphics subsystems */
   printf("Program Free ..... \n");
   program_free(&prog);
   printf("File Close ..... \n");
   fclose(fn);
   printf( "-----PASS ----- \n");
   /* code */
   return 0;
}
