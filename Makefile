CFLAGS = -std=c99 -pedantic -Wextra -Wall -Wshadow -Wstrict-prototypes -Wcast-align\
	-Wstrict-aliasing
SRCDIR     = ./src
BINDIR   = ./bin
SRCFILES = $(wildcard $(SRCDIR)/*.c)

PROGS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SRCFILES))

all: $(PROGS)

$(BINDIR)/%: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
clean: 
	rm -f $(BINDIR)/*

.PHONY: clean
