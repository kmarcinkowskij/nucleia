//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#ifndef PARTICLE_CONTAINER_H
#define PARTICLE_CONTAINER_H

#include "Particle.h"
#include "Control_rod.hpp"

#include <array>
#include <variant>

struct Node {
private:
    sf::Vector2f node_pos;
    std::variant<std::shared_ptr<Particle>, std::shared_ptr<Control_rod>> data;
public:
    Node(const std::variant<std::shared_ptr<Particle>, std::shared_ptr<Control_rod>>& _data, const sf::Vector2f& _node_pos) :node_pos(_node_pos), data(_data) {}
    Node() : node_pos({0, 0}) {};
};

class Particle_container {
private:
    std::vector<std::shared_ptr<Particle>> particles;
    sf::Vector2u window_size;
    float wall_hit_force_decay = 0.5f;
public:
    explicit Particle_container(const sf::Vector2u& _window_size) :window_size(_window_size) {};
    void add_particle(const std::shared_ptr<Particle>& _particle);
    void add_particle(const float& _particle_radius, const sf::Vector2f& _particle_position, const sf::Color& _particle_color, const sf::Vector2f& _particle_force, const float& _mass, const Utils::particle_types& _particle_type);
    void remove_particle(const unsigned int& _particle_id);
    void draw_particles(sf::RenderWindow& _window);

    void update_particles(const float& _delta_time);
    void particle_collisions();
    void particle_collisions_test(sf::RenderWindow& _window);
};

#endif // PARTICLE_CONTAINER_H