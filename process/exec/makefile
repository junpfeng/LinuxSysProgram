src=$(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

CFALGS = -Wall -g
CC = gcc

.PHONY : all clean

all : $(targets)

# 静态模式 %:%.c
$(targets) : %:%.c
	$(CC) $< -o $@

clean :
	rm -f $(targets) *.o *.out
