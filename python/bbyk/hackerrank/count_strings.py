__author__ = 'bbyk'

import sys


class Nfa(object):
    def __init__(self):
        self.states = []


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
        pass

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
        T -= 1

    if cin is not sys.stdin:
        cin.close()
