#include "sine_model_data.h"

ai_handle ai_sine_model_data_weights_get(void)
{

  AI_ALIGNED(4)
  static const ai_u8 s_sine_model_weights[ 1284 ] = {
    0xe2, 0xe0, 0xb3, 0xbe, 0x54, 0x33, 0x0b, 0xbe, 0xc1, 0xc1,
    0xdd, 0x3e, 0xc8, 0x71, 0xbb, 0x3e, 0x5b, 0xf8, 0xd0, 0xbe,
    0xd2, 0x66, 0x10, 0x3f, 0x26, 0x0d, 0xd6, 0xbe, 0xac, 0x15,
    0xe2, 0xbd, 0x53, 0xaf, 0x90, 0xbe, 0xa0, 0xe4, 0xea, 0xbe,
    0xf6, 0x3a, 0xa1, 0x3e, 0x31, 0x2b, 0x12, 0x3f, 0x9d, 0x39,
    0x82, 0x3e, 0xb4, 0xfd, 0xe0, 0xbd, 0xc2, 0xd7, 0x06, 0xbf,
    0x68, 0xc3, 0x3b, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xb3, 0x19, 0xd0, 0xbc, 0xfb, 0xe0, 0x05, 0xbf,
    0x00, 0x00, 0x00, 0x00, 0x2a, 0xc0, 0x28, 0xbf, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7f, 0x5a, 0xd1, 0xbe, 0xc3, 0x43,
    0x39, 0x3f, 0x2d, 0x09, 0x2b, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x22,
    0xca, 0xbe, 0x54, 0xe4, 0xda, 0xbd, 0x13, 0xc6, 0x5d, 0x3e,
    0xdc, 0x8b, 0x05, 0x3d, 0x40, 0x35, 0x83, 0xbc, 0x4c, 0xa1,
    0xa5, 0x3d, 0x24, 0xd8, 0x94, 0xbd, 0x80, 0xbc, 0x6f, 0xbd,
    0xd0, 0xc4, 0x50, 0x3d, 0x5b, 0x4f, 0xa5, 0x3e, 0x27, 0x16,
    0x0e, 0xbf, 0x9a, 0x0d, 0x3d, 0xbc, 0x7b, 0x09, 0x90, 0xbf,
    0x01, 0x50, 0xd5, 0x3e, 0x16, 0x2e, 0x5e, 0x3e, 0x60, 0xb0,
    0xaa, 0x3c, 0x80, 0xc6, 0xab, 0xbd, 0x28, 0x0b, 0x29, 0xbe,
    0x63, 0xa0, 0x50, 0xbf, 0x6c, 0x0f, 0x86, 0xbe, 0x58, 0x34,
    0x25, 0xbd, 0x56, 0x0a, 0x7d, 0xbe, 0x6d, 0x0d, 0xc6, 0x3e,
    0x6d, 0x7f, 0xc0, 0x3e, 0xf2, 0x6c, 0xa6, 0xbe, 0x9c, 0x0b,
    0xa6, 0xbe, 0x26, 0xa0, 0x2b, 0xbf, 0xf4, 0xb0, 0xde, 0xbc,
    0x06, 0x44, 0x11, 0xbe, 0x8e, 0xcd, 0x4f, 0x3e, 0x42, 0x13,
    0x62, 0xbe, 0x14, 0x8f, 0x34, 0xbe, 0xe0, 0xa6, 0x4a, 0x3c,
    0xa0, 0xdb, 0x22, 0xbe, 0xba, 0xf9, 0x80, 0x3e, 0x87, 0xf6,
    0x9b, 0xbe, 0x28, 0xb5, 0x01, 0x3d, 0xdf, 0x51, 0xe0, 0xbc,
    0x25, 0x78, 0x81, 0xbe, 0x3e, 0x7e, 0x90, 0xbe, 0xe4, 0x5f,
    0x60, 0xbe, 0x47, 0xf6, 0xc3, 0x3e, 0x43, 0x3a, 0x06, 0x3e,
    0xe0, 0x08, 0xfd, 0xbc, 0x0c, 0x6a, 0xce, 0xbe, 0x18, 0x53,
    0xf9, 0xbd, 0xec, 0x78, 0xea, 0xbd, 0xd5, 0x02, 0x8a, 0xbe,
    0xf8, 0xb8, 0x10, 0xbe, 0xa0, 0x2b, 0xb7, 0xbc, 0xde, 0xf9,
    0x48, 0x3e, 0x5e, 0x95, 0x36, 0xbe, 0x87, 0x99, 0xb8, 0x3e,
    0x80, 0x9a, 0xda, 0x3b, 0x7b, 0x5d, 0x5d, 0xbe, 0xeb, 0x7a,
    0xa8, 0x3e, 0x64, 0xdd, 0xab, 0xbe, 0x70, 0x18, 0xce, 0xbc,
    0xe0, 0xe0, 0x7a, 0x3d, 0x2d, 0x0b, 0x64, 0xbe, 0x15, 0x63,
    0xb1, 0x3e, 0x23, 0xbe, 0xcd, 0x3e, 0x01, 0x7f, 0xb9, 0x3e,
    0x89, 0x11, 0xd7, 0xbe, 0x80, 0x6a, 0x03, 0xbd, 0x56, 0x7a,
    0x59, 0x3e, 0x3a, 0x1e, 0x9d, 0xbe, 0xf3, 0xf9, 0x8f, 0x3e,
    0x38, 0x68, 0x10, 0xbe, 0xdf, 0xfe, 0xda, 0xbe, 0x00, 0xec,
    0x7d, 0x3b, 0xd8, 0xb8, 0x47, 0x3d, 0xe0, 0x79, 0x18, 0x3c,
    0xcc, 0x4c, 0xfb, 0x3d, 0xf4, 0x4e, 0xbb, 0x3e, 0xf1, 0xef,
    0x59, 0xbe, 0xb2, 0x81, 0x2f, 0x3e, 0x76, 0x39, 0x5a, 0x3e,
    0x82, 0xa5, 0xbb, 0xbe, 0x40, 0xfb, 0xc4, 0xbd, 0xae, 0xab,
    0xbe, 0xbe, 0xac, 0x53, 0x9a, 0xbe, 0x63, 0xe4, 0x9a, 0x3e,
    0x54, 0xb0, 0xfe, 0x3d, 0x99, 0x50, 0xcb, 0x3e, 0x4e, 0x3f,
    0xca, 0x3e, 0x56, 0xb6, 0x76, 0x3e, 0x18, 0x62, 0x67, 0x3d,
    0x36, 0x3f, 0x52, 0x3e, 0x62, 0x82, 0xb4, 0xbe, 0x54, 0x4a,
    0x61, 0x3c, 0xeb, 0x04, 0xdd, 0xbe, 0xa5, 0x8a, 0x22, 0x3f,
    0x84, 0xe7, 0xd2, 0xbe, 0x28, 0x37, 0x47, 0x3d, 0x38, 0x2a,
    0x79, 0x3d, 0x00, 0xf8, 0x9e, 0x39, 0xdc, 0x0f, 0xef, 0x3d,
    0x28, 0x51, 0x4c, 0x3d, 0xf3, 0x60, 0x26, 0xbf, 0x66, 0xc8,
    0x5b, 0xbe, 0x04, 0x02, 0xde, 0xbe, 0x6e, 0x0e, 0x3f, 0x3e,
    0x00, 0x6c, 0xaa, 0x3c, 0x2f, 0x34, 0xdb, 0x3e, 0x16, 0x8f,
    0x15, 0x3e, 0x33, 0x3d, 0xd4, 0xbd, 0xe8, 0xd6, 0xcd, 0x3e,
    0xeb, 0xca, 0x32, 0xbf, 0x1d, 0xe7, 0xc6, 0xbe, 0x16, 0xb9,
    0x64, 0xbe, 0x62, 0x75, 0x53, 0x3e, 0x1b, 0xf9, 0x8a, 0x3e,
    0x3c, 0xe5, 0xc4, 0x3d, 0x55, 0xe3, 0x9d, 0x3e, 0x68, 0x55,
    0xbc, 0xbe, 0x05, 0xe2, 0xcd, 0xbe, 0x88, 0xa2, 0x8f, 0xbd,
    0xef, 0xc6, 0x8a, 0x3e, 0x28, 0xf8, 0xb3, 0xbe, 0xe8, 0x95,
    0x31, 0x3d, 0x2d, 0xcb, 0xd4, 0x3e, 0x79, 0x32, 0x9e, 0x3e,
    0x16, 0xab, 0x6a, 0x3e, 0x0a, 0xae, 0x4f, 0x3e, 0x67, 0xa5,
    0xb4, 0x3e, 0xc7, 0xd4, 0xaf, 0x3e, 0x44, 0xc0, 0xb7, 0xbe,
    0x00, 0xf8, 0xb9, 0x3b, 0xf8, 0xff, 0x05, 0xbe, 0x27, 0x97,
    0xb2, 0x3e, 0xb0, 0xd2, 0x98, 0xbe, 0x32, 0x0e, 0x11, 0xbe,
    0x13, 0xdd, 0xb0, 0x3e, 0x8e, 0x4c, 0x90, 0xbe, 0x50, 0x2e,
    0x03, 0x3d, 0x7c, 0x2f, 0x94, 0x3d, 0xff, 0xd8, 0xc3, 0x3e,
    0xe1, 0x87, 0x0d, 0x3e, 0x3c, 0x93, 0xfe, 0xbd, 0x5d, 0x3f,
    0x5f, 0x3d, 0xc7, 0x06, 0xbd, 0x3e, 0xfa, 0x1e, 0x38, 0x3e,
    0x37, 0x1c, 0xa6, 0x3e, 0x81, 0x15, 0x8f, 0x3e, 0xac, 0x2e,
    0xb3, 0xbe, 0x20, 0xbe, 0x68, 0xbd, 0x04, 0x80, 0xd0, 0xbd,
    0x7c, 0xb1, 0x99, 0x3d, 0xbe, 0x93, 0x12, 0x3e, 0x21, 0xa3,
    0xdb, 0x3e, 0x53, 0x8f, 0x99, 0x3e, 0x4a, 0x7b, 0x1e, 0x3e,
    0xa8, 0x6f, 0xce, 0xbe, 0x29, 0xb3, 0x81, 0x3e, 0x49, 0xee,
    0xa2, 0xbe, 0xa0, 0x73, 0x1e, 0xbe, 0x70, 0x9d, 0x84, 0xbe,
    0xad, 0x1b, 0xa9, 0xbe, 0xe5, 0x0b, 0xdc, 0xbe, 0x60, 0x66,
    0x49, 0xbc, 0xb8, 0x4d, 0xb9, 0xbe, 0xed, 0x02, 0xd8, 0x3d,
    0x3d, 0xfd, 0xe1, 0xbd, 0x82, 0xc8, 0x83, 0xbe, 0xa0, 0xbf,
    0xb1, 0xbe, 0x9b, 0x22, 0xc8, 0x3e, 0x98, 0x62, 0xac, 0xbd,
    0x5a, 0x1b, 0x5b, 0x3e, 0xd0, 0x69, 0x81, 0xbe, 0x8d, 0xd5,
    0x4a, 0x3e, 0xbc, 0x59, 0xc4, 0x3d, 0x68, 0x8a, 0x9d, 0x3c,
    0x5b, 0x4d, 0xbf, 0x3e, 0x60, 0xe1, 0x74, 0xbc, 0x89, 0x5b,
    0xc3, 0x3e, 0x5b, 0x09, 0x88, 0x3e, 0x73, 0xf1, 0xac, 0x3e,
    0x50, 0xe8, 0x8e, 0x3e, 0xc3, 0xa5, 0x68, 0xba, 0x5d, 0xdd,
    0x96, 0xbe, 0xe8, 0x3a, 0xb5, 0xbd, 0x3a, 0x1d, 0xb5, 0xbe,
    0x7b, 0xfc, 0x86, 0x3e, 0x01, 0xc7, 0x80, 0x3e, 0x10, 0x03,
    0x1e, 0xbd, 0xeb, 0x56, 0x12, 0xbe, 0xd4, 0x2b, 0x41, 0xbd,
    0x07, 0x56, 0xc9, 0xbe, 0x74, 0x9c, 0xac, 0x3d, 0x82, 0xe2,
    0xab, 0xbe, 0x30, 0x8d, 0x98, 0x3c, 0xf0, 0xd0, 0x33, 0xbd,
    0x9d, 0x81, 0xad, 0x3e, 0xaf, 0x38, 0x75, 0xbe, 0xba, 0x15,
    0x1b, 0xbf, 0x39, 0xae, 0xb1, 0x3e, 0x9f, 0xe2, 0x39, 0xbf,
    0x1c, 0x9e, 0x1f, 0xbe, 0x30, 0x6c, 0xa8, 0x3c, 0xad, 0xed,
    0xc8, 0x3e, 0x00, 0x1f, 0x5c, 0xbe, 0xae, 0x08, 0xb5, 0xbc,
    0x2c, 0xb2, 0x20, 0x3c, 0xa3, 0x0a, 0xbb, 0x3e, 0x8c, 0x29,
    0xe3, 0x3d, 0xb0, 0x35, 0xb1, 0x3c, 0xda, 0xde, 0xc2, 0xbe,
    0xf3, 0x86, 0x73, 0xbe, 0x69, 0x33, 0x7c, 0xbe, 0xee, 0x53,
    0x80, 0x3e, 0xd3, 0x87, 0xc8, 0x3e, 0xfc, 0x3d, 0x94, 0x3d,
    0xbc, 0xfc, 0x08, 0x3f, 0x62, 0xe9, 0xd5, 0xbe, 0x41, 0xe0,
    0xc9, 0x3e, 0x80, 0xe5, 0xb6, 0xbd, 0xa4, 0x41, 0xef, 0x3d,
    0xc4, 0xc4, 0x74, 0x3d, 0xea, 0x51, 0x87, 0xbe, 0x1e, 0x7e,
    0xa4, 0xbe, 0xcf, 0x5a, 0xc0, 0x3e, 0x94, 0x42, 0xb6, 0xbe,
    0xaf, 0xe1, 0x80, 0x3e, 0xc3, 0x63, 0xc1, 0xbe, 0x77, 0xf2,
    0x95, 0x3e, 0x9e, 0x3e, 0x1e, 0x3e, 0x8b, 0xca, 0xbd, 0x3e,
    0x41, 0x69, 0xbb, 0x3e, 0x5b, 0xb7, 0x72, 0x3e, 0xcc, 0x14,
    0x9d, 0x3d, 0xc0, 0xbd, 0x90, 0x3b, 0x6c, 0xbe, 0xb1, 0x3d,
    0x44, 0x29, 0xfc, 0xbd, 0xcb, 0x39, 0x4c, 0x3d, 0x91, 0x70,
    0xa7, 0xbe, 0x3a, 0x20, 0x49, 0x3f, 0x55, 0x35, 0x9c, 0xbe,
    0xa0, 0xf7, 0x08, 0xbc, 0x15, 0xb8, 0xba, 0x3e, 0xdc, 0x17,
    0x9c, 0x3d, 0x28, 0x43, 0x24, 0x3d, 0x2a, 0xa1, 0xd4, 0x3b,
    0xbb, 0x7b, 0xd2, 0x3e, 0xe5, 0xfe, 0x96, 0x3e, 0x4b, 0x31,
    0xfd, 0x3e, 0xce, 0x55, 0xa1, 0xbe, 0x91, 0xef, 0xbb, 0x3e,
    0x46, 0xd5, 0x04, 0xbe, 0x71, 0x69, 0xa1, 0x3e, 0xaf, 0x85,
    0x28, 0x3e, 0x81, 0xe6, 0xfe, 0x3d, 0xce, 0x0e, 0x26, 0x3e,
    0x9f, 0x6a, 0xcb, 0xbe, 0xcf, 0x69, 0xc6, 0x3e, 0xde, 0x0d,
    0x76, 0x3e, 0xf2, 0xcf, 0x73, 0x3e, 0x70, 0x48, 0xa5, 0x3e,
    0xf5, 0x9a, 0xed, 0xbd, 0x00, 0x00, 0x00, 0x00, 0xb3, 0x11,
    0xb9, 0xbb, 0x66, 0xd8, 0x1d, 0xbf, 0x12, 0xb2, 0xd0, 0x3e,
    0x5d, 0x66, 0x4f, 0xbd, 0xe5, 0xe1, 0x54, 0xbe, 0x00, 0x00,
    0x00, 0x00, 0xcd, 0xdb, 0xd9, 0xbd, 0x20, 0x4d, 0x8b, 0xbd,
    0x22, 0xce, 0x08, 0x3f, 0x6b, 0xb0, 0xbf, 0xbd, 0x33, 0xb0,
    0x0b, 0xbf, 0xf2, 0x7a, 0x42, 0xbe, 0x86, 0xd4, 0x5c, 0x3f,
    0x35, 0x19, 0x91, 0xbf, 0x34, 0xba, 0xea, 0xba, 0x30, 0x59,
    0x18, 0xbd, 0x9b, 0xe7, 0xe8, 0xbe, 0xc1, 0x61, 0xf0,
    0x3f, 0xe0, 0xf8, 0x55, 0x3f, 0x66, 0x44, 0xb5, 0x3e,
    0x8e, 0x4a, 0xa4, 0xbd, 0xd8, 0x07, 0x3a, 0xbe, 0x83,
    0x27, 0x8b, 0xbc, 0x89, 0xee, 0x20, 0xbb, 0xf5, 0x96,
    0x3e, 0xbf, 0x76, 0x47, 0x02, 0xbe, 0x11, 0x97, 0xe4,
    0x3f, 0xb2, 0x28, 0x26, 0xbf, 0xf5, 0x26, 0x13, 0xbd
  };

  return AI_HANDLE_PTR(s_sine_model_weights);

}

