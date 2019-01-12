LIBS = `sdl2-config --libs` -lm
CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi $(LIBS)
DEBUG = -g3
OPTIM = -O2
VALGRIND = --error-exitcode=1 --quiet --leak-check=full
TEXT1 = oct.txt
TEXT2 = loop.txt
TEXT3 = nested.txt
TEXT4 = circle.txt
TEXT5 = flow.txt
TEXT6 = foward_test.txt
TEXT7 = octloop.txt
TEXT8 = triangle.txt
all: interp parse 

interp: blocks.c neillsdl2.c parse.c parse_function.h parse_instruct.h neillsdl2.h
	$(CC) blocks.c neillsdl2.c parse.c -o interp $(CFLAGS) $(OPTIM) -include neillsdl2.h -include parse_function.h  -include parse_instruct.h 
parse: test_function.c  neillsdl2.c parser_test.c parse.c parse_instruct.h neillsdl2.h test_function.h
	$(CC) test_function.c parser_test.c parse.c neillsdl2.c -o parse $(CFLAGS) $(OPTIM) -include neillsdl2.h -include parse_instruct.h  -include parse_function.h  -include test_function.h

run: all
	./parse $(TEXT1)
	./parse $(TEXT2)
	./parse $(TEXT3)
	./parse $(TEXT4)
	./parse $(TEXT5)
	./parse $(TEXT6)
	./parse $(TEXT7)
	./parse $(TEXT8)
clean:
	rm -f interp parse

.PHONY: clean run all
