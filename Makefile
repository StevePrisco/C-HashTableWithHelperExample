.PHONY: clean all

all : wf

wf : wf.c hashTableA6.c hashTableA6.h
	gcc -Wall wf.c hashTableA6.c -o wf

clean :
	rm -f wf wordfrequency.txt *.out *.ref *.diff *.in *.o 
