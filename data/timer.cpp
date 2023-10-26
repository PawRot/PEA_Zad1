//
// Created by Michał Zychowicz on 26/10/2023.
//

#include "timer.h"

timer::timer() = default;

timer::~timer() = default;

bool timer::startTimer() {
    sleep(2);
    return true;
}
