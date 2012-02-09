/*****************************************************************************

The following ODE system:
\begin{align*}
  y_1' = \alpha - y_1 - \frac{4y_1 y_2}{1 + y_1^2}, \\
  y_2' = \beta y_1 \left(1 - \frac{y_2}{1 + y_1^2}\right),
\end{align*}
where $\alpha$ and $\beta$ are parameters, represents a simplified approximation to a chemical reaction. There is a parameter value $\beta_c = \frac{3\alpha}{5} - \frac{25}{\alpha}$ such that for $\beta > \beta_c$ solution trajectories decay in amplitude and spiral in phase space into a stable fixed point, whereas for $\beta < \beta_c$ trajectories oscillate without damping and are attracted to a stable limit cycle. [This is called a \emph{Hopf bifurcation}.]
\begin{enumerate}[(a)]
  \item Set $\alpha = 10$ and use any of the discretization methods introduced in this chapter with a fixed step size $h = .01$ to approximate the solution starting at $y_1(0) = 0$, $y_2(0) = 2$, for $0 \leq t \leq 20$. Do this for the parameter values $\beta = 2$ and $\beta = 4$. For each case plot $y_1$ vs. $t$ and $y_2$ vs. $y_1$. Describe your observations.
  \item Investigate the situation closer to the critical value $\beta_c = 3.5$.
\end{enumerate}

*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double parse_args(int argc, char** argv, int* method);

int main(int argc, char** argv) {
	// method (y1 vs. t) or (y2 vs. y1)
	int method = 0;
	
	// time step
	const float h = 0.01;
	
	// parameters
	const int alpha = 10;
	double    beta  = 0;
	
	// time range
	const int t_min = 0;
	const int t_max = 20;
	long      steps = 0;
	
	// initial values
	const int x_0 = 0;
	const int y_0 = 2;
	
	// solution
	long double (* y)[2] = NULL;
	
	beta  = parse_args(argc, argv, &method);
	steps = round((t_max - t_min) / h) + 1;
	y     = malloc(steps * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(1);
	}
	
	// set the initial conditions
	y[0][0] = x_0;
	y[0][1] = y_0;
	
	for(int i = 1; i < steps; i++) {
		y[i][0] = y[i-1][0] + h * (alpha - y[i-1][0] - (4 * y[i-1][0] * y[i-1][1])/(1 + pow(y[i-1][0], 2)));
		y[i][1] = y[i-1][1] + h * (beta * y[i-1][0] * (1 - (y[i-1][1])/(1 + pow(y[i-1][0], 2))));
	}
	
	switch( method )
	{
		case 1:
			// print the phase space points
			for(int i = 0; i < steps; i++) {
				printf("%Lf %Lf\n", y[i][0], y[i][1]);
			}
			break;
		
		case 2:
			// print the time points
			for(int i = 0; i < steps; i++) {
				printf("%f %Lf\n", i*h, y[i][1]);
			}
			break;
	}
	
	free(y);
	y = NULL;
	
	return 0;
}

double parse_args(int argc, char** argv, int* method) {
	double beta   = 0;
	char*  endptr = NULL;
	
	if (argc != 3) {
		printf("usage: prob4 [-p | -t | -h] beta_value\n");
		exit(1);
	}
	
	if (argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'p': 
				*method = 1;
				break;
			case 't': 
				*method = 2;
				break;
			case 'h':
				printf("usage: prob4 [-p | -t | -h] beta_value\n\n");
				printf("-p phase space\n\n");
				printf("-t y_1 vs. time\n\n");
				printf("-h help\n\n");
				exit(0);
			default:
				printf("usage: prob4 [-p | -t | -h] beta_value\n");
				exit(1);
		}
	}
	
	beta = strtod(argv[2], &endptr);
	
	if (endptr != (argv[2] + strlen(argv[2]))) {
		printf("prob4: beta must be a number\n");
		exit(1);
	}
	
	return beta;
}