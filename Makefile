
BIN=buffertest
CC=gcc
CXX=g++
RM=rm -f

SRCS=src/test.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -O2 -lpthread -o $(BIN) $(OBJS)

src/test.o: src/circularbuffer.h src/circularbuffer.inl

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(BIN)
