CC=g++

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)
BUILD=build/

EXE=$(BUILD)Test.exe

BOOST_PATH=D:/DevEnv/Cpp/boost_1_61_0/
BOOST_LIB=$(BOOST_PATH)stage/gcc/win32/

CFLAGS=-O3 -Wall
INCLUDE=-I$(BOOST_PATH)
LIBS=-L$(BOOST_LIB) -lboost_system-mgw61-mt-1_61 -lboost_thread-mgw61-mt-1_61 -lws2_32

$(EXE):$(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS) 

.cpp.o:
	$(CC) $< $(CFLAGS) $(INCLUDE)  -c -o $@	

.PHONY:clean
clean:
	rm -f $(OBJS)
