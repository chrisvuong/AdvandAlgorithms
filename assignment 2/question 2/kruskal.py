from random import randint, choice, seed

from tkinter import N
h = 100
w = 100
seed(10)
parent = [[(i,j) for j in range(h)] for i in range(w)]

def make_set():
    parent = [[(i,j) for j in range(h)] for i in range(w)]

def find (x,y): # find((x,y))
    # print(x,y)
    if((x,y) != parent[x][y]):
        return find(parent[x][y][0], parent[x][y][1])
    return parent[x][y]

def union (e1, e2):
    r1 = find(e1[0], e1[1])
    r2 = find(e2[0], e2[1])
    if r1 == r2:
        return
    parent[r2[0]] [r2[1]] = find(e1[0], e1[1])
removeWall = []

def neighbor(x,y):
    rs = []
    if x > 0:
        rs.append((x-1,y))
    if x < w-1:
        rs.append((x + 1,y))
    if y > 0:
        rs.append((x,y - 1))
    if y < h-1:
        rs.append((x,y + 1))
    return rs

def rand_maze():
    start = (0,0)
    goal = parent[w-1][h-1]
    while (find(start[0], start[1]) != find(goal[0], goal[1])):
        # random wall:
        x1,y1 = (randint(0, w-1), randint(0, h-1)) # cell location
        n = neighbor(x1,y1)
        neigh = choice(n) # find neighnor
        # print(n, neigh)
        if(find(x1,y1) != find(neigh[0] , neigh[1])):
            removeWall.append(((x1,y1),neigh))
            union((x1,y1) , neigh)
def intersection(lst1, lst2):
    lst3 = [value for value in lst1 if value in lst2]
    return lst3

def horizonNeigh(i, j):
    return [
        ( (i,j) , (i+1, j) ),
        ( (i,j) , (i-1, j) ),
        ( (i+1,j) , (i, j) ),
        ( (i-1,j) , (i, j) )
    ]
def verticalNeigh(i, j):
    return [
        ( (i,j) , (i, j+1) ),
        ( (i,j) , (i, j-1) ),
        ( (i,j+1) , (i, j) ),
        ( (i,j-1) , (i, j) )
    ]
rand_maze()

MAZE_horizone = [ ["  |" for j in range(h)] for i in range(w)]
MAZE_vertical = [ ["+++" for j in range(h)] for i in range(w)]

for wall in removeWall:
    a, b = wall
    if(a[0] == b[0]): #horizon remove
        if (a[1] < b[1]):
            MAZE_horizone[a[0]][a[1]] = "   "
        else:
            MAZE_horizone[b[0]][b[1]] = "   "
    else: #vertical remove
        if (a[0] < b[0]):
            MAZE_vertical[a[0]][a[1]] = "   "
        else:
            MAZE_vertical[b[0]][b[1]] = "   "
[print("***", end="") for _ in range(h+1)]
print()
for i in range(w):
    print("*|", end="")
    for j in range(h):
        print(MAZE_horizone[i][j], end="")
    print("*")
    print("*|", end="")
    for j in range(h):
        print(MAZE_vertical[i][j], end="")
    print("*")
[print("***", end="") for _ in range(h+1)]
print()
# for i in parent:
#     for j in i:
#         print(find(j[0], j[1]), end=" ")
#     print()
# print(len(removeWall))
# print(removeWall)
# parent[6][h]
# [(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)]
# [(1, 0), (1, 1), (1, 2), (1, 3), (1, 4)]
# [(2, 0), (2, 1), (2, 2), (2, 3), (2, 4)]
# [(3, 0), (3, 1), (3, 2), (3, 3), (3, 4)]
# [(4, 0), (4, 1), (4, 2), (4, 3), (4, 4)]
# [(5, 0), (5, 1), (5, 2), (5, 3), (5, 4)]
# [(6, 0), (6, 1), (6, 2), (6, 3), (6, 4)]
# [(7, 0), (7, 1), (7, 2), (7, 3), (7, 4)]
# [(8, 0), (8, 1), (8, 2), (8, 3), (8, 4)]
# [(9, 0), (9, 1), (9, 2), (9, 3), (9, 4)]
