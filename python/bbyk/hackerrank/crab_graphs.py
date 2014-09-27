import sys

'''
https://www.hackerrank.com/challenges/crab-graphs

Idea: If flow is sent through the head of a crab the flow will be max. Let's transform the problem to a maximum flow problem.
'''

__author__ = 'bbyk'


class Solution:
    C_MAX = 1000

    def read_input(self, cin):
        # N - # of vertices
        # T - # of feed of a crab
        # M - number of edges
        self.N, self.T, M = [int(t) for t in cin.readline().split(' ', 2)]
        '''
        N - number of verices. Since we are only interested in crabs we can modify the graph,
        so that from each vertex you can go through the adjacent edges only: from-vertex is map to an even number,
        while to-vertex is mapped to an odd number. This splits the graph in crabs.
        This also allows us to create a flow network graph. 
        '''
        self.adj_mtx = [[0 for j in range(self.map_odd(self.N) + 1)] for i in range(self.map_odd(self.N) + 1)]

        for i in range(M):
            f, t = [int(t) for t in cin.readline().split(' ', 1)]
            # The capacity for each edge is infinite, i.e. greater than max T
            self.adj_mtx[self.map_even(f)][self.map_odd(t)] = Solution.C_MAX
            self.adj_mtx[self.map_even(t)][self.map_odd(f)] = Solution.C_MAX

        '''
        We need a source node and a sink node. Flow from the source node will go to any even node of the graph.
        The capacity of the edge is set to T - size of the crab because if gone through the
        the head of the crab will yield flow at the capacity. The capacity of the edges from odd node to the sink is 1
        for the same reason.
        '''

        for i in range(self.N):
            self.adj_mtx[0][self.map_even(i)] = self.T
            self.adj_mtx[self.map_odd(i)][1] = 1
        pass

    def max_vertices_covered(self):
        '''
        Use Edmonds–Karp algorithm to find max flow
        '''
        self.flow_mtx = [[0 for j in range(self.map_odd(self.N) + 1)] for i in range(self.map_odd(self.N) + 1)]

        while True:
            min_cap, path = self.bfs()
            if not min_cap:
                break
            v = 1  # sink node
            while v != 0:  # source node
                u = path[v]
                # forward direction
                self.flow_mtx[u][v] += min_cap
                # reverse direction
                self.flow_mtx[v][u] -= min_cap
                v = u

        sum = 0
        for i in range(self.N):
            if self.flow_mtx[0][self.map_even(i)] == self.T:
                sum += self.T + 1  # 1 head and T feet
        return sum

    def bfs(self):
        path = dict()
        mins = {0: Solution.C_MAX * Solution.C_MAX}  # kind of infinity
        queue = [0]  # queue with a single element - source

        while len(queue):
            u = queue.pop(0)  # FIFO, to pop the first one
            for v, c in enumerate(self.adj_mtx[u]):
                if c - self.flow_mtx[u][v] > 0 and v not in path:
                    path[v] = u
                    mins[v] = min(mins[u], c - self.flow_mtx[u][v])
                    if v == 1:  # reached sink
                        return mins[1], path
                    else:
                        queue.append(v)

        return 0, path

    @staticmethod
    def map_even(a):
        return (a << 1) + 2


    @staticmethod
    def map_odd(a):
        return (a << 1) + 3


if __name__ == "__main__":

    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1])
    else:
        cin = sys.stdin

    C = int(cin.readline())
    while C:
        s = Solution()
        s.read_input(cin)
        print(s.max_vertices_covered())

        C -= 1

    if cin is not sys.stdin:
        cin.close()
