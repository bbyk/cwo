import unittest

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

    def test_swaps(self):
        swaps = list(Solution.swaps("cdbbaadc"))
        self.assertEqual(28, len(swaps))

    def test_normalize(self):
        key, value = Solution.normalize("gzhhg")
        self.assertEqual(key, "abbcc")
        self.assertEqual(value, "baccb")

    def test_expectation(self):
        # self.assertEqual(3, Solution("abb").expectation())
        self.assertEqual(59.3380, Solution("cbaabbb").expectation())
        # self.assertEqual(59.3380, Solution("cbdecbd").expectation())

    def test_total(self):
        foo = "abbcccc"
        foo = set(Solution.swaps(foo))
        bar = "bcccbac"
        bar = set(Solution.swaps(bar))
        pass

    def test_distance(self):
        foo = Solution.distance("abcccbc")
        bar = Solution.distance("bcacccb")
        self.assertEqual(foo, bar)
        


if __name__ == '__main__':
    unittest.main()
