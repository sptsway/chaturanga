//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

enum Color : uint8_t {
    WHITE = 0,
    BLACK = 1,
};

inline Color operator~(Color c) {
    return Color(c ^ 1);
}

#endif //COLOR_H
