# SpaceInvaders
This is a game that I had created using the SDL library to "draw" fancy rectangles onto a window.
I only knew C at the time this was written so my language options were limited. Even though it was tough to do, the program runs
beautifully and with very little lag. 

rgb[0] = 127 * cos(128 + i + (3.14159 * 2)) + 128;
rgb[1] = 127 * sin(128 + i + (3.14159 * 2)) + 128;
rgb[2] = 127 * cos(128 + i + 3.14159) + 128;

These 3 functions above will span the primary colors in the RGB color space based on input i. 
Offset of 128 within the cos/sin functions determine which color will display at i = 0.

