import sys

__author__ = 'bbyk'

'''
https://www.hackerrank.com/challenges/clique
'''


def e_for_complete(n):
    return (n * (n - 1)) >> 1


def edges_at_most(r, n):
    '''
    https://en.wikipedia.org/wiki/Tur%C3%A1n%27s_theorem
    https://ru.wikipedia.org/wiki/%D0%A2%D0%B5%D0%BE%D1%80%D0%B5%D0%BC%D0%B0_%D0%A2%D1%83%D1%80%D0%B0%D0%BD%D0%B0
    if there is a clique of size r in n-vertex graph this is
    how many edges at most the graph can have.
    '''
    m = n // r  # size of a partition
    k = n % r  # partitions with m+1 size
    rk = r - k  # partitions of m size

    # edges between two groups of m+1 size is (m + 1) * (m + 1)
    # for k groups:
    res = e_for_complete(k) * (m + 1) * (m + 1)

    # edges between two groups of m size is m * m
    # for rk groups:
    res += e_for_complete(rk) * m * m

    # edges between two big groups
    res += k * (m + 1) * rk * m

    return res


def min_max_clique(N, M):
    l = 2
    r = N
    while l < r:
        m = l + ((r - l) >> 1)
        n_edges = edges_at_most(m, N)
        if n_edges == M:
            return m
        if n_edges > M:
            r = m
        else:
            l = m + 1
    return r


if __name__ == "__main__":

    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1])
    else:
        cin = sys.stdin

    T = int(cin.readline())
    while T:
        N, M = [int(t) for t in cin.readline().split(' ', 1)]
        print(min_max_clique(N, M))
        T -= 1

    if cin is not sys.stdin:
        cin.close()
