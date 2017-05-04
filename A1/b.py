#for line in sys.stdin:
#    lines[i] = [float(x) for x in line.split(' ')]
lines = [line.rstrip('\n') for line in open('input')]
lines = [line.split(' ') for line in lines]
l = list()
for line in lines:
    l.append([float(line[0]), float(line[1]), float(line[2])])

qp = [
    [0, 0, 0],
    l[0],
    [0, 0, 0]
]

p_max = 0
for i in range(1, len(l)):
    if qp[1][0] < l[i][0]:
        qp[1] = l[i]
    if p_max < l[i][2]:
        p_max = l[i][2]
q_max = qp[1][0]

p_0 = qp[1][2] / 2
qp[0] = [0, 0, p_0]
max_dist_point = 0
for i in range(0, len(l)):
    if l[i][2] >= (p_0 - 1e-7) and l[i][2] <= (p_0 + 1e-7):
        if qp[0][0] < l[i][0]:
            qp[0][0] = l[i][0]
    dist = pow(l[i][0]/q_max, 2) + pow((l[i][2]/p_max), 2)
    if dist > max_dist_point:
        qp[2] = l[i]
        max_dist_point = dist
print qp
