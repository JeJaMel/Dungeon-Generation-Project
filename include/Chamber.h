#ifndef CHAMBER_H
#define CHAMBER_H

#include <list>

class Chamber
{
private:
    bool isStart;
    bool isExit;
    bool hasKey;
    std::list<int> connections;

public:
    // Constructor
    Chamber() : isStart(false), isExit(false), hasKey(false) {}

    // Getters and setters
    bool getIsStart() const { return isStart; }
    void setIsStart(bool isStart) { this->isStart = isStart; }

    bool getIsExit() const { return isExit; }
    void setIsExit(bool isExit) { this->isExit = isExit; }

    bool getHasKey() const { return hasKey; }
    void setHasKey(bool hasKey) { this->hasKey = hasKey; }

    const std::list<int> &getConnections() const { return connections; }
    void addConnection(int chamber) { connections.push_back(chamber); }
};

#endif