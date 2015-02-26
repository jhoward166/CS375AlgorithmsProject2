CC = gcc


# Specifiy the target
all: BestFirstSearch

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
BestFirstSearch: BestFirstSearch.o
	gcc BestFirstSearch.o -o BestFirstSearch -lm

# Specify how the object files should be created from source files
BestFirstSearch.o: BestFirstSearch.c
	gcc -c BestFirstSearch.c


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o BestFirstSearch
