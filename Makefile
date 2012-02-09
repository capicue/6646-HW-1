PROGS   := prob1 prob2 prob3 prob4
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

all: $(BINS)

plots: $(BINS) $(PLOT) $(PLOTDIR)
	$(BINDIR)/prob1 0.1      | $(PLOT) -o $(PLOTDIR)/plot_1_1 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob1 0.05     | $(PLOT) -o $(PLOTDIR)/plot_1_2 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob1 0.025    | $(PLOT) -o $(PLOTDIR)/plot_1_3 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 0 0.1    | $(PLOT) -o $(PLOTDIR)/plot_2_1 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 0 0.05   | $(PLOT) -o $(PLOTDIR)/plot_2_2 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 0 0.025  | $(PLOT) -o $(PLOTDIR)/plot_2_3 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 -5 0.1   | $(PLOT) -o $(PLOTDIR)/plot_2_4 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	$(BINDIR)/prob2 -5 0.05  | $(PLOT) -o $(PLOTDIR)/plot_2_5 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	$(BINDIR)/prob2 -5 0.025 | $(PLOT) -o $(PLOTDIR)/plot_2_6 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	$(BINDIR)/prob3 -f       | $(PLOT) -o $(PLOTDIR)/plot_3_1 --markersize=1 --aspectratio=1
	$(BINDIR)/prob3 -b       | $(PLOT) -o $(PLOTDIR)/plot_3_2 --markersize=1 --aspectratio=1
	$(BINDIR)/prob3 -t       | $(PLOT) -o $(PLOTDIR)/plot_3_3 --markersize=1 --aspectratio=1
	$(BINDIR)/prob4 -t 2     | $(PLOT) -o $(PLOTDIR)/plot_4_1 --markersize=1
	$(BINDIR)/prob4 -p 2     | $(PLOT) -o $(PLOTDIR)/plot_4_2 --markersize=1
	$(BINDIR)/prob4 -t 4     | $(PLOT) -o $(PLOTDIR)/plot_4_3 --markersize=1
	$(BINDIR)/prob4 -p 4     | $(PLOT) -o $(PLOTDIR)/plot_4_4 --markersize=1
	$(BINDIR)/prob4 -t 3.5   | $(PLOT) -o $(PLOTDIR)/plot_4_5 --markersize=1
	$(BINDIR)/prob4 -p 3.5   | $(PLOT) -o $(PLOTDIR)/plot_4_6 --markersize=1

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
