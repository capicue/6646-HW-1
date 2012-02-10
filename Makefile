PROGS   := prob1 prob2 prob3 prob4 prob5 prob6
SRCDIR  := src
BINDIR  := bin
PLOTDIR := plot
OUTDIR  := out

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
	# Problem 1 plots
	$(BINDIR)/prob1 0.1             | $(PLOT) -o $(PLOTDIR)/plot_1_1 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob1 0.05            | $(PLOT) -o $(PLOTDIR)/plot_1_2 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob1 0.025           | $(PLOT) -o $(PLOTDIR)/plot_1_3 -f "(1 + x**2)**2" --markersize=20
	# Problem 2 plots
	$(BINDIR)/prob2 0 0.1           | $(PLOT) -o $(PLOTDIR)/plot_2_1 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 0 0.05          | $(PLOT) -o $(PLOTDIR)/plot_2_2 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 0 0.025         | $(PLOT) -o $(PLOTDIR)/plot_2_3 -f "(1 + x**2)**2" --markersize=20
	$(BINDIR)/prob2 -5 0.1          | $(PLOT) -o $(PLOTDIR)/plot_2_4 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	$(BINDIR)/prob2 -5 0.05         | $(PLOT) -o $(PLOTDIR)/plot_2_5 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	$(BINDIR)/prob2 -5 0.025        | $(PLOT) -o $(PLOTDIR)/plot_2_6 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	# Problem 3 plots
	$(BINDIR)/prob3 -f              | $(PLOT) -o $(PLOTDIR)/plot_3_1 --markersize=1 --aspectratio=1
	$(BINDIR)/prob3 -b              | $(PLOT) -o $(PLOTDIR)/plot_3_2 --markersize=1 --aspectratio=1
	$(BINDIR)/prob3 -t              | $(PLOT) -o $(PLOTDIR)/plot_3_3 --markersize=1 --aspectratio=1
	# Problem 4 plots
	$(BINDIR)/prob4 -t 2            | $(PLOT) -o $(PLOTDIR)/plot_4_1 --markersize=1
	$(BINDIR)/prob4 -p 2            | $(PLOT) -o $(PLOTDIR)/plot_4_2 --markersize=1
	$(BINDIR)/prob4 -t 4            | $(PLOT) -o $(PLOTDIR)/plot_4_3 --markersize=1
	$(BINDIR)/prob4 -p 4            | $(PLOT) -o $(PLOTDIR)/plot_4_4 --markersize=1
	$(BINDIR)/prob4 -t 3.5          | $(PLOT) -o $(PLOTDIR)/plot_4_5 --markersize=1
	$(BINDIR)/prob4 -p 3.5          | $(PLOT) -o $(PLOTDIR)/plot_4_6 --markersize=1
	# Problem 5 plots
	$(BINDIR)/prob5 -f -p 20 200    | $(PLOT) -o $(PLOTDIR)/plot_5_1 -f "e**(sin(x))" --markersize=10
	$(BINDIR)/prob5 -b -p 20 200    | $(PLOT) -o $(PLOTDIR)/plot_5_2 -f "e**(sin(x))" --markersize=10
	$(BINDIR)/prob5 -t -p 20 200    | $(PLOT) -o $(PLOTDIR)/plot_5_3 -f "e**(sin(x))" --markersize=10
	$(BINDIR)/prob5 -m -p 20 200    | $(PLOT) -o $(PLOTDIR)/plot_5_4 -f "e**(sin(x))" --markersize=10
	# Problem 5 error
	mkdir -p $(OUTDIR)
	$(BINDIR)/prob5 -f -e 1 10          > $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 1 20         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 10 100       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 10 200       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 100 1000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 100 2000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 1000 1000    >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 1000 10000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 1000 20000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -f -e 1000 100000  >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 1 10         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 1 20         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 10 100       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 10 200       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 100 1000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 100 2000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 1000 1000    >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 1000 10000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 1000 20000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -b -e 1000 100000  >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 1 10         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 1 20         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 10 100       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 10 200       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 100 1000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 100 2000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 1000 1000    >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 1000 10000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 1000 20000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -t -e 1000 100000  >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 1 10         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 1 20         >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 10 100       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 10 200       >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 100 1000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 100 2000     >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 1000 1000    >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 1000 10000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 1000 20000   >> $(OUTDIR)/error
	$(BINDIR)/prob5 -m -e 1000 100000  >> $(OUTDIR)/error
	# Problem 6 plots
	$(BINDIR)/prob6 -f 1 -m f -s 0.1           | $(PLOT) -o $(PLOTDIR)/plot_6_1  --markersize=1
	$(BINDIR)/prob6 -f 1 -m f -s 0.05          | $(PLOT) -o $(PLOTDIR)/plot_6_2  --markersize=1
	$(BINDIR)/prob6 -f 1 -m f -s 0.025         | $(PLOT) -o $(PLOTDIR)/plot_6_3  --markersize=1
	$(BINDIR)/prob6 -f 1 -m f -s 0.01          | $(PLOT) -o $(PLOTDIR)/plot_6_4  --markersize=1
	$(BINDIR)/prob6 -f 1 -m b -s 0.1           | $(PLOT) -o $(PLOTDIR)/plot_6_5  --markersize=1
	$(BINDIR)/prob6 -f 1 -m b -s 0.05          | $(PLOT) -o $(PLOTDIR)/plot_6_6  --markersize=1
	$(BINDIR)/prob6 -f 1 -m b -s 0.025         | $(PLOT) -o $(PLOTDIR)/plot_6_7  --markersize=1
	$(BINDIR)/prob6 -f 1 -m b -s 0.01          | $(PLOT) -o $(PLOTDIR)/plot_6_8  --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.5 -s 0.1    | $(PLOT) -o $(PLOTDIR)/plot_6_9  --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.5 -s 0.05   | $(PLOT) -o $(PLOTDIR)/plot_6_10 --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.5 -s 0.025  | $(PLOT) -o $(PLOTDIR)/plot_6_11 --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.5 -s 0.01   | $(PLOT) -o $(PLOTDIR)/plot_6_12 --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.25 -s 0.1   | $(PLOT) -o $(PLOTDIR)/plot_6_13 --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.25 -s 0.05  | $(PLOT) -o $(PLOTDIR)/plot_6_14 --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.25 -s 0.025 | $(PLOT) -o $(PLOTDIR)/plot_6_15 --markersize=1
	$(BINDIR)/prob6 -f 1 -m t -t 0.25 -s 0.01  | $(PLOT) -o $(PLOTDIR)/plot_6_16 --markersize=1
	$(BINDIR)/prob6 -f 2 -m f -s 0.1           | $(PLOT) -o $(PLOTDIR)/plot_6_17 --markersize=1
	$(BINDIR)/prob6 -f 2 -m f -s 0.05          | $(PLOT) -o $(PLOTDIR)/plot_6_18 --markersize=1
	$(BINDIR)/prob6 -f 2 -m f -s 0.025         | $(PLOT) -o $(PLOTDIR)/plot_6_19 --markersize=1
	$(BINDIR)/prob6 -f 2 -m f -s 0.01          | $(PLOT) -o $(PLOTDIR)/plot_6_20 --markersize=1
	$(BINDIR)/prob6 -f 2 -m b -s 0.1           | $(PLOT) -o $(PLOTDIR)/plot_6_21 --markersize=1
	$(BINDIR)/prob6 -f 2 -m b -s 0.05          | $(PLOT) -o $(PLOTDIR)/plot_6_22 --markersize=1
	$(BINDIR)/prob6 -f 2 -m b -s 0.025         | $(PLOT) -o $(PLOTDIR)/plot_6_23 --markersize=1
	$(BINDIR)/prob6 -f 2 -m b -s 0.01          | $(PLOT) -o $(PLOTDIR)/plot_6_24 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.5 -s 0.1    | $(PLOT) -o $(PLOTDIR)/plot_6_25 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.5 -s 0.05   | $(PLOT) -o $(PLOTDIR)/plot_6_26 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.5 -s 0.025  | $(PLOT) -o $(PLOTDIR)/plot_6_27 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.5 -s 0.01   | $(PLOT) -o $(PLOTDIR)/plot_6_28 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.25 -s 0.1   | $(PLOT) -o $(PLOTDIR)/plot_6_29 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.25 -s 0.05  | $(PLOT) -o $(PLOTDIR)/plot_6_30 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.25 -s 0.025 | $(PLOT) -o $(PLOTDIR)/plot_6_31 --markersize=1
	$(BINDIR)/prob6 -f 2 -m t -t 0.25 -s 0.01  | $(PLOT) -o $(PLOTDIR)/plot_6_32 --markersize=1

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
