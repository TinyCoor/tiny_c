exec = a.out
sources =$(wildcard src/*.c)
objects = $(sources:.c =.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec) : $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o : %.c include/%.h
	gcc -c $(flags) $< -o $@

#install :
#	make
#	mkdir -p /usr/local/include/a
#	cp -r ./src/include/* /usr/local/include/a/.

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tiny src/*.c src/include/*.h