/*****************************************************************************

\begin{enumerate}
  \item Consider the scalar problem
  \[
    y' = -5ty^2 + \frac{5}{t} - \frac{1}{t^2}, \qquad y(1) = 1,
  \]
  for $1 \leq t \leq 25$.
  \item Consider the problem
  \[
    y' = y \sin(2t + 3), \qquad y(0) = 1.
  \]
\end{enumerate}
For both cases you should be able to get the exact solution.

Use the following methods to compute the numerical solution for the given problem.
\begin{enumerate}[(i)]
  \item Forward Euler
  \item Backward Euler
  \item $\theta$-method with $\theta = \frac12$ and at least one other value.
\end{enumerate}

For each method, use different $h$ values and include a table showing the values at the end points and maximum error. Analyze the consistency, $0$-stability and convergence based on the theories learned in class. 

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

struct globalArgs_t {
	int    function;  // -f option
	int    method;    // -m option
	double theta;     // -t option
	double h;         // -s option
} globalArgs;

static const char* optString = "f:m:s:t:h";

/* Display the program usage.
 */
void display_usage(void);

/* Parse the arguments.
 */
void parse_args(int argc, char** argv, const char* optString);

int main(int argc, char** argv) {
	long         steps = 0;
	const int    t_max = 25;
	long double* y     = NULL;
	
	double       a     = 0;
	double       c     = 0;
	
	// Initialize globalArgs
	globalArgs.function = 1;
	globalArgs.method   = 1;
	globalArgs.theta    = 0.5;
	globalArgs.h        = 0.1;
	
	parse_args(argc, argv, optString);
	switch (globalArgs.function) {
		case 1:
			steps = round((t_max-1)/globalArgs.h);
			break;
		case 2:
			steps = round(t_max/globalArgs.h);
			break;
	}
	y = malloc((steps+1) * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	switch (globalArgs.function) {
		case 1: // First differential equation
			y[0] = 1;
			switch (globalArgs.method) {
				case 1: // Forward Euler
					for (int i=1; i <= steps; i++) {
						y[i] = y[i-1] + globalArgs.h*(-5.0 * (1 + 
						       globalArgs.h * (i-1)) * pow(y[i-1],2) + 
						       (5.0/(1 + globalArgs.h * (i-1))) - (1/pow(1 + 
						       globalArgs.h * (i-1), 2)));
					}
					break;
				case 2: // Backward Euler
					for (int i=1; i <= steps; i++) {
						a = 5.0 * globalArgs.h * (globalArgs.h * i + 1);
						c = -y[i-1] - (5.0 * globalArgs.h)/(i * globalArgs.h 
						    + 1) + globalArgs.h/pow(i * globalArgs.h + 1, 2);
						y[i] = (-1 + sqrt(1 - 4 * a * c))/(2 * a);
					}
					break;
				case 3: // Theta Method
					for (int i=1; i <= steps; i++) {
						a = 5.0 * globalArgs.h * globalArgs.theta * 
						    (globalArgs.h * i + 1);
						c = -y[i-1] - globalArgs.h * (globalArgs.theta * 
						    (5/(i * globalArgs.h + 1) - 1/pow(i * 
						    globalArgs.h + 1, 2)) + (1 - globalArgs.theta) * 
						    (-5 * (globalArgs.h * (i-1) + 1) * pow(y[i-1], 2) 
						    + 5/(globalArgs.h * (i-1) + 1) - 
						    1/pow(globalArgs.h * i + 1, 2)));
						y[i] = (-1 + sqrt(1 - 4 * a * c))/(2 * a);
					}
					break;
			}
			break;
		case 2: // Second differential equation
			y[0] = 1;
			switch(globalArgs.method) {
				case 1: // Forward Euler
					for (int i=1; i <= steps; i++) {
						y[i] = y[i-1] + globalArgs.h * (y[i-1] * sin(2 * 
						       globalArgs.h * (i-1) + 3));
					}
					break;
				case 2: // Backward Euler
					for (int i=1; i <= steps; i++) {
						y[i] = y[i-1]/(1 - globalArgs.h * sin(2 * 
						       globalArgs.h * i + 3));
					}
					break;
				case 3: // Theta Method
					for (int i=1; i <= steps; i++) {
						y[i] = (y[i-1] + globalArgs.h * (1 - 
						       globalArgs.theta) * (y[i-1] * sin(2 * 
						       globalArgs.h * (i-1) + 3)))/(1 - globalArgs.h 
						       * globalArgs.theta * sin(2 * globalArgs.h * 
						       i + 3));
					}
					break;
			}
			break;
	}
	
	// Output the points
	switch (globalArgs.function) {
		case 1:
			for (int i=0; i <= steps; i++) {
				printf("%f %Lf\n", i*globalArgs.h+1, y[i]);
			}
			break;
		case 2:
			for (int i=0; i <= steps; i++) {
				printf("%f %Lf\n", i*globalArgs.h, y[i]);
			}
			break;
	}
	
	free(y);
	y = NULL;
	
	return EXIT_SUCCESS;
}

void display_usage(void) {
	puts("prob6 [-f function] [-m method] [-t theta_value] [-s step_size] [-h] ");
	exit(EXIT_FAILURE);
}

void parse_args(int argc, char** argv, const char* optString) {
	int opt = 0;
	char* endptr = NULL;
	
	opt = getopt(argc, argv, optString);
	while(opt != -1) {
		switch(opt) {
			case 'f':
				globalArgs.function = strtol(optarg, &endptr, 10);
				if (endptr != (optarg + strlen(optarg))) {
					puts("prob6: f must be a number.");
					exit(EXIT_FAILURE);
				}
				if (globalArgs.function < 1 || globalArgs.function > 2) {
					puts("prob6: f must be either 1 or 2.");
					exit(EXIT_FAILURE);
				}
				break;
			case 'm':
				switch(optarg[0]) {
					case 'f':
						globalArgs.method = 1;
						break;
					case 'b':
						globalArgs.method = 2;
						break;
					case 't':
						globalArgs.method = 3;
						break;
					default:
						puts("prob6: m must be either f, b, or t.");
						exit(EXIT_FAILURE);
				}
				break;
			case 't':
				globalArgs.theta = strtod(optarg, &endptr);
				if (endptr != (optarg + strlen(optarg))) {
					puts("prob6: t must be a number.");
					exit(EXIT_FAILURE);
				}
				if (globalArgs.theta < 0 || globalArgs.theta > 1) {
					puts("prob6: t must be between 0 and 1.");
					exit(EXIT_FAILURE);
				}
				break;
			case 's':
				globalArgs.h = strtod(optarg, &endptr);
				if (endptr != (optarg + strlen(optarg))) {
					puts("prob6: h must be a number.");
					exit(EXIT_FAILURE);
				}
				if (globalArgs.h < 0 || globalArgs.h > 25) {
					puts("prob6: h must be between 0 and 25.");
					exit(EXIT_FAILURE);
				}
				break;
			case 'h':
				display_usage();
				break;
			default:
				break;
		}
		
		opt = getopt(argc, argv, optString);
	}
}
