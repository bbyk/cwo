__author__ = 'bbyk'


class Grid:
    pass


i = input("You play x (y/n)?")

if i == "y":
    pc = "x"
    npc = "o"
else:
    pc = "o"
    npc = "x"

grid = [None] * 9


def is_draw(g):
    for x in g:
        if x is None:
            return False
    return True


def print_grid(g):
    print("---")
    for i, x in enumerate(g):
        if i % 3 == 0:
            print()
        print(" " if x is None else x, end="")
    print("---")


# http://en.wikipedia.org/wiki/Minimax
def minmax(g, maxx=None, depth=None):
    mv = None
    if maxx:
        mv = [-20000, -1]
        for i, v in enumerate(g):
            if v is None:
                gi = list(g)
                gi[i] = npc if maxx else pc
                if won(gi, npc if maxx else pc):
                    mm = 10000 if maxx else -10000
                elif is_draw(gi):
                    mm = 5000 if maxx else -5000
                else:
                    mm, vv = minmax(gi, maxx=False, depth=depth + 1)
                if (mm > mv[0]):
                    mv[0] = mm
                    mv[1] = i
    else:
        mv = [20000, -1]
        for i, v in enumerate(g):
            if v is None:
                gi = list(g)
                gi[i] = npc if maxx else pc
                if won(gi, npc if maxx else pc):
                    mm = 10000 if maxx else -10000
                elif is_draw(gi):
                    mm = 5000 if maxx else -5000
                else:
                    mm, vv = minmax(gi, maxx=True, depth=depth + 1)
                if (mm < mv[0]):
                    mv[0] = mm
                    mv[1] = i

    return mv


def ply(g):
    v, i = minmax(list(g), maxx=True, depth=1)
    g[i] = npc
    pass


def occupy(g, x, y, pc):
    g[(y - 1) * 3 + (x - 1)] = pc
    pass


def user_turn():
    print()
    i = input("Your turn:")
    return [int(t) for t in i.split(",")]


wins = []
wins.append((0, 1, 2))
wins.append((3, 4, 5))
wins.append((6, 7, 8))
wins.append((0, 3, 6))
wins.append((1, 4, 7))
wins.append((2, 5, 8))
wins.append((0, 4, 8))
wins.append((2, 4, 6))


def won(g, c):
    for w in wins:
        found = True
        for i in w:
            if g[i] != c:
                found = False
                break
        if found:
            return True

    return False


while True:
    if is_draw(grid):
        break
    if pc == "x":
        print_grid(grid)
        x, y = user_turn()
        occupy(grid, x, y, pc)
        if won(grid, pc):
            break
        ply(grid)
        if won(grid, npc):
            break
    else:
        ply(grid)
        print_grid(grid)
        if won(grid, npc):
            break
        x, y = user_turn()
        occupy(grid, x, y, pc)
        if won(grid, pc):
            break
