//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Utils.hpp"


class Particle {
protected:
    unsigned int particle_id;
    sf::CircleShape shape;
    sf::Color color;
    sf::Vector2f particle_force;
    sf::Vector2f particle_force_base;
    float mass;
    Utils::particle_types particle_type = Utils::unset;
public:


    void set_particle_force_base(const sf::Vector2f &particle_force_base);

    Particle(const unsigned int &_particle_id,const float &_particle_radius, const sf::Vector2f &_particle_position,const sf::Color &_particle_color, const sf::Vector2f &_particle_force, const float &_mass, const Utils::particle_types &_particle_type)
    :particle_id(_particle_id), color(_particle_color), particle_force(_particle_force), mass(_mass), particle_type(_particle_type){
        shape.setRadius(_particle_radius);
        shape.setFillColor(_particle_color);
        shape.setPosition(_particle_position);
        particle_force_base = _particle_force;
    }

    void update(const float &_delta_time);
    void render(sf::RenderWindow &_window);

    void set_force(const sf::Vector2f &_force);
    sf::Vector2f get_force() const;
    sf::Vector2f get_base_force() const;
    sf::CircleShape get_shape() const;
    float get_mass() const;

    int return_id() const;

    Utils::particle_types get_particle_type() const {
        return particle_type;
    }


};



#endif //PARTICLE_H
