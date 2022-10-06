COMPILER = g++
OPTIONS = -Wall
PROGRAM = main.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): hospitalCharges.cpp Patient.cpp
	$(COMPILER) $(OPTIONS) hospitalCharges.cpp Patient.cpp -o $(PROGRAM)

clean:
	rm *.out
