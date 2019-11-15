#include "lcd_ui.h"
const uint8_t UI_WELCOME [] PROGMEM = {1, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 3, 128, 0, 0, 0, 0, 0, 0, 0, 0, 224, 1, 192, 0, 0, 0, 0, 0, 0, 0, 0, 192, 0, 192, 0, 15, 128, 0, 0, 0, 0, 0, 192, 0, 192, 0, 8, 64, 0, 0, 0, 0, 0, 192, 0, 195, 128, 8, 32, 0, 2, 0, 0, 0, 192, 0, 79, 224, 8, 35, 194, 23, 131, 139, 0, 192, 0, 92, 248, 8, 68, 34, 18, 4, 76, 0, 192, 0, 112, 62, 15, 132, 34, 18, 8, 72, 0, 192, 0, 192, 15, 8, 132, 34, 18, 15, 200, 0, 192, 0, 0, 3, 8, 68, 34, 18, 8, 8, 0, 224, 4, 0, 1, 8, 68, 34, 18, 8, 8, 0, 112, 14, 0, 1, 8, 36, 34, 50, 4, 8, 0, 56, 14, 0, 3, 8, 19, 193, 209, 131, 200, 0, 7, 63, 128, 3, 0, 0, 0, 0, 0, 0, 0, 7, 63, 128, 3, 0, 0, 0, 0, 0, 0, 0, 24, 14, 0, 1, 0, 0, 0, 0, 0, 0, 0, 112, 14, 0, 1, 0, 0, 0, 0, 48, 14, 0, 192, 4, 0, 1, 0, 0, 0, 9, 16, 18, 0, 128, 0, 0, 3, 0, 0, 0, 5, 16, 4, 0, 128, 0, 192, 15, 0, 0, 0, 6, 16, 18, 0, 128, 0, 240, 62, 0, 0, 0, 2, 56, 142, 0, 128, 0, 156, 248, 0, 0, 0, 0, 0, 0, 0, 128, 0, 207, 224, 0, 0, 0, 0, 0, 0, 0, 128, 0, 195, 128, 0, 0, 0, 0, 0, 0, 0, 128, 0, 192, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 192, 0, 0, 0, 0, 0, 0, 0, 0, 192, 1, 192, 0, 0, 0, 0, 0, 0, 0, 0, 240, 7, 128, 0, 0, 0, 0, 0, 32, 0, 0, 124, 15, 0, 0, 28, 0, 0, 0, 32, 112, 0, 30, 60, 0, 0, 20, 234, 187, 156, 224, 84, 128, 7, 248, 0, 0, 29, 47, 58, 29, 32, 98, 128, 1, 224, 0, 0, 17, 47, 34, 17, 32, 83, 0, 0, 0, 0, 0, 16, 229, 58, 28, 224, 113, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8, 33, 4, 7, 195, 226, 15, 204, 19, 255, 224, 4, 97, 10, 8, 36, 18, 8, 12, 18, 1, 0, 4, 81, 10, 16, 8, 2, 8, 10, 18, 1, 0, 4, 82, 9, 16, 8, 2, 8, 9, 18, 1, 0, 4, 146, 17, 16, 232, 114, 15, 137, 147, 225, 0, 2, 138, 17, 16, 40, 18, 8, 8, 146, 1, 0, 2, 140, 63, 144, 40, 18, 8, 8, 82, 1, 0, 3, 12, 32, 136, 36, 18, 8, 8, 50, 1, 0, 1, 12, 64, 71, 195, 227, 239, 200, 51, 241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_RESET [] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 112, 0, 0, 4, 0, 0, 0, 8, 143, 34, 32, 72, 0, 0, 4, 0, 144, 0, 8, 144, 146, 64, 73, 76, 99, 7, 37, 249, 142, 12, 144, 149, 64, 73, 146, 132, 4, 164, 146, 73, 10, 144, 149, 64, 113, 30, 66, 4, 164, 146, 73, 10, 144, 149, 64, 65, 16, 33, 4, 164, 146, 73, 9, 144, 149, 64, 65, 16, 33, 4, 164, 146, 73, 8, 144, 136, 128, 65, 14, 198, 7, 28, 217, 137, 8, 143, 8, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 254, 0, 0, 0, 0, 16, 0, 0, 0, 0, 252, 31, 128, 0, 0, 0, 16, 0, 0, 0, 1, 240, 7, 192, 32, 0, 0, 16, 0, 0, 0, 3, 192, 1, 224, 120, 240, 3, 144, 113, 225, 96, 3, 128, 0, 224, 33, 8, 4, 16, 136, 17, 128, 7, 0, 0, 112, 33, 8, 8, 17, 8, 17, 0, 15, 0, 0, 120, 33, 8, 8, 17, 248, 241, 0, 14, 0, 0, 56, 33, 8, 8, 17, 1, 17, 0, 14, 0, 0, 56, 33, 8, 8, 17, 1, 17, 0, 12, 1, 192, 24, 33, 8, 4, 16, 129, 49, 0, 12, 3, 224, 24, 24, 240, 3, 204, 120, 209, 0, 30, 3, 224, 24, 0, 0, 0, 64, 0, 0, 0, 255, 195, 224, 24, 0, 2, 16, 0, 0, 0, 0, 127, 129, 192, 24, 120, 231, 188, 69, 193, 225, 224, 63, 0, 0, 56, 129, 18, 16, 70, 34, 34, 0, 30, 0, 0, 56, 130, 18, 16, 68, 36, 34, 0, 12, 0, 0, 120, 99, 242, 16, 68, 36, 33, 128, 0, 0, 0, 112, 18, 2, 16, 68, 36, 32, 64, 0, 0, 0, 224, 10, 2, 16, 68, 36, 32, 32, 0, 0, 1, 224, 9, 2, 16, 68, 36, 96, 32, 0, 48, 7, 192, 240, 241, 140, 68, 35, 163, 192, 0, 124, 31, 128, 0, 0, 0, 0, 0, 32, 0, 0, 63, 254, 0, 0, 0, 0, 0, 0, 32, 0, 0, 31, 252, 0, 0, 0, 0, 0, 3, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_CONN_APP [] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 115, 136, 145, 60, 255, 72, 142, 0, 0, 0, 0, 132, 76, 153, 33, 4, 76, 144, 0, 0, 0, 0, 132, 74, 149, 33, 4, 74, 144, 0, 0, 0, 0, 132, 74, 149, 61, 4, 74, 144, 0, 0, 1, 0, 132, 73, 147, 33, 4, 73, 150, 0, 0, 1, 128, 132, 72, 145, 33, 4, 72, 146, 0, 0, 1, 192, 115, 136, 145, 60, 228, 72, 142, 0, 0, 1, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 248, 0, 0, 0, 0, 0, 0, 0, 0, 1, 255, 240, 0, 0, 0, 0, 0, 0, 0, 0, 3, 225, 224, 0, 248, 64, 126, 8, 30, 31, 128, 7, 129, 192, 0, 132, 64, 64, 8, 33, 16, 0, 15, 1, 128, 0, 130, 64, 64, 20, 32, 16, 0, 14, 1, 0, 0, 130, 64, 64, 20, 32, 16, 0, 28, 0, 0, 96, 130, 64, 64, 20, 16, 16, 0, 28, 0, 0, 224, 132, 64, 126, 34, 12, 31, 128, 56, 0, 0, 112, 248, 64, 64, 34, 2, 16, 0, 56, 0, 0, 112, 128, 64, 64, 62, 1, 16, 0, 56, 0, 0, 112, 128, 64, 64, 65, 1, 16, 0, 56, 0, 0, 112, 128, 64, 64, 65, 33, 16, 0, 56, 0, 0, 112, 128, 126, 126, 128, 158, 31, 128, 56, 0, 0, 112, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 112, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 112, 0, 0, 0, 0, 0, 0, 0, 28, 0, 0, 224, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 224, 132, 32, 64, 159, 192, 0, 0, 0, 2, 1, 192, 132, 32, 64, 130, 0, 0, 0, 0, 6, 3, 192, 138, 32, 160, 130, 0, 0, 0, 0, 14, 7, 128, 74, 64, 160, 130, 0, 0, 0, 0, 30, 31, 0, 74, 64, 160, 130, 0, 0, 0, 0, 63, 254, 0, 81, 65, 16, 130, 0, 0, 0, 0, 127, 248, 0, 81, 65, 16, 130, 0, 0, 0, 0, 127, 224, 0, 81, 65, 240, 130, 0, 0, 0, 0, 62, 0, 0, 32, 130, 8, 130, 0, 0, 0, 0, 30, 0, 0, 32, 130, 8, 130, 0, 0, 0, 0, 14, 0, 0, 32, 132, 4, 130, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_CONN_CLOUD [] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 113, 20, 79, 59, 234, 35, 128, 0, 0, 0, 32, 137, 150, 72, 64, 139, 36, 0, 0, 0, 0, 32, 137, 85, 72, 64, 138, 164, 0, 0, 0, 0, 32, 137, 85, 79, 64, 138, 164, 0, 0, 0, 0, 32, 137, 52, 200, 64, 138, 101, 128, 0, 0, 0, 32, 137, 20, 72, 64, 138, 36, 128, 63, 128, 0, 28, 113, 20, 79, 56, 138, 35, 128, 255, 224, 0, 0, 0, 0, 0, 0, 0, 0, 1, 224, 240, 0, 0, 0, 0, 0, 0, 0, 0, 3, 192, 120, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 31, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 112, 0, 15, 0, 62, 60, 7, 32, 241, 9, 224, 224, 0, 15, 192, 8, 36, 8, 32, 145, 9, 16, 192, 0, 1, 224, 8, 66, 16, 33, 9, 9, 9, 192, 0, 0, 96, 8, 66, 16, 33, 9, 9, 9, 128, 0, 0, 112, 8, 66, 16, 33, 9, 9, 9, 128, 0, 0, 48, 8, 66, 16, 33, 9, 9, 9, 192, 0, 0, 48, 8, 66, 16, 33, 9, 9, 8, 192, 0, 0, 112, 8, 36, 8, 32, 145, 9, 16, 224, 0, 0, 96, 8, 60, 7, 62, 240, 241, 224, 120, 0, 1, 224, 0, 0, 0, 0, 0, 0, 0, 63, 255, 255, 192, 0, 0, 0, 0, 0, 0, 0, 15, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_ERROR [] PROGMEM = {112, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 124, 14, 34, 14, 136, 71, 32, 0, 0, 62, 0, 248, 17, 34, 16, 200, 68, 160, 0, 0, 31, 1, 240, 17, 34, 16, 168, 164, 160, 0, 0, 15, 131, 224, 17, 62, 12, 168, 167, 32, 0, 0, 7, 199, 192, 17, 34, 2, 152, 228, 32, 0, 0, 3, 239, 128, 17, 34, 2, 136, 164, 0, 0, 0, 1, 255, 0, 14, 34, 28, 137, 20, 32, 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 239, 128, 0, 0, 0, 0, 0, 0, 0, 0, 7, 199, 192, 0, 0, 0, 0, 0, 0, 0, 0, 15, 131, 224, 0, 0, 0, 0, 0, 0, 0, 0, 31, 1, 240, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 248, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 124, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 112, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_CONNECTED [] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 192, 0, 0, 0, 0, 0, 8, 0, 0, 64, 4, 0, 0, 0, 0, 4, 0, 8, 0, 0, 224, 8, 14, 44, 88, 112, 239, 56, 120, 0, 0, 224, 8, 17, 50, 100, 137, 4, 68, 136, 0, 1, 224, 8, 17, 34, 68, 137, 4, 68, 136, 0, 3, 192, 8, 17, 34, 68, 249, 4, 124, 136, 0, 7, 128, 8, 17, 34, 68, 129, 4, 64, 136, 0, 15, 0, 4, 17, 34, 68, 129, 4, 64, 152, 0, 30, 0, 3, 206, 34, 68, 120, 227, 60, 104, 0, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 224, 0, 0, 0, 0, 0, 0, 0, 0, 128, 3, 192, 0, 0, 0, 0, 0, 0, 0, 1, 192, 7, 128, 0, 0, 0, 0, 0, 0, 0, 3, 224, 15, 0, 0, 0, 0, 0, 0, 0, 0, 1, 224, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_CONN_WIFI [] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 113, 20, 79, 59, 234, 35, 128, 0, 0, 0, 32, 137, 150, 72, 64, 139, 36, 0, 0, 0, 0, 32, 137, 85, 72, 64, 138, 164, 0, 0, 0, 0, 32, 137, 85, 79, 64, 138, 164, 0, 0, 0, 0, 32, 137, 52, 200, 64, 138, 101, 128, 0, 0, 0, 32, 137, 20, 72, 64, 138, 36, 128, 0, 0, 0, 28, 113, 20, 79, 56, 138, 35, 129, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 15, 255, 248, 0, 0, 0, 0, 0, 0, 0, 0, 31, 255, 252, 0, 0, 0, 0, 0, 0, 0, 0, 126, 0, 63, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 15, 128, 0, 0, 0, 0, 0, 0, 0, 224, 0, 3, 128, 0, 0, 0, 0, 0, 0, 0, 64, 8, 1, 0, 31, 199, 128, 66, 20, 249, 0, 0, 255, 128, 0, 2, 8, 64, 34, 36, 129, 0, 3, 255, 224, 0, 2, 16, 32, 34, 36, 129, 0, 7, 227, 240, 0, 2, 16, 32, 37, 36, 129, 0, 7, 0, 112, 0, 2, 16, 32, 37, 36, 249, 0, 2, 0, 32, 0, 2, 16, 32, 21, 68, 129, 0, 0, 0, 0, 0, 2, 16, 32, 21, 68, 129, 0, 0, 28, 0, 0, 2, 16, 32, 21, 68, 129, 0, 0, 127, 0, 0, 2, 8, 64, 8, 132, 129, 0, 0, 62, 0, 0, 2, 7, 128, 8, 132, 129, 0, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UI_GET_APP [] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 3, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 7, 255, 224, 3, 207, 207, 224, 32, 248, 248, 0, 7, 255, 224, 4, 40, 1, 0, 32, 132, 132, 0, 15, 255, 240, 8, 8, 1, 0, 80, 130, 130, 0, 15, 255, 240, 8, 8, 1, 0, 80, 130, 130, 0, 14, 0, 112, 8, 8, 1, 0, 80, 130, 130, 0, 14, 0, 112, 8, 15, 193, 0, 136, 132, 132, 0, 14, 0, 112, 8, 232, 1, 0, 136, 248, 248, 0, 14, 0, 112, 8, 40, 1, 0, 248, 128, 128, 0, 14, 0, 112, 8, 40, 1, 1, 4, 128, 128, 0, 14, 0, 112, 4, 40, 1, 1, 4, 128, 128, 0, 14, 0, 112, 3, 239, 193, 2, 2, 128, 128, 0, 14, 0, 112, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 112, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 112, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 112, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 112, 1, 129, 2, 8, 56, 0, 8, 0, 14, 0, 112, 2, 129, 2, 8, 36, 0, 0, 0, 14, 0, 112, 2, 130, 142, 56, 34, 50, 40, 198, 14, 0, 112, 3, 2, 146, 72, 34, 73, 73, 9, 14, 0, 112, 5, 36, 146, 72, 34, 121, 73, 15, 14, 0, 112, 4, 199, 146, 72, 34, 65, 73, 8, 15, 255, 240, 4, 68, 82, 72, 36, 64, 137, 8, 15, 255, 240, 3, 168, 78, 56, 56, 56, 136, 199, 7, 255, 224, 0, 0, 0, 0, 0, 0, 0, 0, 7, 255, 224, 0, 0, 0, 0, 0, 0, 0, 0, 3, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
