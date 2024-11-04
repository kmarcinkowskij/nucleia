//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#include "Particle.h"

void Particle::set_particle_force_base(const sf::Vector2f &particle_force_base) {
        this->particle_force_base = particle_force_base;
}

void Particle::update(const float &_delta_time) {

        this->shape.move(this->particle_force * _delta_time);
}

void Particle::render(sf::RenderWindow &_window) {
    _window.draw(this->shape);
}

void Particle::set_force(const sf::Vector2f &_force) {
    this->particle_force = _force;
}

sf::Vector2f Particle::get_force() const {
    return this->particle_force;
}

sf::Vector2f Particle::get_base_force() const {
    return this->particle_force_base;
}

sf::CircleShape Particle::get_shape() const {
    return this->shape;
}

float Particle::get_mass() const  {
    return this->mass;
}

int Particle::return_id() const {
    return this->particle_id;
}

