#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>

#define PRINT(s,c)  printf("%s : %d, %d, %d\n", s, c.r, c.g, c.b);
#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#define MIN(a,b)    ((a) < (b) ? (a) : (b))

typedef struct {
  int r, g, b;
} Color;

Color ceil_color(Color const *c);
Color floor_color(Color const *c);


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage: %s /path/to/image\n", argv[0]);
    printf("\n  Generate a set of colors from an image");
    printf("\n  to help theme your desktop environment.\n");
    return EXIT_FAILURE;
  }

  int w, h, n;
  unsigned char *data = stbi_load(argv[1], &w, &h, &n, 3);

  if (data == NULL) {
    printf("error: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  Color sum = { 0 };

  int const area = w * h;
  int const size = area * 3;

  for (unsigned char const *p = data; p != &data[size]; p += 3) {
    sum.r += *(p);
    sum.g += *(p + 1);
    sum.b += *(p + 2);
  }

  Color const average = {
    .r = sum.r / area,
    .g = sum.g / area,
    .b = sum.b / area
  };

  Color const ceil = ceil_color(&average);
  Color const floor = floor_color(&average);

  PRINT("average", average);
  PRINT("ceiling", ceil);
  PRINT("floor", floor);
  return EXIT_SUCCESS;
}


Color ceil_color(Color const *c)
{
  int max = MAX(MAX(c->r, c->g), c->b);

  Color color = {
    .r = 255 - max + c->r,
    .g = 255 - max + c->g,
    .b = 255 - max + c->b
  };

  return color;
}


Color floor_color(Color const *c)
{
  int min = MIN(MIN(c->r, c->g), c->b);

  Color color = {
    .r = c->r - min,
    .g = c->g - min,
    .b = c->b - min
  };

  return color;
}
