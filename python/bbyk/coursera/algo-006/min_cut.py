import sys
import math
import random

__author__ = 'bbyk'


class MinCut:
    def value(self):
        min = None
        max_iter = 3 * int(math.ceil(math.log(len(self.input))))
        while max_iter > 0:
            self.extractVE()
            cut_of_g = self.min_cut()
            if min is None or cut_of_g < min:
                min = cut_of_g
            max_iter -= 1
        return min

    def __init__(self, input):
        self.input = input

    def min_cut(self):

        while len(self.V) > 2:
            while not self.E[-1]:
                del self.E[-1]

            e_i = random.randint(0, len(self.E) - 1)
            e_to_kill = self.E[e_i]
            if not e_to_kill:
                self.E[e_i] = self.E[len(self.E) - 1]
                del self.E[-1]
                continue

            f = e_to_kill.pop()
            fv = self.V[f]
            t = e_to_kill.pop()
            tv = self.V[t]

            for e in tv:
                if e and f not in e:
                    e.remove(t)
                    e.add(f)
                    fv.append(e)
                else:
                    e.clear()
            del self.V[t]

            for i in range(len(fv) - 1, 0, -1):
                if not len(fv[i]):
                    last_i = len(fv) - 1
                    if i < last_i:
                        fv[i] = fv[-1]
                    del fv[-1]
            pass

        v1, v2 = self.V.keys()
        sum = 0
        for e in self.V[v1]:
            if v2 in e:
                sum += 1
        return sum

    def extractVE(self):

        V = {}
        E = {}

        for vs in self.input:
            V[vs[0]] = []
            for v in vs[1:]:
                e = {vs[0], v}
                fe = frozenset(e)
                if fe not in E:
                    E[fe] = e
                else:
                    e = E[fe]

                V[vs[0]].append(e)

        self.V = V
        self.E = list(E.values())


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], 'r')
    else:
        cin = sys.stdin

    V = []
    while True:
        line = cin.readline().rstrip('\n\t')
        if not line:
            break
        V.append([int(s) - 1 for s in line.split('\t')])

    mc = MinCut(V)

    print(mc.value())
