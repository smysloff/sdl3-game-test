APP    := game
SRCS   := ./src/*\.c
INCL   := -I./src
CC     := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic -Ofast
LIBS   := -lm -lSDL3
RM     := rm -rf

all: clean build run

clean:
	@$(RM) $(APP) 

build:
	@$(CC) -o $(APP) $(SRCS) $(INCL) $(CFLAGS) $(LIBS)

run:
	@./$(APP)

.PHONY: all clean build run
