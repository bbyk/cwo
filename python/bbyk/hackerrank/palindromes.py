import sys
from collections import OrderedDict

__author__ = 'bbyk'


class Solution:
    g_cache = {}

    def __init__(self, str):
        self.str = str
        self.normalize()

    def expectation(self):
        if self.is_palindom(self.str):
            return 0

        if self.sorted_key not in self.g_cache:
            self.ensure_cache()
        return round(self.g_cache[self.sorted_key][self.norm_str], 4)

    def palindromes(self):
        ''' 
        all possible palindromes are all permutation of a half of the palindrome reciprocated to the other half.
        '''

        visited = set()

        s = list(self.norm_palin)
        l = len(s) >> 1
        i = 0
        j = 0
        stack = []

        while True:
            if i == l:
                perm = "".join(s)
                if perm not in visited:
                    visited.add(perm)
                    yield perm
                i, j = stack.pop()
                s[-1 - i], s[-1 - j] = s[-1 - j], s[-1 - i]
                s[i], s[j] = s[j], s[i]
                j += 1
                continue

            if j == l:
                if len(stack) == 0:
                    break
                i, j = stack.pop()
                s[-1 - i], s[-1 - j] = s[-1 - j], s[-1 - i]
                s[i], s[j] = s[j], s[i]
                j += 1
                continue

            s[i], s[j] = s[j], s[i]
            s[-1 - i], s[-1 - j] = s[-1 - j], s[-1 - i]
            stack.append([i, j])
            i += 1
            j = i

    def normalize(self):
        ht = OrderedDict()
        for c in self.str:
            if c not in ht:
                ht[c] = [c, 1]
            else:
                ht[c][1] += 1
        vals = sorted(ht.values(), key=lambda p: p[1])
        key = []
        palin = []
        c = ord('a')
        for i in range(len(vals)):
            p = vals[i]
            norm_c = chr(c + i)
            if p[1] == 1:
                self.mid_c = norm_c
                palin.append(norm_c)
            ht[p[0]] = norm_c
            for j in range(p[1]):
                key.append(norm_c)
            for j in range(p[1] >> 1):
                palin.append(norm_c)
                palin.insert(0, norm_c)
        self.norm_palin = "".join(palin)
        self.sorted_key = "".join(key)
        self.norm_str = "".join([ht[c] for c in self.str])
        self.n1_perm = ((len(self.norm_str) - 1) * len(self.norm_str)) >> 1

    @staticmethod
    def same_of(s):
        '''
        If you swap mirrored chars it doesn't lead to a palindrome. All such permutations have the same expectation.
        '''
        r = list(s)
        for perm in Solution.sameness_r(r, 0):
            yield perm
            yield perm[::-1]

    @staticmethod
    def sameness_r(r, i):
        l = len(r) >> 1
        if l == i:
            yield "".join(r)
            return

        for ix in range(i, l):
            # for perm in Solution.sameness_r(r, ix + 1):
            # yield perm
            r[i], r[-1 - i] = r[-1 - i], r[i]
            for perm in Solution.sameness_r(r, ix + 1):
                yield perm
            r[i], r[-1 - i] = r[-1 - i], r[i]


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

    def ensure_cache(self):
        stack = [self.sorted_key]
        visited_perm = {self.sorted_key}

        sames = {}

        var_id = 0
        vars = {}
        eqvs = OrderedDict()

        while len(stack):
            pop = stack.pop(0)
            eq_var = []
            eq_var_freq = {}

            for perm in Solution.swaps(pop):
                if not self.is_palindom(perm):
                    if perm not in visited_perm:
                        visited_perm.add(perm)
                        stack.append(perm)

                    if perm not in sames:
                        for p in Solution.same_of(perm):
                            sames[p] = perm

                    dist_p = sames[perm]
                    if dist_p not in eq_var_freq:
                        eq_var_freq[dist_p] = 1
                        eq_var.append(dist_p)

                        if dist_p not in vars:
                            vars[dist_p] = var_id
                            # vars[var_id] = dist_p
                            var_id += 1
                    else:
                        eq_var_freq[dist_p] += 1
            eq_var_freq[sames[pop]] -= self.n1_perm

            eq_var = frozenset([(t, eq_var_freq[t]) for t in eq_var])

            if eq_var not in eqvs:
                eqvs[eq_var] = eq_var

            # if len(eqvs) == len(vars):
            #     break

        assert self.sorted_key in visited_perm
        assert self.norm_str in visited_perm
        assert len(eqvs) == len(vars)

        m = [[(0 if t < var_id else -1) for t in range(var_id + 1)] for j in range(var_id)]
        i = 0
        for eq_var in eqvs.keys():
            for var, freq in eq_var:
                j = vars[var]
                m[i][j] = freq / self.n1_perm
            i += 1

        for i in range(len(m) - 1):
            for k in range(i + 1, len(m)):
                coef = m[k][i] / m[i][i]
                m[k][i] = 0
                for j in range(i + 1, len(m[i])):
                    m[k][j] = m[k][j] - (coef * m[i][j])
                pass
            pass

        i2e_cache = {}
        for i in range(len(m) - 1, - 1, -1):
            sum = 0
            for j in range(i + 1, len(m[i]) - 1):
                sum += m[i][j] * i2e_cache[j]
            i2e_cache[i] = (m[i][-1] - sum ) / m[i][i]

        perm2e_cache = {}
        for perm in visited_perm:
            perm2e_cache[perm] = i2e_cache[vars[sames[perm]]]

        self.g_cache[self.sorted_key] = perm2e_cache


if __name__ == "__main__":

    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1])
    else:
        cin = sys.stdin

    T = int(cin.readline())
    while T:
        line = cin.readline().split('\n', 1)[0].split(' ', 1)[0]
        # print(line)
        print("%4.4f" % Solution(line).expectation())
        T -= 1

    if cin is not sys.stdin:
        cin.close()
