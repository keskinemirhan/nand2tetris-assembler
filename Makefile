objects = main.o symbol.o code.o str_helper.o parser.o
sources = main.c symbol.c code.c str_helper.c parser.c

hackasm : $(objects) 
	cc -o hackasm $(objects) 

debug : $(objects)
	cc -o hackasm $(sources) -g

parser.o : str_helper.o str_helper.h parser.h
	cc -c parser.c

symbol.o : symbol.h
	cc -c symbol.c

code.o : parser.o parser.h str_helper.h str_helper.o
	cc -c code.c

str_helper.o : str_helper.h
	cc -c str_helper.c

main.o : symbol.o code.o str_helper.o parser.o symbol.h code.h str_helper.h parser.h
	cc -c main.c

clean : 
	rm $(objects)
