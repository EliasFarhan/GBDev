#include "../../src/game_screen.h"
# include <stdlib.h>
const unsigned char Lvl12TileMap[] = {6,6,6,6,6,6,6,6,6,6,6,6,6,13,11,13,11,13,11,3,
5,1,1,1,1,1,1,1,1,1,1,1,1,14,12,14,12,14,12,3,
5,13,11,13,11,13,11,13,11,3,11,13,11,13,11,13,11,13,11,3,
5,14,12,14,12,14,12,14,12,3,12,14,12,14,12,14,12,14,12,3,
5,13,11,15,17,13,11,13,11,3,11,13,11,15,17,13,11,13,11,3,
5,14,12,16,18,14,12,14,12,3,12,14,12,16,18,14,12,14,12,3,
5,13,11,13,11,13,11,13,11,3,11,13,11,13,11,13,11,13,11,3,
5,14,12,14,12,14,12,14,12,3,12,14,12,14,12,14,12,14,12,3,
5,13,11,13,11,13,11,13,11,3,11,13,11,13,11,13,11,13,11,3,
12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,3,
5,6,6,6,6,6,6,6,6,6,6,6,5,13,11,13,11,13,11,3,
5,14,12,14,12,1,12,14,12,14,5,1,5,14,12,14,12,14,12,3,
5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,3,
5,14,12,15,17,14,12,14,12,14,12,14,12,15,17,14,12,14,12,14,
5,13,11,16,18,13,11,13,11,13,11,13,11,16,18,13,11,13,11,13,
5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,1};
size_t boxes_lvl12_length = 5;
Box box_lvl12[5] = 
{
{0U,88U,104U,8U},
{72U,72U,8U,64U},
{72U,136U,8U,48U},
{80U,96U,24U,16U},
{152U,136U,8U,32U}
};
LOCK locks_lvl12[1] =
{
    {&(box_lvl12[2]), 1U}
};
const Box box_locks_lvl12_value[1] =
                {
                    {72, 136, 8, 48}
                };
WALL walls_lvl12[1] =
            {
                {&(box_lvl12[4]), 1U}
            };
const Box box_walls_lvl12_value[1] =
                            {
                                {152, 136, 8, 32}
                            };
Level lvl12 = {
box_lvl12,
boxes_lvl12_length,
Lvl12TileMap,
locks_lvl12,
walls_lvl12,
NULL,
NULL,
NULL,
};
