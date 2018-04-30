#include "../../src/game_screen.h"
# include <stdlib.h>
const unsigned char Lvl5TileMap[] = {6,13,11,13,6,13,11,6,6,6,6,6,6,6,6,6,6,6,6,6,
5,14,12,14,3,14,12,14,12,14,12,14,12,14,12,14,12,14,12,3,
5,13,11,13,3,13,11,13,11,13,11,13,11,13,11,13,11,13,11,3,
5,14,12,14,3,14,12,14,12,14,12,14,12,14,12,14,12,14,12,3,
5,15,17,13,3,13,11,13,11,13,11,13,11,13,11,15,17,13,11,3,
5,16,18,14,3,14,12,14,12,14,12,14,12,14,12,16,18,14,12,3,
5,13,11,13,3,13,11,19,21,27,29,13,11,13,11,13,11,13,11,3,
5,14,12,14,3,14,12,20,22,28,30,14,12,14,12,14,12,14,12,3,
5,13,11,13,11,13,11,23,25,31,33,13,11,13,11,13,11,13,11,3,
5,14,12,14,12,14,12,24,26,32,34,14,12,14,12,14,12,14,12,14,
5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,2,6,6,6,3,
5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,6,1,1,1,3,
5,13,11,13,6,6,6,6,6,6,6,6,6,6,6,6,5,5,5,3,
5,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,14,12,3,
5,15,17,13,11,13,11,13,11,13,11,13,11,13,11,15,17,13,11,3,
5,16,18,14,12,14,12,14,12,14,12,14,12,14,12,16,18,14,12,3,
5,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,11,13,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6};
size_t boxes_lvl5_length = 4;
Box box_lvl5[4] = 
{
{32U,96U,8U,32U},
{32U,64U,8U,64U},
{32U,104U,120U,8U},
{120U,104U,32U,24U}
};
LOCK locks_lvl5[1] =
{
    {&(box_lvl5[0]), 1U}
};
const Box box_locks_lvl5_value[1] =
                {
                    {32, 96, 8, 32}
                };
/*Level lvl5 = {
&box_lvl5,
 boxes_lvl5_length,
 Lvl5TileMap, locks_lvl5 };*/
