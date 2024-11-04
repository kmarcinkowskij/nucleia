//
// Created by Konrad Marcinkowski on 04/11/2024.
//

#include "Particle_container.h"

#include <iostream>

#include "Utils.hpp"


void Particle_container::add_particle(const std::shared_ptr<Particle> &_particle) {
    try {

        const auto it = std::find_if(this->particles.begin(), this->particles.end(), [&](const std::shared_ptr<Particle> &current_particle) {
            return current_particle->return_id() == _particle->return_id();
        });

        if(it != this->particles.end()) {
            std::cerr << "Particle with this ID already exists!\n";
            return;
        }

        this->particles.push_back(_particle);


    }catch(const std::exception &exception) {
        std::cout << exception.what() << "\n";
    }
}

void Particle_container::add_particle(const unsigned int &_particle_id, const float &_particle_radius,
    const sf::Vector2f &_particle_position, const sf::Color &_particle_color, const sf::Vector2f &_particle_force, const float &_mass) {
    try {

        const auto it = std::find_if(this->particles.begin(), this->particles.end(), [&](const std::shared_ptr<Particle> &current_particle) {
            return current_particle->return_id() == _particle_id;
        });

        if(it != this->particles.end()) {
           std::cerr << "Particle with this ID already exists!\n";
            return;
        }

        this->particles.push_back(std::make_shared<Particle>(Particle(_particle_id, const_cast<float &>(_particle_radius), _particle_position, _particle_force, _mass)));


    }catch(const std::exception &exception) {
        std::cout << exception.what() << "\n";
    }
}

void Particle_container::remove_particle(const unsigned int &_particle_id) {
        const auto it = std::find_if(this->particles.begin(), this->particles.end(), [&](const std::shared_ptr<Particle> &current_particle) {
            return current_particle->return_id() == _particle_id;
        });

        this->particles.erase(it);
    }

void Particle_container::draw_particles(sf::RenderWindow &_window) {
    for(const std::shared_ptr<Particle> &Particle: this->particles ) {
        Particle->render(_window);
    }
}

void Particle_container::update_particles(const float &_delta_time) {
    for(const auto& particle: this->particles) {
        if(particle->get_shape().getPosition().x + particle->get_shape().getRadius() <= particle->get_shape().getRadius() ||
            particle->get_shape().getPosition().x + particle->get_shape().getRadius() >= this->window_size.x - particle->get_shape().getRadius())
        {
            particle->set_force(sf::Vector2f((particle->get_force().x - this->wall_hit_force_decay) * -1, (particle->get_force().y)));
        }

        if(particle->get_shape().getPosition().y + particle->get_shape().getRadius() <= particle->get_shape().getRadius() ||
            particle->get_shape().getPosition().y + particle->get_shape().getRadius() >= this->window_size.y - particle->get_shape().getRadius())
        {
            particle->set_force(sf::Vector2f(particle->get_force().x, (particle->get_force().y - this->wall_hit_force_decay) * -1));
        }
        particle->update(_delta_time);
    }
}

void Particle_container::particle_collisions() {
    // for(int iter = 0; iter < this->particles.size(); iter++) {
    //     if(this->particles.at(iter)->get_shape().getPosition().)
    // }

   //TODO: create an optimized system for detecting collisions

    for(int iter = 0; iter < this->particles.size(); iter++) {
        for(int iter_y = iter+1; iter_y < this->particles.size(); iter_y++) {



            std::shared_ptr<Particle> p1 = particles[iter];
            std::shared_ptr<Particle> p2 = particles[iter_y];

            float xa = p1->get_shape().getPosition().x;
            float xb = p2->get_shape().getPosition().x;
            float ya = p1->get_shape().getPosition().y;
            float yb = p2->get_shape().getPosition().y;
            float distance_between_centers = sqrt((xb-xa)*(xb-xa) + (yb-ya)*(yb-ya));
            float sum_of_radius = p1->get_shape().getRadius() + p2->get_shape().getRadius();
            // std::cout << "particle 1 ID: " << this->particles[iter]->return_id() << " particle 2 ID: " << this->particles[iter_y]->return_id() << " the distance " << distance_between_centers << " the radius " << sum_of_radius << "\n";
            if(sum_of_radius >= distance_between_centers) {

                sf::Vector2f v1 = p1->get_force();
                sf::Vector2f v2 = p2->get_force();

                sf::Vector2f relative_velocity = Utils::subtract_vectors(v1, v2);
                sf::Vector2f collision_normal = Utils::normalize_vector(Utils::subtract_vectors(p1->get_shape().getPosition(), p2->get_shape().getPosition()));

                float dot_product = Utils::calculate_dot_product(relative_velocity, collision_normal);

                //         # If vel_along_normal > 0, they are moving apart already, no need to adjust
                //         if vel_along_normal > 0:
                //             return p1.velocity, p2.velocity
                //
                //         # Step 3.3: Calculate the impulse scalar
                //         restitution = 1  # for a perfectly elastic collision
                //         impulse = (-(1 + restitution) * vel_along_normal) / (1 / p1.mass + 1 / p2.mass)
                //
                //         # Step 3.4: Calculate the final velocities
                //         impulse_vector = (impulse * collision_normal[0], impulse * collision_normal[1])
                //
                //         # Update velocities by adding/subtracting impulse
                //         v1_final = (p1.velocity[0] + impulse_vector[0] / p1.mass,
                //                     p1.velocity[1] + impulse_vector[1] / p1.mass)
                //
                //         v2_final = (p2.velocity[0] - impulse_vector[0] / p2.mass,
                //                     p2.velocity[1] - impulse_vector[1] / p2.mass)
                //
                //         return v1_final, v2_final

                if(dot_product > 0) continue;
                float restitution = 0.5;
                float impulse = (-(1 + restitution) * dot_product) / (1 / p1->get_mass() + 1/p2->get_mass());
                sf::Vector2f impulse_vector = {impulse * collision_normal.x, impulse * collision_normal.y};

                if(p1->get_force().x < 0) {
                    p1->set_force(sf::Vector2f(p1->get_force().x + this->wall_hit_force_decay + impulse_vector.x / p1->get_mass(), p1->get_force().y + impulse_vector.y / p1->get_mass()));
                } else {
                    p1->set_force(sf::Vector2f(p1->get_force().x - this->wall_hit_force_decay + impulse_vector.x / p1->get_mass(), p1->get_force().y + impulse_vector.y / p1->get_mass()));
                }

                p2->set_force({p2->get_force().y - impulse_vector.y / p2->get_mass(), p2->get_force().y - impulse_vector.y / p2->get_mass()});


                //         float xa = this->particles[iter]->get_shape().getPosition().x;
                //         float xb = this->particles[iter_y]->get_shape().getPosition().x;
                //         float ya = this->particles[iter]->get_shape().getPosition().y;
                //         float yb = this->particles[iter_y]->get_shape().getPosition().y;
                //         float distance_between_centers = sqrt((xb-xa)*(xb-xa) + (yb-ya)*(yb-ya));
                //         float sum_of_radius = this->particles[iter]->get_shape().getRadius() + this->particles[iter_y]->get_shape().getRadius();
                //         // std::cout << "particle 1 ID: " << this->particles[iter]->return_id() << " particle 2 ID: " << this->particles[iter_y]->return_id() << " the distance " << distance_between_centers << " the radius " << sum_of_radius << "\n";
                //         if(sum_of_radius >= distance_between_centers) {
                //             // std::cout << "particle " << particles[iter]->return_id() << " collided with particle " << particles[iter_y]->return_id() << "\n";
                //             // particles[iter]->get_shape().setFillColor(sf::Color::Green);
                //             particles[iter]->set_force(sf::Vector2f(particles[iter]->get_force().x * -1,particles[iter]->get_force().y * -1 ));
                //             particles[iter_y]->set_force(sf::Vector2f(particles[iter_y]->get_force().x * -1,particles[iter_y]->get_force().y * -1 ));
                //
            }
        }


        // std::cout << "distance: " << distance << ", sum of radius " << this->particles[iter]->get_shape().getRadius() + this->particles[iter+1]->get_shape().getRadius() << "\n";
        // if(distance <= this->particles[iter]->get_shape().getRadius() + this->particles[iter+1]->get_shape().getRadius()) {
        //     // remove_particle(this->particles[iter]->return_id());
        //
        // }
    }
    };
