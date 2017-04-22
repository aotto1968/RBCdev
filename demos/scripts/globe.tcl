rbc::bitmap define globe.0 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x40, 0x02, 0x00, 0x00, 0x1c, 0x3c, 0x00, 0x00, 0x01, 0xfe, 0x00, 
    0x80, 0x80, 0xfe, 0x03, 0x60, 0x00, 0xff, 0x07, 0x10, 0xc0, 0xf1, 0x0f,
    0x00, 0x80, 0xc0, 0x1f, 0x00, 0xc0, 0x07, 0x3f, 0x00, 0xc0, 0xff, 0x3f, 
    0x00, 0xf0, 0xff, 0x4f, 0x02, 0xf0, 0xff, 0x5d, 0x00, 0xf0, 0xff, 0x1b,
    0x00, 0xf0, 0xff, 0x8f, 0x02, 0xf0, 0xff, 0x0f, 0x06, 0xe0, 0xfc, 0x0f, 
    0x0e, 0x00, 0xf8, 0x0f, 0x0f, 0x00, 0xf8, 0x07, 0x3f, 0x00, 0xf8, 0x03,
    0x7e, 0x00, 0xf0, 0x03, 0x7e, 0x00, 0xf0, 0x03, 0x3e, 0x00, 0xf0, 0x0b, 
    0x3c, 0x00, 0xf0, 0x09, 0x3c, 0x00, 0xf0, 0x01, 0x18, 0x00, 0xf0, 0x00,
    0x18, 0x00, 0x70, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00};
}

rbc::bitmap define globe.1 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0xc0, 0x00, 0x00, 0x00, 0x34, 0x38, 0x00, 0x00, 0x02, 0xe8, 0x00, 
    0x80, 0x01, 0xfa, 0x03, 0xe0, 0x00, 0xfc, 0x07, 0x30, 0x00, 0xe6, 0x0f,
    0x10, 0x00, 0x86, 0x1f, 0x08, 0x00, 0x3e, 0x3c, 0x04, 0x00, 0xff, 0x3f, 
    0x04, 0x80, 0xff, 0x5f, 0x02, 0x80, 0xff, 0x3f, 0x00, 0x80, 0xff, 0x2f,
    0x00, 0x80, 0xff, 0x3f, 0x0c, 0x00, 0xff, 0x3f, 0x1c, 0x00, 0xee, 0x3f, 
    0x3c, 0x00, 0xc0, 0x3f, 0x7e, 0x00, 0xc0, 0x1f, 0xfe, 0x01, 0x80, 0x1f,
    0xfc, 0x03, 0x80, 0x1f, 0xfc, 0x01, 0x80, 0x1f, 0xfc, 0x01, 0x80, 0x2f, 
    0xf8, 0x01, 0x80, 0x0f, 0xf0, 0x00, 0x80, 0x17, 0xf0, 0x00, 0x80, 0x03,
    0xf0, 0x00, 0x80, 0x03, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00};
}

rbc::bitmap define globe.2 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0xc0, 0x01, 0x00, 0x00, 0x60, 0x30, 0x00, 0x00, 0x04, 0xf0, 0x00, 
    0x80, 0x07, 0xe0, 0x03, 0xe0, 0x01, 0xf0, 0x07, 0xf0, 0x00, 0x38, 0x0f,
    0x30, 0x00, 0x10, 0x1e, 0x18, 0x00, 0xf0, 0x30, 0x04, 0x00, 0xf8, 0x3f, 
    0x10, 0x00, 0xf8, 0x7f, 0x12, 0x00, 0xfc, 0x7f, 0x02, 0x00, 0xfc, 0x7f,
    0x04, 0x00, 0xfc, 0x7f, 0x74, 0x00, 0xf8, 0x7f, 0xf0, 0x00, 0x70, 0x7f, 
    0xf8, 0x01, 0x00, 0x7e, 0xf8, 0x03, 0x00, 0x7e, 0xf8, 0x0f, 0x00, 0x7c,
    0xf8, 0x1f, 0x00, 0x3c, 0xf0, 0x1f, 0x00, 0x3c, 0xf0, 0x0f, 0x00, 0x3e, 
    0xe0, 0x0f, 0x00, 0x5e, 0xc0, 0x07, 0x00, 0x1c, 0xc0, 0x03, 0x00, 0x0e,
    0xc0, 0x03, 0x00, 0x04, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 
    0x80, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x1c, 0x00};
}

rbc::bitmap define globe.3 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0xc0, 0x01, 0x00, 0x00, 0xdc, 0x20, 0x00, 0x00, 0x09, 0xc0, 0x00, 
    0x80, 0x1f, 0xa0, 0x03, 0xe0, 0x07, 0xc0, 0x07, 0xf0, 0x01, 0xc0, 0x0c,
    0xf8, 0x00, 0x40, 0x18, 0x78, 0x00, 0xc0, 0x23, 0x08, 0x00, 0xc0, 0x3f, 
    0x04, 0x00, 0xe0, 0x7f, 0x54, 0x00, 0xe0, 0x7f, 0x0c, 0x00, 0xc0, 0x7f,
    0x10, 0x00, 0xc0, 0xff, 0xd0, 0x01, 0xc0, 0xff, 0xc0, 0x03, 0x80, 0xfb, 
    0xe0, 0x0f, 0x00, 0xf0, 0xe0, 0x1f, 0x00, 0xf0, 0xe0, 0xff, 0x00, 0xf0,
    0xe0, 0xff, 0x00, 0x70, 0xc0, 0xff, 0x00, 0x70, 0xc0, 0x7f, 0x00, 0x70, 
    0x00, 0x7f, 0x00, 0x70, 0x00, 0x3f, 0x00, 0x30, 0x00, 0x1f, 0x00, 0x38,
    0x00, 0x1f, 0x00, 0x18, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 
    0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x18, 0x00};
}

rbc::bitmap define globe.4 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0xc0, 0x03, 0x00, 0x00, 0x7c, 0x03, 0x00, 0x00, 0x13, 0x00, 0x00, 
    0x80, 0x7f, 0xc0, 0x03, 0xc0, 0x1f, 0x00, 0x07, 0xe0, 0x0f, 0x00, 0x0d,
    0xf0, 0x03, 0x00, 0x10, 0xf0, 0x01, 0x00, 0x0e, 0x38, 0x01, 0x00, 0x3e, 
    0x10, 0x00, 0x00, 0x7f, 0x50, 0x00, 0x00, 0x7f, 0x30, 0x00, 0x00, 0x7f,
    0x40, 0x00, 0x00, 0xff, 0x00, 0x1e, 0x00, 0xfe, 0x00, 0x3f, 0x00, 0xec, 
    0x00, 0x7f, 0x00, 0xc0, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xff, 0x07, 0xc0,
    0x00, 0xff, 0x0f, 0xc0, 0x00, 0xfe, 0x07, 0xc0, 0x00, 0xfe, 0x07, 0xc0, 
    0x00, 0xf8, 0x03, 0x40, 0x00, 0xf8, 0x01, 0x60, 0x00, 0xf8, 0x00, 0x20,
    0x00, 0xf8, 0x00, 0x20, 0x00, 0x38, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 
    0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0x00};
}

rbc::bitmap define globe.5 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0xc0, 0x03, 0x00, 0x00, 0xbc, 0x06, 0x00, 0x00, 0xcf, 0x00, 0x00, 
    0x80, 0xff, 0x01, 0x02, 0xc0, 0x7f, 0x00, 0x06, 0xc0, 0x3f, 0x00, 0x0e,
    0xe0, 0x1f, 0x00, 0x14, 0xe0, 0x0f, 0x00, 0x18, 0xe0, 0x00, 0x00, 0x38, 
    0x60, 0x00, 0x00, 0x78, 0x40, 0x08, 0x00, 0x78, 0xc0, 0x01, 0x00, 0x78,
    0x00, 0x02, 0x00, 0xf8, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x01, 0xb0, 
    0x00, 0xf8, 0x07, 0x80, 0x00, 0xf8, 0x0f, 0x80, 0x00, 0xf8, 0x3f, 0x00,
    0x00, 0xf8, 0x7f, 0x00, 0x00, 0xf0, 0x3f, 0x80, 0x00, 0xf0, 0x3f, 0x80, 
    0x00, 0xc0, 0x1f, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0xc0, 0x07, 0x40,
    0x00, 0xc0, 0x07, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x00, 0xe0, 0x00, 0x00, 
    0x00, 0x60, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x10, 0x00};
}

rbc::bitmap define globe.6 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x80, 0x07, 0x00, 0x00, 0x7c, 0x0d, 0x00, 0x00, 0x9f, 0x03, 0x00, 
    0x00, 0xff, 0x07, 0x02, 0x00, 0xff, 0x03, 0x04, 0x80, 0xff, 0x00, 0x08,
    0xc0, 0x7f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x30, 0x80, 0x07, 0x00, 0x20, 
    0x00, 0x03, 0x00, 0x60, 0x00, 0x03, 0x00, 0x60, 0x00, 0x0e, 0x00, 0x60,
    0x00, 0x10, 0x00, 0xe0, 0x00, 0x80, 0x07, 0xc0, 0x00, 0x80, 0x0f, 0xc0, 
    0x00, 0x80, 0x3f, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00, 0xc0, 0xff, 0x01,
    0x00, 0xc0, 0xff, 0x03, 0x00, 0x80, 0xff, 0x01, 0x00, 0x80, 0xff, 0x01, 
    0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3e, 0x00,
    0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x03, 0x00, 
    0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00};
}

rbc::bitmap define globe.7 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x80, 0x07, 0x00, 0x00, 0xfc, 0x1a, 0x00, 0x00, 0x7d, 0x02, 0x00, 
    0x00, 0xfe, 0x1f, 0x00, 0x00, 0xfe, 0x0f, 0x00, 0x00, 0xfe, 0x07, 0x00,
    0x00, 0xff, 0x03, 0x00, 0x00, 0xfe, 0x01, 0x20, 0x00, 0x1c, 0x01, 0x00, 
    0x00, 0x1c, 0x00, 0x40, 0x00, 0x18, 0x00, 0x40, 0x00, 0x70, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x39, 0x80, 0x00, 0x00, 0x7c, 0x00, 
    0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0xfe, 0x0f,
    0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0xf8, 0x07, 
    0x00, 0x00, 0xf0, 0x07, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0xf0, 0x01,
    0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x18, 0x00, 
    0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00};
}

rbc::bitmap define globe.8 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x07, 0x00, 0x00, 0xfc, 0x25, 0x00, 0x00, 0xf8, 0x19, 0x00, 
    0x00, 0xf8, 0x7f, 0x00, 0x00, 0xf8, 0x3f, 0x00, 0x00, 0xf8, 0x1f, 0x00,
    0x00, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x0f, 0x00, 0x00, 0xf0, 0x08, 0x00, 
    0x00, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0x04, 0x00, 0x00, 0x80, 0x03, 0x00,
    0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc8, 0x01, 0x00, 0x00, 0xe0, 0x03, 
    0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0xf0, 0x3f,
    0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0xc0, 0x1f, 
    0x00, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x80, 0x0f, 0x00, 0x00, 0xc0, 0x07,
    0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x60, 0x00, 
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00};
}

rbc::bitmap define globe.9 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x03, 0x00, 0x00, 0xfc, 0x27, 0x00, 0x00, 0xf0, 0x13, 0x00, 
    0x00, 0xe0, 0xff, 0x00, 0x00, 0xe0, 0xff, 0x01, 0x00, 0xe0, 0x7f, 0x00,
    0x00, 0xe0, 0x7f, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00, 0x80, 0x47, 0x00, 
    0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x1c, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x40, 0x0e, 0x00, 0x00, 0x00, 0x1f, 
    0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x7f,
    0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7e, 
    0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x1e,
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x80, 0x01, 
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00};
}

rbc::bitmap define globe.10 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x06, 0x00, 0x00, 0xf4, 0x2f, 0x00, 0x00, 0xc8, 0x4f, 0x00, 
    0x00, 0x80, 0xff, 0x01, 0x00, 0x80, 0xff, 0x01, 0x00, 0x80, 0xff, 0x01,
    0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0xfe, 0x01, 0x00, 0x00, 0x3c, 0x00, 
    0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x38, 
    0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xfc,
    0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xf8, 
    0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x38,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x06, 
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00};
}

rbc::bitmap define globe.11 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x06, 0x00, 0x00, 0xec, 0x1f, 0x00, 0x00, 0x91, 0x9f, 0x00, 
    0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 0xfc, 0x07,
    0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 0xf0, 0x07, 0x00, 0x00, 0xf0, 0x01, 
    0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00, 0x00, 0x07,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xe0, 
    0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0,
    0x01, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 
    0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x08, 
    0x40, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00};
}

rbc::bitmap define globe.12 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x04, 0x00, 0x00, 0xdc, 0x3f, 0x00, 0x00, 0x42, 0x7e, 0x00, 
    0x00, 0x00, 0xf8, 0x03, 0x20, 0x00, 0xf0, 0x07, 0x10, 0x00, 0xf0, 0x0f,
    0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x07, 
    0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x18,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x80, 
    0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x40,
    0x08, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
}

rbc::bitmap define globe.13 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x04, 0x00, 0x00, 0xbc, 0x3f, 0x00, 0x00, 0x01, 0x79, 0x00, 
    0x80, 0x00, 0xe0, 0x03, 0x60, 0x00, 0xc0, 0x07, 0x10, 0x00, 0x80, 0x0f,
    0x00, 0x00, 0x80, 0x1f, 0x08, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1c, 
    0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00};
}

rbc::bitmap define globe.14 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x03, 0xe6, 0x00, 
    0x80, 0x01, 0xc0, 0x03, 0x60, 0x00, 0x00, 0x07, 0x30, 0x00, 0x00, 0x0f,
    0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x38, 0x04, 0x00, 0x00, 0x30, 
    0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 
    0x3c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
    0x78, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00};
}

rbc::bitmap define globe.15 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3d, 0x00, 0x00, 0x27, 0xc8, 0x00, 
    0x80, 0x13, 0x00, 0x03, 0xe0, 0x01, 0x00, 0x06, 0x70, 0x00, 0x00, 0x0c,
    0x10, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x20, 
    0x0c, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x03, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
    0xf8, 0x00, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x00,
    0xf0, 0x03, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00};
}

rbc::bitmap define globe.16 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3b, 0x00, 0x00, 0x9f, 0xa0, 0x00, 
    0x80, 0x4f, 0x00, 0x02, 0xe0, 0x0f, 0x00, 0x04, 0xf0, 0x01, 0x00, 0x08,
    0x70, 0x00, 0x00, 0x10, 0x38, 0x00, 0x00, 0x20, 0x3c, 0x00, 0x00, 0x00, 
    0x1c, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
    0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x28, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x02, 0x00, 0x00, 
    0xe0, 0x07, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xe0, 0x1f, 0x00, 0x00,
    0xe0, 0x1f, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00};
}

rbc::bitmap define globe.17 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x37, 0x00, 0x00, 0x3f, 0x42, 0x00, 
    0x80, 0x3f, 0x01, 0x02, 0xe0, 0x1f, 0x00, 0x00, 0xf0, 0x07, 0x00, 0x00,
    0xf0, 0x11, 0x00, 0x00, 0xf8, 0x04, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 
    0x7c, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x9a, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x20, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00,
    0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 
    0x00, 0x3f, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00, 0x80, 0x7f, 0x00, 0x00,
    0x80, 0x7f, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00};
}

rbc::bitmap define globe.18 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x2f, 0x00, 0x00, 0xff, 0x84, 0x00, 
    0x80, 0xff, 0x04, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0xf0, 0x9f, 0x00, 0x00,
    0xf0, 0x97, 0x00, 0x00, 0xf8, 0x27, 0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 
    0xfc, 0x03, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
    0x60, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
    0x20, 0x01, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x00, 0xc0, 0x05, 0x00,
    0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0x00, 
    0x00, 0xfc, 0x01, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0xfe, 0x03, 0x00,
    0x00, 0xfc, 0x03, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00};
}

rbc::bitmap define globe.19 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0x13, 0x00, 
    0x80, 0xff, 0x13, 0x00, 0xe0, 0xff, 0x03, 0x00, 0xf0, 0xff, 0x00, 0x00,
    0xf0, 0x9f, 0x00, 0x00, 0xf8, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 
    0xf8, 0x1f, 0x00, 0x00, 0xba, 0x07, 0x00, 0x00, 0x98, 0x23, 0x00, 0x00,
    0x08, 0x03, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0x09, 0x00, 0x00, 0x00, 0x0d, 0x01, 0x00, 0x00, 0x21, 0x0e, 0x00,
    0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x09, 0x00, 
    0x00, 0xe0, 0x0f, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x00, 0xf0, 0x1f, 0x00,
    0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x07, 0x00};
}

rbc::bitmap define globe.20 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0x07, 0x00, 
    0x80, 0xff, 0x0f, 0x00, 0xe0, 0xff, 0x0f, 0x00, 0xf0, 0xff, 0x13, 0x00,
    0xf0, 0xff, 0x10, 0x00, 0xf8, 0xff, 0x00, 0x00, 0xfc, 0xff, 0x01, 0x00, 
    0xf4, 0xff, 0x00, 0x00, 0xe6, 0x1e, 0x00, 0x00, 0x62, 0x1c, 0x01, 0x00,
    0x20, 0x18, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
    0x01, 0xcc, 0x00, 0x00, 0x01, 0x68, 0x08, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 
    0x00, 0x00, 0x7e, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x80, 0xff, 0x00,
    0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x04, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00};
}

rbc::bitmap define globe.21 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x80, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0x1f, 0x00, 
    0x80, 0xff, 0xbf, 0x00, 0xe0, 0xff, 0x3f, 0x00, 0xf0, 0xff, 0x1f, 0x00,
    0xf8, 0xff, 0x17, 0x00, 0xf8, 0xff, 0x27, 0x00, 0xec, 0xff, 0x0f, 0x00, 
    0x8c, 0xff, 0x07, 0x00, 0x9e, 0xf7, 0x00, 0x00, 0x0e, 0xe3, 0x00, 0x00,
    0x06, 0xc1, 0x00, 0x00, 0x06, 0x81, 0x10, 0x00, 0x03, 0x40, 0x04, 0x00, 
    0x03, 0x20, 0x06, 0x00, 0x03, 0x40, 0x06, 0x00, 0x01, 0x80, 0x00, 0x03,
    0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0xe0, 0x02, 
    0x02, 0x00, 0xf0, 0x03, 0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0xfc, 0x03,
    0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00};
}

rbc::bitmap define globe.22 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x01, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0x3f, 0x00, 
    0x80, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0x00, 0xf0, 0xff, 0x7f, 0x00,
    0xf0, 0xff, 0x1f, 0x00, 0xe0, 0xff, 0x3f, 0x00, 0xfc, 0xff, 0x3f, 0x00, 
    0x34, 0xfe, 0x3f, 0x00, 0x76, 0xbc, 0x07, 0x00, 0x36, 0x1c, 0x07, 0x00,
    0x0e, 0x08, 0x0e, 0x00, 0x1e, 0x08, 0x80, 0x00, 0x0f, 0x00, 0x02, 0x00, 
    0x0f, 0x00, 0x20, 0x00, 0x07, 0x00, 0x36, 0x00, 0x07, 0x00, 0x04, 0x08,
    0x07, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x0b, 
    0x16, 0x00, 0x80, 0x0f, 0x04, 0x00, 0xe0, 0x0f, 0x04, 0x00, 0xe0, 0x0f,
    0x08, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x10, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00};
}

rbc::bitmap define globe.23 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0x7f, 0x00, 
    0x80, 0xff, 0xff, 0x01, 0xe0, 0xff, 0xff, 0x01, 0xe0, 0xff, 0xff, 0x01,
    0xe8, 0xff, 0xff, 0x00, 0xc0, 0xff, 0xff, 0x00, 0xfc, 0xfe, 0xff, 0x01, 
    0xdc, 0xf2, 0xff, 0x01, 0xde, 0xe3, 0x3d, 0x00, 0xde, 0xe1, 0x38, 0x02,
    0x7e, 0x40, 0x70, 0x00, 0xfe, 0x40, 0x00, 0x04, 0x7f, 0x00, 0x00, 0x00, 
    0x3e, 0x00, 0x30, 0x01, 0x3e, 0x00, 0xa0, 0x01, 0x1e, 0x00, 0x20, 0x20,
    0x1e, 0x00, 0x00, 0x20, 0x1c, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x3c,
    0x1c, 0x00, 0x00, 0x3e, 0x1c, 0x00, 0x00, 0x3f, 0x18, 0x00, 0x80, 0x3f,
    0x10, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00};
}

rbc::bitmap define globe.24 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x02, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0xff, 0x00, 
    0x80, 0xff, 0xff, 0x01, 0xc0, 0xff, 0xff, 0x03, 0x80, 0xff, 0xff, 0x03,
    0xe0, 0xff, 0xff, 0x03, 0x18, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0x07, 
    0x7c, 0x87, 0xff, 0x07, 0xfe, 0x1f, 0xef, 0x01, 0xfe, 0x0e, 0xc6, 0x01,
    0xfe, 0x01, 0x82, 0x03, 0xfe, 0x03, 0x02, 0x00, 0xff, 0x03, 0x00, 0x08, 
    0xfc, 0x01, 0x80, 0x09, 0xfc, 0x00, 0x00, 0x0d, 0xfc, 0x00, 0x00, 0x00,
    0xf8, 0x00, 0x00, 0x80, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x20, 
    0x78, 0x02, 0x00, 0x70, 0x70, 0x02, 0x00, 0x7c, 0x70, 0x00, 0x00, 0x3c,
    0x60, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00};
}

rbc::bitmap define globe.25 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0x00, 
    0x80, 0xff, 0xff, 0x03, 0x80, 0xff, 0xff, 0x07, 0xa0, 0xff, 0xff, 0x07,
    0x10, 0xff, 0xff, 0x07, 0x30, 0xf8, 0xff, 0x0f, 0xf8, 0xdf, 0xff, 0x1f, 
    0xfc, 0x3b, 0xfc, 0x1f, 0xfc, 0xfb, 0x78, 0x07, 0xfe, 0x77, 0x30, 0x0e,
    0xfe, 0x1f, 0x30, 0x0c, 0xfe, 0x3f, 0x00, 0x48, 0xfe, 0x1f, 0x00, 0x00, 
    0xf0, 0x0f, 0x00, 0x24, 0xf0, 0x07, 0x00, 0xa0, 0xf0, 0x07, 0x00, 0x08,
    0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x27, 0x00, 0xc0, 
    0xe0, 0x13, 0x00, 0x40, 0xc0, 0x13, 0x00, 0x70, 0xc0, 0x03, 0x00, 0x70,
    0x80, 0x01, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00};
}

rbc::bitmap define globe.26 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0xe8, 0xff, 0x00, 
    0x00, 0xfc, 0xff, 0x03, 0x00, 0xff, 0xff, 0x07, 0xc0, 0xfe, 0xff, 0x0f,
    0x40, 0xf0, 0xff, 0x1f, 0xe0, 0xe0, 0xff, 0x1f, 0xf0, 0xff, 0xfe, 0x3f, 
    0xf8, 0xdf, 0xe1, 0x3f, 0xf8, 0xdf, 0xc7, 0x1b, 0xfc, 0xbf, 0x83, 0x19,
    0xfc, 0xff, 0x80, 0x30, 0xfc, 0xff, 0x01, 0x20, 0xf8, 0xff, 0x00, 0x00, 
    0xc0, 0xff, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0xe0, 0x80, 0x3f, 0x00, 0x20,
    0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x80, 
    0x80, 0x9f, 0x00, 0x00, 0x00, 0x9f, 0x00, 0x40, 0x00, 0x0f, 0x00, 0x60,
    0x00, 0x0e, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00};
}

rbc::bitmap define globe.27 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x80, 0x00, 0x00, 0x00, 0xc4, 0x3f, 0x00, 0x00, 0xf0, 0xff, 0x00, 
    0x00, 0xfe, 0xff, 0x03, 0x00, 0xfe, 0xff, 0x07, 0x00, 0xeb, 0xff, 0x0f,
    0x80, 0xc9, 0xff, 0x1f, 0x80, 0x07, 0xff, 0x3f, 0xc0, 0xff, 0xf7, 0x3f, 
    0xe0, 0xff, 0x0e, 0x7f, 0xf0, 0xff, 0x3e, 0x6e, 0xf0, 0xff, 0x1d, 0x64,
    0xf0, 0xff, 0x07, 0x44, 0xf0, 0xff, 0x0f, 0x00, 0x60, 0xff, 0x0f, 0x00, 
    0x00, 0xfe, 0x07, 0x40, 0x00, 0xfe, 0x03, 0x00, 0x01, 0xfc, 0x01, 0x00,
    0x01, 0xfc, 0x01, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0xfc, 0x09, 0x00, 
    0x02, 0xfc, 0x08, 0x00, 0x00, 0xf8, 0x04, 0x00, 0x00, 0x78, 0x00, 0x40,
    0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00};
}

rbc::bitmap define globe.28 {
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x3f, 0x00, 0x00, 0x40, 0xff, 0x00, 
    0x00, 0xe8, 0xff, 0x03, 0x00, 0xf8, 0xff, 0x07, 0x00, 0x8c, 0xff, 0x0f,
    0x00, 0x06, 0xfe, 0x1f, 0x00, 0x1e, 0xf8, 0x3f, 0x00, 0xff, 0xbf, 0x3f, 
    0x80, 0xff, 0x77, 0x7c, 0x80, 0xff, 0xff, 0x79, 0xc0, 0xff, 0xef, 0x10,
    0xc0, 0xff, 0x3f, 0x90, 0xc0, 0xff, 0x7f, 0x00, 0x81, 0xfb, 0x7f, 0x00, 
    0x01, 0xf0, 0x3f, 0x00, 0x01, 0xf0, 0x1f, 0x00, 0x03, 0xe0, 0x1f, 0x00,
    0x07, 0xe0, 0x0f, 0x00, 0x02, 0xc0, 0x1f, 0x00, 0x02, 0xe0, 0x5f, 0x00, 
    0x06, 0xe0, 0x47, 0x00, 0x04, 0xc0, 0x27, 0x00, 0x04, 0xc0, 0x03, 0x00,
    0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00};
}

rbc::bitmap define globe.29 { 
#define globe_width 32
#define globe_height 32
static char globe_bits[] = {
    0x00, 0x40, 0x01, 0x00, 0x00, 0x0c, 0x3f, 0x00, 0x00, 0x80, 0xfd, 0x00, 
    0x00, 0xa0, 0xff, 0x03, 0x20, 0xe0, 0xff, 0x07, 0x00, 0x30, 0xfd, 0x0f,
    0x00, 0x10, 0xf4, 0x1f, 0x00, 0xf8, 0xc0, 0x3f, 0x00, 0xf8, 0xff, 0x3f, 
    0x00, 0xfc, 0xbf, 0x73, 0x00, 0xfe, 0xff, 0x67, 0x00, 0xfe, 0x7f, 0x47,
    0x00, 0xfe, 0xff, 0x41, 0x00, 0xfe, 0xff, 0x03, 0x01, 0xdc, 0xff, 0x03, 
    0x03, 0x00, 0xff, 0x01, 0x07, 0x80, 0xff, 0x00, 0x0f, 0x00, 0xff, 0x00,
    0x1f, 0x00, 0x7e, 0x00, 0x0e, 0x00, 0xfe, 0x00, 0x0e, 0x00, 0xff, 0x02, 
    0x0e, 0x00, 0x3f, 0x01, 0x0c, 0x00, 0x3e, 0x01, 0x0c, 0x00, 0x1e, 0x00,
    0x08, 0x00, 0x1c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1f, 0x00};
}
