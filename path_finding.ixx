module;

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

export module path_finding;

import scara_functions;

constexpr int SCARA = 0;
constexpr int DEFAULT_TILE = 1;
constexpr int ANKH = 2;

constexpr int DIRECTION = 13;

constexpr int RIGHT_LEVEL_BORDER = 21;
constexpr int BOTTOM_LEVEL_BORDER = 22;

struct int2
{
    int x, y;

    int2() : x(0), y(0) {}
    int2(int x, int y) : x(x), y(y) {}

    static int2 up() { return int2(0, -1); }
    static int2 down() { return int2(0, 1); }
    static int2 right() { return int2(1, 0); }
    static int2 left() { return int2(-1, 0); }
    static int mag(const int2& a) { return static_cast<int>(sqrt(a.x * a.x + a.y * a.y)); }
    
    int2 operator+(const int2& a) const
    {
        return { x + a.x, y + a.y };
    }

    int2 operator-(const int2& a) const
    {
        return { x - a.x, y - a.y };
    }
    
    int2 operator/(const int a) const
    {
        return { x / a, y / a };
    }
    
    static size_t hash(const int2& key) {
        return std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
    }
    
    static bool equal(const int2& a, const int2& b) {
        return a.x == b.x && a.y == b.y;
    }
};

struct int2Hasher {
    size_t operator()(const int2& key) const {
        return int2::hash(key);
    }
};

struct int2Equal {
    bool operator()(const int2& a, const int2& b) const {
        return int2::equal(a, b);
    }
};

class tile
{
    int2 position_;
    int2 connection_position_;
    int mask_;
    int g_cost_, h_cost_;
    
public:
    tile() : position_({}), connection_position_({}), mask_(0), g_cost_(0), h_cost_(0){}
    tile(const int2 position, const int mask) : position_(position), connection_position_(int2()), mask_(mask), g_cost_(0), h_cost_(0) {}

    [[nodiscard]] int2 get_position() const { return position_; }
    [[nodiscard]] int2 get_connection() { return connection_position_; }
    [[nodiscard]] int get_f_cost() const { return g_cost_ + h_cost_; }
    [[nodiscard]] int get_g_cost() const { return g_cost_; }
    [[nodiscard]] int get_h_cost() const { return h_cost_; }
    [[nodiscard]] int get_mask() const { return mask_; }

    void set_connection(int2 connection) { connection_position_ = connection; }
    void set_position(int2 position) { position_ = position; }
    void set_g_cost(const int g_cost) { g_cost_ = g_cost; }
    void set_h_cost(const int h_cost) { h_cost_ = h_cost; }
    
    bool operator==(const tile& tile) const
    {
        return int2::equal(position_, tile.position_);
    }

    struct hash {
        std::size_t operator()(const tile& t) const {
            return int2::hash(t.get_position());
        }
    };
};

void get_level_tiles(std::unordered_map<int2, tile, int2Hasher, int2Equal>& tiles, int2& scara, int2& ankh)
{
    std::vector<tile> specific_tiles;

    int tile_mask = 0;
    for (int x = 0; !is_tile(tile_mask, RIGHT_LEVEL_BORDER); ++x)
    {
        tile_mask = 0;
        for (int y = 0; !is_tile(tile_mask, BOTTOM_LEVEL_BORDER); ++y)
        {
            tile_mask = scan_tile_at(x, y);
            int2 tile_position = int2(x, y);
            tiles[tile_position] = tile(tile_position, tile_mask);

            if(is_tile(tile_mask, SCARA)) { scara = tile_position; }
            if(is_tile(tile_mask, ANKH)) { ankh = tile_position; }
        }
    }
}

tile* get_lowest_f_cost(std::vector<tile>& tiles)
{
    int lowest_f_cost_index = 0;
    for (int i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].get_f_cost() < tiles[lowest_f_cost_index].get_f_cost()
            || tiles[i].get_f_cost() == tiles[lowest_f_cost_index].get_f_cost()
            && tiles[i].get_h_cost() < tiles[lowest_f_cost_index].get_h_cost())
            { lowest_f_cost_index = i; }
    }
    return &tiles[lowest_f_cost_index];
}

std::vector<tile*> get_neighbours(const tile& current_tile, std::unordered_map<int2, tile, int2Hasher, int2Equal>& tiles)
{
    std::vector<tile*> neighbours;

    int2 current_position = current_tile.get_position();

    // NORTH NEIGHBOUR
    int2 north_position = current_position + int2::up();
    if (tiles.contains(north_position)) { neighbours.push_back(&tiles[north_position]); }
    
    // EAST NEIGHBOUR
    int2 east_position = current_position + int2::right();
    if (tiles.contains(east_position)) { neighbours.push_back(&tiles[east_position]); }

    // SOUTH NEIGHBOUR
    int2 south_position = current_position + int2::down();
    if (tiles.contains(south_position)) { neighbours.push_back(&tiles[south_position]); }

    // WEST NEIGHBOUR
    int2 west_position = current_position + int2::left();
    if (tiles.contains(west_position)) { neighbours.push_back(&tiles[west_position]); }

    return neighbours;
}

bool is_walkable(const tile& tile)
{
    return is_tile(tile.get_mask(), DEFAULT_TILE) || is_tile(tile.get_mask(), ANKH);
}

int get_distance(const int2& a, const int2& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int2 get_scaras_direction(const tile& scara)
{
    int direction_mask = scara.get_mask() >> 13 & 0b11;

    switch (direction_mask)
    {
        case 0: return int2(0, -1);
        case 1: return int2(1, 0);
        case 2: return int2(0, 1);
        case 3: return int2(-1, 0);
    }

    return int2{};
}

std::vector<tile> get_shortest_path(tile& start, tile& end, std::unordered_map<int2, tile, int2Hasher, int2Equal>& tiles)
{
    std::vector open_vector { start };
    std::unordered_set<tile, tile::hash> closed_set;

    while (!open_vector.empty())
    {
        // Get the lowest f cost in open vector
        tile current_tile = *get_lowest_f_cost(open_vector);
        
        // If current is equals to the end tile; return path
        if (current_tile == end)
        {
            std::vector<tile> path;
            tile* current_path_tile = &end;

            while (current_path_tile != &start)
            {
                path.push_back(*current_path_tile);
                current_path_tile = &tiles[current_path_tile->get_connection()];
            }

            std::reverse(path.begin(), path.end());
            return path;
        }

        // Move current tile from open to closed set
        closed_set.insert(current_tile);
        open_vector.erase(std::ranges::find(open_vector, current_tile));

        // Get neighbours of current tile
        for (tile* neighbour : get_neighbours(current_tile, tiles))
        {
            // Skip neighbour if it's not walkable or in closed set
            if (!is_walkable(*neighbour) || closed_set.count(*neighbour) > 0)
                continue;

            // Calculate new cost to neighbour
            int new_g_cost = current_tile.get_g_cost() + get_distance(current_tile.get_position(), neighbour->get_position());

            // If neighbour is not in open set or new g cost is less than current g cost, update neighbour's costs and connection
            auto it = std::ranges::find(open_vector, *neighbour);
            if (it == open_vector.end() || new_g_cost < neighbour->get_g_cost())
            {
                neighbour->set_g_cost(new_g_cost);
                neighbour->set_h_cost(get_distance(neighbour->get_position(), end.get_position()));
                neighbour->set_connection(current_tile.get_position());

                // Add neighbour to open set if not already present
                if (it == open_vector.end())
                    open_vector.push_back(*neighbour);
            }
        }
    }

    // No path found
    return {};
}

int2 get_direction_from_to(tile& a, tile& b)
{
    int2 direction = int2(b.get_position() - a.get_position());
    return direction / int2::mag(direction);
}

void turn_towards_tile(int2& direction, const int2& path_direction)
{
    while(!int2::equal(direction, path_direction))
    {
        if(int2::equal(direction, int2::up())) { direction = int2::left(); }
        else if(int2::equal(direction, int2::left())) { direction = int2::down(); }
        else if(int2::equal(direction, int2::down())) { direction = int2::right(); }
        else if(int2::equal(direction, int2::right())) { direction = int2::up(); }
        turn_left();
    }
}

export void move_with_shortest_path()
{
    // Get required information
    std::unordered_map<int2, tile, int2Hasher, int2Equal> tiles;
    int2 scara_position, ankh_position;
    get_level_tiles(tiles, scara_position, ankh_position);
    std::vector<tile> path = get_shortest_path(tiles[scara_position], tiles[ankh_position], tiles);
    
    if(path.empty()) return;

    // Turn scara to initial position
    int2 direction = get_scaras_direction(tiles[scara_position]);
    int2 path_direction = get_direction_from_to(tiles[scara_position], *path.begin());
    turn_towards_tile(direction, path_direction);
    
    for (auto current_tile = path.begin(); current_tile != path.end(); current_tile++)
    {
        path_direction = get_direction_from_to(tiles[scara_position], *current_tile);
        turn_towards_tile(direction, path_direction);
        tiles[scara_position].set_position(tiles[scara_position].get_position() + direction);
        move();
    }
}