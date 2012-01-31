/*****************************************************************************

L 2.5.4 Demonstrate the effect of zero-instability by using the method
\[
y_{n + 2} - (1 + \alpha)y_{n + 1} + \alpha y_n = \frac{h}{2}\left[(3-\alpha) 
f(x_{n+1}, y_{n+1}) - (1 + \alpha) f(x_n, y_n)\right]
\]
with (i) $\alpha = 0$, (ii) $\alpha = -5$ to compute numerical solutions of 
the scalar initial value problem $y' = 4xy^{1/2}$, $y(0) = 1$ for 
$0 \leq x \leq 2$, using the steplengths $h = 0.1, 0.05, 0.025$.

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void parse_args(int argc, char** argv, int* alpha, long double* h);

int main(int argc, char** argv) {
	int          alpha = 0;
	long double  h     = 0;
	long double* y     = NULL;
	long long    steps = 0;
	
	parse_args(argc, argv, &alpha, &h);
	steps = round(2.0 / h);
	y     = malloc(steps * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(1);
	}
	
	// plot the actual solution for comparison
	printf("p = plot((x^2 + 1)^2, (0,2))\n");
	printf("p += scatter_plot([");
	
	y[0] = y[1] = 1;
	printf("(%Lf, %Lf), ", 0 * h, y[0]);
	printf("(%Lf, %Lf), ", 1 * h, y[1]);
	
	for(int i = 2; i <= steps; i++) {
		y[i] = (1 + alpha) * y[i-1]
		       - alpha * y[i-2]
		       + 2 * (3 - alpha) * (i - 1) * pow(h, 2) * sqrt(y[i-1])
		       - 2 * (1 + alpha) * (i - 2) * pow(h, 2) * sqrt(y[i-2]);
		
		printf("[%Lf, %Lf], ", i * h, y[i]);
	}
	
	printf("], marker=\"o\", markersize=\"20\")\n");
	printf("p.show\n");
	
	free(y);
	y = NULL;
	
	return 0;
}

void parse_args(int argc, char** argv, int* alpha, long double* h) {
	char*       endptr = 0;
	
	if (argc != 3) {
		printf("usage: prob2 alpha_value h_value\n");
		exit(1);
	}
	
	*alpha = strtold(argv[1], &endptr);
	
	if (endptr != (argv[1] + strlen(argv[1]))) {
		printf("prob2: alpha must be a number\n");
		exit(1);
	}
	
	*h = strtold(argv[2], &endptr);
	
	if (endptr != (argv[2] + strlen(argv[2]))) {
		printf("prob2: h must be a number\n");
		exit(1);
	}
	
	if (*h <= 0 || *h >= 2) {
		printf("prob2: h must be a number between 0 and 2\n");
		exit(1);
	}
}