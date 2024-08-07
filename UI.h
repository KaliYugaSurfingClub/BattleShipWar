#ifndef BATTLESHIP_WAR_UI_H
#define BATTLESHIP_WAR_UI_H

#include "Core/Player.h"
#include "utils.h"

struct ShipSpec {
    size_t width;
    size_t height;
};

std::istream &operator>>(std::istream &is, ShipSpec &spec) {
    return is >> spec.width >> spec.height;
}

std::vector<ShipSpec> get_ship_spec(size_t grid_size) {
    auto count_of_ships_constraints = [grid_size](size_t sz) { return sz <= grid_size && sz > 0; };
    auto count_of_ships = input<size_t>("Enter count of battleships", count_of_ships_constraints);

    std::vector<ShipSpec> dimensions_vec;
    dimensions_vec.reserve(count_of_ships);

    auto dimensions_constraints = [grid_size](const ShipSpec &spec) {
        return
            spec.width <= grid_size &&
            spec.height <= grid_size &&
            spec.width > 0 &&
            spec.height > 0;
    };

    for (size_t i = 0; i < count_of_ships; ++i) {
        std::string message = std::format("Enter dimensions of ship number {}", i + 1);
        dimensions_vec.push_back(input<ShipSpec>(message, dimensions_constraints));
    }

    return dimensions_vec;
}

template<std::unsigned_integral T>
T difference(T a, T b) {
    const auto [min, max] = std::minmax(a, b);
    return max - min;
}

struct GameOptions {
    size_t grid_size_;
    std::vector<ShipSpec> ship_spec_;
};

GameOptions get_game_options() {
    auto size_constraint = [](size_t sz) { return sz <= 1000 && sz >= 5; };
    size_t grid_size{input<size_t>("Enter size of board (5 <= size <= 1000)", size_constraint)};

    return {grid_size, get_ship_spec(grid_size)};
}

Player init_player(const GameOptions &gameOptions) {
    const auto [grid_size, ship_spec] = gameOptions;

    Player player{grid_size, GridType::close};

    for (size_t i = 0; i < ship_spec.size(); ++i) {
        const auto [width, height] = ship_spec[i];

        std::cout << std::format("Enter points to init ship {}x{}\n", width, height);

        auto point_constraints = [grid_size](Point p) {
            return p.first <= grid_size && p.second <= grid_size;
        };

        auto a = input<Point>("first point of ship:", point_constraints);
        auto b = input<Point>("second point of ship:", point_constraints);

        bool correct_size = difference(a.first, b.first) == width - 1 && difference(a.second, b.second) == height - 1;
        bool reverse_ship_correct_size = difference(a.first, b.first) == height - 1 && difference(a.second, b.second) == width - 1;

        if (correct_size || reverse_ship_correct_size) {
            player.add_ship(a, b);
        } else {
            std::cout << "those point do not def ship correct size\n";
            --i;
        }
    }

    return player;
};

std::pair<Player, Player> init_players() {
    const auto game_options = get_game_options();
    return {
        init_player(game_options),
        init_player(game_options)
    };
}

std::ostream &operator<<(std::ostream &os, PointState point) {
    char c;

    switch (point) {
        case PointState::empty:
            c = '.';
            break;
        case PointState::missed:
            c = 'M';
            break;
        case PointState::ship:
            c = 'S';
            break;
        case PointState::hit:
            c = 'H';
            break;
        case PointState::destroyed:
            c = 'D';
            break;
        default:
            break;
    }

    return os << c;
}

#endif //BATTLESHIP_WAR_UI_H
