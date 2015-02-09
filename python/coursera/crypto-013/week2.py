__author__ = 'bbyk'

'''
Install PyCrypto:

pip3 PyCrypto
'''

import codecs
import io

from Crypto.Cipher import AES


cbc_key_s = codecs.decode("140b41b22a29beb4061bda66b6747e14", "hex_codec")
ct = codecs.decode(
    "5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253",
    "hex_codec")

iv = ct[:16]

# brute force
cipher = AES.new(cbc_key_s, AES.MODE_CBC, iv)
print(cipher.decrypt(ct[16:]))

# recommended way - custom CBC impl
cipher = AES.new(cbc_key_s, AES.MODE_ECB, iv)
prev = iv
block_pos = 16
output = []
while block_pos < len(ct):
    ct_block = ct[block_pos:block_pos + 16]
    output.append(bytes(x ^ y for x, y in zip(cipher.decrypt(ct_block), prev)))
    prev = ct_block
    block_pos += 16

print(b"".join(output))

# recommended way - custom CTR impl

cbc_key_s = codecs.decode("36f18357be4dbd77f050515c73fcf9f2", "hex_codec")
ct = codecs.decode(
    "770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451",
    "hex_codec")
cipher = AES.new(cbc_key_s, AES.MODE_ECB, iv)

iv = bytearray(ct[:16])
block_pos = 16
output = []
while block_pos < len(ct):
    ct_block = ct[block_pos:block_pos + 16]
    Fkiv = cipher.encrypt(bytes(iv))
    output.append(bytes(x ^ y for x, y in zip(Fkiv, ct_block)))
    block_pos += 16
    iv[15] += 1
print(b"".join(output))
