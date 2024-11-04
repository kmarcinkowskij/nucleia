//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#include "Utils.hpp"

sf::Vector2f Utils::subtract_vectors(sf::Vector2f v1, sf::Vector2f v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

sf::Vector2f Utils::sum_vectors(sf::Vector2f v1, sf::Vector2f v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

sf::Vector2f Utils::normalize_vector(sf::Vector2f v1) {
    float magnitude = calculate_magnitude_of_vector(v1);
    return { v1.x / magnitude, v1.y / magnitude };
}

float Utils::calculate_magnitude_of_vector(sf::Vector2f v) {
    return std::sqrt((v.x * v.x)+(v.y * v.y));
}

float Utils::calculate_dot_product(sf::Vector2f v1, sf::Vector2f v2) {
    return (v1.x*v2.x)+(v1.y*v2.y);
}
