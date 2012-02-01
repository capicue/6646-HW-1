/*****************************************************************************

To draw a circle of radius $r$ on a graphics screen, one may proceed to evaluate pairs of values $x = r \cos \theta$, $y = r \sin \theta$ for a succession of values $\theta$. But this is expensive. A cheaper method may be obtained by considering the ODE
\begin{alignat*}{2}
  \dot{x} &= -y, \quad&\quad x(0) &= r, \\
  \dot{y} &= x,  \quad&\quad y(0) &= 0, 
\end{alignat*}
where $\dot{x} = \frac{dx}{d\theta}$, and approximating this using a simple discretization method. However, care must be taken so as to ensure that the obtained approximate solution looks right, i.e., that the approximate curve closes rather than spirals.

For each of the three discretization methods introduced in this chapter, namely, forward Euler, backward Euler, and trapezoidal methods, carry out this integration using a uniform step size $h = .02$ for $0 \leq \theta \leq 120$. Determine if the solution spirals in, spirals out, or forms an approximate circle as desired. Explain the observed results.

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	long double  r        = 1.0;
	long double  h        = 0.02;
	long double  (* y)[2] = NULL;
	long long    steps    = 0;
	
	steps = round(120.0 / h) + 1;
	y     = malloc(steps * sizeof(*y));
	
	if (y == NULL) {
		fprintf(stderr, "couldn't allocate memory\n");
		exit(1);
	}
	
	// set the initial conditions
	y[0][0] = r;
	y[0][1] = 0;
	
	// compute the numerical solution
	for(int i = 1; i < steps; i++) {
		y[i][0] = y[i-1][0] - h * y[i-1][1];
		y[i][1] = y[i-1][1] + h * y[i-1][0];
	}
	
	// output the points
	for(int i = 0; i < steps; i++) {
		printf("[%Lf, %Lf]\n", y[i][0], y[i][1]);
	}
	
	free(y);
	y = NULL;
	
	return 0;
}