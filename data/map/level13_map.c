#include "../../src/game_screen.h"
# include <stdlib.h>
const unsigned char Lvl13TileMap[] = {6,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,1,1,1,1,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,1,1,1,1,
1,13,11,13,1,13,11,13,11,13,11,13,11,13,11,13,1,1,1,1,
1,14,12,14,1,14,12,14,12,14,12,14,12,14,12,14,1,1,1,1,
1,13,11,13,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2};
size_t boxes_lvl13_length = 5;
Box box_lvl13[5] = 
{
{32U,96U,8U,96U},
{32U,104U,96U,8U},
{128U,104U,32U,40U},
{72U,136U,8U,32U},
{0U,136U,8U,32U}
};
LOCK locks_lvl13[1] =
{
    {&(box_lvl13[3]), 1U}
};
const Box box_locks_lvl13_value[1] =
                {
                    {72, 136, 8, 32}
                };
WALL walls_lvl13[1] =
            {
                {&(box_lvl13[4]), 1U}
            };
const Box box_walls_lvl13_value[1] =
                            {
                                {0, 136, 8, 32}
                            };
Level lvl13 = {
box_lvl13,
boxes_lvl13_length,
Lvl13TileMap,
locks_lvl13,
walls_lvl13,
NULL,
NULL,
NULL,
};
