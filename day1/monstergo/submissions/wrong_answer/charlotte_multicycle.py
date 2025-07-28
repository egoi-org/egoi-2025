n = int(input())

# works for 1,2,3,4,25,26,27,28,50,51,52,75,76,100
start = 0


def cycle():
    global start
    for i in range(25):
        for j in [1 + start + x for x in range(25) if x != i]:
            print(j)
    start += 25


def single():
    global start
    for i in [1 + start + x for x in range(24)]:
        print(i)
    start += 25


def two():
    global start
    for i in range(13):
        for j in [1 + start + x for x in range(13) if x != i]:
            print(j)
        for j in [1 + start + 13 + x for x in range(13) if x != i]:
            print(j)
    start += 2 * 13


def three():
    global start

    for i in range(9):
        for j in [1 + start + x for x in range(9) if x != i]:
            print(j)
        for j in [1 + start + 9 + x for x in range(9) if x != i]:
            print(j)
        for j in [1 + start + 2 * 9 + x for x in range(9) if x != i]:
            print(j)
    start += 3 * 9


def four():

    global start

    for i in range(7):
        for j in [1 + start + x for x in range(7) if x != i]:
            print(j)
        for j in [1 + start + 7 + x for x in range(7) if x != i]:
            print(j)
        for j in [1 + start + 2 * 7 + x for x in range(7) if x != i]:
            print(j)
        for j in [1 + start + 3 * 7 + x for x in range(7) if x != i]:
            print(j)
    start += 4 * 7


def six():
    global start

    for i in range(5):
        for j in [1 + start + x for x in range(5) if x != i]:
            print(j)
        for j in [1 + start + 5 + x for x in range(5) if x != i]:
            print(j)
        for j in [1 + start + 2 * 5 + x for x in range(5) if x != i]:
            print(j)
        for j in [1 + start + 3 * 5 + x for x in range(5) if x != i]:
            print(j)
        for j in [1 + start + 4 * 5 + x for x in range(5) if x != i]:
            print(j)
        for j in [1 + start + 5 * 5 + x for x in range(5) if x != i]:
            print(j)
    start += 6 * 5

def eight():
    global start

    for i in range(4):
        for j in [1 + start + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 2 * 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 3 * 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 4 * 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 5 * 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 6 * 4 + x for x in range(4) if x != i]:
            print(j)
        for j in [1 + start + 7 * 4 + x for x in range(4) if x != i]:
            print(j)
    start += 8 * 4

def twelve():
    global start

    for i in range(3):
        for j in [1 + start + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 2 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 3 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 4 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 5 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 6 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 7 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 8 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 9 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 10 * 3 + x for x in range(3) if x != i]:
            print(j)
        for j in [1 + start + 11 * 3 + x for x in range(3) if x != i]:
            print(j)
    start += 12 * 3

    

s = 0
while n > 0 and start <= 75:
    print("cards:",n)
    if n % 25 == 0:
        cycle()
        n -= 25
        continue
    elif n % 13 == 0:
        two()
        n -= 13
        continue
    elif n % 9 == 0:
        three()
        n -= 9
        continue
    elif n % 7 == 0:
        four()
        n -= 7
        continue
    elif n % 5 == 0:
        six()
        n -= 5
        continue
    elif n % 4 == 0:
        eight()
        n -= 4
        continue
    elif n % 3 == 0:
        twelve()
        n -= 3
        continue
    else:
        single()
        n -= 1
