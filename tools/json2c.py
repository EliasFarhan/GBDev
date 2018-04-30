import json
import os
from os.path import basename
from os.path import splitext
from functools import reduce

gb_white_len = 1
gb_environment_len = 10
gb_background_len = 8
gb_posters_len = 48

gb_environment_index = 1
gb_background_index = gb_environment_index+gb_environment_len
gb_posters_index = gb_background_index+gb_background_len

gb_32x32 = [
    [0, 2, 8, 10],
    [1, 3, 9, 11],
    [4, 6, 12, 14],
    [5, 7, 13 , 15]
]

tiled_environment_index = 9
tiled_background_index = 1
tiled_posters_index = 28

gb_resolution = (160, 144)
tile_size = (8,8)
gb_tilesize = (int(gb_resolution[0]/tile_size[0]), int(gb_resolution[1]/tile_size[1]))


def tiled2gbtile(tiled_tile):

    #Environment
    if tiled_tile >= tiled_environment_index and tiled_tile < tiled_posters_index:
        return tiled_tile-tiled_environment_index+1

    #Background
    if tiled_tile >= tiled_background_index and tiled_tile < tiled_environment_index:
        delta_index = tiled_tile-tiled_background_index
        bg_delta_index = int(delta_index/4)*4
        t_index = delta_index-bg_delta_index
        #print("T_INDEX: "+str(t_index)+" "+str(bg_delta_index))
        if t_index == 1:
            t_index = 2
        elif t_index == 2:
            t_index = 1
        return t_index+bg_delta_index+gb_background_index

    #Posters
    if tiled_tile >= tiled_posters_index:
        delta_index = tiled_tile-tiled_posters_index
        posters_delta_index = int(delta_index/16)*16
        t_index = delta_index-posters_delta_index
        gb_index = gb_32x32[int(t_index/4)][t_index-int(t_index/4)*4]
        return gb_index+posters_delta_index+gb_posters_index
    return 0


def json2c(json_filename, offset):

    with open(json_filename, 'r') as json_file:
        json_content = json_file.read()
    json_obj = json.loads(json_content)
    size = (int(json_obj["width"]/gb_tilesize[0]), int(json_obj["height"]/gb_tilesize[1]))

    tiled_map = [
        [[0 for i in range(gb_tilesize[0])] for j in range(gb_tilesize[1])] for n in range(size[0]*size[1])
    ]
    boxes = [
        [] for n in range(size[0]*size[1])
    ]
    locks = [
        [] for n in range(size[0]*size[1])
    ]
    tile_per_row = gb_tilesize[0]*size[0]
    for layer in json_obj["layers"]:
        if layer.get("objects") is not None:
            for box_def in layer["objects"]:
                #Calculate lock index
                box_size = int(box_def["width"]), int(box_def["height"])
                box_topleft_pos = int(box_def["x"]), int(box_def["y"])

                tilemap_row = int(box_topleft_pos[0]/gb_resolution[0])
                tilemap_column = int(box_topleft_pos[1]/gb_resolution[1])

                tilemap_index = tilemap_row+size[0]*tilemap_column
                print("{0}, {1}".format(tilemap_row, tilemap_column))
                box_index = len(boxes[tilemap_index])
                #LOCK
                if box_def.get("properties") is not None:
                    for box_property in box_def.get("properties"):
                        if box_property.get("name") == "lock" and box_property.get("value"):
                            locks[tilemap_index].append([box_index])
                #BOX
                boxes[tilemap_index].append([box_topleft_pos[0]-tilemap_row*gb_resolution[0],
                                             box_topleft_pos[1]+box_size[1]-tilemap_column*gb_resolution[1],
                                             box_size[0],
                                             box_size[1]])
        elif layer.get("data") is not None:
            data = layer["data"]
            index = 0
            for d in data:
                row = int(index/tile_per_row)
                column = index-row*tile_per_row

                tiled_row = int(row/gb_tilesize[1])
                tiled_column = int(column/gb_tilesize[0])
                tiled_map_index = tiled_row*size[0] + tiled_column

                gb_value = tiled2gbtile(d)
                if gb_value != 0:
                    pass
                    tiled_map[tiled_map_index][row-tiled_row*gb_tilesize[1]][column - tiled_column*gb_tilesize[0]] = gb_value

                """print("{0} row: {1} col: {2} tiled_map_index: {3} tiled_value: {4} gb_value: {5}"
                      .format(str(index),
                              str(row - tiled_row * gb_tilesize[1]),
                              str(column - tiled_column*gb_tilesize[0]),
                              str(tiled_map_index),
                              str(d),
                              str(gb_value)))"""

                index += 1

    for i in range(size[0]*size[1]):
        print(boxes[i])
        with open(os.path.dirname(json_filename)+"/level"+str(offset+i+1)+"_map.c", "w") as c_file:
            c_file.write("""#include "../../src/game_screen.h"\n""")
            c_file.write("""# include <stdlib.h>\n""")
            c_file.write("const unsigned char Lvl"+str(offset+i+1)+"TileMap[] = {"+
                         ",\n".join(map((lambda l : ",".join(map(lambda item: str(item), l))), tiled_map[i]))+"};\n")
            c_file.write("size_t boxes_lvl"+str(offset+i+1)+"_length = "+str(len(boxes[i]))+";\n")
            if len(locks[i]) == 0:
                #c_file.write("const ")
                pass
            if len(boxes[i]) > 0:
                c_file.write("Box box_lvl"+str(offset+i+1)+"["+str(len(boxes[i]))+"] = \n")#+str(len(boxes[i]))
                c_file.write("{\n"+",\n".join(map((lambda l : "{"+",".join(map(lambda item: str(item)+"U", l))+"}"), boxes[i]))+"\n};\n")
            if len(locks[i]) == 1:
                c_file.write("LOCK locks_lvl"+str(i+1)+"["+str(len(locks[i]))+"""] =
{
    {&(box_lvl"""+str(i+1)+"""["""+str(locks[i][0][0])+"""]), 1U}
};\n""")
                c_file.write("const Box box_locks_lvl" + str(offset+i + 1) + "_value[" + str(len(locks[i])) + """] =
                {
                    {""" + ", ".join(map((lambda val : str(val)), boxes[i][locks[i][0][0]])) + """}
                };\n""")
            c_file.write("/*Level lvl"+str(offset+i+1)+" = {\n&box_lvl"+str(offset+i+1)+",\n boxes_lvl"+str(offset+i+1)+"_length,\n Lvl"+str(offset+i+1)+"TileMap, ")
            if len(locks[i]) == 1:
                c_file.write("locks_lvl"+str(offset+i+1)+" };*/\n")
            else:
                c_file.write("NULL};*/\n")


def main():
    json2c("../data/map/map1.json", 0)
    #json2c("../data/map/map2.json", 6)


if __name__ == "__main__":
    main()