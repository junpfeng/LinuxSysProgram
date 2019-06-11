target01=p_01_fork
obj01=p_01_fork.o

target02 = p_02_loopfork
obj02 = p_02_loopfork.o

$(target01) : $(obj01)
	cc $^ -o $@

$(target02) : $(obj02)
	cc $^ -o $@

clean:
	rm -f *.o $(target01) $(target02)
