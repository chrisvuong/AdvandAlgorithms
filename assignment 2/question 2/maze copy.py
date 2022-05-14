from random import shuffle, randrange
 
def make_maze(w = 16, h = 8):
    vis = [[0] * w + [1] for _ in range(h)] + [[1] * (w + 1)]
    ver = [["|  "] * w + ['|'] for _ in range(h)] + [[]]
    hor = [["+--"] * w + ['+'] for _ in range(h + 1)]
 
    # def walk(x, y):

    stack = [(0,0)]
    while stack:
        x,y = stack.pop()
        vis[y][x] = 1
        d = [(x - 1, y), (x, y + 1), (x + 1, y), (x, y - 1)] # make naighbor
        shuffle(d)
        while(d):
            xx,yy = d.pop()
            if not vis[yy][xx]:
                if xx == x: hor[max(y, yy)][x] = "+  "
                if yy == y: ver[y][max(x, xx)] = "   "
                stack.append((xx,yy))
                # break
        # for (xx, yy) in d:
        #     if vis[yy][xx]: continue
        #     if xx == x: hor[max(y, yy)][x] = "+  "
        #     if yy == y: ver[y][max(x, xx)] = "   "
        #     # walk(xx, yy)
        #     stack.append((xx,yy))
            # print('here')
    # walk(0, 0)

    s = ""
    for (a, b) in zip(hor, ver):
        s += ''.join(a + ['\n'] + b + ['\n'])
    return s
 
if __name__ == '__main__':
    print(make_maze())