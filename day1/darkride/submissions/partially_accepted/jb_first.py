#!/usr/bin/env python3

n = int(input())

def query(r):
  s = ['0']*n
  for i in r:
      s[i] = '1'
  print("?", ''.join(s))
  return int(input())

a, b = 1, n
while a+1 != b:
  mid = (a+b)//2
  if query(list(range(a,mid))) % 2:
    b = mid
  else:
    a = mid

print("!", 0, a)
