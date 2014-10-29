import sys

__author__ = 'bbyk'


def first_elem_pivot(nums, s, l):
    return s


def last_elem_pivot(nums, s, l):
    return s + l - 1


def median_of_three_pivot(nums, s, l):
    ai = s
    bi = s + (l >> 1 if l & 1 else (l >> 1) - 1)
    ci = s + l - 1

    a = nums[ai]
    b = nums[bi]
    c = nums[ci]

    if a > b:
        a, b = b, a
        ai, bi = bi, ai

    if b > c:
        b, c = c, b
        bi, ci = ci, bi

    if a > b:
        c, b = b, c
        ai, bi = bi, ai

    return bi


class Solution:
    def __init__(self, nums, pivot_strategy):
        self.nums = nums
        self.nc = 0
        self.pivot_strategy = pivot_strategy

    def calc_comparisons(self):
        self.quick_sort()
        return self.nc

    def pirtition(self, s, l):
        pi = self.pivot_strategy(self.nums, s, l)
        if s != pi:
            self.nums[s], self.nums[pi] = self.nums[pi], self.nums[s]
        pv = self.nums[s]

        i = s + 1
        for j in range(i, s + l):
            if pv > self.nums[j]:
                if j > i:
                    self.nums[i], self.nums[j] = self.nums[j], self.nums[i]
                i += 1
        if s != i - 1:
            self.nums[s], self.nums[i - 1] = self.nums[i - 1], self.nums[s]

        return i - 1

    def quick_sort(self):
        stack = []
        stack.append((0, len(self.nums)))

        while len(stack):
            s, l = stack.pop()
            if l < 2:
                continue

            # length - 1 'coz we don't count pivots
            self.nc += l - 1

            pi = self.pirtition(s, l)
            assert pi >= s and pi < s + l, "pi is out of range: %d %d %d" % (s, l, pi)

            stack.append((s, pi - s))
            stack.append((pi + 1, s + l - pi - 1))


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], 'r')
    else:
        cin = sys.stdin

    T = int(cin.readline())
    nums = []
    while T > 0:
        nums.append(int(cin.readline()))
        T -= 1

    s = Solution(list(nums), first_elem_pivot)
    print(s.calc_comparisons())
    print(s.nums)

    s = Solution(list(nums), last_elem_pivot)
    print(s.calc_comparisons())
    print(s.nums)

    s = Solution(list(nums), median_of_three_pivot)
    print(s.calc_comparisons())
    print(s.nums)
    
