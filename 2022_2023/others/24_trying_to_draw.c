#include <stdio.h>

#define DRAWING_DIM 1080

#define SQUARE(x) (x) * (x)

#define CENTER (DRAWING_DIM / 2)
#define RADIUS_SQUARE (SQUARE(CENTER))

typedef struct {
  unsigned char red, green, blue;
} color_t;

int main(void) {
  FILE* drawing;
  unsigned int pX, pY, total_pixel, circle;
  color_t grid[DRAWING_DIM][DRAWING_DIM];
  unsigned char pixel_byte_y, pixel_byte_x;
  if ((drawing = fopen("drawing.ppm", "w"))) {
    fprintf(drawing, "P6\n");
    fprintf(drawing, "%u %u\n", DRAWING_DIM, DRAWING_DIM);
    fprintf(drawing, "%d\n", 0xff);

    for (pY = 0; pY < DRAWING_DIM; pY++) {
      pixel_byte_y = (pY * 0xff / DRAWING_DIM);
      for (pX = 0; pX < DRAWING_DIM; pX++) {
        pixel_byte_x = (pX * 0xff / DRAWING_DIM);
        circle = SQUARE(pX - CENTER) + SQUARE(pY - CENTER);
        if (circle < RADIUS_SQUARE) {
          grid[pX][pY].red = pixel_byte_x;
          grid[pX][pY].green = pixel_byte_y;
          grid[pX][pY].blue = 0x80;
        } else {
          grid[pX][pY].red = 0xff - pixel_byte_x;
          grid[pX][pY].green = 0xff - pixel_byte_y;
          grid[pX][pY].blue = 0x80;
        }
      }
    }
    total_pixel = DRAWING_DIM * DRAWING_DIM;
    fwrite(grid, sizeof(color_t), total_pixel, drawing);
  }

  return 0;
}
