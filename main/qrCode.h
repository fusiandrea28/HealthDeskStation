/* A dial jpeg file can be converted to a byte array using:

   https://tomeko.net/online_tools/file_to_hex.php?lang=en

   Paste the byte array into a sketch tab "jpeg_name" and add
   two lines at the start with a unique array name:

                const uint8_t  jpeg_name[] PROGMEM = {

   At the end add:

        };

   See example below. Include the tab in the main sketch, e.g.:

        #include "jpeg_name.h"
*/

const uint8_t qrCodepic[] PROGMEM = {
0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 
0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xC8, 0x01, 0x03, 0x00, 0x00, 0x00, 0x97, 0x96, 0x3C, 
0xDD, 0x00, 0x00, 0x00, 0x06, 0x50, 0x4C, 0x54, 0x45, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x55, 
0xC2, 0xD3, 0x7E, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0E, 0xC4, 0x00, 
0x00, 0x0E, 0xC4, 0x01, 0x95, 0x2B, 0x0E, 0x1B, 0x00, 0x00, 0x01, 0xD2, 0x49, 0x44, 0x41, 0x54, 
0x58, 0xC3, 0xED, 0x97, 0x41, 0xAE, 0xC2, 0x30, 0x0C, 0x44, 0x1D, 0x75, 0x91, 0x65, 0x8F, 0x90, 
0x9B, 0xA4, 0x17, 0xAB, 0x54, 0xA4, 0x5E, 0xAC, 0xBD, 0x49, 0x8E, 0x90, 0x65, 0x16, 0x55, 0xFD, 
0x67, 0x0C, 0xB4, 0xC0, 0x1A, 0xCC, 0xE2, 0x13, 0x09, 0x09, 0x78, 0x2C, 0x8C, 0x3D, 0xE3, 0x4C, 
0x45, 0x7E, 0xE7, 0x5F, 0x9D, 0xA4, 0xAA, 0x2D, 0xD4, 0x6E, 0x97, 0x51, 0xDA, 0x98, 0xDA, 0x80, 
0xCF, 0xD5, 0x97, 0xE0, 0xD5, 0xA4, 0xD7, 0x55, 0xB5, 0xE8, 0x25, 0xB5, 0x2C, 0x12, 0x9C, 0x49, 
0xD4, 0x82, 0x82, 0x66, 0xAD, 0xA3, 0xFD, 0x28, 0xE3, 0x47, 0x5F, 0x20, 0x41, 0xB7, 0x01, 0x85, 
0xA1, 0x3C, 0xF9, 0x12, 0x91, 0xFE, 0xC2, 0x96, 0x34, 0xF4, 0xEA, 0x63, 0x84, 0x7F, 0x1C, 0x5F, 
0x67, 0xE9, 0x0A, 0x74, 0x20, 0x2F, 0xF3, 0xF1, 0x20, 0x54, 0x62, 0xEE, 0xE7, 0x15, 0x53, 0x88, 
0x73, 0x79, 0xD5, 0xA8, 0x03, 0xB1, 0x63, 0x3A, 0x98, 0x8A, 0x6E, 0x68, 0xD0, 0xF3, 0x71, 0x20, 
0x89, 0x2E, 0xD8, 0xFB, 0x2D, 0x50, 0x04, 0x80, 0xBB, 0xC4, 0xC5, 0x97, 0x48, 0x54, 0x8D, 0x0B, 
0xC9, 0xAC, 0x71, 0x56, 0xD4, 0x76, 0x57, 0x88, 0x1B, 0x91, 0x80, 0xA1, 0x98, 0x42, 0x14, 0xB5, 
0x09, 0xDE, 0x06, 0x67, 0xA2, 0x6B, 0x89, 0x5C, 0x88, 0x20, 0xBA, 0xA5, 0xB8, 0x9E, 0xF2, 0xF0, 
0x22, 0xA8, 0x0D, 0x43, 0xE9, 0x96, 0x7E, 0x2E, 0x71, 0xB3, 0xAD, 0xBC, 0x7C, 0x82, 0x24, 0xC8, 
0x10, 0x0D, 0x98, 0x00, 0x35, 0x42, 0x89, 0x70, 0x63, 0x76, 0x26, 0xBA, 0x98, 0x18, 0xD7, 0xDA, 
0x95, 0xAB, 0x2D, 0xE2, 0xE1, 0x53, 0x1F, 0x42, 0x25, 0x62, 0xF2, 0x9D, 0x56, 0xD3, 0x01, 0x6A, 
0xA3, 0x2A, 0x5C, 0x89, 0x64, 0x94, 0x27, 0x23, 0xBD, 0x40, 0x35, 0xE4, 0xDE, 0x9D, 0xB4, 0x50, 
0xCC, 0x8D, 0x95, 0x57, 0x04, 0xD6, 0xA3, 0x40, 0x2F, 0xAE, 0x24, 0xC5, 0x9D, 0xB5, 0xDD, 0xDD, 
0x48, 0x85, 0x0C, 0xD5, 0x95, 0x48, 0x5C, 0x39, 0x9F, 0x11, 0x51, 0x44, 0xDB, 0xA4, 0x9C, 0xD6, 
0xFD, 0x78, 0x11, 0x74, 0x07, 0xB5, 0x75, 0x18, 0x91, 0xE0, 0x5E, 0x80, 0x40, 0x0F, 0x07, 0xBF, 
0x95, 0x24, 0x0B, 0x02, 0xB8, 0x00, 0x40, 0x2C, 0x78, 0xD4, 0xD3, 0xA7, 0x3E, 0x84, 0xE1, 0x03, 
0x56, 0x9C, 0x56, 0xEA, 0x60, 0xE6, 0xEE, 0x3D, 0x95, 0xE8, 0x43, 0xB0, 0x6D, 0xCB, 0xCD, 0x8D, 
0xD7, 0x9D, 0x58, 0xCF, 0xD4, 0xE9, 0x43, 0xB8, 0x05, 0x91, 0xC5, 0x36, 0x42, 0x74, 0x47, 0xF5, 
0xCC, 0x21, 0x5E, 0xC4, 0x56, 0x02, 0xF6, 0x01, 0x93, 0x90, 0x05, 0xC3, 0xA7, 0x90, 0xE2, 0x40, 
0x2C, 0x8B, 0x21, 0xF4, 0xE2, 0x6A, 0x80, 0x1B, 0x19, 0xCB, 0xE2, 0x63, 0x4A, 0xF3, 0x20, 0x6C, 
0xD0, 0x00, 0x7F, 0xF4, 0x28, 0x6C, 0x62, 0x6D, 0x47, 0x16, 0xF3, 0x22, 0x6C, 0x49, 0xE6, 0xED, 
0xCC, 0xE1, 0x70, 0x3E, 0x47, 0x4A, 0x7B, 0x3F, 0x09, 0x15, 0x77, 0xF0, 0x54, 0xAE, 0x4B, 0xA7, 
0x3D, 0x3E, 0x67, 0x79, 0x91, 0xE1, 0x76, 0x07, 0x63, 0x0A, 0x41, 0x5F, 0x9E, 0xC0, 0x3E, 0x4F, 
0x6C, 0x0A, 0x30, 0x82, 0x32, 0x09, 0xD1, 0x16, 0x2D, 0x8B, 0x2F, 0xB1, 0xA7, 0x0F, 0x7A, 0x01, 
0x91, 0x73, 0x4C, 0xD8, 0x8D, 0xC7, 0x46, 0x72, 0x22, 0xBF, 0xF3, 0x3B, 0xF2, 0x07, 0x1B, 0x3C, 
0x6A, 0x1E, 0x46, 0x05, 0xAC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 
0x60, 0x82
};