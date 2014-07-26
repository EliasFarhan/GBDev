#include <gb/gb.h>
#include "title_screen.h"
#include "kwakwa_screen.h"
#include "utils/reset_graphics.c"

void main()
{
	kwakwa_screen();
	disable_APA();
	title_screen();

}
