#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // perform padding for channel coordinate
    if (c < 0) {
        c = 0;
    }
    else if (c >= im.c) {
        c = im.c - 1;
    }
    // perform padding for height coordinate
    if (y < 0) {
        y = 0;
    }
    else if (y >= im.h) {
        y = im.h - 1;
    }
    // perform padding for width coordinate
    if (x < 0) {
        x = 0;
    }
    else if (x >= im.w) {
        x = im.w - 1;
    }
    return *(im.data + ((c * im.h + y) * im.w + x));
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if (x >= im.w || y >= im.h || c >= im.c) {
        return;
    }
    *(im.data + ((c * im.h + y) * im.w + x)) = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    int x, y, c;
    for (c = 0; c < im.c; ++c) {
        for (y = 0; y < im.h; ++y) {
            for (x = 0; x < im.w; ++x) {
                float pixel = get_pixel(im, x, y, c);
                set_pixel(copy, x, y, c, pixel);
            }
        }
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    int x, y;
    for (y = 0; y < im.h; ++y) {
        for (x = 0; x < im.w; ++x) {
            // get all three colors
            float r = get_pixel(im, x, y, 0);
            float g = get_pixel(im, x, y, 1);
            float b = get_pixel(im, x, y, 2);
            // calculate new value
            float val = (float) (0.299 * r + 0.587 * g + 0.114 * b);
            set_pixel(gray, x, y, 0, val);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    int x, y;
    for (y = 0; y < im.h; ++y) {
        for (x = 0; x < im.w; ++x) {
            // get current value
            float val = get_pixel(im, x, y, c);
            // shift value by v
            val += v;
            // set pixel to new value
            set_pixel(im, x, y, c, val);
        }
    }
}

void clamp_image(image im)
{
    int x, y, c;
    for (c = 0; c < im.c; ++c) {
        for (y = 0; y < im.h; ++y) {
            for (x = 0; x < im.w; ++x) {
                float val = get_pixel(im, x, y, c);
                if (val < 0) {
                    val = 0;
                }
                else if (val > 1) {
                    val = 1;
                }
                set_pixel(im, x, y, c, val);
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    int x, y;
    for (y = 0; y < im.h; ++y) {
        for (x = 0; x < im.w; ++x) {
            // get all three colors
            float r = get_pixel(im, x, y, 0);
            float g = get_pixel(im, x, y, 1);
            float b = get_pixel(im, x, y, 2);
            // calculate value
            float value = three_way_max(r, g, b);
            // calculate min, c, and then saturation
            float min = three_way_min(r, g, b);
            float c = value - min;
            float saturation = 0;
            if (value != 0) {
                saturation = c / value;
            }
            // calculate H prime
            float h_prime;
            if (c == 0) {
                h_prime = 0;
            }
            else if (value == r) {
                h_prime = (g - b) / c;
            }
            else if (value == g) {
                h_prime = (b - r) / c + 2;
            }
            else {
                h_prime = (r - g) / c + 4;
            }
            // now we can finally calculate the hue
            float hue;
            if (h_prime < 0) {
                hue = h_prime / 6 + 1;
            }
            else {
                hue = h_prime / 6;
            }
            // assign to channels
            set_pixel(im, x, y, 0, hue);
            set_pixel(im, x, y, 1, saturation);
            set_pixel(im, x, y, 2, value);
        }
    }
}

void hsv_to_rgb(image im)
{
    int x, y;
    for (y = 0; y < im.h; ++y) {
        for (x = 0; x < im.w; ++x) {
            // get hue, saturation and value
            float h = get_pixel(im, x, y, 0);
            float s = get_pixel(im, x, y, 1);
            float v = get_pixel(im, x, y, 2);
            // calculate new hue
            float i = floorf(h * 6);
            float f = h * 6 - i;
            // calculate intermediary values
            float p = v * (1 - s);
            float q = v * (1 - s * f);
            float t = v * (1 - s * (1 - f));
            // calculate r, g, b
            float r, g, b;
            switch ((int) i % 6) {
                case 0: r = v, g = t, b = p; break;
                case 1: r = q, g = v, b = p; break;
                case 2: r = p, g = v, b = t; break;
                case 3: r = p, g = q, b = v; break;
                case 4: r = t, g = p, b = v; break;
                case 5: r = v, g = p, b = q; break;
                default: r = 0, g = 0, b = 0;
            }
            // assign to channels
            set_pixel(im, x, y, 0, r);
            set_pixel(im, x, y, 1, g);
            set_pixel(im, x, y, 2, b);
        }
    }
}
