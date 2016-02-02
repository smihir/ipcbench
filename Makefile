CC = gcc
CSCOPE = cscope
CFLAGS += -Wall -Werror
#LDFLAGS += -lrt

SOCKETIPCOBJS := tcp_socket.o\

SHMEMIPCOBJS := shared_mem.o\

ifeq ($(DEBUG), y)
 CFLAGS += -g -DDEBUG
endif

.PHONY: all
all: socketipc smemipc

socketipc: $(SOCKETIPCOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOCKETIPCOBJS) -o $@

smemipc: $(SHMEMIPCOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHMEMIPCOBJS) -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -o $@ -c $<

cscope:
	$(CSCOPE) -bqR

.PHONY: clean
clean:
	rm -rf *.o socketipc smemipc
