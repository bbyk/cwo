import sys
from collections import OrderedDict

__author__ = 'bbyk'


class Solution:
    g_cache = {}

    def __init__(self, str):
        self.str = str
        self.mid_c = None
        self.norm_str = None

    def expectation(self):
        if self.is_palindom(self.str):
            return 0

        self.normalize()

        if self.sorted_key not in self.g_cache:
            self.build_cache()
        return round(self.g_cache[self.sorted_key][self.norm_str], 4)


    def normalize(self):
        if self.norm_str is not None:
            return

        ht = OrderedDict()
        for c in self.str:
            if c not in ht:
                ht[c] = [c, 1]
            else:
                ht[c][1] += 1
        vals = sorted(ht.values(), key=lambda p: p[1])
        key = []
        c = ord('a')
        for i in range(len(vals)):
            p = vals[i]
            norm_c = chr(c + i)
            if p[1] == 1:
                self.mid_c = norm_c
            ht[p[0]] = norm_c
            for j in range(p[1]):
                key.append(norm_c)

        self.sorted_key = "".join(key)
        self.norm_str = "".join([ht[c] for c in self.str])

    def distance(self):
        self.normalize()

        swaps2p = 0
        for i in range(len(self.norm_str) >> 1):
            c = self.norm_str[i]
            if c == self.mid_c:
                swaps2p += 1
            elif self.norm_str[-i - 1] != c:
                swaps2p += 1
        return swaps2p


    @staticmethod
    def swaps(s):
        s = list(s)
        for i in range(len(s) - 1):
            for j in range(i + 1, len(s)):
                s[i], s[j] = s[j], s[i]
                perm = "".join(s)
                yield perm
                s[i], s[j] = s[j], s[i]

    @staticmethod
    def is_palindom(s):
        # from 0 to half of the string
        for i in range(len(s) >> 1):
            if s[i] != s[-1 - i]:
                return False
        return True

    def build_cache(self):
        stack = [self.sorted_key]
        var_id = 0
        vars = {}
        eqvs = []
        p = None
        n_perm = 0

        while len(stack):
            pop = stack.pop(0)
            eqvs.append([pop])

            for perm in Solution.swaps(pop):
                if p is None:
                    n_perm += 1
                if not self.is_palindom(perm):
                    if perm not in vars:
                        vars[perm] = var_id
                        # vars[var_id] = perm
                        var_id += 1
                        if pop != perm:
                            stack.append(perm)

                    eqvs[-1].append(perm)

            p = 1 / n_perm

        assert self.sorted_key in vars
        assert self.norm_str in vars

        m = [[(0 if t < var_id else -1) for t in range(var_id + 1)] for j in range(var_id)]
        for i, eqv in enumerate(eqvs):
            vp = vars[eqv[0]]
            m[i][vp] -= 1
            for var in eqv[1:]:
                vp = vars[var]
                m[i][vp] += p

        for i in range(len(m) - 1):
            for k in range(i + 1, len(m)):
                coef = m[k][i] / m[i][i]
                m[k][i] = 0
                for j in range(i + 1, len(m[i])):
                    m[k][j] = m[k][j] - (coef * m[i][j])
                pass

        i2e_cache = {}
        for i in range(len(m) - 1, - 1, -1):
            sum = 0
            for j in range(i + 1, len(m[i]) - 1):
                sum += m[i][j] * i2e_cache[j]
            i2e_cache[i] = (m[i][-1] - sum ) / m[i][i]

        perm2e_cache = {}
        for perm in vars.keys():
            perm2e_cache[perm] = i2e_cache[vars[perm]]

        self.g_cache[self.sorted_key] = perm2e_cache


if __name__ == "__main__":

    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1])
    else:
        cin = sys.stdin

    T = int(cin.readline())
    while T:
        print(Solution(cin.readline()).expectation())
        T -= 1

    if cin is not sys.stdin:
        cin.close()
