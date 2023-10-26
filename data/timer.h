//
// Created by Michał Zychowicz on 26/10/2023.
//

#ifndef PEA_ZAD1_TIMER_H
#define PEA_ZAD1_TIMER_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


class timer {
    timer();
    ~timer();

    void startTimer();

};


#endif //PEA_ZAD1_TIMER_H
