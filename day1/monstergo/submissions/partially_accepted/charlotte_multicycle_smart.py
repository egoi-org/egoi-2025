n = int(input())

start = 0


def cycle():
    global start
    for i in range(13):
        for j in [start + x for x in range(13) if x != i]:
            print(j)
    start += 13


def single():
    global start
    for i in [start + x for x in range(12)]:
        print(i)
    start += 12


def two():
    global start
    for i in range(7):
        for j in [start + x for x in range(7) if x != i]:
            print(j)
        for j in [start + 7 + x for x in range(7) if x != i]:
            print(j)
    start += 2 * 7


def three():
    global start

    for i in range(5):
        for j in [start + x for x in range(5) if x != i]:
            print(j)
        for j in [start + 5 + x for x in range(5) if x != i]:
            print(j)
        for j in [start + 2 * 5 + x for x in range(5) if x != i]:
            print(j)
    start += 3 * 5


def four():

    global start

    for i in range(4):
        for j in [start + x for x in range(4) if x != i]:
            print(j)
        for j in [start + 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [start + 2 * 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [start + 3 * 4 + x for x in range(4) if x != i]:
            print(j)
    start += 4 * 4


def six():
    global start

    for i in range(3):
        for j in [start + x for x in range(3) if x != i]:
            print(j)
        for j in [start + 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [start + 2 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [start + 3 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [start + 4 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [start + 5 * 3 + x for x in range(3) if x != i]:
            print(j)
    start += 6 * 3


    

s = 0


dp = [(1000,-1) for _ in range(51)] 

dp[1] = (12,0) 
for i in [1,2,3,4,6]:
    dp[(12//i)+1] = (i*(12//i+1),0)

for i in range(51):
    
    for j in [1,2,3,4,6]:
        if i + 1 <= 50:
            dp[i+1] = min(dp[i+1],(dp[i][0]+12,i))
        if i+j*(12//j)+1<=50:
            dp[i+(12//j)+1] = min(dp[i+(12//j)+1],(dp[i][0]+j*(12//j+1),i))

#print(list(enumerate(dp)))
while(n>0):
    if dp[n][0] <= 45:
            if n - dp[n][1] == 1:
                single()
            if n - dp[n][1] == 3:
                six()
            if n - dp[n][1] == 4:
                four()
            if n - dp[n][1] == 5:
                three()
            if n - dp[n][1] == 7:
                two()
            if n - dp[n][1] == 13:
                cycle()
    n = dp[n][1]
        
