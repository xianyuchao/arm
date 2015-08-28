//取码规则:	低位在前, 逐列式扫描, 阴码(1-亮, 0-灭)
const unsigned char  img1[] = {	//640*40
0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0x3A,0x00,0x00,0xD0,0xFF,0x1F,0x00,0x00,
0xFC,0xAA,0x7A,0x0A,0x00,0x1E,0xFE,0xEF,0x0F,0x80,0x07,0x5F,0xBF,0x06,0xB8,0x85,
0x03,0xF0,0x0F,0x48,0xC4,0x11,0xC0,0x1D,0x10,0xA4,0x13,0x00,0x3F,0x30,0xE8,0xB1,
0x03,0x3C,0x38,0xF0,0x33,0x07,0x18,0x3C,0xFE,0xB2,0x07,0x30,0x34,0x75,0xE2,0x07,
0x20,0x9E,0x7A,0xE2,0x01,0x40,0xDE,0x7E,0x44,0x00,0x83,0x4E,0x3F,0x00,0x00,0x85,
0x8E,0x3E,0x00,0x00,0x87,0x8F,0x1F,0x00,0x00,0x85,0xCF,0x1F,0x00,0x00,0x82,0xAF,
0x07,0x00,0x00,0x81,0xFF,0x07,0x00,0x00,0xC0,0xEF,0x07,0x00,0x00,0xC0,0xFF,0x07,
0x00,0x00,0xE0,0xDF,0x0F,0x48,0x00,0xE0,0x7E,0x0F,0xC8,0x0F,0xF0,0xFE,0x3F,0xC8,
0x1C,0xF8,0xFE,0xFD,0xC8,0x1C,0xFC,0x7C,0xF7,0xCA,0x1F,0xFE,0xFC,0xEF,0x9B,0x1F,
0xFE,0xF8,0xBE,0xBF,0xA1,0xFF,0xF8,0xFB,0x7E,0xCA,0xFF,0xF0,0x6F,0xFF,0xEB,0xFF,
0xF0,0xFF,0xFC,0xFF,0xFF,0xE0,0x7F,0xFE,0xFF,0xFF,0xC0,0x7F,0xF4,0xFF,0xFF,0x80,
0x7F,0x80,0xFF,0xFF,0x00,0x7F,0xE0,0xFF,0xFF,0x00,0x5E,0xC0,0xFF,0x7F,0x00,0x18,
0xE0,0xFF,0x1F,0x00,0x10,0xF0,0xFF,0x03,0x00,0x00,0xC0,0x03,0xFC,0x00,0x00,0x30,
0x04,0xF6,0x00,0x01,0x18,0x0C,0xFA,0x8C,0x00,0x04,0x08,0xF2,0xCC,0xE1,0x07,0x10,
0xF2,0x7C,0x5D,0x8C,0x11,0xCA,0x74,0x07,0xC8,0x20,0xFE,0x0C,0x01,0xD8,0xA0,0xF1,
0x08,0x00,0xD0,0xE0,0x80,0x08,0x00,0x30,0x23,0x00,0x18,0x00,0x20,0x43,0x00,0x10,
0x08,0x60,0x2E,0x00,0x10,0x86,0x7F,0x6C,0x00,0x18,0xE6,0x78,0x38,0x00,0x08,0xA2,
0x78,0x30,0xFE,0x10,0x93,0x7F,0xB0,0xE1,0x18,0x11,0x7E,0xC0,0xC0,0x08,0x30,0x60,
0xC0,0x80,0x04,0x60,0x20,0x80,0x00,0x04,0x80,0x23,0x00,0x01,0x06,0x00,0x1C,0x00,
0x01,0x02,0x00,0x10,0x00,0x02,0x02,0x00,0x30,0x00,0x02,0x61,0x06,0x3E,0x00,0x02,
0x79,0x8C,0x7F,0x00,0x02,0xDD,0x58,0x7E,0x00,0x02,0xD7,0x43,0x00,0x04,0x00,0x73,
0xFC,0xC0,0x06,0x01,0x10,0x40,0xFF,0x03,0x01,0x00,0x00,0x80,0x81,0x00,0x00,0x00,
0x80,0x40,0x00,0x00,0x00,0x40,0x60,0x00,0x00,0x00,0x60,0x50,0x00,0x00,0x00,0x30,
0x58,0x00,0x00,0x00,0x10,0x6C,0x00,0x00,0x00,0x10,0x26,0x00,0x00,0x00,0x18,0x20,
0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x30,0x0E,0x00,0x00,0x00,0xC0,0x03,0x00,
0x0C,0x50,0x02,0x00,0x00,0x06,0x00,0x03,0x00,0x00,0x03,0xAA,0x03,0x00,0x00,0x81,
0x80,0x03,0x3D,0x00,0x20,0xEA,0xE1,0x28,0x00,0x8A,0xF8,0xC8,0x40,0x00,0xA0,0x7F,
0xB0,0x41,0x00,0xCA,0x1F,0x30,0xF3,0x00,0xC0,0x00,0xC8,0x9E,0x00,0xD0,0x01,0xC4,
0x0D,0x81,0x81,0x03,0x06,0x17,0x41,0x07,0x2F,0x51,0x23,0x62,0x0C,0xFD,0x81,0x05,
0x32,0x30,0xF4,0xA8,0x00,0x1C,0xE0,0x60,0xFC,0x01,0x34,0x00,0x3F,0x06,0x19,0x6C,
0x00,0x18,0x03,0x31,0xCC,0x00,0x08,0x32,0x71,0x88,0x00,0x08,0x7B,0xA1,0x31,0x00,
0x48,0x4A,0x11,0x71,0x00,0x88,0xFE,0x21,0xC1,0x00,0x2E,0x80,0xB3,0xC1,0x00,0x99,
0xAA,0xE5,0xC1,0x80,0x38,0xFE,0x1C,0xC1,0x60,0x98,0x82,0x24,0x71,0x10,0x32,0x83,
0x93,0x39,0x0C,0xFE,0xF1,0xE0,0x7C,0x06,0xAF,0xDB,0x30,0xFC,0xA1,0x07,0xDB,0x00,
0x34,0x80,0x07,0xFE,0x00,0xE4,0xC8,0x0F,0xBC,0x00,0xC6,0x90,0x1F,0xF8,0x01,0x02,
0xC0,0x3F,0x70,0x03,0x01,0x28,0x3F,0xE0,0x8E,0x01,0x84,0x72,0xC0,0xFB,0x00,0x53,
0xF5,0x80,0x3F,0x00,0x06,0xE0,0x01,0x1F,0x00,0xAC,0xEA,0x01,0x04,0x00,0xF8,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,
0x0C,0x00,0x00,0x00,0x80,0x1C,0x00,0x00,0x00,0x80,0x7C,0x00,0x00,0x00,0xFC,0xDF,
0x00,0x00,0x00,0x83,0x1F,0x03,0x00,0x80,0x80,0x1F,0x06,0x00,0x40,0x68,0x07,0x04,
0x00,0xE0,0xF7,0x01,0x0C,0xF0,0xBF,0xEF,0x00,0x18,0xFC,0x1F,0xFF,0x00,0x1C,0xFC,
0x0F,0x85,0x00,0x38,0xF8,0x47,0xDA,0x00,0x2C,0xF8,0xA7,0xA0,0x00,0x2C,0xF8,0x13,
0xFF,0x00,0x4C,0xF0,0xE3,0xC1,0x00,0x44,0xE0,0x31,0x80,0x00,0x46,0xE0,0x19,0x80,
0x00,0x46,0xC0,0x09,0x88,0x00,0xC6,0x80,0x19,0xFE,0x00,0x82,0x00,0x8D,0xFF,0x00,
0xC3,0x80,0x91,0xD7,0x80,0xC1,0x00,0xFD,0xEF,0x80,0xC0,0x80,0xF1,0xFF,0x00,0x40,
0x00,0xCD,0xFF,0x00,0xC0,0x00,0x73,0xFF,0x00,0x40,0x80,0x89,0xD5,0x01,0xE0,0xC0,
0x71,0x2A,0x01,0x60,0xE0,0x8C,0xD5,0x01,0xF0,0x78,0x72,0x2A,0x03,0x30,0x38,0x8D,
0xD5,0x03,0xD8,0x9E,0x7E,0x2A,0x06,0xAC,0x9E,0xBF,0xD5,0x0D,0xFE,0xEF,0x7F,0x2A,
0xFA,0xFF,0xAF,0xFE,0xF5,0xFF,0xFF,0xFF,0xAF,0xEA,0xFF,0x17,0xFF,0xFF,0xFF,0x3F,
0x00,0xFE,0xFF,0xFF,0x07,0x00,0xF8,0xFF,0x3F,0x00,0x00,0x00,0x95,0x00,0x00,0x00,
0x00,0x3E,0x00,0x00,0x00,0xE0,0x77,0x00,0x00,0x00,0x70,0xC0,0x00,0x00,0x00,0x58,
0x60,0x00,0x08,0x00,0x1C,0x30,0x00,0x0A,0x04,0x86,0x18,0xE0,0x3D,0x02,0x12,0x08,
0x30,0xC8,0x03,0x82,0x04,0x48,0x88,0x81,0x01,0xFC,0x47,0x88,0x83,0x03,0x00,0xC0,
0x88,0x42,0x01,0x00,0x80,0xC8,0x46,0x02,0xD0,0x00,0x49,0x60,0x02,0x04,0x01,0x61,
0x26,0x02,0x02,0x02,0x00,0x24,0x00,0x1D,0x04,0x00,0x16,0x06,0x3E,0x00,0x00,0x12,
0x02,0x37,0x3C,0x00,0x16,0x0E,0x32,0x7C,0x80,0x0F,0x36,0x32,0xE6,0xC0,0x0F,0x4A,
0xD8,0xC2,0xF0,0x1D,0x36,0x0C,0xE3,0xC0,0x0D,0x0E,0x02,0xE6,0x80,0x1F,0x02,0x08,
0x7C,0x00,0x0F,0x04,0x3E,0x34,0x00,0x3F,0x04,0x3F,0x04,0x00,0x14,0x02,0x32,0x04,
0x00,0x34,0x02,0x32,0x02,0x21,0x26,0x00,0x0C,0x01,0x49,0x20,0x03,0xF0,0x80,0xC9,
0x66,0x01,0x00,0x80,0xC8,0x42,0x01,0x0A,0x40,0x88,0x43,0x93,0xFC,0x7F,0x88,0xC1,
0x03,0x04,0x60,0xE8,0x81,0x0A,0x08,0xE0,0x3F,0x02,0x56,0x10,0x00,0x0A,0x04,0x2C,
0x30,0x00,0x08,0x00,0x1C,0x60,0x00,0x00,0x00,0xB0,0x40,0x00,0x00,0x00,0xE0,0x6B,
0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0xF0,0xFF,0xFF,
0x03,0x00,0x70,0x00,0x40,0x0E,0x00,0x08,0x00,0x40,0x3C,0x00,0x18,0x00,0x40,0x24,
0xC0,0x88,0x2F,0x40,0xC4,0x62,0x88,0x1F,0x40,0x80,0x31,0x08,0x0F,0x00,0xC0,0x11,
0x18,0x07,0x00,0x40,0x1B,0x10,0x07,0x00,0x00,0x0A,0x30,0x00,0x00,0x00,0x8E,0x20,
0x08,0x7C,0x00,0x44,0x40,0x08,0xC3,0x00,0xFC,0x40,0x04,0x01,0x01,0x5C,0x60,0x04,
0x79,0x01,0xFC,0x60,0x04,0xF9,0x15,0x5C,0x20,0x08,0xF3,0x00,0xFC,0x20,0x00,0x7C,
0x01,0x48,0x20,0x00,0x80,0x83,0xE8,0x20,0x00,0x00,0x06,0x48,0x20,0x00,0x40,0x06,
0xE8,0x20,0x00,0x40,0x4E,0x48,0x20,0x00,0x40,0x26,0xE8,0x60,0x00,0x40,0x86,0x48,
0x20,0x04,0xBE,0x03,0xEC,0x60,0x04,0x41,0x01,0x5C,0x20,0x84,0x91,0x40,0xFC,0x10,
0x84,0xFC,0x00,0x54,0x98,0x09,0x7D,0x00,0xFE,0x88,0x01,0x7B,0x00,0x06,0xCC,0x03,
0x1C,0x00,0x0E,0xE4,0x07,0x00,0x20,0x1B,0xE4,0x07,0x00,0x20,0x31,0x04,0x0F,0x00,
0xC0,0x61,0x0C,0x00,0x00,0xC0,0xC0,0xF8,0x02,0x00,0xE4,0x00,0xC0,0x3F,0x40,0x3C,
0x01,0x00,0xE0,0x40,0x0E,0x00,0x00,0x80,0xFF,0x07,0x00,0x00,0x00,0x40,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,
0x68,0x00,0x00,0x80,0x00,0xF6,0xF3,0x00,0xC0,0x80,0x81,0x0E,0x03,0xC0,0xC0,0xE2,
0xFB,0x04,0xE0,0x60,0x11,0x74,0x0F,0xE0,0xB0,0xE2,0x1F,0x38,0x60,0xF0,0xFF,0x1B,
0xC0,0xE0,0xDC,0x85,0x24,0x80,0xF3,0xA4,0x80,0x25,0x00,0x7E,0xC6,0x81,0x09,0x00,
0x9C,0x82,0x81,0x7E,0x00,0x30,0xC2,0x81,0x3D,0x00,0x70,0x23,0x03,0x3C,0x80,0xE0,
0xCB,0x03,0x18,0x00,0xC1,0xA3,0x02,0x00,0x10,0xC1,0xD3,0x04,0x80,0x37,0xC1,0x2B,
0x05,0x60,0x15,0x83,0xD3,0x0D,0x00,0x20,0x85,0x2F,0x08,0x00,0x10,0xA1,0x32,0x1C,
0x18,0x00,0xC1,0x2E,0x9F,0x24,0x00,0xC1,0x06,0xBF,0x20,0x80,0x61,0x00,0xFF,0x5E,
0x00,0x70,0x24,0xCF,0x3C,0x00,0x38,0xEC,0x9F,0x7C,0x00,0x9E,0xF8,0xDF,0x3C,0x80,
0x5F,0xF0,0xBF,0x18,0xE0,0xB1,0xF0,0xFF,0x00,0x7E,0xF0,0xC0,0xFF,0xEB,0x0F,0xE0,
0x80,0xFF,0xFF,0x04,0xE0,0x00,0xFE,0x13,0x03,0xC0,0x00,0x50,0xE0,0x00,0xC0,0x00,
0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEF,0xFB,0xFF,0x7F,0x80,0x7F,0xFF,
0xED,0x1F,0xE0,0xFF,0xFD,0xFF,0x0F,0xF0,0xF8,0xFF,0xFB,0x85,0x38,0x7E,0xFF,0xFE,
0xA1,0x0C,0xD7,0xBF,0x7F,0xF8,0x86,0xF1,0xFD,0x97,0xEF,0x61,0xF8,0xFF,0xBF,0xFA,
0x01,0xDE,0xFF,0xEB,0xFF,0x00,0xFE,0xBD,0xFE,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0x80,
0xC7,0xF7,0xFF,0x7F,0xC0,0xE1,0x5D,0xFD,0x1F,0x60,0x78,0x47,0xF5,0x05,0x30,0xD8,
0x09,0xC0,0x00,0x00,0xFE,0x3D,0x00,0x03,0x00,0xB6,0x7C,0x00,0x06,0x80,0xBF,0xFC,
0x00,0x0C,0x80,0x9D,0xE5,0x00,0x18,0xC0,0x07,0x64,0x00,0x10,0xE1,0x86,0x7D,0x00,
0x30,0xE3,0x03,0x1D,0x00,0x60,0x7E,0x03,0x0D,0x00,0x00,0xDF,0x01,0x02,0x00,0xC0,
0xFB,0x01,0x00,0x80,0xC0,0xFE,0x01,0x00,0x00,0x80,0xDC,0x01,0x00,0x80,0xC0,0xF0,
0x01,0x00,0x00,0xE1,0x70,0x83,0x00,0x80,0xE1,0xF0,0x6F,0x02,0x00,0xF0,0xE0,0x3F,
0x1D,0x00,0xF8,0xC0,0x1D,0x3D,0x00,0xF8,0xC0,0xAF,0x7F,0x00,0xFE,0x01,0xBF,0x6C,
0x00,0xBF,0x03,0xFF,0x66,0xA0,0xFF,0x0E,0xDC,0x2D,0xE8,0x6F,0x7F,0xF0,0xFF,0xFF,
0x3F,0xFE,0x4B,0xF7,0xFF,0x1A,0xF4,0xFF,0xBD,0xAA,0x0F,0xF8,0xFF,0xFF,0xFF,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF4,0xBF,0x00,
0x00,0xFA,0xDF,0x6A,0xF0,0xC1,0x57,0xAA,0xFF,0x10,0x79,0xA9,0x55,0xAD,0x10,0xAF,
0x56,0xAA,0xFA,0x90,0x53,0xA9,0xD5,0xFF,0xB8,0xAF,0x56,0x6A,0x52,0x6C,0x57,0xE9,
0x95,0xAD,0x66,0xAC,0x17,0x68,0x52,0x01,0x5C,0xA0,0x96,0xAD,0x3B,0x14,0x5C,0x69,
0x52,0x36,0x8C,0xA2,0xFF,0xAF,0x3A,0x46,0xFD,0x55,0xFF,0xE7,0xA1,0xFF,0x03,0xFC,
0x59,0xF8,0xFD,0x03,0xFA,0x27,0x9A,0x7C,0x02,0xE4,0x1B,0xCC,0x7E,0x00,0x58,0x0F,
0x46,0xCC,0x01,0xB0,0x8B,0x43,0x84,0x00,0x60,0x0F,0x41,0x0C,0x00,0x80,0xEF,0x41,
0x00,0x00,0x40,0x9E,0x00,0x00,0x80,0xC0,0xFD,0x00,0x00,0x00,0x00,0xF7,0x00,0x00,
0x80,0x82,0xD9,0x00,0x00,0x00,0x03,0xE7,0x00,0x00,0x80,0xC2,0x9A,0x01,0x00,0x08,
0x81,0x66,0x01,0x00,0x80,0xE0,0x88,0x03,0x78,0x00,0xF0,0x4C,0x47,0xFC,0x00,0xE0,
0x94,0x4C,0xDC,0x00,0xF8,0x18,0x7B,0x8E,0x00,0xFA,0x30,0xE4,0x8C,0x00,0x7E,0x60,
0x98,0xCD,0x80,0x1F,0xC0,0x61,0x1B,0xA8,0x01,0x00,0x8F,0xAE,0xFF,0xFF,0x00,0xF8,
0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,
0xE0,0x0F,0x00,0x00,0x00,0xF0,0x07,0x00,0x00,0x00,0xF8,0x07,0x00,0x00,0x00,0xFC,
0x03,0x00,0x40,0x01,0xFE,0x07,0x00,0xFC,0x07,0xFF,0x0D,0x00,0xFF,0xFF,0xFF,0x10,
0xC0,0xFF,0xFF,0x7F,0x20,0xE0,0xFF,0x03,0x1F,0x60,0xF8,0xE7,0xF3,0x06,0x40,0xFC,
0xDF,0xC7,0x0C,0x80,0x1E,0xBF,0x1F,0x0D,0x80,0xFE,0xFE,0xFF,0x30,0x00,0xFF,0xFF,
0x1F,0xD0,0x00,0xFF,0xFF,0x0F,0x40,0x8B,0xFF,0xFF,0x2D,0x00,0x2F,0xFF,0xF8,0x5D,
0x00,0xF8,0x7D,0x60,0x3C,0x00,0xF4,0x7B,0x00,0xFC,0x00,0xF8,0x7D,0x00,0xEC,0x00,
0x20,0x33,0x00,0xFC,0x01,0x20,0x7D,0x00,0xFC,0x01,0x20,0x7A,0x00,0x9C,0x81,0x20,
0xFD,0x00,0x98,0x81,0x20,0xFB,0x00,0xF0,0x01,0x25,0xF7,0x00,0x70,0xA0,0x1A,0xEB,
0x01,0x70,0x21,0x05,0xF7,0x01,0x30,0xA0,0x01,0xCF,0x03,0xF0,0x6F,0x00,0xFF,0x03,
0xF0,0x3B,0x00,0x9F,0x07,0xB0,0x05,0x00,0xFF,0x07,0x98,0x01,0x00,0xFC,0xFF,0xF7,
0x00,0x00,0xF0,0x1F,0x70,0x00,0x00,0xE0,0x3F,0x00,0x00,0x00,0xB0,0x43,0x00,0x00,
0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xD8,0x01,0xC0,0x03,0x00,0x08,0x00,0x00,0x0C,0x00,0x44,0x00,0x00,0x3F,0x00,0x04,
0x80,0x00,0x06,0x00,0x06,0x00,0x02,0x0C,0x00,0x01,0x00,0x3F,0x30,0x00,0x01,0x00,
0xF2,0x33,0x00,0x00,0x00,0x0C,0x4F,0x00,0x00,0x00,0x88,0xF8,0x01,0x00,0xEC,0x4F,
0xE1,0x07,0x00,0x70,0x48,0x02,0x3B,0x00,0xC0,0xA8,0x07,0xCE,0x00,0x00,0x53,0x06,
0x1C,0x00,0x00,0xDC,0x06,0xF0,0x00,0xF8,0xDF,0x03,0xE0,0x00,0xC0,0x20,0x03,0x40,
0x00,0x00,0x03,0x70,0xC2,0x00,0x00,0x0C,0x80,0xC8,0x80,0x02,0x08,0x00,0x8C,0x00,
0xFD,0x10,0x00,0x8C,0x00,0x0C,0x2E,0x00,0x8C,0x00,0x30,0x30,0x01,0x82,0x00,0xC0,
0xD0,0x02,0x80,0x00,0x80,0x11,0x04,0xE0,0x00,0x00,0xEA,0x04,0x50,0x00,0x00,0x6D,
0x06,0xE0,0x00,0x00,0xEC,0x06,0xF8,0x00,0x00,0xF8,0x07,0x5A,0x00,0x00,0xC8,0x03,
0xAE,0x00,0x00,0xF0,0x80,0x57,0x00,0xA8,0x80,0xE0,0xA9,0x00,0xD0,0x6B,0xF9,0xFE,
0x01,0x00,0xBF,0x5F,0x19,0x03,0x00,0xE0,0xAE,0x16,0x0C,0x00,0x14,0x53,0x29,0x30,
0x00,0xC0,0xAC,0x7F,0xE0,0x01,0x00,0x7B,0x00,0x80,0x02,0x00,0x24,0x00,0x00,0x0B,
0xA8,0xFE,0x00,0x00,0x2C,0x54,0x79,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x80,
0x03,0x00,0x00,0x00,0xE0,0x83,0x07,0x00,0x00,0xE0,0x61,0x18,0x00,0x00,0xF8,0x31,
0x30,0x00,0x00,0xFC,0x18,0x20,0x00,0xA0,0xFF,0xF7,0x40,0x00,0xFC,0x1F,0x80,0x41,
0x80,0xFF,0x0F,0x00,0x43,0xE0,0xFF,0x09,0x00,0x44,0x70,0xC7,0x11,0x00,0x6C,0xB8,
0x93,0x10,0x00,0x38,0xDC,0x91,0x20,0x00,0x10,0xCC,0xC3,0x00,0x00,0x10,0xE6,0xFF,
0x20,0x00,0x10,0xF2,0xFF,0x00,0x00,0x20,0xFA,0x83,0x10,0x00,0x10,0xFB,0x91,0x11,
0x00,0x20,0xFB,0x93,0x09,0x00,0x20,0xFD,0xC7,0x03,0x00,0x20,0xFF,0xFF,0x07,0x00,
0x20,0xFF,0xFD,0x0F,0x00,0x20,0xFF,0xF4,0x1F,0x00,0x20,0x43,0xF8,0x3F,0x00,0x20,
0x03,0xF0,0xFF,0x00,0x20,0x62,0xF8,0xFF,0x01,0x10,0xF4,0xF4,0xFF,0x03,0x20,0xF4,
0xF9,0x7F,0x0F,0x30,0xF2,0xD0,0xFF,0x3C,0x50,0x41,0xE0,0xFF,0x3B,0xD8,0x01,0xC0,
0xFF,0x77,0x88,0x02,0xE8,0xFF,0xEF,0x8C,0x3C,0xFE,0xFF,0xCF,0x86,0x20,0xFC,0xF7,
0xEE,0x47,0x60,0x01,0xC0,0xE1,0x60,0xC0,0x00,0x80,0xFF,0x1F,0x00,0x00,0x00,0xFF,
0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x00,0x18,0x00,
0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0xDC,0x0F,0x00,0x00,0x00,0x84,0x33,0x00,0x00,
0x00,0x86,0x63,0x00,0x00,0x00,0x82,0xC3,0x00,0x00,0x00,0x86,0x03,0x03,0x00,0x00,
0x83,0x07,0x03,0x00,0x00,0xEF,0x07,0x04,0x00,0x80,0xD2,0x07,0x0C,0x00,0xC0,0xEE,
0x03,0x08,0x00,0x60,0xF6,0x03,0x18,0x00,0x20,0xEC,0x03,0x10,0x80,0x12,0xFC,0x01,
0x10,0x60,0x18,0xF8,0x00,0x30,0x10,0x10,0x60,0x00,0x10,0x10,0x07,0x00,0x00,0x31,
0x06,0x2F,0x00,0x00,0x10,0x72,0x18,0x00,0x80,0x11,0x16,0x20,0x00,0x80,0x18,0x0B,
0x00,0x00,0x80,0x08,0x01,0x40,0x00,0x80,0x0C,0x05,0x40,0x00,0x40,0x04,0x09,0x46,
0x00,0x40,0x06,0x08,0x2F,0x00,0x20,0x03,0x38,0x1F,0x00,0x90,0x0F,0x84,0x07,0x00,
0xC0,0x78,0x04,0xA0,0x2A,0x60,0xC0,0xFC,0xFF,0xFF,0x3F,0x00,0xFC,0x55,0xFF,0xFF,
0x01,0x0E,0x00,0xFE,0xFF,0x07,0x0E,0x00,0xFE,0xFF,0x0F,0x0E,0xC0,0xFF,0xFF,0x1F,
0x3C,0xA8,0xFE,0xFF,0x1F,0xF8,0xF2,0xFF,0xFF,0x7F,0xE0,0xAF,0xFE,0xFF,0xDF,0x80,
0xFF,0xFF,0xFF,0x0F,0x00,0xFC,0xFF,0xFF,0x0F,0x00,0xE0,0xFF,0xFF,0x07,0x00,0x00,
0xFE,0xFF,0x01,0x00,0x00,0x80,0x1F,0x00,0x00,0x02,0x00,0x00,0x00,0x80,0xC3,0x00,
0x00,0x00,0x80,0x63,0x00,0x00,0x00,0xC0,0x79,0x00,0x00,0x00,0xE0,0x3B,0x40,0x01,
0x00,0xF0,0x3F,0xA0,0x16,0x00,0xB8,0x1F,0x18,0xFC,0x00,0xB8,0x1F,0x08,0x88,0x01,
0xDC,0x1F,0x00,0x10,0x07,0x2C,0x0F,0x0C,0x10,0x04,0xDE,0x2F,0x08,0x18,0x0C,0x2E,
0xFE,0x0F,0x08,0x08,0xFE,0x3F,0x3F,0x06,0x10,0xFF,0x66,0xE0,0x03,0x30,0xFF,0x07,
0x00,0x00,0x30,0xFF,0x47,0x02,0x00,0x30,0xFF,0x6F,0x0F,0x00,0x38,0xFF,0x67,0x06,
0x00,0x2C,0xFF,0x3F,0x00,0x00,0x6E,0xFF,0x2F,0x00,0xC0,0x23,0xFF,0x3F,0x00,0x00,
0x60,0xFE,0x2F,0x00,0x00,0x20,0xFE,0x3F,0x00,0x00,0x20,0x7E,0x18,0x00,0x00,0x30,
0x5C,0x18,0x00,0x00,0x10,0x1C,0x38,0x00,0x00,0x18,0x38,0x3E,0x00,0x00,0x98,0x38,
0x3E,0x00,0x00,0xDC,0xF0,0x3F,0x00,0x00,0x70,0xE0,0x7F,0x00,0x80,0x7A,0xE0,0x7F,
0x00,0xC0,0x3B,0xC0,0xFF,0xAA,0xFA,0x3F,0x80,0xFF,0xFF,0x7F,0x18,0x00,0xFF,0xCF,
0x7F,0xB8,0x00,0xFE,0x9F,0x7F,0x58,0x00,0xFC,0x9F,0x3F,0xB8,0x00,0xF8,0xDF,0x1F,
0x58,0x00,0xF8,0xEF,0x07,0xB0,0x00,0x78,0x7F,0x00,0x70,0x00,0x38,0x00,0x00,0xE0,
0x54,0x25,0x34,0x00,0x00,0xB8,0xBA,0xD8,0x00,0x00,0xE0,0xFF,0xFF,0x01,0x00,0xD0,
0x10,0xCE,0x03,0x00,0xA0,0x11,0x3E,0x02,0x00,0x40,0x13,0xE9,0x00,0x00,0x00,0x97,
0x88,0x01,0x00,0x02,0x9C,0x1E,0x07,0x00,0xE8,0xB8,0x1F,0x1C,0x00,0x16,0xFF,0x3F,
0x30,0x00,0xFA,0xFD,0x19,0x60,0x00,0xAF,0xEA,0x19,0x80,0x01,0xFF,0xDF,0x1F,0x05,
0x03,0x00,0x7E,0xEF,0x05,0x06,0x00,0xE0,0x33,0x0C,0x0C,0x03,0x00,0x07,0x04,0x18,
0x02,0x00,0x04,0x04,0x30,0x0D,0x00,0x00,0x80,0x30,0x0C,0x10,0x00,0x80,0x20,0x1A,
0x08,0x00,0x80,0x40,0x34,0x0C,0x03,0x80,0x40,0x38,0x84,0x04,0x40,0xC0,0x60,0x66,
0x04,0x00,0xC0,0xD0,0x22,0x08,0x00,0xC0,0xE0,0xD2,0x0B,0x00,0xC0,0xC2,0x73,0x06,
0x00,0x60,0xCA,0x73,0x16,0x00,0xE8,0x8A,0xF1,0x0F,0x00,0x74,0xB5,0xF3,0x0F,0x00,
0x5A,0xAA,0xE1,0x07,0x00,0x79,0xB5,0xC3,0x03,0x80,0x1E,0xCA,0xC3,0x00,0x40,0x97,
0xF5,0x0F,0x00,0xA8,0xEB,0xDA,0x0F,0x00,0xE0,0xE5,0xED,0x3F,0x00,0x78,0xFA,0xD2,
0x3F,0x80,0xBE,0xFD,0xFD,0xFF,0x00,0x4E,0xFE,0xEA,0xFF,0x81,0xB3,0xFF,0xF5,0x7F,
0x19,0xCD,0xFF,0xEA,0xBF,0x3D,0xE1,0xFF,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,
0x00,0xC0,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x20,0x00,0xFE,0x0F,0x00,
0x30,0x80,0xFF,0xFF,0x3F,0x10,0xE0,0xFF,0x3F,0x20,0x10,0x70,0xFF,0x3F,0x4F,0x38,
0xB8,0xFF,0x3F,0xC5,0xA8,0x98,0xFF,0xFF,0x81,0x5E,0xCC,0xFF,0xFF,0x2A,0xAB,0xEE,
0x81,0x3F,0x00,0xFF,0xE6,0x80,0x4F,0x55,0x5E,0x66,0x80,0x1F,0x00,0x15,0x72,0x80,
0x1F,0x00,0x2C,0x73,0x80,0xFF,0x00,0x38,0x33,0x80,0x7F,0x03,0x50,0x3B,0x8F,0xBF,
0x03,0x70,0xB9,0xB1,0xFF,0x03,0xA0,0xBB,0xA0,0xDF,0x01,0x60,0xBB,0xAC,0x1F,0x00,
0xC0,0xBF,0xB8,0x0F,0x00,0x40,0xBF,0xBB,0x0F,0x00,0xC1,0x3F,0xAC,0x0F,0x00,0xC1,
0x3F,0x86,0x1F,0x00,0x8D,0xBF,0x9B,0xFF,0x01,0xC9,0xBE,0xB0,0x3F,0x33,0xC1,0xFE,
0xA0,0xFF,0x03,0xC0,0xFC,0xAC,0xFA,0x01,0x60,0xBC,0xB9,0x9D,0x00,0xF0,0x38,0xBF,
0x18,0x00,0x28,0x30,0x80,0x08,0x00,0x66,0x60,0x80,0x08,0xC0,0x41,0x80,0xFF,0x58,
0x15,0x40,0x00,0x40,0x08,0x00,0x40,0x00,0x40,0x08,0x00,0xC0,0x00,0x80,0x08,0x00,
0xC0,0x00,0x80,0x08,0x00,0x80,0x00,0x80,0x09,0x00,0x00,0x00,0x00,0x06,0x00,0x00};
//d:\我的文档\桌面\新建文件夹\2009-08-05_165416.bmp0

