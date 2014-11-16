import sys
import heapq

__author__ = 'bbyk'


class SccFinder():
    def __init__(self, V):
        self.V = V
        self.F = [[] for t in range(len(self.V))]

    def top(self, max_scc):
        top_heap = []

        self.visited = set()

        fc = 0

        for v in range(len(self.V) - 1, 0, -1):
            if v not in self.visited:
                for node in self.dfs(v, tail_ix=1, head_ix=0):
                    self.F[fc] = node
                    fc += 1

        self.visited = set()
        for v in reversed(self.F):
            if v not in self.visited:
                s = 0
                for node in self.dfs(v, tail_ix=0, head_ix=1):
                    s += 1

                print(s)
                if not top_heap or (s == top_heap[0] and len(top_heap) < max_scc):
                    heapq.heappush(top_heap, s)
                elif s > top_heap[0]:
                    heapq.heappushpop(top_heap, s)

        stack = [0 for t in range(max_scc - len(top_heap))]
        while top_heap:
            stack.append(heapq.heappop(top_heap))

        return reversed(stack)

    def dfs(self, node, tail_ix, head_ix):
        self.visited.add(node)
        stack = [node]
        backtracks = {}

        while stack:
            node = stack.pop()
            bt_len = len(backtracks)
            for arc in self.V[node]:
                if arc[tail_ix] == node and arc[head_ix] not in self.visited:
                    # only first child gets to be in the backtracks
                    # the first child is the last one oopped out from the stack 
                    if len(backtracks) == bt_len and arc[head_ix] not in backtracks:
                        backtracks[arc[head_ix]] = node
                    self.visited.add(arc[head_ix])
                    stack.append(arc[head_ix])

            assert len(backtracks) == bt_len or len(backtracks) - 1 == bt_len

            if len(backtracks) == bt_len:
                yield node

                while node in backtracks:
                    prev_node = backtracks[node]
                    del backtracks[node]
                    yield prev_node
                    node = prev_node


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], 'r')
    else:
        cin = sys.stdin

    T = int(cin.readline())
    V = [[] for t in range(T)]

    while True:
        line = cin.readline().rstrip('\n\t ')
        if not line:
            break
        arc = tuple([int(s) - 1 for s in line.split(' ')])
        V[arc[0]].append(arc)
        V[arc[1]].append(arc)

    print(",".join([str(t) for t in SccFinder(V).top(5)]))
