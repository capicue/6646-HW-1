PROGS  := prob1 prob2
SRCDIR  := src
BINDIR  := bin
PLOTDIR := plot

SRCS  := $(addprefix $(SRCDIR)/, $(addsuffix .c, $(PROGS)))
OBJS  := $(patsubst %.c, %.o, $(SRCS))
BINS  := $(addprefix $(BINDIR)/, $(PROGS))
PLOTS := $(PLOTDIR)/*

CC        := /usr/bin/clang
LD        := /usr/bin/clang
PLOT      := $(BINDIR)/plot.py
CFLAGS    := -std=c99 -Wall -Wextra -Werror -g
LDFLAGS   :=
PLOTFLAGS := --markersize=20 -f "(1 + x**2)**2"

all: $(BINS)

plots: $(BINS) $(PLOT) $(PLOTDIR)
	$(BINDIR)/prob1 0.1      | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_1_1
	$(BINDIR)/prob1 0.05     | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_1_2
	$(BINDIR)/prob1 0.025    | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_1_3
	$(BINDIR)/prob2 0 0.1    | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_2_1
	$(BINDIR)/prob2 0 0.05   | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_2_2
	$(BINDIR)/prob2 0 0.025  | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_2_3
	$(BINDIR)/prob2 -5 0.1   | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_2_4 --xmax=2 --ymin="-15" --ymax="25"
	$(BINDIR)/prob2 -5 0.05  | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_2_5 --xmax=2 --ymin="-15" --ymax="25"
	$(BINDIR)/prob2 -5 0.025 | $(PLOT) $(PLOTFLAGS) -o $(PLOTDIR)/plot_2_6 --xmax=2 --ymin="-15" --ymax="25"

$(BINS): $(BINDIR)/%: $(SRCDIR)/%.o
	$(LD) $(LDFLAGS) -o $@ $<

$(OBJS): $(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(PLOTDIR):
	mkdir $(PLOTDIR)

clean:
	rm -f $(OBJS)
	rm -f $(BINS)
	rm -f $(PLOTS)

.PHONY: all plots clean
