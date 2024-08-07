#include "Core/Game.h"

int main() {
    auto [player1, player2] = init_players();
    Game g(player1, player2);
    g.run();

    return 0;
}
