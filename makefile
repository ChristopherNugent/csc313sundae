# Building
CC = g++
CFLAGS = -lGL -lGLU -lglut -O3 -std=c++11
OUT = out/simulation
IN = simulation.cpp

# Formatting
CLANG_STYLE = {BasedOnStyle: google, IndentWidth: 4}


mainmake: $(IN)
	mkdir -p out
	$(CC) -o $(OUT)  $(IN) $(CFLAGS)


.PHONY: clean

clean:
	rm -r -f out/ *.o a.out 
.PHONY: format

format: $(IN)
	clang-format -i $(IN) -style="$(CLANG_STYLE)"	