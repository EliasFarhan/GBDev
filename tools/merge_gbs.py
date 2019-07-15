import sys
import os.path
from enum import Enum


class ReadingState(Enum):
    BEFORE_TILEDATA = 0
    READ_TILEDATA = 1
    BEFORE_TILEMAP = 2
    READ_TILEMAP = 3
    FINISH = 4


text_before_tiledata = ""
text_before_tilemap = ""

tiledata = []
tilemap = []


def parse_db_line(line: str, data_array: list):
    data_line = line.replace(".db", "")
    data = list(map(lambda x: int(x, 16), data_line.split(",")))
    data_array.extend(data)



def read_input_gbs(inputfile: str):
    global text_before_tiledata, text_before_tilemap, tiledata, tilemap
    state = ReadingState.BEFORE_TILEDATA
    with open(inputfile) as f:
        lines = f.readlines()
        for i in range(len(lines)):
            if state is ReadingState.BEFORE_TILEDATA:
                if ".db" in lines[i]:
                    state = ReadingState.READ_TILEDATA
                else:
                    text_before_tiledata += lines[i]

            if state is ReadingState.READ_TILEDATA:
                if ".db" in lines[i]:
                    parse_db_line(lines[i], tiledata)
                else:
                    state = ReadingState.BEFORE_TILEMAP
            if state is ReadingState.BEFORE_TILEMAP:
                if ".db" in lines[i]:
                    state = ReadingState.READ_TILEMAP
                else:
                    text_before_tilemap += lines[i]

            if state is ReadingState.READ_TILEMAP:
                if ".db" in lines[i]:
                    parse_db_line(lines[i], tilemap)
                else:
                    state = ReadingState.FINISH

    for i in range(len(tilemap)):
        tilemap[i] = i

def merge_gbs():
    global tiledata, tilemap
    print("Origin tiledata count: " + str(len(tiledata) >> 4))
    i = 0
    while i < len(tiledata) >> 4:
        same_tile_indexes = []
        # list all similar tile
        for j in range(i + 1, len(tiledata) >> 4):
            same_tile = True
            for x in range(16):
                if tiledata[i * 16 + x] != tiledata[j * 16 + x]:
                    same_tile = False
                    break
            if same_tile:
                same_tile_indexes.append(j)

        # remove all similar tile and update tilemap
        for j in same_tile_indexes[::-1]:
            for x in range(16):
                tiledata.pop(j * 16)
            for map_index in range(len(tilemap)):
                if tilemap[map_index] == j:
                    tilemap[map_index] = i
                elif tilemap[map_index] > j:
                    tilemap[map_index] -= 1
        i += 1


def write_gbs(outputfile: str):
    print("Write result to: "+outputfile)
    print("Final tiledata count: "+str(len(tiledata) >> 4))
    with open(outputfile, 'w') as f:
        f.write(text_before_tiledata)
        for i in range(len(tiledata) >> 3):
            f.write(".db ")
            tile = tiledata[i*8:i*8+8]
            f.write(",".join(list(map(lambda x: "0x{:02x}".format(x).upper(), tile))))
            f.write("\n")

        f.write(text_before_tilemap)
        for i in range(len(tilemap) >> 3):
            f.write(".db ")
            tile = tilemap[i * 8:i * 8 + 8]
            f.write(",".join(list(map(lambda x: "0x{:02x}".format(x).upper(), tile))))
            f.write("\n")


def main():
    argv = sys.argv
    inputfile = ""
    outputfile = ""
    if len(argv) == 3:
        if os.path.isfile(argv[1]):
            inputfile = argv[1]
        else:
            sys.stderr.write("Error: First argument is not a file\n")
            return
        outputfile = argv[2]
    elif len(argv) == 2:
        if os.path.isfile(argv[1]):
            inputfile = argv[1]
        else:
            sys.stderr.write("Error: First argument is not a file\n")
            return
        outputfile = os.path.basename(inputfile).split(".")[0] + "_merge.s"
    else:
        sys.stderr.write("Error: No argument given\n")
        return

    read_input_gbs(inputfile)
    merge_gbs()
    write_gbs(outputfile)


if __name__ == '__main__':
    main()
