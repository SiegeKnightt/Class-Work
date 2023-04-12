#/********************************/
#/*Phillip Hedden                *
#*CPSC 2310 Spring 23            *
#*UserName: pchedde              *
#*Email: pchedde@clemson.edu     *
#*Instructor:  Dr. Yvon Feaster  */
#/********************************/


# Config, just variables
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=LAB6
ARGS=classdata.csv output.txt


C_SRCS := \
$(wildcard *.c) \
$(wildcard src/*.c) \
$(wildcard src/**/*.c)


HDRS := \
$(wildcard *.h) \
$(wildcard src/*.h) \
$(wildcard src/**/*.h)
# add comments
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))


# Target that prints the message "All Done" to the screen.
all: build
	@echo "All Done"

# Takes all built objects and links them together.
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

# Catches the top-most files (root directory files) in src.
# Also creates any directories needed using mkdir.
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Catches any files under the root directory files (nested files).
# Also creates any directories needed using mkdir.
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Removes any files of specific types.
clean:
	rm -f $(TARGET)
	rm -rf bin

# Executes target file with specified arguments.
run: build
	./$(TARGET) $(ARGS)

# Executes target file and check for memory leaks.
mem_leak: build
	valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes ./$(TARGET) $(ARGS)

# Lists all found sources, headers, and target objects of file.
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "TARGET OBJS: ${OBJS}"