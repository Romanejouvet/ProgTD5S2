#include <iostream>
#include <unordered_set>
#include <sstream>

enum Direction { UP, RIGHT, DOWN, LEFT };

struct Position {
    int x, y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}

Position operator+(Position p, Direction d) {
    if (d == UP) p.y--;
    if (d == DOWN) p.y++;
    if (d == LEFT) p.x--;
    if (d == RIGHT) p.x++;
    return p;
}

Direction turn_right(Direction d) {
    return Direction((d + 1) % 4);
}

struct Input {
    Position start;
    Direction dir;
    std::unordered_set<Position> obstacles;
    int width = 0, height = 0;
};

Input parse_input(std::istream& in) {
    Input input;
    std::string line;
    int y = 0;

    while (std::getline(in, line) && !line.empty()) {
        input.width = line.size();

        for (int x = 0; x < line.size(); x++) {
            Position p{x, y};

            if (line[x] == '#') input.obstacles.insert(p);
            if (line[x] == '^') { input.start = p; input.dir = UP; }
            if (line[x] == '>') { input.start = p; input.dir = RIGHT; }
            if (line[x] == 'v') { input.start = p; input.dir = DOWN; }
            if (line[x] == '<') { input.start = p; input.dir = LEFT; }
        }
        y++;
    }

    input.height = y;
    return input;
}

bool inside(Position p, int w, int h) {
    return p.x >= 0 && p.x < w && p.y >= 0 && p.y < h;
}

std::unordered_set<Position> simulate(Input input) {
    Position pos = input.start;
    Direction dir = input.dir;

    std::unordered_set<Position> visited;

    while (true) {
        visited.insert(pos);

        Position next = pos + dir;
        if (!inside(next, input.width, input.height)) break;
        if (input.obstacles.count(next))
            dir = turn_right(dir);
        else
            pos = next;
    }

    return visited;
}

int main() {

    std::istringstream input_map(R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...)");

    Input input = parse_input(input_map);

    auto visited = simulate(input);

    std::cout << "Positions visitees : " << visited.size() << "\n";

    return 0;
}

