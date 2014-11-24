import sys

__author__ = 'bbyk'


class PriorityQueue:
    def __init__(self):
        self.heap = []
        self.fast_line = {}

    def __contains__(self, item):
        return item in self.fast_line

    def insert(self, elem, priority, i=None):
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
            i = pi

        self.fast_line[elem] = i

    def sift_down(self, i):
        while True:
            ci = (i << 1) + 1
            if ci >= len(self.heap):
                break

            if ci + 1 < len(self.heap) and self.heap[ci][1] > self.heap[ci + 1][1]:
                ci += 1

            self.heap[ci], self.heap[i] = self.heap[i], self.heap[ci]
            self.fast_line[self.heap[i][0]] = i

            i = ci

    def extract_min(self):
        min = self.heap[0]
        del self.fast_line[min[0]]

        if len(self.heap) > 1:
            self.heap[0], self.heap[-1] = self.heap[-1], self.heap[0]
            self.fast_line[self.heap[0][0]] = 0

        del self.heap[-1]
        self.sift_down(0)

        return min

    def __len__(self):
        return len(self.heap)

    def change_priority_if_higher(self, elem, priority):
        e_ix = self.fast_line[elem]
        if self.heap[e_ix][1] > priority:
            del self.fast_line[elem]
            last_i = e_ix
            while True:
                ci = (last_i << 1) + 1
                if ci >= len(self.heap):
                    break
                if ci + 1 < len(self.heap) and self.heap[ci][1] > self.heap[ci + 1][1]:
                    ci += 1
                last_i = ci

            if last_i != e_ix:
                self.heap[e_ix], self.heap[last_i] = self.heap[e_ix], self.heap[last_i]
                self.fast_line[self.heap[e_ix][0]] = e_ix
                self.sift_down(e_ix)

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
            yield str(self.VL[v - 1])

    def calc_shortest(self):
        while self.queue:
            next_v, length = self.queue.extract_min()
            self.visited.add(next_v)
            self.VL[next_v] = length

            for arc in self.V[next_v]:
                if arc[0] in self.visited:
                    pass

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

    print(",".join(Dijkstra(graph=V, start=1).path_size_for(1, 2, 3, 4)))
