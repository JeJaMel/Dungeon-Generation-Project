#include "Graph.h"
#include "loadingBar.h"

int main()
{
    int numChambers[3] = {5, 8, 15};
    for (int level = 0; level < 3; level++)
    {
        std::cout << "\n========================\n";
        std::cout << "Entering Level " << level + 1 << "\n";
        std::cout << "========================\n";
        Graph dungeon(numChambers[level]);

        dungeon.generateDungeon(numChambers[level]);

        // Find the start, key, and exit chambers
        int start, key, exit;
        for (int i = 0; i < numChambers[level]; i++)
        {
            if (dungeon.getChamber(i).getIsStart())
            {
                start = i;
            }
            else if (dungeon.getChamber(i).getHasKey())
            {
                key = i;
            }
            else if (dungeon.getChamber(i).getIsExit())
            {
                exit = i;
            }
        }

        // User-controlled movement
        int current = start;
        bool keyFound = false;
        while (current != exit || !keyFound)
        {
            std::cout << "You are in chamber " << current << ".\n";
            if (current == key)
            {
                std::cout << "You found the key!\n";
                keyFound = true;
            }
            std::cout << "You can move to the following chambers: ";
            for (int neighbor : dungeon.getChamber(current).getConnections())
            {
                std::cout << neighbor << " ";
            }
            std::cout << "\nWhich chamber do you want to move to? ";
            int next;
            std::cin >> next;
            if (next == exit && !keyFound)
            {
                std::cout << "You found the exit! but...\n";
                std::cout << "You can't exit without the key \n";
            }
            else
            {
                current = next;
            }
        }

        std::cout << "\nReached the exit!\n";
        if (level < 2) // Check if current level is not the last one
        {
            std::cout << "\nMoving to next level...\n";
            loadingBar(duration, steps); // Display loading bar
        }
    }

    std::cout << "\n============================================\n";
    std::cout << "\nCongratulations! You've escaped the dungeon!\n";
    std::cout << "\n============================================\n";

    return 0;
}