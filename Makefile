# ==============================
# Machine Learning Library in C
# Cross-Platform Makefile
# ==============================

# Compiler settings
CC = gcc
CFLAGS = -Wall -std=c11

# Executable name
TARGET = ml_app

# Source files
SRCS = main.c linear_regression.c utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Detect OS and choose delete command
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC = $(TARGET).exe
else
    RM = rm -f
    EXEC = ./$(TARGET)
endif

# ==============================
# Main build rules
# ==============================

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: all
	$(EXEC)

# Clean build files
clean:
	-$(RM) $(OBJS) $(TARGET) $(TARGET).exe 2>nul || true

# View dataset quickly
show-data:
	@echo Displaying dataset contents:
	@type data.csv 2>nul || cat data.csv
