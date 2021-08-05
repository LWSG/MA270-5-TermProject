INCL=incl/
SRC=src/
BIN=bin/


term_project:calc.o main.o
	${CXX} -o term_project main.o calc.o
	rm -f main.o calc.o
	mv term_project ${BIN}

calc.o:
	${CXX} -I ${INCL} -c ${SRC}calc.cpp

main.o:
	${CXX} -I ${INCL} -c ${SRC}main.cpp
