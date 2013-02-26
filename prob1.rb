#!/usr/bin/ruby -w

h      = ARGV[0].to_f
steps  = (2.0 / h).round + 1.0
result = steps.to_i.times.inject([]) do |ary, i|
  next ary.push 1 if i == 0
  next ary.push 1 if i == 1

  a = (4.0 / 3.0) * i * (h ** 2)
  b = (1.0 / 3.0) * (i - 2) * (h ** 2) * Math.sqrt(ary[i - 2]) -
    ary.last - (8.0 / 3.0) * (i - 1) * (h ** 2) * Math.sqrt(ary.last)
  c = 2.0 * b - a ** 2
  d = b ** 2
  e = (-c + Math.sqrt((c ** 2.0) - (4 * d))) / 2.0

  ary.push e
end

puts result
