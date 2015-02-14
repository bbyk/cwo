# --------------------------------------------------------------
# padding oracle
# --------------------------------------------------------------

__author__ = 'bbyk'

import codecs
import urllib.request
import urllib.error
import urllib.parse


ct_hex = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4".encode('ascii')
ct = codecs.decode(ct_hex, "hex_codec")

TARGET = 'http://crypto-class.appspot.com/po?er='


class PaddingOracle(object):
    def query(self, q):
        target = TARGET + urllib.parse.quote(q)  # Create query URL
        req = urllib.request.Request(target)  # Send HTTP request to server
        try:
            f = urllib.request.urlopen(req)  # Wait for response
            return False
        except urllib.error.HTTPError as e:
            if e.code == 404:
                print(("We got: %d" % e.code))  # Print response code
                return True  # good padding
            return False  # bad padding


clear_t = [None] * 64

po = PaddingOracle()
for b in range(2, -1, -1):
    for i in range(15, -1, -1):
        pos = (b << 4) + i
        bact = bytearray(ct[:(b << 4) + 32])
        for p in range((b << 4) + 31, pos + 16, -1):
            if clear_t[p] is None:
                break
            bact[p - 16] = bact[p - 16] ^ clear_t[p] ^ (16 - i)

        print("pos %d" % pos)
        print("pad %d" % (16 - i))

        saved_v = bact[pos]
        for g in range(0, 256):
            bact[pos] = g ^ saved_v ^ (16 - i)
            forged_ct_hex = codecs.encode(bact, "hex_codec").decode('ascii')
            print(g)
            if po.query(forged_ct_hex):
                clear_t[pos + 16] = g
                break

        if clear_t[pos + 16] is None:
            clear_t[pos + 16] = 16 - i
        print(bytes(clear_t[pos + 16:]))

print(bytes(clear_t))

# po.query(sys.argv[1])  # Issue HTTP query with the given argument

