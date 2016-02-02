CC = gcc
CSCOPE = cscope
CFLAGS += -Wall -Werror

SOCKET-IPC-OBJS := tcp_socket.o \

ifeq ($(DEBUG), y)
 CFLAGS += -g -DDEBUG
endif

.PHONY: all
all: socketipc

socketipc: $(SOCKET-IPC-OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOCKET-IPC-OBJS) -o $@

%.o: %.c *.h
	$(CC) $(CFLAGS) -o $@ -c $<

cscope:
	$(CSCOPE) -bqR

.PHONY: clean
clean:
	rm -rf *.o socketipc
