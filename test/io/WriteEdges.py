from random import randint, random

edges = 60
nodes = 10

with open("edges.txt","w") as wr:
    for i in range(edges):
        p1 = randint(0, nodes-1)
        p2 = randint(0, nodes-1)
        wr.write("%s %s 1\n" % (p1, p2))