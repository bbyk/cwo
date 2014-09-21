__author__ = 'bbyk'

import sys


class Nfa(object):
    def __init__(self):
        self.states = []
        # start state
        self.ss = None
        # acceptance state
        self.acs = None


    def new_state(self):
        s = State()
        s.id = len(self.states)
        self.states.append(s)
        return s


class Transition(object):
    def __init__(self, c, s):
        self.c = c
        self.s = s


class State(object):
    def __init__(self):
        self.trans = []


class Parser(object):
    def __init__(self, pattern):
        self.nfa = Nfa()
        self.pattern = pattern
        self.s_stack = []
        self.caret = 0

    def parse(self):
        self.parse_node()
        self.nfa.ss = self.s_stack.pop()
        self.nfa.acs = self.s_stack.pop()
        return self.nfa

    def parse_node(self):
        """
        http://www.codeproject.com/Articles/5412/Writing-own-regular-expression-parser 
        """

        l = None
        r = None
        c = self.pattern[self.caret]
        if c == 'a' or c == 'b':
            l = self.nfa.new_state()
            r = self.nfa.new_state()
            l.trans.append(Transition(c, r))
            self.caret += 1
        elif c == '(':
            self.caret += 1
            self.parse_node()
            c = self.pattern[self.caret]
            if c == '|':
                self.caret += 1
                self.parse_node()

                l = self.nfa.new_state()
                r = self.nfa.new_state()

                l.trans.append(Transition('e', self.s_stack.pop()))
                self.s_stack.pop().trans.append(Transition('e', r))
                l.trans.append(Transition('e', self.s_stack.pop()))
                self.s_stack.pop().trans.append(Transition('e', r))
            elif c == '*':
                l = self.nfa.new_state()
                r = self.nfa.new_state()

                l.trans.append(Transition('e', r))

                ll = self.s_stack.pop()
                l.trans.append(Transition('e', ll))

                rr = self.s_stack.pop()
                rr.trans.append(Transition('e', r))
                rr.trans.append(Transition('e', ll))
            else:
                self.parse_node()
                sl = self.s_stack.pop()
                sr = self.s_stack.pop()
                rl = self.s_stack.pop()
                rr = self.s_stack.pop()
                rr.trans.append(Transition('e', sl))

                l = rl
                r = sr

            self.caret += 1

        self.s_stack.append(r)
        self.s_stack.append(l)


class Dfa(object):
    def __init__(self, nfa):
        self.nfa = nfa
        self.visited = dict()
        self.dfs = []
        self.dfa = dict()
        self.sid = 0
        self.matrix = []
        self.build_dfa()
        self.build_adjacency_matrix()

    class State(object):

        def __init__(self, u):
            self.trans = []
            self.u = u

    @staticmethod
    def epsilon_closure(T):
        # on epsilon trans we can go to the same node
        res = set(T)
        # copy the set the stack
        stack = list(T)

        while len(stack):
            s = stack.pop()
            for tr in s.trans:
                if tr.c == 'e' and tr.s not in res:
                    res.add(tr.s)
                    stack.append(tr.s)

        return frozenset(res)

    def build_dfa(self):
        dstates = [self.epsilon_closure([self.nfa.ss])]

        while len(dstates):
            t = dstates.pop()

            self.visited[t] = self.sid
            self.dfs.append(t)
            self.sid += 1

            for c in ['a', 'b']:
                t_on_c = self.move(t, c)
                if not len(t_on_c):
                    continue
                u = self.epsilon_closure(t_on_c)
                if u not in self.visited:
                    dstates.append(u)
                    if t not in self.dfa:
                        self.dfa[t] = {c: u}
                    else:
                        self.dfa[t][c] = u

        pass

    @staticmethod
    def move(t, c):
        res = set()
        for s in t:
            for tr in s.trans:
                if tr.c == c:
                    res.add(tr.s)
        return res

    def build_adjacency_matrix(self):
        self.matrix = [[0 for x in xrange(self.sid)] for x in xrange(self.sid)]
        for ix, t in enumerate(self.dfs):
            if t not in self.dfa:
                continue
            for u in self.dfa[t].values():
                self.matrix[ix][self.visited[u]] = 1
        pass


class Solution(object):
    def __init__(self, dfa):
        self.dfa = dfa

    def get_number(self, l):
        if l > 1:
            m = self.multiply(l)
        else:
            m = self.dfa.matrix
        sum = 0
        for ix in xrange(1, len(m[0])):
            dfs_state = self.dfa.dfs[ix]
            if self.dfa.nfa.acs in dfs_state:
                sum = (sum + m[0][ix]) % 1000000007

        return sum

    def multiply(self, l):
        pass


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], 'r')
    else:
        cin = sys.stdin

    T = int(cin.readline())

    while T:
        line = cin.readline()
        regex, L = line.split(' ', 1)
        L = int(L)
        nfa = Parser(regex).parse()
        dfa = Dfa(nfa)
        solution = Solution(dfa)
        print solution.get_number(L)
        T -= 1

    if cin is not sys.stdin:
        cin.close()
