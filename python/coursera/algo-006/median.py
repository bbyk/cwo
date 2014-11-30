import heapq
import sys

__author__ = 'bbyk'

if __name__ == "__main__":
    cin = None

    if len(sys.argv) > 1:
        cin = open(sys.argv[1], mode='r', buffering=True)
    else:
        cin = sys.stdin

    min_h = []
    max_h = []
    l = 0
    m_sum = 0
    while True:
        line = cin.readline().rstrip('\r\n\t')
        if not line:
            break
        v = int(line)
        l += 1
        if min_h and v > min_h[0]:
            heapq.heappush(min_h, v)
        else:
            heapq.heappush(max_h, -v)

        # check if not balanced
        while True:
            if len(max_h) < len(min_h):
                v = heapq.heappop(min_h)
                heapq.heappush(max_h, -v)
                continue
            elif len(max_h) > len(min_h) + 1:
                v = -heapq.heappop(max_h)
                heapq.heappush(min_h, v)
                continue

            break
        assert (l & 1 and len(max_h) - 1 == len(min_h)) or (not l & 1 and len(max_h) == len(min_h))

        m_sum = (m_sum - max_h[0]) % 10000

    print(l, m_sum)
