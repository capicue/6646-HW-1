/*****************************************************************************

A&P 3.9 Write a short program which uses the forward Euler, the backward Euler, and the trapezoidal \emph{or} midpoint methods to integrate a linear scalar ODE with a known solution, using a fixed step size $h = b/N$, and which finds the maximum error. Apply your program to the following problem:
\[
  \frac{dy}{dt} = (\cos t) y, \qquad 0 \leq t \leq b,
\]
$y(0) = 1$. The exact solution is
\[
  y(t) = e^{\sin t}.
\]
Verify the entries given in the table and complete the missing ones. Make as many (useful) observations as you can on the results in the complete table. Attempt to provide explanations.

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void parse_args(int argc, char** argv, int* method, int* output, int* b, long* steps);

int main(int argc, char** argv) {
	int          method = 0;
	int          output = 0;
	int          b      = 0;
	long         steps  = 0;
	double       h      = 0;
	double       error  = 0;
	double       temp   = 0;
	long double* y      = NULL;
	
	parse_args(argc, argv, &method, &output, &b, &steps);
	
	h = (double) b / (double) steps;
	y = malloc(steps * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(1);
	}
	
	// set the initial conditions
	y[0] = 1;
	
	switch( method )
	{
		case 1:
			// compute the forward euler solution
			for (int i = 1; i < steps; i++) {
				y[i] = y[i-1] + h * cos(h * (i-1)) * y[i-1];
				if (output == 2) {
					temp = fabs(y[i] - exp(sin(h*i)));
					if (temp > error) {
						error = temp;
					}
				}
			}
			break;
		
		case 2:
			// compute the backward euler solution
			for(int i = 1; i < steps; i++) {
				y[i] = y[i-1] / (1 - h * cos(h*i));
				if (output == 2) {
					temp = fabs(y[i] - exp(sin(h*i)));
					if (temp > error) {
						error = temp;
					}
				}
			}
			break;
		
		case 3:
			//compute the trapezoidal solution
			for(int i = 1; i < steps; i++) {
				y[i] = y[i-1] * (1.0+0.5*h*cos(h*(i-1)))/(1.0-0.5*h*cos(h*i));
				if (output == 2) {
					temp = fabs(y[i] - exp(sin(h*i)));
					if (temp > error) {
						error = temp;
					}
				}
			}
			break;
		
		case 4:
			// compute the midpoint solution
			for(int i = 1; i < steps; i ++) {
				y[i]=y[i-1]*(1+0.5*h*cos(h*(i-0.5)))/(1-0.5*h*cos(h*(i-0.5)));
				if (output == 2) {
					temp = fabs(y[i] - exp(sin(h*i)));
					if (temp > error) {
						error = temp;
					}
				}
			}
	}
	
	switch( output )
	{
		case 1:
			// output the points
			for(int i = 0; i < steps; i++) {
				printf("%f %Lf\n", i*h, y[i]);
			}
			break;
		
		case 2:
			// output the max error
			switch( method )
			{
				case 1:
					printf("F. Euler    ");
					break;
				case 2:
					printf("B. Euler    ");
					break;
				case 3:
					printf("Trapezoidal ");
					break;
				case 4:
					printf("Midpoint    ");
			}
			printf("b = %-5d", b);
			printf("N = %-7ld", steps);
			printf("%e\n", error);
			break;
	}
	
	free(y);
	y = NULL;
	
	return 0;
}

void parse_args(int argc, char** argv, int* method, int* output, int* b, long* steps) {
	char* endptr = NULL;
	
	if (argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'f': 
				*method = 1;
				break;
			case 'b': 
				*method = 2;
				break;
			case 't':
				*method = 3;
				break;
			case 'm':
				*method = 4;
				break;
			case 'h':
				printf("usage: prob5 [-f | -b | -t | -m] [-p | -e] b_value n_value");
				printf("-f forward euler\n");
				printf("-b backward euler\n");
				printf("-t trapezoidal\n");
				printf("-m midpoint\n");
				printf("-h help\n\n");
				printf("-p points mode\n");
				printf("-e error mode\n");
				exit(0);
			default:
				printf("usage: prob5 [-f | -b | -t | -m] [-p | -e] b_value n_value");
				exit(1);
		}
	}
	
	if (argc != 5) {
		printf("usage: prob5 [-f | -b | -t | -m] [-p | -e] b_value n_value");
		exit(1);
	}
	
	if (argv[2][0] == '-') {
		switch (argv[2][1]) {
			case 'p': 
				*output = 1;
				break;
			case 'e': 
				*output = 2;
				break;
			default:
				printf("usage: prob5 [-f | -b | -t | -m] [-p | -e] b_value n_value");
				exit(1);
		}
	}
	
	*b = strtol(argv[3], &endptr, 10);
	
	if (endptr != (argv[3] + strlen(argv[3]))) {
		printf("prob5: b must be a number\n");
		exit(1);
	}
	
	*steps = strtol(argv[4], &endptr, 10);
	
	if (endptr != (argv[4] + strlen(argv[4]))) {
		printf("prob5: n must be a number\n");
		exit(1);
	}
}