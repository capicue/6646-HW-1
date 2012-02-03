SHELL = /bin/sh
CFLAGS=-Wall -Wextra -Werror -Os --std=c99

all: prob1 prob2 prob3

prob1: prob1.c plot
	cc $(CFLAGS) prob1.c -o prob1
	# ./prob1 0.1 | ./plot
	./prob1 0.1 | ./plot -f "(1 + x**2)**2" -o plot_1_1 --markersize=20
	./prob1 0.05 | ./plot -f "(1 + x**2)**2" -o plot_1_2 --markersize=20
	./prob1 0.025 | ./plot -f "(1 + x**2)**2" -o plot_1_3 --markersize=20

prob2: prob2.c plot
	cc $(CFLAGS) prob2.c -o prob2
	./prob2 0 0.1 | ./plot -o plot_2_1 -f "(1 + x**2)**2" --markersize=20
	./prob2 0 0.05 | ./plot -o plot_2_2 -f "(1 + x**2)**2" --markersize=20
	./prob2 0 0.025 | ./plot -o plot_2_3 -f "(1 + x**2)**2" --markersize=20
	./prob2 -5 0.1 | ./plot -o plot_2_4 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	./prob2 -5 0.05 | ./plot -o plot_2_5 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20
	./prob2 -5 0.025 | ./plot -o plot_2_6 -f "(1 + x**2)**2" --xmax=2 --ymin="-15" --ymax="25" --markersize=20

prob3: prob3.c plot
	cc $(CFLAGS) prob3.c -o prob3
	./prob3 -f | ./plot -o plot_3_1 --markersize=1 --aspectratio=1
	./prob3 -b | ./plot -o plot_3_2 --markersize=1 --aspectratio=1
	./prob3 -t | ./plot -o plot_3_3 --markersize=1 --aspectratio=1

clean:
	rm prob1 prob2 prob3 *.png
