import unittest
import math

from bbyk.hackerrank.palindromes import Solution


__author__ = 'bbyk'


class PalindromTests(unittest.TestCase):
    def test_str_is_already_palindrom(self):
        self.assertEqual(0, Solution("b").expectation())
        self.assertEqual(0, Solution("bb").expectation())
        self.assertEqual(0, Solution("aba").expectation())

    def test_three_letter_palindrom(self):
        self.assertEqual(3, Solution("abb").expectation())

    def test_is_palindrom(self):
        self.assertTrue(Solution.is_palindom("bab"))
        self.assertFalse(Solution.is_palindom("abb"))

    def test_sameness(self):
        l = list(Solution.same_of("abcdabcd"))
        s = set(l)
        self.assertEqual(len(l), len(s))

    def test_swaps(self):
        swaps = list(Solution.swaps("cdbbaadc"))
        self.assertEqual(28, len(swaps))

    def test_normalize(self):
        s = Solution("gzhhg")
        s.normalize()
        self.assertEqual(s.sorted_key, "abbcc")
        self.assertEqual(s.norm_str, "baccb")
        self.assertEqual(s.mid_c, 'a')

    def test_expectation(self):
        # self.assertEqual(3, Solution("abb").expectation())
        self.assertEqual(59.3380, Solution("cbaabbb").expectation())
        self.assertEqual(59.3380, Solution("abcdabcd").expectation())
        # self.assertEqual(59.3380, Solution("cbdecbd").expectation())

    def test_allpalin(self):
        s = "abcdabcd"
        half = len(s) >> 1
        self.assertEqual(math.factorial(half), len(list(Solution(s).palindromes())))

        s = "abccabcc"
        half = len(s) >> 1
        # twice as less palindromes are there because of cc
        self.assertEqual(math.factorial(half) >> 1, len(list(Solution(s).palindromes())))

        s = "cccccccc"
        half = len(s) >> 1
        # 16x as less palindromes are there because of cc
        self.assertEqual(math.factorial(half) >> 4, len(list(Solution(s).palindromes())))


    def test_total(self):
        foo = "abbcccc"
        foo = set(Solution.swaps(foo))
        bar = "bcccbac"
        bar = set(Solution.swaps(bar))
        pass


if __name__ == '__main__':
    unittest.main()
