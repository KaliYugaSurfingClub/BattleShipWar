#ifndef BATTLESHIP_WAR_GAME_H
#define BATTLESHIP_WAR_GAME_H

#include "Player.h"
#include "../UI.h"

class Game {
public:
    Game(const Player &player1, const Player &player2) : player1_(player1), player2_(player2) {}

    void print() {
        const auto &grid1 = player1_.get_grid_();
        const auto &grid2 = player2_.get_grid_();

        const size_t grid_width = grid1[0].size();

        std::cout << std::left << std::setw(grid_width * 3 + 3) << "Player 1 grid" << "Player 2 grid\n";

        for (size_t i = 0; i < grid1.size(); ++i) {
            auto out_it = std::ostream_iterator<PointState>{std::cout, "  "};

            print_close_row(grid1[i]);
            std::cout << "|  ";
            print_close_row(grid2[i]);
            std::cout << '\n';
        }

        std::cout << '\n';
    }

    void print_close_row(const std::vector<PointState> &player1_row) {
        for (PointState state : player1_row) {
            char c;

            if (state == PointState::destroyed) {
                c = 'D';
            } else if (state == PointState::missed) {
                c = 'M';
            } else if (state == PointState::hit) {
                c = 'H';
            } else {
                c = '.';
            }

            std::cout << c << "  ";
        }
    }

    void print_open_row(const std::vector<PointState> &player1_row) {

    }

    void run() {
        for (size_t i = 0; !player1_.is_loser() && !player2_.is_loser(); ++i) {
            print();

            auto message = std::format("Move number {}. Player {} choose point to hit", i + 1, i % 2 + 1);

            auto point_constraints = [this](Point p) {
                return p.first <= player1_.get_grid_().size() && p.second <= player1_.get_grid_().size();
            };

            Point point = input<Point>(message, point_constraints);

            if (i % 2 == 0) {
                player2_.take_hit(point);
            } else {
                player1_.take_hit(point);
            }
        }

        std::cout << "End";
    }

private:
    Player player1_;
    Player player2_;
};

#endif //BATTLESHIP_WAR_GAME_H
