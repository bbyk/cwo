__author__ = 'bbyk'

import sys


def v_k(v):
    '''
    histogram principle - group v by bands of 20000
    '''
    return (v + 10000) // 20000


def k_v(k):
    return (k * 20000) - 10000


if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], mode='r', buffering=True)
    else:
        cin = sys.stdin

    max_band_w = 1
    nums = {}
    while True:
        line = cin.readline().rstrip('\r\n\t')
        if not line:
            break
        v = int(line)
        k = v_k(v)

        if k not in nums:
            nums[k] = {v}
        else:
            nums[k].add(v)
            if len(nums[k]) > max_band_w:
                max_band_w = len(nums[k])

    found = set()
    for x_band in nums.keys():
        min_y_band = v_k(-10000 - k_v(x_band))
        for y_band in range(min_y_band, min_y_band + 2):
            if y_band not in nums:
                continue

            for x in nums[x_band]:
                for y in nums[y_band]:
                    if x == y:
                        continue
                    t = x + y
                    assert t >= -20000 and t <= 40000, "t = %d %d %d" % (t, x, y)
                    if t >= -10000 and t <= 10000:
                        found.add(t)
    print(len(nums), len(found), max_band_w)
