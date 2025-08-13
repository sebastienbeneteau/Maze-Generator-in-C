_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lm

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o test-dummy.o app-ex-loader.o map.o loader.o test-loader.o \
	test-find-neighbors.o maze.o prim.o test-prim.o app-generate-maze.o \
	heap.o test-heap-correctness.o test-heap-complexity.o

# put all the rules to build your applications and tests here (see examples)
example-main: example-main.o
	$(CC) $(CFLAGS) -o example-main example-main.o $(LDFLAGS)

example-string: example-string.o
	$(CC) $(CFLAGS) -o example-string example-string.o $(LDFLAGS)

read-file-formatted: read-file-formatted.o
	$(CC) $(CFLAGS) -o read-file-formatted read-file-formatted.o $(LDFLAGS)

read-file-text: read-file-text.o
	$(CC) $(CFLAGS) -o read-file-text read-file-text.o $(LDFLAGS)

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o write-fact write-fact.o $(LDFLAGS)

test-dummy: test-dummy.o
	$(CC) $(CFLAGS) -o test-dummy test-dummy.o $(LDFLAGS)

# the app-ex-loader app
app-ex-loader: app-ex-loader.o
	$(CC) $(CFLAGS) -o app-ex-loader app-ex-loader.o $(LDFLAGS)

#Creation of map
map: src/map.c include/map.h src/loader.c
	$(CC) $(CFLAGS) -o map src/map.c src/loader.c

#Creation of loader
loader: src/loader.c include/map.h
	$(CC) $(CFLAGS) -o loader src/loader.c
#Creation of test-loader
test-loader: tests/test-loader.c src/map.c include/map.h
	$(CC) $(CFLAGS) -o test-loader tests/test-loader.c src/map.c


#Creation of test-find-neighbors
test-find-neighbors: tests/test-find-neighbors.c src/map.c src/loader.c include/map.h
	$(CC) $(CFLAGS) -o test-find-neighbors tests/test-find-neighbors.c src/map.c src/loader.c

#Creation of maze
maze: src/maze.c include/maze.h
	$(CC) $(CFLAGS) -o maze src/maze.c

#Creation of prim
prim: src/prim.c src/map.c src/loader.c include/map.h include/prim.h include/maze.h
	$(CC) $(CFLAGS) -o prim src/prim.c src/map.c src/loader.c

#Creation of test-prim
test-prim: tests/test-prim.c src/prim.c src/map.c src/loader.c include/map.h include/prim.h include/maze.h
	$(CC) $(CFLAGS) -o test-prim tests/test-prim.c src/prim.c src/map.c src/loader.c

#Creation of app-generate-maze
app-generate-maze: src/app-generate-maze.c src/prim.c src/map.c src/loader.c  src/maze.c include/map.h include/prim.h include/maze.h
	$(CC) $(CFLAGS) -o app-generate-maze src/app-generate-maze.c src/prim.c src/map.c src/loader.c src/maze.c

#Creation of heap
heap: src/heap.c include/heap.h
	$(CC) $(CFLAGS) -o heap src/heap.c

#Creation of test-heap-correctness
test-heap-correctness: tests/test-heap-correctness.c src/heap.c include/heap.h
	$(CC) $(CFLAGS) -o test-heap-correctness tests/test-heap-correctness.c src/heap.c

#Creation of test-heap-complexity
test-heap-complexity: tests/test-heap-complexity.c src/heap.c include/heap.h
	$(CC) $(CFLAGS) -o test-heap-complexity tests/test-heap-complexity.c src/heap.c

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: example-main example-string read-file-formatted read-file-text \
	write-fact test-dummy app-ex-loader test-loader \
	test-find-neighbors test-prim app-generate-maze \
	test-heap-correctness test-heap-complexity

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-dummy test-loader test-find-neighbors test-prim test-heap-correctness test-heap-complexity

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# add all .c, .h and .txt files in repository
git-add-all-files:
	git add tests/*.c src/*.c include/*.h data/*.txt
