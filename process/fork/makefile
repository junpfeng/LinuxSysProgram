# wildcard用于模式匹配，获取当前目录下所有的.c文件
src = $(wildcard *.c) 
# % 表示任意长度字符，取出src中所有变量的后缀
targets = $(patsubst %.c, %, $(src)) 
# 采用变量，修改方便
CC = gcc

# -Wall是指显示所有警告（warn all) -g就是gdb
CFLAGS = -Wall -g

.PHONY : test all clean

test : 
	echo $(targets)
# %=$(targets) 里面是工作目录下所有.c文件的文件名（无后缀)，以空格间隔
all:$(targets)

# 目标项只能是一个文件(抽象或者具体)
$(targets): $(src)
	cc $< -o $@ -g 

clean :
	rm -f *.o $(targets)
