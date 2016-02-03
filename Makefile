CC = gcc
CSCOPE = cscope
CFLAGS += -Wall -Werror
LDFLAGS += -lpthread

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LDFLAGS += -lrt
endif

SOCKETIPCOBJS := tcp_socket.o\

SHMEMIPCOBJS := shared_mem.o\

PIPEIPCOBJS := pipes.o\

PRECISIONOBJS := precision.o\

ifeq ($(DEBUG), y)
 CFLAGS += -g -DDEBUG
endif

ifeq ($(TSCTIMER), y)
 CFLAGS += -DTSCTIMER
endif

.PHONY: all
all: socketipc smemipc pipeipc tsc_precision

socketipc: $(SOCKETIPCOBJS)
	$(CC) $(CFLAGS) $(SOCKETIPCOBJS) -o $@ $(LDFLAGS)

smemipc: $(SHMEMIPCOBJS)
	$(CC) $(CFLAGS) $(SHMEMIPCOBJS) -o $@ $(LDFLAGS)

pipeipc: $(PIPEIPCOBJS)
	$(CC) $(CFLAGS) $(PIPEIPCOBJS) -o $@ $(LDFLAGS)

tsc_precision: $(PRECISIONOBJS)
	$(CC) $(CFLAGS) $(PRECISIONOBJS) -o $@ $(LDFLAGS)

%.o: %.c *.h
	$(CC) $(CFLAGS) -o $@ -c $<

cscope:
	$(CSCOPE) -bqR

.PHONY: clean
clean:
	rm -rf *.o socketipc smemipc pipeipc tsc_precision
