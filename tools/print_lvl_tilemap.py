

tile_size = (160/8,144/8)

tile_map = [[0 for i in range(tile_size[0])] for j in range(tile_size[1])]
for j in range(tile_size[1]):
    for i in range(tile_size[0]):
        if j == 0 or j == tile_size[1]-1:
            tile_map[j][i] = 6
            continue
        if i == 0 :
            tile_map[j][i] = 5
            continue
        if i == tile_size[0]-1:
            tile_map[j][i] = 3
            continue
        if i % 2 == 1 and j % 2 == 1:
            tile_map[j][i] = 11
        if i % 2 == 0 and j % 2 == 1:
            tile_map[j][i] = 13
        if i % 2 == 1 and j % 2 == 0:
            tile_map[j][i] = 12
        if i % 2 == 0 and j % 2 == 0:
            tile_map[j][i] = 14
        
string_map = ",\n".join([",".join(str(x) for x in tile_map[i]) for i in range(len(tile_map))])

print "{"+string_map+"}"
