#include <gb/gb.h>
void sonido_muerte()
{
NR52_REG = 0x80;	//ON
NR51_REG = 0x11;	//L/R
NR50_REG = 0x77;	//vol

NR10_REG = 0x1E;	//ENT1
NR11_REG = 0x10;	//LEN1
NR12_REG = 0xF3;	//ENV1
NR13_REG = 0x00;	//FRQ1
NR14_REG = 0x87;	//KIK1
}

void sonido_crujido()
{
NR52_REG = 0x80;	//ON
NR51_REG = 0x88;	//L/R
NR50_REG = 0x77;	//vol

NR41_REG = 0x00;	//LEN4
NR42_REG = 0xA3;	//ENV4
NR43_REG = 0x4D;	//FRQ4
NR44_REG = 0x83;	//KIK4
}

void sonido_ruido()
{
NR52_REG = 0x80;	//ON
NR51_REG = 0x88;	//L/R
NR50_REG = 0x77;	//vol

NR41_REG = 0x00;	//LEN4
NR42_REG = 0xf4;	//ENV4
NR43_REG = 0x5D;	//FRQ4
NR44_REG = 0x83;	//KIK4
}

void sonido_salto()
{
NR52_REG = 0x80;	//ON
NR51_REG = 0x11;	//L/R
NR50_REG = 0x77;	//vol

NR10_REG = 0x15;	//ENT1
NR11_REG = 0xF0;	//LEN1
NR12_REG = 0xA1;	//ENV1
NR13_REG = 0xFF;	//FRQ1
NR14_REG = 0x83;	//KIK1
}
