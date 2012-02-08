#!/usr/bin/env sage -python

import fileinput
import sys
from optparse import OptionParser
from sage.all import *

parser = OptionParser()
parser.add_option('-o', '--output', dest='filename',
    help='Specifies the name of the generated png. Default is plot.')
parser.add_option('-f', '--function', dest='function',
    help='Specifies a function to plot. Optional.')
parser.add_option('--marker', dest='marker',
    help='Specifies the marker style. o = circle (default), s = square, . = point')
parser.add_option('--markersize', dest='markersize',
    help='Specifies the marker size. Default is 50.')
parser.add_option('--xmin', dest='xmin',
    help='Specifies xmin. Defaults to the smallest x value from the array.')
parser.add_option('--xmax', dest='xmax',
    help='Specifies xmax. Defaults to the largest x value from the array.')
parser.add_option('--ymin', dest='ymin',
    help='Specifies ymin. Defaults to the smallest y value from the array.')
parser.add_option('--ymax', dest='ymax',
    help='Specifies ymax. Defaults to the largest y value from the array.')
parser.add_option('--aspectratio', dest='aspectratio',
    help='Specifies the aspect ratio. Optional.')
options, files = parser.parse_args()

points = []

for line in fileinput.input(files):
    a, b = line.strip().split(" ")
    points.append([float(a), float(b)])

xmin = 0
ymin = 0
xmax = 1
ymax = 1

for point in points:
    if point[0] < xmin: xmin = point[0]
    if point[0] > xmax: xmax = point[0]
    if point[1] < ymin: ymin = point[1]
    if point[1] > ymax: ymax = point[1]

filename = options.filename or 'plot'

opt = {}
opt['marker'] = options.marker or 'o'
opt['markersize'] = int(options.markersize) if options.markersize else 50
opt['xmin'] = int(options.xmin) if options.xmin else math.floor(xmin)
opt['xmax'] = int(options.xmax) if options.xmax else math.ceil(xmax)
opt['ymin'] = int(options.ymin) if options.ymin else math.floor(ymin)
opt['ymax'] = int(options.ymax) if options.ymax else math.ceil(ymax)
if options.aspectratio:
    opt['aspect_ratio'] = int(options.aspectratio)

s = scatter_plot(points, **opt)

var('x')

if options.function:
    s += plot(eval(options.function), (x, opt['xmin'], opt['xmax']))
else:
    s += plot([])

s.save(filename + '.png')
