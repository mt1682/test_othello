#include "disk.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "func.h"

void Disk::init() {
    x = 0;
    y = 0;
    color = 0;
    keepColor = 0;
    for (int i = 0; i < 9; i++) {
        near[i] = 0;
        keepNear[i] = 0;
    }
}

void Disk::flip() { color = 3 - color; }

int Disk::set(int player) {
    if (player == 1) {
        color = 1;
    } else if (player == 2) {
        color = 2;
    } else {
        color = -2;
    }
    return color;
}
int Disk::getColor() { return color; }

void Disk::save() {
    for (int i = 0; i < 9; i++) {
        keepNear[i] = near[i];
    }
    keepColor = color;
}

void Disk::restore() {
    for (int i = 0; i < 9; i++) {
        near[i] = keepNear[i];
    }
    color = keepColor;
}