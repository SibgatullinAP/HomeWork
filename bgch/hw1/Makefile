all: clean buil_all

DIRECTORIES = $(sort $(wildcard *_*)) \

buil_all:
	for i in $(DIRECTORIES) ; do \
		cd $$i; \
		make ; \
		cp a.out ../  ;\
		make clean ; \
		cd .. ;\
		mv a.out $$i.out ;\
	done \

clean:
	rm  -f *.out