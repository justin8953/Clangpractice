LIBS = `sdl2-config --libs` -lSDL2_ttf -lm
CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi $(LIBS)
DEBUG = -g3
OPTIM = -O2
VALGRIND = --error-exitcode=1 --quiet --leak-check=full
TEXT1 = nested.txt
TEXT2 = extension.txt
all: interp parse extension

extension: extension.c neillsdl2.c interpreter_function.c turtle_function.c  turtle_function.h interpreter_function.h grammar.h neillsdl2.h 
	$(CC) extension.c neillsdl2.c interpreter_function.c turtle_function.c -o extension $(CFLAGS) $(OPTIM) -include neillsdl2.h -include turtle_function.h -include interpreter_function.h  -include grammar.h  
interp: interp.c   neillsdl2.c interpreter_function.c turtle_function.c turtle_function.h interpreter_function.h grammar.h neillsdl2.h 
	$(CC) interp.c  neillsdl2.c interpreter_function.c turtle_function.c -o interp $(CFLAGS) $(OPTIM) -include neillsdl2.h -include turtle_function.h -include interpreter_function.h  -include grammar.h  
parse: parse.c parser_function.c neillsdl2.c turtle_function.c turtle_function.h grammar.h neillsdl2.h parser_function.h
	$(CC) parse.c parser_function.c turtle_function.c neillsdl2.c -o parse $(CFLAGS) $(OPTIM) -include neillsdl2.h -include turtle_function.h  -include grammar.h    -include parser_function.h

run: all
	./parse $(TEXT1)
	./interp $(TEXT1)
	./extension $(TEXT1)
	./extension $(TEXT2)

clean:
	rm -f interp parse extension

.PHONY: clean run all
