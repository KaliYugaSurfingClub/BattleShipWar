#ifndef BATTLESHIP_WAR_PLAYER_H
#define BATTLESHIP_WAR_PLAYER_H

#include "bits/stdc++.h"
#include "Point.h"

enum class HitResponse : short {
    miss = 0, hit, destroy,
};

enum class GridType : short {
    open = 0, close,
};

class Player {
public:
    Player(size_t size, GridType grid_type) : grid_(size, std::vector<PointState>(size)), grid_type_(grid_type) {}

    void add_ship(Point a, Point b) {
//        if (!is_correct_point(a)) {
//            throw std::invalid_argument("first point out of range");
//        }
//
//        if (!is_correct_point(b)) {
//            throw std::invalid_argument("second point out of range");
//        }

        if (!all_of_rect(a, b, PointState::empty)) {
            throw std::invalid_argument("some point is not empty");
        }

        fill_rect(a, b, PointState::ship);

        std::set<Point> ship;
        auto [x_start, x_end] = std::minmax(a.first, b.first);
        auto [y_start, y_end] = std::minmax(a.second, b.second);

        for (size_t y = y_start; y <= y_end; ++y) {
            for (size_t x = x_start; x <= x_end; ++x) {
                ship.emplace(x, y);
            }
        }

        ships_.push_back(ship);
    }

    Point hit() {
        return {};
    }

    HitResponse take_hit(Point point) {
        PointState &state = grid_[point.second][point.first];

//        if (!is_correct_point(point)) {
//            throw std::invalid_argument("hole out of range");
//        }

        if (state == PointState::hit || state == PointState::missed || state == PointState::destroyed) {
            throw std::invalid_argument("that hole already was take_hit");
        }

        if (state == PointState::empty) {
            state = PointState::missed;
            return HitResponse::miss;
        }

        state = PointState::hit;

        std::set<Point> &ship = *std::find_if(ships_.begin(), ships_.end(), [&point](const auto &ship) {
            return ship.contains(point);
        });

        bool all_were_hit = std::ranges::all_of(ship, [this](Point p) {
            return grid_[p.second][p.first] == PointState::hit;
        });

        if (all_were_hit) {
            for (const Point &p: ship) {
                grid_[p.second][p.first] = PointState::destroyed;
            }

            return HitResponse::destroy;
        }

        return HitResponse::hit;
    }

    const std::vector<std::vector<PointState>> &get_grid_() const {
        return grid_;
    }

    GridType get_grid_type() const {
        return grid_type_;
    }

    bool is_loser() const {
        return ships_.empty();
    }

private:
    GridType grid_type_;
    std::vector<std::vector<PointState>> grid_;
    std::vector<std::set<Point>> ships_;
//    std::set<Point> own_hits_;

//    bool is_correct_point(Point point) const {
//        if (point.first >= 10 || point.second >= 10) {
//            return false;
//        }
//
//        return true;
//    }

    //заменить на использование RectRange и Stl
    void fill_rect(Point a, Point b, PointState value) {
        auto [x_start, x_end] = std::minmax(a.first, b.first);
        auto [y_start, y_end] = std::minmax(a.second, b.second);

        for (size_t y = y_start; y <= y_end; ++y) {
            for (size_t x = x_start; x <= x_end; ++x) {
                grid_[y][x] = value;
            }
        }
    }

    bool all_of_rect(Point a, Point b, PointState value) const {
        auto [x_start, x_end] = std::minmax(a.first, b.first);
        auto [y_start, y_end] = std::minmax(a.second, b.second);

        for (size_t y = y_start; y <= y_end; ++y) {
            for (size_t x = x_start; x <= x_end; ++x) {
                if (grid_[y][x] != value) {
                    return false;
                }
            }
        }

        return true;
    }
};

#endif //BATTLESHIP_WAR_PLAYER_H
