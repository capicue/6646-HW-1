SHELL = /bin/sh
CFLAGS=-Wall -Wextra -Werror -Os --std=c99

all: prob1 prob2 prob3

prob1: prob1.c
	cc $(CFLAGS) prob1.c -o prob1
	./prob1 0.1 > points_1_1.sage
	./prob1 0.05 > points_1_2.sage
	./prob1 0.025 > points_1_3.sage

prob2: prob2.c
	cc $(CFLAGS) prob2.c -o prob2
	./prob2 0 0.1 > points_2_1.sage
	./prob2 0 0.05 > points_2_2.sage
	./prob2 0 0.025 > points_2_3.sage
	./prob2 -5 0.1 > points_2_4.sage
	./prob2 -5 0.05 > points_2_5.sage
	./prob2 -5 0.025 > points_2_6.sage

prob3: prob3.c
	cc $(CFLAGS) prob3.c -o prob3
	./prob3 -f > points_3_1.sage
	./prob3 -b > points_3_2.sage
	./prob3 -t > points_3_3.sage

clean:
	rm prob1 prob2 prob3 *.sage
