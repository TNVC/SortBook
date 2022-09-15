CC=g++
FLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
SOURCE=main.cpp fiofunctions.cpp copyfunctions.cpp sortfunctions.cpp newmergesort.cpp heapfunctions.cpp logging.cpp
OBJECTS=${SOURCE:.cpp=.o}
INCLUDE=include
OS=OS_WINDOWS_
LOG_LEVEL=-DLOG_LEVEL_ERROR -DLOG_LEVEL_MESSAGE #-DLOG_LEVEL_VALUE

all: sortbook

sortbook: ${OBJECTS}
	@${CC} ${OBJECTS}

main.o: main.cpp ${INCLUDE}/fiofunctions.h ${INCLUDE}/logging.h
	@${CC} -c -I ${INCLUDE} ${FLAGS} ${LOG_LEVEL} main.cpp

fiofunctions.o: fiofunctions.cpp
	@${CC} -c -I ${INCLUDE} ${FLAGS} -D ${OS} ${LOG_LEVEL} fiofunctions.cpp

copyfunctions.o: copyfunctions.cpp
	@${CC} -c -I ${INCLUDE} ${FLAGS} -D ${OS} ${LOG_LEVEL} copyfunctions.cpp

sortfunctions.o: sortfunctions.cpp
	@${CC} -c -I ${INCLUDE} ${FLAGS} ${LOG_LEVEL} sortfunctions.cpp

newmergesort.o: newmergesort.cpp
	@${CC} -c -I ${INCLUDE} ${FLAGS} ${LOG_LEVEL} newmergesort.cpp

heapfunctions.o: heapfunctions.cpp
	@${CC} -c -I ${INCLUDE} ${FLAGS} ${LOG_LEVEL} heapfunctions.cpp
	
logging.o: logging.cpp
	@${CC} -c -I ${INCLUDE} ${FLAGS} ${LOG_LEVEL} logging.cpp

clean:
	@rm -f ${OBJECTS} a.exe