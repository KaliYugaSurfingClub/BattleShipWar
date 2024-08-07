#ifndef BATTLESHIP_WAR_POINT_H
#define BATTLESHIP_WAR_POINT_H

#include "iostream"

using Point = std::pair<size_t, size_t>;

enum class PointState : short {
    empty = 0, missed, ship, hit, destroyed
};

std::istream &operator>>(std::istream &is, Point &point) {
    return is >> point.first >> point.second;
}


#endif //BATTLESHIP_WAR_POINT_H
