all: main

CPP_FLAGS = -g -std=c++11 -Wall -Wno-reorder

CPP_LIBS = -pthread

define recipe
$(1).o: $(1).cpp $(1).h
	g++ -c $(CPP_FLAGS) $(1).cpp -o $(1).o
endef

main.o: main.cpp
	g++ -c $(CPP_FLAGS) main.cpp -o main.o

SRC = server game
$(foreach i,$(SRC),$(eval $(call recipe,$(i))))

RECIPES = main.o $(foreach i, $(SRC), $(i).o)

main: $(RECIPES)
	g++ -o main $(RECIPES) $(CPP_LIBS)
	rm -f src/*h.gch

clean:
	rm -f bin/*.o
	rm -f src/*h.gch