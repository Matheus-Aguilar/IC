from random import random

def randFloat(a, b):
    return a + (b - a) * random()

n = int(input())

low = -1000
up = 1000

print(n)

for i in range(n):
    print(randFloat(low, up), randFloat(low, up), randFloat(low, up))
    print(randFloat(low, up), randFloat(low, up), randFloat(low, up))
    print(randFloat(low, up), randFloat(low, up), randFloat(low, up))