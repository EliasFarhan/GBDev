#include "../../src/game_screen.h"
# include <stdlib.h>
const unsigned char Lvl1TileMap[] = {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,3,
5,13,15,17,11,13,11,13,11,13,11,13,11,13,11,13,15,17,11,13,
5,14,16,18,12,14,12,14,12,14,12,14,12,14,12,14,16,18,12,14,
5,13,11,13,5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
5,14,12,14,5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
5,13,11,13,5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
5,14,12,14,5,14,12,14,12,14,12,14,3,14,12,14,12,14,12,14,
5,13,11,13,5,13,11,13,11,13,11,13,3,13,11,13,11,13,11,13,
5,14,12,14,5,14,12,14,12,14,12,14,3,14,12,14,12,14,12,14,
5,13,11,13,5,13,11,13,11,13,11,13,3,13,11,13,11,13,11,13,
5,14,12,14,5,14,12,14,12,14,12,14,1,6,6,6,6,6,6,3,
5,13,11,13,5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
5,14,15,17,5,14,12,14,12,14,12,14,12,14,12,14,15,17,12,14,
5,13,16,18,5,13,11,13,11,13,11,13,11,13,11,13,16,18,11,13,
5,14,12,14,5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,
5,13,11,13,1,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,14,12,14,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
size_t boxes_lvl1_length = 5;
Box box_lvl1[5] = 
{
{96U,96U,8U,40U},
{32U,136U,128U,8U},
{104U,96U,56U,8U},
{32U,128U,8U,96U},
{112U,128U,8U,32U}
};
LOCK locks_lvl1[1] =
{
    {&(box_lvl1[4]), 1U}
};
const Box box_locks_lvl1_value[1] =
                {
                    {112, 128, 8, 32}
                };
Level lvl1 = {
box_lvl1,
boxes_lvl1_length,
Lvl1TileMap,
locks_lvl1,
NULL,
NULL,
NULL,
NULL,
};
