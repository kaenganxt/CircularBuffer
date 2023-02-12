
BIN=buffertest
CC=gcc
CXX=g++
RM=rm -f

SRCS=src/test.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -O2 -o $(BIN) $(OBJS)

src/test.o: src/circularbuffer.h src/circularbuffer.hpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(BIN)