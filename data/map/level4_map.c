#include "../../src/game_screen.h"
# include <stdlib.h>
const unsigned char Lvl4TileMap[] = {5,13,15,17,11,13,11,13,11,13,11,13,11,13,11,13,6,15,17,6,
5,14,16,18,12,14,12,14,12,14,12,14,12,14,12,14,6,16,18,3,
5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,6,13,11,3,
5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,6,14,12,3,
5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,6,13,11,3,
5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,6,14,12,3,
11,13,11,13,11,13,11,35,37,43,45,13,11,13,11,13,6,13,11,3,
5,5,5,14,12,14,12,36,38,44,46,14,12,14,12,14,6,14,12,3,
5,5,5,13,11,13,11,39,41,47,49,13,11,13,11,13,6,13,11,3,
5,5,5,14,12,14,12,40,42,48,50,14,12,14,12,14,6,14,12,3,
5,5,5,13,11,13,11,13,11,13,11,13,11,13,11,13,6,13,11,3,
5,5,5,14,12,14,12,14,12,14,12,14,12,14,12,14,6,14,12,3,
5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,13,11,3,
12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,6,14,12,3,
11,15,17,13,11,13,11,13,11,13,11,13,11,13,11,13,6,15,17,3,
12,16,18,14,12,14,12,14,12,14,12,14,12,14,12,14,12,16,18,3,
11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,3,
6,6,6,6,6,6,6,6,6,6,6,6,6,14,12,14,12,14,12,3};
size_t boxes_lvl4_length = 3;
Box box_lvl4[3] = 
{
{0U,104U,24U,48U},
{0U,104U,136U,8U},
{128U,120U,8U,120U}
};
/*Level lvl4 = {
&box_lvl4,
 boxes_lvl4_length,
 Lvl4TileMap, NULL};*/