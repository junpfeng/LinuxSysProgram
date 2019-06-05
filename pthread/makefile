target1=consumers_producers
obj1=consumers_producers.o

target2=sem_producers_conducers
obj2=sem_consumers_producers.o

$(target1) : $(obj1)
	cc $^ -o $@ -lpthread

$(target2) : $(obj2)
	cc $^ -o $@ -lpthread

clean:
	rm -f *.o
