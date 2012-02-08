MATH 6646 Problem Set 1
=======================

This project is a homework assignment for [MATH 6646](http://people.math.gatech.edu/~kang/6646/index.html). It is a set of 6 programs that numerically solve specified ODEs using various methods.

Dependencies
------------

You must have [sage](http://www.sagemath.org/) installed for plotting the graphs.

Running
-------

To compile the binaries for all problems use:

	% make

To run each binary for a given set of parameters and plot the results using sage, use:

	% make plots

This will create a bunch of image files like this one.

![Example plot](http://capicue.com/images/plot_2_2.png)

As expected, to get rid of the output and image files, use:

	% make clean