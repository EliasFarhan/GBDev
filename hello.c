#include <gb/gb.h>
#include <stdio.h>

void main()
{
        printf("Welcome to GAMEBOY\nProgramming");
        printf("\nPress Start");
        waitpad(J_START);  // other keys are J_A, J_UP, J_SELECT, etc.
        printf("\nIsn't it easy!");
}
