#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    return get_pixel(im, (int) roundf(x), (int) roundf(y), c);
}

image nn_resize(image im, int w, int h)
{
    image resize_im = make_image(w, h, im.c);
    float a_x = im.w / (float) w;
    float b_x = (float) (-0.5 + 0.5 * a_x);
    float a_y = im.h / (float) h;
    float b_y = (float) (-0.5 + 0.5 * a_y);
    int x, y, c;
    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            // map to old coordinate system
            float old_x = a_x * x + b_x;
            float old_y = a_y * y + b_y;
            for (c = 0; c < im.c; ++c) {
                // nearest neighbour interpolation
                float val = nn_interpolate(im, old_x, old_y, c);
                set_pixel(resize_im, x, y, c, val);
            }
        }
    }
    return resize_im;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}

