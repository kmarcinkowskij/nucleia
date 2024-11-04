//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#ifndef NEUTRON_HPP
#define NEUTRON_HPP

#include "Particle.h"
#include "Utils.hpp"


class Neutron : public Particle {
    Utils::particle_types particle_type = Utils::neutron;
public:
    Neutron(const unsigned int &_particle_id,const float &_particle_radius, const sf::Vector2f &_particle_position, const sf::Vector2f &_particle_force, const float &_mass):Particle(_particle_id, _particle_radius, _particle_position, _particle_force, _mass) {
        this->shape.setFillColor(sf::Color::Red);
    };

    Utils::particle_types get_particle_type() const {
        return particle_type;
    }
};



#endif //NEUTRON_HPP
