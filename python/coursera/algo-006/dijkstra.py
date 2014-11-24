import sys

__author__ = 'bbyk'

"""
Dijkstra algorithm with priority queue. Supported operations:
1. insert with priority
2. extract min
3. decrease priority 
"""


class PriorityQueue:
    def __init__(self):
        self.heap = []
        self.fast_line = {}

    def __contains__(self, item):
        return item in self.fast_line

    def assert_link_inv(self):
        for k, v in self.fast_line.items():
            assert k == self.heap[v][0]

    def insert(self, elem, priority, i=None):
        # self.assert_link_inv()

        if i is None:
            self.heap.append([elem, priority])
            i = len(self.heap) - 1
        else:
            self.heap[i] = [elem, priority]

        while i > 0:
            pi = (i - 1) >> 1
            if self.heap[pi][1] > self.heap[i][1]:
                self.heap[pi], self.heap[i] = self.heap[i], self.heap[pi]
                self.fast_line[self.heap[i][0]] = i
            else:
                break
            i = pi

        self.fast_line[elem] = i
        # self.assert_link_inv()

    def sift_down(self, i, l=None):
        if l is None:
            l = len(self.heap)
        if not l:
            return

        while True:
            ci = (i << 1) + 1
            if ci >= l:
                break

            if ci + 1 < l and self.heap[ci][1] > self.heap[ci + 1][1]:
                ci += 1

            if self.heap[i][1] > self.heap[ci][1]:
                self.heap[ci], self.heap[i] = self.heap[i], self.heap[ci]
                self.fast_line[self.heap[i][0]] = i
            else:
                break

            i = ci

        self.fast_line[self.heap[i][0]] = i

    def extract_min(self):
        # self.assert_link_inv()

        min = self.heap[0]
        del self.fast_line[min[0]]

        if len(self.heap) > 1:
            self.heap[0], self.heap[-1] = self.heap[-1], self.heap[0]
            self.fast_line[self.heap[0][0]] = 0

        del self.heap[-1]
        self.sift_down(0)

        # self.assert_link_inv()

        return min

    def __len__(self):
        return len(self.heap)

    def change_priority_if_higher(self, elem, priority):
        e_ix = self.fast_line[elem]

        assert self.heap[e_ix][0] == elem

        if self.heap[e_ix][1] > priority:
            del self.fast_line[elem]
            last_i = e_ix
            while True:
                ci = (last_i << 1) + 2
                if ci >= len(self.heap):
                    ci -= 1
                    if ci >= len(self.heap):
                        break
                last_i = ci

            if last_i != e_ix:
                self.heap[e_ix], self.heap[last_i] = self.heap[last_i], self.heap[e_ix]
                self.heap[last_i] = None
                # self.fast_line[self.heap[e_ix][0]] = e_ix
                self.sift_down(e_ix, last_i)
                # self.assert_link()

            self.insert(elem=elem, priority=priority, i=last_i)


class Dijkstra:
    def __init__(self, graph, start):
        start -= 1
        self.V = graph
        self.VL = [1000000] * len(self.V)
        self.VL[start] = 0
        self.visited = {start}
        self.queue = PriorityQueue()
        for arc in self.V[start]:
            self.queue.insert(elem=arc[0], priority=arc[1])
        self.calc_shortest()

    def path_size_for(self, *v_ids):
        for v in v_ids:
            yield self.VL[v - 1]

    def calc_shortest(self):
        while self.queue:
            next_v, length = self.queue.extract_min()
            self.visited.add(next_v)
            self.VL[next_v] = length

            for arc in self.V[next_v]:
                if arc[0] in self.visited:
                    continue

                if arc[0] in self.queue:
                    self.queue.change_priority_if_higher(elem=arc[0], priority=length + arc[1])
                else:
                    self.queue.insert(elem=arc[0], priority=length + arc[1])


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], mode='r', buffering=True)
    else:
        cin = sys.stdin

    NV = int(cin.readline())
    V = [[]] * NV

    while True:
        line = cin.readline().rstrip('\n\t ')
        if not line:
            break
        parts = line.split('\t')
        V[int(parts[0]) - 1] = tuple(
            [[int(t) - 1 if i == 0 else int(t) for i, t in enumerate(p.split(','))] for p in parts[1:]])

    print(",".join([str(t) for t in Dijkstra(graph=V, start=1).path_size_for(7, 37, 59, 82, 99, 115, 133, 165, 188, 197)]))
