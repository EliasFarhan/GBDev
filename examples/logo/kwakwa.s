;
;  GameBoy ToolKit v0.013a
;
;  Filename : kwakwa.asm
;  Source   : kwakwa.jpg
;
;  Number of Tiles   : 361
;  TileMap Size      : 21x19
;

.area _CODE_3

.globl _kwakwa_tiledata
.dw _kwakwa_tiledata

_kwakwa_tiledata:
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x02,0x01,0x08,0x07
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x6E,0x10,0x00,0xFF,0x00,0xFF
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0xC0,0x00,0x20,0xC0
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x10,0x0F,0x22,0x1C,0x04,0x38,0x48,0x30
.db 0x10,0x60,0x80,0x60,0x20,0xC0,0x20,0xC0
.db 0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x07,0x00,0x08,0x07,0x00,0x0F,0x00,0x0F
.db 0x10,0xE0,0x08,0x70,0x24,0x18,0x04,0x18
.db 0x02,0x0C,0x89,0x06,0x00,0x87,0x07,0x80
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0xFE,0x00,0x00,0xFE,0xF8,0x06
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x01,0x00,0x02,0x01
.db 0x04,0x03,0x00,0x07,0x09,0x06,0x02,0x0C
.db 0x00,0x00,0x80,0x00,0x10,0xE0,0x0C,0xF0
.db 0xC2,0x3C,0x11,0x0E,0x08,0x07,0x04,0x03
.db 0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x80,0x00,0x40,0x80
.db 0x20,0xC0,0x20,0xC0,0x20,0xC0,0x20,0xC0
.db 0x20,0xC0,0x80,0x60,0x90,0x60,0x00,0x70
.db 0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x01
.db 0x01,0x06,0x01,0x06,0x08,0x06,0x08,0x06
.db 0x02,0x0C,0x00,0x1C,0xC4,0x38,0x08,0xF0
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x12,0x0C,0x00,0x1C,0x24,0x18,0x24,0x18
.db 0x20,0x18,0x00,0x38,0x08,0x30,0x08,0x30
.db 0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x20,0xC0,0x00,0xFF,0x80,0x7F,0x5C,0x20
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x48,0x30,0x04,0xF8,0x00,0xFC,0x7C,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x20,0x1F,0x27,0x18,0x04,0x18,0x10,0x0C
.db 0x12,0x0C,0x02,0x0C,0x08,0x06,0x08,0x06
.db 0x20,0xC0,0x80,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x48,0x30,0x48,0x30,0x48,0x30,0x08,0x30
.db 0x08,0x30,0x00,0x38,0x20,0x18,0x24,0x18
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x08,0x06,0x01,0x06,0x01,0x06,0x01,0x06
.db 0x01,0x06,0x01,0x06,0x08,0x06,0x08,0x06
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x90,0x60,0x10,0xE0
.db 0x10,0xE0,0x10,0xE0,0x10,0xE0,0x10,0xE0
.db 0x00,0x00,0x00,0x00,0x03,0x00,0x04,0x03
.db 0x08,0x07,0x00,0x0F,0x10,0x0F,0x01,0x1E
.db 0x00,0x00,0x00,0x00,0x30,0x00,0xC8,0x30
.db 0x48,0xB0,0x48,0xB0,0xC8,0x30,0x08,0x30
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x28,0x10,0x40,0x38
.db 0x40,0x38,0x40,0x38,0x48,0x30,0x48,0x30
.db 0x00,0x00,0x00,0x00,0x00,0x7F,0x80,0x7F
.db 0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x30,0xC0,0x08,0xF0
.db 0x00,0xF8,0x44,0x38,0x24,0x18,0x20,0x1C
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x24,0x18,0x04,0x18,0x00,0x1C,0x12,0x0C
.db 0x00,0x0E,0x09,0x06,0x00,0x07,0x04,0x03
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x80,0x00,0x20,0xC0
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x02,0x0C,0x02,0x0C,0x12,0x0C,0x00,0x1C
.db 0x24,0x18,0x00,0x38,0x48,0x30,0x80,0x70
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x10,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0
.db 0x00,0xE0,0x00,0xE0,0x01,0xE0,0x00,0xE1
.db 0x20,0x1E,0x02,0x3C,0x40,0x3C,0x44,0x38
.db 0x08,0x70,0x00,0xF0,0x10,0xE0,0x20,0xC0
.db 0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38
.db 0x00,0x38,0x00,0x38,0x20,0x18,0x24,0x18
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x04,0x03,0x00,0x07,0x08,0x07,0x00,0x0F
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x80,0x00,0x00,0x80,0x40,0x80
.db 0x48,0x30,0x48,0x30,0x00,0x70,0x00,0x70
.db 0x00,0x70,0x00,0x70,0x00,0x70,0x10,0x60
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x1C,0x00,0x1C,0x02,0x1C,0x02,0x1C
.db 0x12,0x0C,0x12,0x0C,0x12,0x0C,0x12,0x0C
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00
.db 0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x01,0x00,0x03,0x00
.db 0x0C,0xF0,0x81,0x7E,0x30,0x0F,0x0E,0x01
.db 0x00,0x00,0x00,0x00,0x9C,0x00,0xDC,0x00
.db 0x00,0x00,0x80,0x00,0x1F,0xE0,0x00,0xFF
.db 0xE0,0x1F,0x03,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF
.db 0x00,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00
.db 0x06,0x01,0x30,0x0F,0x01,0xFE,0x0E,0xF0
.db 0xE0,0x00,0x00,0x00,0x1C,0x00,0x1C,0x00
.db 0x00,0xE0,0x20,0xC0,0x80,0x00,0x00,0x00
.db 0x00,0x00,0x07,0x00,0x3F,0x00,0x7F,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x80,0x00,0xF8,0x00,0xFC,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x02,0xE1,0x00,0xE3,0x04,0xE3,0x24,0xC3
.db 0x28,0xC7,0x20,0xCE,0x32,0xCC,0x00,0xFC
.db 0x20,0xC0,0x40,0x80,0x00,0x80,0x80,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x24,0x18,0x24,0x18,0x24,0x18,0x24,0x18
.db 0x24,0x18,0x24,0x18,0x24,0x18,0x04,0x18
.db 0x00,0x0F,0x12,0x0D,0x01,0x1C,0x05,0x18
.db 0x24,0x18,0x20,0x18,0x00,0x38,0x48,0x30
.db 0x40,0x80,0x00,0xC0,0x00,0xC0,0x20,0xC0
.db 0x20,0xC0,0x80,0x60,0x80,0x60,0x10,0x60
.db 0x10,0x60,0x90,0x60,0x80,0x60,0x80,0x60
.db 0x80,0x60,0x00,0xE0,0x00,0xE0,0x20,0xC0
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x12,0x0C,0x12,0x0C,0x02,0x0C,0x02,0x0C
.db 0x02,0x0C,0x02,0x0C,0x02,0x0C,0x02,0x0C
.db 0x78,0x00,0x78,0x00,0x78,0x00,0x78,0x00
.db 0x78,0x00,0x78,0x00,0x78,0x00,0x70,0x00
.db 0x03,0x00,0x07,0x00,0x07,0x00,0x0F,0x00
.db 0x0F,0x00,0x1E,0x00,0x1E,0x00,0x3C,0x00
.db 0xFC,0x00,0xDC,0x00,0x9C,0x00,0x9C,0x00
.db 0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x1C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00
.db 0x3C,0x00,0x3C,0x00,0x3C,0x00,0x38,0x00
.db 0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0xFC,0x00,0x1E,0x00,0x0E,0x00,0x0E,0x00
.db 0x0E,0x00,0x0E,0x00,0x0E,0x00,0x07,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x04,0xF8,0x00,0xF8,0x00,0xF8,0x04,0xF8
.db 0x02,0xFC,0x11,0xEE,0x28,0xC7,0x24,0xC3
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x80,0x00,0x40,0x80
.db 0x04,0x18,0x00,0x1C,0x00,0x1C,0x00,0x1C
.db 0x00,0x1C,0x00,0x1C,0x01,0x1C,0x11,0x0C
.db 0x40,0x30,0x00,0x70,0x10,0x60,0x80,0x60
.db 0x80,0x60,0x20,0xC0,0x20,0xC0,0x00,0xC0
.db 0x00,0x70,0x40,0x30,0x48,0x30,0x09,0x30
.db 0x01,0x38,0x25,0x18,0x25,0x18,0x00,0x1D
.db 0x20,0xC0,0x20,0xC0,0x20,0xC0,0x22,0xC1
.db 0x20,0xC3,0x04,0xC3,0x04,0xC3,0x04,0xC3
.db 0x00,0x00,0x1F,0x00,0x80,0x7F,0x00,0xFF
.db 0x1F,0xE0,0x40,0x80,0x00,0x80,0x00,0x80
.db 0x12,0x0C,0x12,0x0C,0x02,0xFC,0x02,0xFC
.db 0x82,0x7C,0x12,0x0C,0x02,0x0C,0x02,0x0C
.db 0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00
.db 0x70,0x00,0x71,0x00,0x71,0x00,0x73,0x00
.db 0x3C,0x00,0x78,0x00,0x70,0x00,0xF0,0x00
.db 0xE0,0x00,0xE0,0x00,0xC0,0x00,0xC0,0x00
.db 0x1C,0x00,0x1C,0x00,0x1C,0x00,0x0C,0x00
.db 0x0C,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00
.db 0x03,0x00,0x03,0x00,0x03,0x00,0x07,0x00
.db 0x07,0x00,0x06,0x00,0x0E,0x00,0x0E,0x00
.db 0xC0,0x00,0xC0,0x00,0xC0,0x00,0xE0,0x00
.db 0xE0,0x00,0xE0,0x00,0x60,0x00,0x70,0x00
.db 0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00
.db 0x38,0x00,0x38,0x00,0x38,0x00,0x30,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00
.db 0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x22,0xC1,0x21,0xC0,0x20,0xC0,0x20,0xC0
.db 0x20,0xC0,0x20,0xC0,0xA0,0x40,0x40,0x00
.db 0x00,0xE0,0x00,0xF0,0x84,0x78,0x42,0x3C
.db 0x21,0x1E,0x11,0x0E,0x08,0x06,0x00,0x00
.db 0x12,0x0D,0x12,0x0D,0x10,0x0F,0x10,0x0F
.db 0x00,0x0F,0x00,0x0F,0x09,0x06,0x00,0x00
.db 0x00,0xC0,0x40,0x80,0x40,0x80,0x00,0x80
.db 0x80,0x00,0x80,0x00,0x00,0x00,0x00,0x00
.db 0x10,0x0D,0x12,0x0D,0x00,0x0F,0x00,0x0F
.db 0x08,0x07,0x00,0x07,0x07,0x00,0x00,0x00
.db 0x04,0xC3,0x44,0x83,0x44,0x83,0x40,0x83
.db 0x42,0x81,0x01,0x80,0x80,0x00,0x00,0x00
.db 0x00,0x80,0x40,0x80,0x21,0xC0,0x08,0xF7
.db 0x00,0xFF,0x00,0xFF,0x7C,0x00,0x00,0x00
.db 0x02,0x0C,0x22,0x1C,0x82,0x7C,0x02,0xFC
.db 0x22,0xDC,0x92,0x0C,0x12,0x0C,0x00,0x00
.db 0x73,0x00,0x77,0x00,0x77,0x00,0x7E,0x00
.db 0x7E,0x00,0x7C,0x00,0x7C,0x00,0x7E,0x00
.db 0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00
.db 0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00
.db 0x0C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00
.db 0x38,0x00,0x38,0x00,0x38,0x00,0x30,0x00
.db 0x70,0x00,0x30,0x00,0x38,0x00,0x38,0x00
.db 0x38,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00
.db 0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00
.db 0x70,0x00,0x70,0x00,0x70,0x00,0x60,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x1F,0x00,0x7F,0x00,0xFF,0x00
.db 0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00
.db 0x07,0x00,0xE7,0x00,0xFF,0x00,0xFF,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x7F,0x00,0x77,0x00,0x73,0x00,0x71,0x00
.db 0x70,0x00,0x70,0x00,0x70,0x00,0x70,0x00
.db 0x00,0x00,0x80,0x00,0xE0,0x00,0xF0,0x00
.db 0xF8,0x00,0x7C,0x00,0x3E,0x00,0x1F,0x00
.db 0x0E,0x00,0x0E,0x00,0x06,0x00,0x06,0x00
.db 0x06,0x00,0x07,0x00,0x07,0x00,0x07,0x00
.db 0x70,0x00,0x70,0x00,0x60,0x00,0xE0,0x00
.db 0xE0,0x00,0xE0,0x00,0xC0,0x00,0xC0,0x00
.db 0x1C,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00
.db 0x06,0x00,0x07,0x00,0x07,0x00,0x07,0x00
.db 0x61,0x00,0x61,0x00,0xE3,0x00,0xE3,0x00
.db 0xE3,0x00,0xE3,0x00,0xE1,0x00,0xE1,0x00
.db 0xE0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00
.db 0xC0,0x00,0xE0,0x00,0xF0,0x00,0xFF,0x00
.db 0x1F,0x00,0x07,0x00,0x07,0x00,0x07,0x00
.db 0x07,0x00,0x1F,0x00,0xFF,0x00,0xFF,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x70,0x00,0x70,0x00,0x30,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x0F,0x00,0x07,0x00,0x03,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x87,0x00,0x87,0x00,0x01,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0xC0,0x00,0x80,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x03,0x00,0x03,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0xC0,0x00,0xC0,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0xFF,0x00,0x7F,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0xE7,0x00,0x07,0x00,0x06,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
.db 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00


.globl _kwakwa_tilemap

.dw _kwakwa_tilemap

_kwakwa_tilemap:
.db 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07
.db 0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
.db 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17
.db 0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
.db 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27
.db 0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F
.db 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37
.db 0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F
.db 0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47
.db 0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F
.db 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57
.db 0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F
.db 0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67
.db 0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F
.db 0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77
.db 0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F
.db 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87
.db 0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F
.db 0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97
.db 0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F
.db 0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7
.db 0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF
.db 0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7
.db 0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF
.db 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7
.db 0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF
.db 0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7
.db 0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF
.db 0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7
.db 0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
.db 0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7
.db 0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
.db 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07
.db 0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
.db 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17
.db 0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F
.db 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27
.db 0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F
.db 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37
.db 0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F
.db 0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47
.db 0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F
.db 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57
.db 0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F
.db 0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67

