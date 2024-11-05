#include <iostream>
#include <random>
#include <__random/random_device.h>

#include "headers/Graphics.hpp"
#include "Particle_container.h"
int main()
{

    sf::RenderWindow window(sf::VideoMode(1280, 1090), "SFML Application");
    window.setFramerateLimit(60);
    sf::Clock time;
    auto container = new Particle_container(window.getSize());

    int increment = 120;

    for(int i = increment; i < window.getSize().x - increment; i += increment) {
        for(int j = increment; j < window.getSize().y - increment; j += increment) {
            container->add_particle(20, sf::Vector2f(i, j), sf::Color{69,123,157}, sf::Vector2f(0.f, 0.f),25.f,Utils::nucleon);
        }
    }

    container->add_particle(5, {5,5}, sf::Color{29, 53, 87}, sf::Vector2f(50.f, 50.f), 1.f, Utils::neutron);


    while (window.isOpen())
    {
        sf::Time delta_time = time.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        window.clear(sf::Color{ 241, 250, 238 });
        container->update_particles(delta_time.asSeconds());
        container->particle_collisions();
        container->draw_particles(window);

        window.display();
    }
    delete(container);
    return 0;
}
