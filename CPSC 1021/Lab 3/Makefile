COMPILER = g++
OPTIONS = -Wall
PROGRAM = main.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): areaCalc.cpp Circle.cpp Rectangle.cpp Square.cpp Trapezoid.cpp
	$(COMPILER) $(OPTIONS) areaCalc.cpp Circle.cpp Rectangle.cpp Square.cpp Trapezoid.cpp -o $(PROGRAM)

clean:
	rm *.out
