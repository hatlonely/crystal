#!/usr/bin/env python3
#coding: utf-8

import sys
import struct

def main():
    serials_filename = '../build/serials_file' if len(sys.argv) < 2 else sys.argv[1]
    serials_file = open(serials_filename, 'rb')
    index = 0
    maxid = serials_file.read(8)
    while maxid:
        print('{0}\t{1}'.format(index, struct.unpack("l", maxid)[0]))
        index += 1
        maxid = serials_file.read(8)

if __name__ == '__main__':
    main()
