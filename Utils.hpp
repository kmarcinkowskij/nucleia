//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/System/Vector2.hpp>
#include <iostream>


class Utils {
public:
    enum particle_types {nucleon, neutron, xenon, water};
    static sf::Vector2f subtract_vectors(sf::Vector2f v1, sf::Vector2f v2);
    static sf::Vector2f sum_vectors(sf::Vector2f v1, sf::Vector2f v2);
    static sf::Vector2f normalize_vector(sf::Vector2f v1);
    static float calculate_magnitude_of_vector(sf::Vector2f v);
    static float calculate_dot_product(sf::Vector2f v1, sf::Vector2f v2);

};



#endif //UTILS_HPP
