//
// Created by Konrad Marcinkowski on 05/11/2024.
//

#ifndef CONTROL_ROD_HPP
#define CONTROL_ROD_HPP

#include <SFML/Graphics.hpp>

struct Moderator {
    sf::RectangleShape moderator_shape;
    Moderator(const float &_height, const float &_width) {
        this->moderator_shape.setSize({_height, _width});
    }
};

struct Control_rod {
    sf::RectangleShape upper_shape;
    sf::RectangleShape lower_shape;
    Moderator moderator_rod;
};

#endif //CONTROL_ROD_HPP
