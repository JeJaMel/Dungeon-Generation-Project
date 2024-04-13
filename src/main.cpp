#include "Graph.h"
#include "loadingBar.h"

int main()
{
    int numChambers[3] = {5, 8, 15};
    for (int level = 0; level < 3; level++)
    {

        std::cout << "\n========================\n";
        std::cout << "        Level " << level + 1
                  << "\n";
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
                std::cout << "\n============================================\n";
                SetColor(10); // Green color (10)
                std::cout << "You found the key!";
                SetColor(7);
                std::cout << "\n============================================\n\n";
                keyFound = true;
            }
            std::cout << "You can move to the following chambers: ";
            for (int neighbor : dungeon.getChamber(current).getConnections())
            {
                std::cout << neighbor << " ";
            }
            std::cout << "\nWhich chamber do you want to move to? Or press 'S' ";
            std::string input;
            std::cin >> input;
            if (input == "S" || input == "s")
            {
                std::cout << "\n============================================\n";
                std::cout << "Shortest path from start to key: ";
                std::pair<int *, int> result = dungeon.findShortestPath(start, key);
                int *path = result.first;
                int length = result.second;
                for (int i = 0; i < length; i++)
                {
                    std::cout << path[i] << " ";
                }
                std::cout << "\n";
                delete[] path;

                std::cout << "Shortest path from key to exit: ";

                result = dungeon.findShortestPath(key, exit);
                path = result.first;
                length = result.second;
                for (int i = 0; i < length; i++)
                {
                    std::cout << path[i] << " ";
                }
                std::cout << "\n============================================\n";
                std::cout << "\n";
                delete[] path;
            }
            else
            {
                int next = std::stoi(input);
                if (next == exit && !keyFound)
                {
                    std::cout << "\n============================================\n";
                    std::cout << "You found the exit! but...\n";
                    SetColor(12); // Red color (12)
                    std::cout << "You can't exit without the key ";
                    SetColor(7);
                    std::cout << "\n============================================\n\n";
                }
                else
                {
                    current = next;
                }
            }
        }

        std::cout << "\nReached the exit!\n";
        if (level < 2) // Check if current level is not the last one
        {
            std::cout << "\nMoving to next level...\n";
            loadingBar(duration, steps); // Display loading bar
            system("cls");               // Clear the screen
        }
    }

    std::cout << "\n============================================\n";
    SetColor(10);
    std::cout << "\nCongratulations! You've escaped the dungeon!\n";
    SetColor(7);
    std::cout << "\n============================================\n";

    return 0;
}