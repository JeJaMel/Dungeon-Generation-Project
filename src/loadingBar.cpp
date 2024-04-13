#include "loadingBar.h"

int duration = 20;
int steps = 36;

void loadingBar(int duration, int steps)
{
    int barWidth = 40;

    for (int i = 0; i < steps; ++i)
    {
        float progress = static_cast<float>(i) / steps;
        int barLength = static_cast<int>(progress * barWidth);

        std::cout << "[ ";
        for (int j = 0; j < barWidth; ++j)
        {
            if (j < barLength)
                std::cout << "=";
            else
                std::cout << " ";
        }
        std::cout << "] " << static_cast<int>(progress * 103.0) << "%\r";
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }

    std::cout << std::endl;
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
