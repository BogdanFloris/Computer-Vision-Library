#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    float divisor = im.h * im.w * im.c;
    int x, y, c;
    for (c = 0; c < im.c; ++c) {
        for (y = 0; y < im.h; ++y) {
            for (x = 0; x < im.w; ++x) {
                float pixel = get_pixel(im, x, y, c);
                pixel /= divisor;
                set_pixel(im, x, y, c, pixel);
            }
        }
    }
}

image make_box_filter(int w)
{
    image box_filter = make_image(w, w, 1);
    int x, y;
    for (y = 0; y < w; ++y) {
        for (x = 0; x < w; ++x) {
            set_pixel(box_filter, x, y, 0, (float) 1 / (w * w));
        }
    }
    return box_filter;
}

image convolve_image(image im, image filter, int preserve)
{
    assert(im.c == filter.c || filter.c == 1);
    return make_image(1,1,1);
}

image make_highpass_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_sharpen_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO
    return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
