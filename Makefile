CFLAGS ?= -std=c11 -O2
LDFLAGS ?= -lm

DAYS := $(wildcard day*.c)
EXES := $(patsubst %.c,%,$(DAYS))

.PHONY: all clean

all: $(EXES)

clean:
	$(RM) $(EXES)
