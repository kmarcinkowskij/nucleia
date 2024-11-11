#include "headers/Graphics.hpp"
#include "Particle_container.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 1090), "SFML Application");
    window.setFramerateLimit(60);
    sf::Clock time;

    auto container = std::make_unique<Particle_container>(window.getSize());

    for(int i = 100; i < window.getSize().x - 100; i += 100) {
        for(int j = 100; j < window.getSize().y - 100; j += 100) {
            container->add_particle(20, sf::Vector2f(i, j), sf::Color{69,123,157}, sf::Vector2f(0.f, 0.f), 25.f, Utils::nucleon);
        }
    }

    container->add_particle(5, {5,5}, sf::Color{29, 53, 87}, sf::Vector2f(50.f, 50.f), 1.f, Utils::slow_neutron);

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
    return 0;
}
