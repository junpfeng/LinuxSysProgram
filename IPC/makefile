target1=mmap1
obj1=mmap1.o

target2=mmap2
obj2=mmap2_一些问题.o

target3=mmap3

obj3=mmap3_父子进程.o

target4=mmap4
obj4=mmap4_匿名映射.o

target5=mmap5_r  
obj5=mmap5_r.o

target6=mmap5_w
obj6=mmap5_w.o

$(target5) : $(obj5)
	gcc $^ -o $@

$(target6) : $(obj6)
	gcc $^ -o $@

$(target4) : $(obj4)
	g++ $^ -o $@

$(target3) : $(obj3)
	g++ $^ -o $@

$(target2) : $(obj2)
	g++ $^ -o $@

$(target1) : $(obj1)
	g++ $^ -o $@

clean :
	rm -rf *.o
