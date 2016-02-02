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

ifeq ($(DEBUG), y)
 CFLAGS += -g -DDEBUG
endif

.PHONY: all
all: socketipc smemipc pipeipc

socketipc: $(SOCKETIPCOBJS)
	$(CC) $(CFLAGS) $(SOCKETIPCOBJS) -o $@

smemipc: $(SHMEMIPCOBJS)
	$(CC) $(CFLAGS) $(SHMEMIPCOBJS) -o $@  $(LDFLAGS)

pipeipc: $(PIPEIPCOBJS)
	$(CC) $(CFLAGS) $(PIPEIPCOBJS) -o $@
%.o: %.c *.h
	$(CC) $(CFLAGS) -o $@ -c $<

cscope:
	$(CSCOPE) -bqR

.PHONY: clean
clean:
	rm -rf *.o socketipc smemipc pipeipc
