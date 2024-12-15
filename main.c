#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: %s /path/to/image\n", argv[0]);
    return EXIT_FAILURE;
  }

  int w, h, n;
  unsigned char *data = stbi_load(argv[1], &w, &h, &n, 3);

  if (data == NULL) {
    printf("error: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  int const area = w * h;
  int const size = area * 3;

  unsigned r_sum = 0;
  unsigned g_sum = 0;
  unsigned b_sum = 0;

  for (unsigned char const *p = data; p != &data[size]; p += 3) {
    r_sum += *(p);
    g_sum += *(p + 1);
    b_sum += *(p + 2);
  }

  int const r_avg = r_sum / area;
  int const g_avg = g_sum / area;
  int const b_avg = b_sum / area;

  printf("%d, %d, %d\n", r_avg, g_avg, b_avg);
  return EXIT_SUCCESS;
}
