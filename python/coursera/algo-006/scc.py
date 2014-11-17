import sys
import heapq

__author__ = 'bbyk'


class SccFinder():
    def __init__(self, V):
        self.V = V
        self.F = [None] * len(self.V)

    def top(self, max_scc):
        top_heap = []

        self.visited = set()
        self.stack = []
        self.backtracks = {}

        fc = 0

        for v in range(len(self.V) - 1, 0, -1):
            if v not in self.visited:
                for node in self.dfs(v, tail_ix=1, head_ix=0):
                    self.F[fc] = node
                    fc += 1

        self.visited.clear()

        for v in reversed(self.F):
            if v not in self.visited:
                s = 0
                for node in self.dfs(v, tail_ix=0, head_ix=1):
                    s += 1

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
        self.stack.append(node)

        while self.stack:
            node = self.stack.pop()
            bt_len = len(self.backtracks)
            for arc in self.V[node]:
                if arc[tail_ix] == node and arc[head_ix] not in self.visited:
                    # only first child gets to be in the backtracks
                    # the first child is the last one oopped out from the stack 
                    if len(self.backtracks) == bt_len and arc[head_ix] not in self.backtracks:
                        self.backtracks[arc[head_ix]] = node
                    self.visited.add(arc[head_ix])
                    self.stack.append(arc[head_ix])

            assert len(self.backtracks) == bt_len or len(self.backtracks) - 1 == bt_len

            if len(self.backtracks) == bt_len:
                yield node

                while node in self.backtracks:
                    prev_node = self.backtracks[node]
                    del self.backtracks[node]
                    yield prev_node
                    node = prev_node

        assert not self.stack
        assert not self.backtracks


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], mode='r', buffering=True)
    else:
        cin = sys.stdin

    T = int(cin.readline())
    V = [None] * T

    while True:
        line = cin.readline().rstrip('\n\t ')
        if not line:
            break
        arc = tuple([int(s) - 1 for s in line.split(' ')])
        if V[arc[0]] is None:
            V[arc[0]] = [arc]
        else:
            V[arc[0]].append(arc)

        if V[arc[1]] is None:
            V[arc[1]] = [arc]
        else:
            V[arc[1]].append(arc)

    print(",".join([str(t) for t in SccFinder(V).top(5)]))
