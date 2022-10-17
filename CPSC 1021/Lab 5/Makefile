COMPILER = g++
OPTIONS = -Wall
PROGRAM = main.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): main.cpp Car.cpp Employee.cpp Invoice.cpp Lev.cpp Moped.cpp Motorcycle.cpp Service.cpp Student.cpp Visitor.cpp
	$(COMPILER) $(OPTIONS) main.cpp Car.cpp Employee.cpp Invoice.cpp Lev.cpp Moped.cpp Motorcycle.cpp Service.cpp Student.cpp Visitor.cpp -o $(PROGRAM)

clean:
	rm *.out
