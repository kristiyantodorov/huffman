CXX = g++

INCPATH = -I./include \

DEPS = ./include/frequency_table.hpp

SRCS = main.cpp frequency_table.cpp
BIN = bin
OBJS = $(BIN)/main.o $(BIN)/frequency_table.o
EXE = $(BIN)/huffman

CFLAGS = -Wall \
				 -c \
				 -g \
				 --std=c++11 \
				 -D$(DEBUG) \

LDFLAGS = -Wall \
				  -g \
				  -pthread \
					-static-libstdc++ \

$(BIN)/%.o: %.cpp
	$(CXX) $(CFLAGS)  $(INCPATH) -o $@ $<

#$(BIN)/frequency_table.o: frequency_table.cpp $(DEPS)
	#$(CXX) $(CFLAGS) $(INCPATH) frequency_table.cpp

#$(BIN)/main.o: main.cpp $(DEPS)
	#$(CXX) $(CFLAGS) $(INCPATH) main.cpp

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm $(BIN)/*

all: $(EXE)
