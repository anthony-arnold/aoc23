CFLAGS := -std=c11

DAYS := $(wildcard day*.c)
EXES := $(patsubst %.c,%,$(DAYS))

.PHONY: all

all: $(EXES)
