import sys

"""
https://www.hackerrank.com/challenges/even-tree
"""
__author__ = 'bbyk'


def read_tree(N):
    tree = dict()
    while N:
        t, f = [int(i) for i in (cin.readline().split(' ', 1))]
        if f not in tree:
            tree[f] = [t]
        else:
            tree[f].append(t)
        N -= 1
    return tree


def num_to_remove(tree, node, cnt):
    sum = 1
    if node not in tree:
        return sum
    for i in tree[node]:
        ns = num_to_remove(tree, i, cnt)
        if not ns & 1:
            cnt[0] += 1
        else:
            sum += ns
    return sum


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1])
    else:
        cin = sys.stdin

    N, M = [int(i) for i in (cin.readline().split(' ', 1))]

    cnt = [0]
    num_to_remove(read_tree(M), 1, cnt)
    print(cnt[0])

    if cin is not sys.stdin:
        cin.close()
    pass
