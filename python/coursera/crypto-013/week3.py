import codecs
from Crypto.Hash import SHA256

__author__ = 'bbyk'

import sys, os

'''
Implement this algorithm: https://d396qusza40orc.cloudfront.net/crypto/images/pp3-fig.jpg
'''

file_name = sys.argv[1]

stat = os.stat(file_name)
file_size = stat.st_size
block_size = 1024

p = file_size - (file_size % block_size)
eff_block_size = file_size % block_size
ch = None
with open(file_name, 'rb') as f:
    while p >= 0:
        f.seek(p)
        block = f.read(eff_block_size)
        if ch:
            block = b"".join((block, ch))

        h = SHA256.new()
        h.update(block)
        ch = h.digest()

        eff_block_size = block_size
        p -= eff_block_size

print(codecs.encode(ch, "hex_codec"))

