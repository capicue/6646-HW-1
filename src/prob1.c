/*****************************************************************************

L 2.4.2 Use the method of exercise 2.4.2 to compute numerical solutions of 
the scalar initial value problem $y' = 4 x y^{1/2}$, $y(0) = 1$ for 
$0 \leq x \leq 2$, using the steplengths $h = 0.1, 0.05,$ and $0.025$.
Compare the results with the exact solution $y(x) = (1 + x^2)^2$ and deduce
that the numerical solutions are not converging to the exact solution as
$h \to 0$.

The method used is
\[
y_{n + 2} - y_{n + 1} = \frac{h}{12}\left[4 f(x_{n + 2}, y_{n + 2}) + 
8 f(x_{n + 1}, y_{n + 1}) - f(x_n, y_n)\right].
\]

*****************************************************************************/

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
	steps = round(2.0 / h) + 1.0;
	y     = malloc(steps * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(1);
	}
	
	// set and print the initial conditions
	y[0] = y[1] = 1;
	
	// compute the numerical solution
	for(int i = 2; i < steps; i++) {
		long double a, b, c, d;
		
		a = (4.0 / 3.0) * i * pow(h, 2);
		b = (1.0 / 3.0) * (i - 2) * pow(h, 2) * sqrt(y[i-2])
			- y[i-1] - (8.0 / 3.0) * (i - 1) * pow(h, 2) * sqrt(y[i-1]);
		c = 2 * b - pow(a, 2);
		d = pow(b, 2);
		
		y[i] = (-c + sqrt(pow(c,2) - 4 * d))/2;
	}
	
	// output the points
	for(int i = 0; i < steps; i++) {
		printf("%Lf %Lf\n", i * h, y[i]);
	}
	
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