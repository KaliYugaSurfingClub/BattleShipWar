#ifndef BATTLESHIP_WAR_UTILS_H
#define BATTLESHIP_WAR_UTILS_H

#include "bits/stdc++.h"

template<typename T, typename Pred>
T input(std::string_view text, Pred constraint) {
    using namespace std;

    T res;

    cout << text << '\n';
    while (!(cin >> res) || !constraint(res)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again\n";
    }

    return res;
}

template<typename T>
T input(std::string_view text) {
    return input<T>(text, [](const T&) { return true; });
}

#endif //BATTLESHIP_WAR_UTILS_H
