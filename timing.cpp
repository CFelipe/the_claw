#include "timing.h"
#include <math.h>
#include <iostream>

float rad = M_PI / 180.0f;

LoopTimer::LoopTimer(float min, float max, float dur) {
    this->min = min;
    this->max = max;
    this->dur = dur;
    this->valor = min;

    elapsed = 0;
}

void LoopTimer::atualizar(float dt) {
    elapsed = (elapsed + dt);
    if(elapsed > dur) elapsed = elapsed - dur;

    valor = ((max - min) * (sinf((elapsed / dur) * (360.0f * rad)) + 1) / 2) + min;
}
