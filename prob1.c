#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long double parse_args(int argc, char** argv);

int main(int argc, char** argv) {
	long double  h     = 0;
	long double* y     = NULL;
	long long    steps = 0;
	
	h     = parse_args(argc, argv);
	steps = round(2.0 / h);
	y     = malloc(steps * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(1);
	}
	
	printf("p = plot((x^2 + 1)^2, (0,2))\n");
	printf("p += point((");
	
	y[0] = y[1] = 1;
	printf("(%Lf, %Lf), ", 0 * h, y[0]);
	printf("(%Lf, %Lf), ", 1 * h, y[1]);
	
	for(int i = 2; i <= steps; i++) {
		long double a, b, c, d;
		
		a = (4.0 / 3.0) * i * pow(h, 2);
		b = (1.0 / 3.0) * (i - 2) * pow(h, 2) * sqrt(y[i-2])
			- y[i-1] - (8.0 / 3.0) * (i - 1) * pow(h, 2) * sqrt(y[i-1]);
		c = 2 * b - pow(a, 2);
		d = pow(b, 2);
		
		y[i] = (-c - sqrt(pow(c,2) - 4 * d))/2;
		
		printf("(%Lf, %Lf), ", i * h, y[i]);
	}
	
	printf("), color='red', pointsize=1)\n");
	
	free(y);
	y = NULL;
	
	return 0;
}

long double parse_args(int argc, char** argv) {
	long double h      = 0;
	char*       endptr = 0;
	
	if (argc != 2) {
		printf("usage: prob1 h_value\n");
		exit(1);
	}
	
	h = strtold(argv[1], &endptr);
	
	if (endptr != (argv[1] + strlen(argv[1]))) {
		printf("prob1: h must be a number\n");
		exit(1);
	}
	
	if (h <= 0 || h >= 2) {
		printf("prob1: h must be a number between 0 and 2\n");
		exit(1);
	}
	
	return h;
}