#!bin/python3

# this strategy only works for n = 1 or n = 13
n = int(input())
for i in range(n):
    for x in range(12):
        print((i+x)%13)
