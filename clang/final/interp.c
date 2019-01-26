
int main(int argc, char const *argv[])
{
   FILE *fn;
   SDL_Simplewin sw;
   int i;
   Prog *prog;
   test_interpreter_all();
   if (argc !=2)
   {
      fprintf(stderr, "Usage : i%s <parse file>", argv[0]);
   }
   prog = intialise_program(MAXTOKEN);
   printf("Intilise ..... \n");
   if(!(fn = fopen(argv[1],"r")))
   {
      fprintf(stderr, "Cannot open test.txt \n");
      exit(2);
   }
   printf("File %s open ..... \n",argv[1]);
   i = 0;
   while(fscanf(fn, "%s",prog->tokenlist[i++].token)==1)
   {
      if(i > prog->sz*GROWFACT)
      {
         Prog_grow(prog,i);
      }
   }
   printf("File Load ..... \n");
   Neill_SDL_Init(&sw);
   printf("Program Start ..... \n");
   Block_start(prog, &sw);
   printf("Program End ..... \n");
   /* Clear up graphics subsystems */
   SDL_Quit();
   atexit(SDL_Quit);  
   printf("Program Free ..... \n");
   program_free(&prog);
   printf("File Close ..... \n");
   fclose(fn);
   
   /* code */
   return 0;
}
