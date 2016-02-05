CC = gcc
CSCOPE = cscope
CFLAGS += -Wall -Werror
LDFLAGS += -lpthread -lm

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LDFLAGS += -lrt
endif

SOCKETIPCOBJS := tcp_socket.o\

SHMEMIPCOBJS := shared_mem.o\

PIPEIPCOBJS := pipes.o\

TSCPRECISIONOBJS := tsc_precision.o\

RAWPRECISIONOBJS := raw_precision.o\

CLKPRECISIONOBJS := clock_precision.o\

ifeq ($(DEBUG), y)
 CFLAGS += -g -DDEBUG
endif

ifeq ($(TSCTIMER), y)
 TIMERFLAGS += -DTSCTIMER
endif

.PHONY: all
all: socketipc smemipc pipeipc tsc_precision raw_precision clk_precision

socketipc: $(SOCKETIPCOBJS)
	$(CC) $(CFLAGS) $(TIMERFLAGS) $(SOCKETIPCOBJS) -o $@ $(LDFLAGS)

smemipc: $(SHMEMIPCOBJS)
	$(CC) $(CFLAGS) $(TIMERFLAGS) $(SHMEMIPCOBJS) -o $@ $(LDFLAGS)

pipeipc: $(PIPEIPCOBJS)
	$(CC) $(CFLAGS) $(TIMERFLAGS) $(PIPEIPCOBJS) -o $@ $(LDFLAGS)

tsc_precision: $(TSCPRECISIONOBJS)
	$(CC) $(CFLAGS) $(TSCPRECISIONOBJS) -o $@ $(LDFLAGS)

raw_precision: $(RAWPRECISIONOBJS)
	$(CC) $(CFLAGS) $(RAWPRECISIONOBJS) -o $@ $(LDFLAGS)

clk_precision: $(CLKPRECISIONOBJS)
	$(CC) $(CFLAGS) $(CLKPRECISIONOBJS) -o $@ $(LDFLAGS)

%.o: %.c *.h
	$(CC) $(CFLAGS) $(TIMERFLAGS) -o $@ -c $<

cscope:
	$(CSCOPE) -bqR

.PHONY: clean
clean:
	rm -rf *.o socketipc smemipc pipeipc tsc_precision raw_precision
