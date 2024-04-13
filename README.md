# Dungeon Generation Project

This project is a part of the Dynamic Data Structures course at Rafael Urdaneta University. The main objective is to create a program that generates a three-level dungeon using graph data structures. Each level of the dungeon has a different number of chambers (nodes), and the goal is to find the shortest path from the start chamber to the key, and from the key to the exit.

## Project Requirements

### Dungeon Levels
The dungeon should have three levels, with a specific number of chambers in each:
- Level 1: 5 chambers
- Level 2: 8 chambers
- Level 3: 15 chambers

### Start and Exit Chambers
Each level should have a start chamber and an exit chamber, both selected randomly. The exit chamber of one level serves as the entrance to the next level.

### Chamber Connections
Each chamber should have at least one and at most three connections to other chambers. The connections should be generated randomly.

### Key Placement
A key should be placed in a random chamber on each level. The key cannot be in the start or exit chamber.

### Path Finding
The program should indicate the shortest path from the start chamber to the key, and from the key to the exit chamber. There should be at least one chamber between the start and exit chambers.

## Implementation
This project was implemented individually. The code follows the project requirements closely and uses efficient algorithms for path finding and random dungeon generation.

## Future Improvements
While the current implementation meets the project requirements, there are several potential improvements and additional features that could be added in the future. These include, but are not limited to, adding more complex dungeon layouts, introducing additional types of rooms or obstacles, and implementing more advanced pathfinding algorithms.