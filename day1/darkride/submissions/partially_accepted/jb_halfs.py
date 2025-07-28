#!/usr/bin/env python3

n = int(input())

def query(r):
  s = ['0']*n
  for i in r:
      s[i] = '1'
  print("?", ''.join(s))
  return int(input())

a, b = 0, n//2
while a+1 != b:
  mid = (a+b)//2
  if query(list(range(a,mid))) % 2:
    b = mid
  else:
    a = mid

x = a

a, b = n//2, n
while a+1 != b:
  mid = (a+b)//2
  if query(list(range(a,mid))) % 2:
    b = mid
  else:
    a = mid

print("!",a,x)
