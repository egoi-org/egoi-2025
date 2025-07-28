#!/usr/bin/env python3

n = int(input())

def query(r):
  r = set(r)
  print("?", ''.join(["01"[i in r] for i in range(n)]))
  return int(input()) % 2


for i in range(n):
    for(j) in range(i+1,n):
        if not query([i,j]):
            print('!',i,j)
            quit()
