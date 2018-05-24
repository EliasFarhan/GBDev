#include "../../src/game_screen.h"
# include <stdlib.h>
const unsigned char Lvl10TileMap[] = {6,13,11,13,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
6,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14};
size_t boxes_lvl10_length = 4;
Box box_lvl10[4] = 
{
{32U,144U,8U,40U},
{32U,104U,128U,8U},
{32U,72U,8U,72U},
{56U,48U,104U,8U}
};
/*Level lvl10 = {
&box_lvl10,
 boxes_lvl10_length,
 Lvl10TileMap, NULL};*/