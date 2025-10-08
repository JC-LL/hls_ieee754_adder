all: tb_add
	@echo "all done"

tb_add: conversions.o tb_add.o add.o
	g++ -o tb_add tb_add.o conversions.o add.o

tb_add.o : tb_add.cpp
	g++ -c tb_add.cpp

add.o:	conversions.h add.cpp add.h
	g++ -c add.cpp

conversions.o: conversions.cpp conversions.h
	g++ -c conversions.cpp

run: tb_add
	./tb_add

clean:
	@echo cleaning...
	rm -rf *.o tb_add *.log

help:
	@echo ====== COMMAND INFOS =========
	@echo make clean
	@echo make all   : builds tb_add
	@echo make run   : runs tb_add
