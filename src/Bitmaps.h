#include <Bitmap.h>
//const int32 kLargeIconWidth = 32;
//const int32 kLargeIconHeight = 32;
//const color_space kLargeIconColorSpace = B_COLOR_8_BIT;

const unsigned char kLargeIconBits [] = {
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,
	0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x2a,0x07,
	0x07,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x12,0x12,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x3f,0x3f,0x3f,0x12,0x07,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x12,0x12,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x2a,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x12,0x12,0x07,0x07,0x00,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x12,0x12,0x07,
	0x07,0x07,0x07,0x07,0x07,0x3f,0x3f,0x3f,0x12,0x07,0x07,0x07,0x00,0x00,0xff,0xff,
	0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x3f,0x3f,0x3f,0x12,
	0x07,0x07,0x07,0x07,0x07,0x07,0x12,0x12,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0xff,
	0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x12,0x12,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0xff,0xff,
	0xff,0x00,0x07,0x07,0x07,0x07,0x2a,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x12,0x12,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0xae,0xae,0xae,
	0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x12,0x12,0x07,0x07,0x07,0x07,0x07,
	0x07,0x3f,0x3f,0x3f,0x12,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0xae,0xae,0xff,
	0xff,0xae,0x00,0x00,0x07,0x07,0x07,0x07,0x3f,0x3f,0x3f,0x12,0x07,0x07,0x07,0x07,
	0x07,0x07,0x12,0x12,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x07,0x07,0x00,0xae,0xff,
	0xff,0xff,0xae,0x00,0x00,0x00,0x07,0x07,0x07,0x12,0x12,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x07,0x07,0x07,0x01,0x00,0xae,
	0xff,0xff,0xff,0xae,0x00,0x07,0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x12,0x12,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x07,0x07,0x00,0x00,0xae,0xae,0xae,
	0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x00,0x00,0x07,0x07,0x07,0x3f,0x3f,0x3f,
	0x12,0x07,0x07,0x07,0x07,0x07,0x07,0x29,0x07,0x00,0x00,0xae,0xae,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x07,0x00,0x00,0x07,0x07,0x12,0x12,
	0x07,0x07,0x07,0x07,0x07,0x07,0x01,0x00,0x00,0xae,0xae,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x07,0x07,0x00,0x00,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x01,0x00,0xae,0xae,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x07,0x07,0x07,0x00,0x00,
	0x07,0x07,0x07,0x07,0x00,0xae,0xae,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x07,0x07,0x07,0x07,
	0x00,0x00,0x07,0x00,0xae,0xae,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x07,0x07,0x00,
	0x00,0xae,0x00,0xae,0xae,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xae,0x00,0x07,0x00,0x00,0xae,
	0xae,0xae,0xae,0xae,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xae,0x00,0xae,0xae,0xff,
	0xff,0xff,0xae,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xae,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

//const int32 kSmallIconWidth = 16;
//const int32 kSmallIconHeight = 16;
//const color_space kSmallIconColorSpace = B_COLOR_8_BIT;

const unsigned char kSmallIconBits [] = {
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0x00,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0x07,0x07,0x2a,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x12,0x07,0x00,0x00,0xff,0xff,0xff,
	0xff,0xff,0x00,0x07,0x07,0x2a,0x07,0x07,0x12,0x0e,0x0e,0x07,0x07,0x00,0x00,0xff,
	0xff,0x00,0x07,0x07,0x07,0x07,0x07,0x12,0x07,0x07,0x12,0x07,0x07,0x07,0x00,0x00,
	0x00,0x07,0x07,0x2a,0x07,0x07,0x07,0x12,0x12,0x12,0x07,0x07,0x07,0x00,0x00,0xae,
	0xae,0x00,0x00,0x07,0x07,0x12,0x12,0x07,0x12,0x07,0x07,0x07,0x01,0x07,0x00,0x00,
	0xff,0xae,0x00,0x00,0x00,0x07,0x12,0x12,0x07,0x07,0x07,0x00,0x07,0x00,0xae,0xae,
	0xff,0xff,0xae,0x00,0x07,0x00,0x00,0x07,0x07,0x07,0x00,0x00,0x00,0xae,0xff,0xff,
	0xff,0xff,0xff,0xae,0x00,0x07,0x07,0x00,0x07,0x00,0xae,0xae,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xae,0x00,0x00,0x00,0x00,0xae,0xae,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xae,0x00,0xae,0xff,0xae,0xff,0xff,0xff,0xff,0xff,0xff
};

