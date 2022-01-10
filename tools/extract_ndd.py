#!/usr/bin/env python3
#
#   64DD .ndd rom area extraction
#   Usage: extract_ndd.py <.ndd file> <output file>
#   Based on https://github.com/jkbenaim/leotools/blob/master/leogeo.c
#

import struct, sys

block_size_per_vzone = ( 19720, 18360, 17680, 16320, 14960, 13600, 12240, 10880, 9520 )

pzone_tbl1 = (
    ( 267, 559, 833, 1125, 1417, 1691, 1965, 2239, 2513, 2717, 2921, 3195, 3469, 3743, 4017, 4291 ),
    ( 267, 559, 833, 1107, 1381, 1673, 1965, 2239, 2513, 2787, 2991, 3195, 3469, 3743, 4017, 4291 ),
    ( 267, 559, 833, 1107, 1381, 1655, 1929, 2221, 2513, 2787, 3061, 3265, 3469, 3743, 4017, 4291 ),
    ( 267, 559, 833, 1107, 1381, 1655, 1929, 2203, 2477, 2769, 3061, 3335, 3539, 3743, 4017, 4291 ),
    ( 267, 559, 833, 1107, 1381, 1655, 1929, 2203, 2477, 2751, 3025, 3317, 3609, 3813, 4017, 4291 ),
    ( 267, 559, 833, 1107, 1381, 1655, 1929, 2133, 2407, 2681, 2955, 3229, 3503, 3795, 4087, 4291 ),
    ( 267, 559, 833, 1107, 1381, 1655, 1929, 2133, 2337, 2611, 2885, 3159, 3433, 3707, 3999, 4291 ),
)

pzone_tbl2 = (
    ( 0,  1,  2, 14, 15,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 ),
    ( 0,  1,  2,  3, 13, 14, 15,  4,  5,  6,  7,  8,  9, 10, 11, 12 ),
    ( 0,  1,  2,  3,  4, 12, 13, 14, 15,  5,  6,  7,  8,  9, 10, 11 ),
    ( 0,  1,  2,  3,  4,  5, 11, 12, 13, 14, 15,  6,  7,  8,  9, 10 ),
    ( 0,  1,  2,  3,  4,  5,  6, 10, 11, 12, 13, 14, 15,  7,  8,  9 ),
    ( 0,  1,  2,  3,  4,  5,  6,  7,  9, 10, 11, 12, 13, 14, 15,  8 ),
    ( 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 ),
)

vzone_tbl = ( 0, 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1 )

def lba_to_pzone(t, lba):
    pzone = 0

    for i in reversed(range(16)):
        if lba <= pzone_tbl1[t][i]:
            pzone = pzone_tbl2[t][i]
        else:
            break
    return pzone

def pzone_to_vzone(pzone):
    return vzone_tbl[pzone]

def size_of_lba(t, lba):
    return block_size_per_vzone[pzone_to_vzone(lba_to_pzone(t, lba))]

def size_of_sectors(t, lba):
    return size_of_lba(t, lba) / 85

def lba_to_offset(t, lba):
    return sum([size_of_lba(t, i) for i in range(lba)])

def read_16(b, offset):
    return struct.unpack(">H", b[offset:][:2])[0]

ndd_img = None
with open(sys.argv[1], "rb") as infile:
    ndd_img = bytearray(infile.read())

sys_area = ndd_img[:232]
disk_id = ndd_img[276080:][:232]

# System Area
disk_type = sys_area[5] & 0xF
retail = bool(sys_area[5] & 0x10)
ipl_load_size = read_16(sys_area, 6)
ipl_load_addr = read_16(sys_area, 0x1C)
rom_end_lba = read_16(sys_area, 0xE0)
ram_start_lba = read_16(sys_area, 0xE2)
ram_end_lba = read_16(sys_area, 0xE4)

# Disk Id
initial_code = disk_id[:4].decode("ASCII")
game_version = disk_id[4]
disk_number = disk_id[5]
ram_use = disk_id[6]
disk_use = disk_id[7]
company_code = disk_id[0x18:][:2].decode("ASCII")
free_area = disk_id[0x1A:][:6]

manufacture_datetime = f"{read_16(disk_id, 0x11):04x}-{disk_id[0x13]:02x}-{disk_id[0x14]:02x} {disk_id[0x15]:02x}-{disk_id[0x16]:02x}-{disk_id[0x17]:02x}"

rom_start_offset = (19720*24) + lba_to_offset(disk_type, 0)
rom_end_offset =   (19720*24) + lba_to_offset(disk_type, rom_end_lba + 1) - 1

print(rom_start_offset)
print(rom_end_offset)
print(rom_end_offset - rom_start_offset)

with open(sys.argv[2], "wb") as outfile:
    outfile.write(ndd_img[rom_start_offset:rom_end_offset+1])
