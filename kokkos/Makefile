JAC=jacobi_it.pgr
GAUSS=gauss_seidel_it.pgr
OBJECTS_JAC=obj/iterative_jacobi.o obj/gaussianNoise.o
OBJECTS_GAUSS=obj/iterative_gauss_seidel.o obj/gaussianNoise.o

all: $(JAC)

jacobi: $(JAC)
gauss: $(GAUSS)

CC=g++
CFLAGS=-Wall -O3
LDFLAGS=

CFLAGS += $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs opencv4)

$(JAC): $(OBJECTS_JAC)
	$(CC) $(CFLAGS) $^ -o $@  $(LDFLAGS)

$(GAUSS): $(OBJECTS_GAUSS)
	$(CC) $(CFLAGS) $^ -o $@  $(LDFLAGS)

obj/%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

proper :
	rm -f obj/*.o

clean:
	rm -rf obj/*.o *.pgr
