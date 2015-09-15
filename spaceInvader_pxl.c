#include "grlib.h"
#include "images.h"

static const unsigned char pixel_SPACEINVADER_11x8[] =
{
//Hex code for 8x8 Space Invader art.
0x00,
0x3c,
0x7e,
0xdb,
0xff,
0x24,
0x5a,
0xa5
};
	
static const unsigned long palette_SPACEINVADER_11X8[]=
{
	0xffffff, 0x000000
};

const tImage SPACEINVADER_11x8=
{
	IMAGE_FMT_1BPP_UNCOMP,
	8,
	8,
	2,
	palette_SPACEINVADER_11X8,
	pixel_SPACEINVADER_11x8,
};

