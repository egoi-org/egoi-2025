#!/usr/bin/env python3

n = int(input())

def query(r):
  r = set(r)
  print("?", ' '.join(["01"[i in r] for i in range(n)]))
  return int(input())

# if cyclic testcase, one has an even position
evens = [2*i for i in range((n+1)//2)]

a, b = 0, len(evens)
while a+1 != b:
  mid = (a+b)//2
  if query(evens[a:mid]) % 2:
    b = mid
  else:
    a = mid

x = evens[a]
y = -1
if query([(x+1)%n]) == 1:
  y = (x+1)%n
if query([(x-1+n)%n]) == 1:
  y = (x-1+n)%n
assert y != -1
print("!", x, y)
