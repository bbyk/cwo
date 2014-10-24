import sys

__author__ = 'bbyk'


class Solution:
    def __init__(self, nums):
        self.nums = nums
        self.merge = [0 for i in range(len(nums))]
        self.ni = 0

    def calc_inversions(self):
        self.sort(0, len(nums))
        return self.ni

    def sort(self, s, l):
        if l == 1:
            return

        hl = l >> 1
        self.sort(s, hl)
        self.sort(s + hl, l - hl)

        end_l = s + hl
        end_r = s + l
        m = s
        n = end_l

        for k in range(l):
            if n == end_r or (m < end_l and self.nums[m] <= self.nums[n]):
                self.merge[s + k] = self.nums[m]
                m += 1
            else:
                self.merge[s + k] = self.nums[n]
                n += 1
                self.ni += end_l - m

        for k in range(l):
            self.nums[s + k] = self.merge[s + k]


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

    print(Solution(nums).calc_inversions())
