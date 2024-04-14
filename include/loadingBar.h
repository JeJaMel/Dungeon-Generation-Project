#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

extern int duration;
extern int steps;

void loadingBar(int duration, int steps);

void SetColor(int ForgC);

#endif 