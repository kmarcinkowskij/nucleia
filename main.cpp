#include <iostream>
#include <random>
#include <__random/random_device.h>

#include "Neutron.hpp"
#include "Nucleon.hpp"
#include "headers/Graphics.hpp"
#include "Particle_container.h"
int main()
{

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,400); // distribution in range [1, 6]


    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    window.setFramerateLimit(60);
    sf::Clock time;
    auto container = new Particle_container(window.getSize());

    container->add_particle(std::make_shared<Nucleon>(60, 30, sf::Vector2f(100.f, 100.f), sf::Vector2f(0.f, 0.f), 5.f));


    for(int i = 0; i < 50; i++) {
        container->add_particle(std::make_shared<Neutron>(i, 10, sf::Vector2f(dist6(rng), dist6(rng)), sf::Vector2f(60.f, 60.f), 1.f));
    }

    while (window.isOpen())
    {
        sf::Time delta_time = time.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        window.clear();
        container->update_particles(delta_time.asSeconds());
        container->particle_collisions();
        container->draw_particles(window);

        window.display();
    }
    delete(container);
    return 0;
}
