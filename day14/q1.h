#include <stdio.h>

#define WIDTH 101
#define HEIGHT 103

typedef struct {
        int px;
        int py;
        int vx;
        int vy;
} Robo;

void printRobo(Robo robo) {
        printf("px: %d ", robo.px);
        printf("py: %d ", robo.py);
        printf("vx: %d ", robo.vx);
        printf("vy: %d \n\r", robo.vy);
}

void incrementRobo(Robo* robo) {
        robo->px = robo->px + robo->vx;
        robo->py = robo->py + robo->vy;
        if (robo->px >= WIDTH) {
                robo->px = robo->px - WIDTH;
        }
        if (robo->px < 0) {
                robo->px = robo->px + WIDTH;
        }
        if (robo->py >= HEIGHT) {
                robo->py = robo->py - HEIGHT;
        }
        if (robo->py < 0) {
                robo->py = robo->py + HEIGHT;
        }
}
