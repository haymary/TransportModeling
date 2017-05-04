import math as m

def sort(first, L):
    for i in range(0, len(L)):
        for j in range(0, len(L) - 1):
            if to_right(first, L[j], L[j+1]):
                L[j], L[j+1] = L[j+1], L[j]
    return L
 
def to_right(A , B, C):
    if ((float(B[2])-float(A[2]))*(float(C[0])-float(B[0])) - (float(B[0])-float(A[0]))*(float(C[2])-float(B[2]))) > 0:
        return True
    else: return False
 
def distance(x,y):
    return m.sqrt(pow(float(x[0]) - float(y[0]), 2) + pow(float(x[2]) - float(y[2]), 2))
 
def t_square(x, y, z):
    a = distance(x, y)
    b = distance(y, z)
    c = distance(z, x)
    p = a + b + c
    return m.sqrt(p * (p - a) * (p - b) * (p - c))
 
def square(L):
    s = 0
    for i in range(1, len(L) - 1):
        s += t_square(L[0], L[i], L[i+1])
    return s
 
import sys
i = 0
lines = []
 
for line in sys.stdin:
    lines[i] = [float(x) for x in line.split(' ')]
#lines = [line.rstrip('\n') for line in open('input')]
#lines = [line.split(' ') for line in lines]
 
cov = lines
s_last = -1
orig_size = len(lines)
while (len(lines) > 0.9 * orig_size):
    # get the point with smallest x
    for i in range(1, len(lines)):
        if float(lines[0][0]) > float(lines[i][0]):
            lines[0], lines[i] = lines[i], lines[0]
    # sort
    lines = [lines[0]] + sort(lines[0], lines[1: len(lines)])
    cov = [lines[0], lines[1]]
    for i in range(2, len(lines)):
        while to_right(cov[-2], cov[-1], lines[i] ):
            del cov[-1]
        cov.append(lines[i])
 
    s_new = square(cov)
 
    for i in range(0, len(cov)):
        del lines[lines.index(cov[i])]
 
    if (s_last > 0 and (s_last - s_new) < 0.1 * s_last):
        break
 
    s_last = s_new
 
#f1=open('output', 'w+')
#f1.write(str(len(lines)) + "\n")
print len(lines)
for i in range(0, len(lines)):
    #f1.write(lines[i][0] + ' ' + lines[i][1] + ' ' + lines[i][2] + "\n")
    print lines[i][0] + ' ' + lines[i][1] + ' ' + lines[i][2]
