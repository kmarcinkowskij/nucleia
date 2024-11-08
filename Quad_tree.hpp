#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <SFML/Graphics.hpp>
#include "Particle.h"

#include <memory>
#include <array>

constexpr int MAX_PARTICLES = 4; 
constexpr int MAX_DEPTH = 5;

class Quadtree {
public:
    Quadtree(const int& level, const sf::FloatRect& bounds) : level(level), bounds(bounds), divided(false) {}

    void insert(std::shared_ptr<Particle> particle) {
        if (!bounds.contains(particle->get_shape().getPosition()))
            return;

        if (particles.size() < MAX_PARTICLES || level == MAX_DEPTH)
            particles.push_back(particle);
        else {
            if (!divided) subdivide();

            for (auto& existing_particle : particles) {
                for (auto& child : children)
                    child->insert(existing_particle);
            }
            particles.clear();

            for (auto& child : children)
                child->insert(particle);
        }
    }

    void retrieve(const sf::FloatRect& range, std::vector<std::shared_ptr<Particle>>& found) {
        if (!bounds.intersects(range))
            return;

        for (auto& particle : particles) {
            if (range.contains(particle->get_shape().getPosition()))
                found.push_back(particle);
        }

        if (divided) {
            for (auto& child : children)
                child->retrieve(range, found);
        }
    }

    void clear() {
        particles.clear();
        if (divided) {
            for (auto& child : children) {
                child->clear();
                child.reset();
            }
            divided = false;
        }
    }
private:
    int level;
    sf::FloatRect bounds;
    bool divided;
    std::vector<std::shared_ptr<Particle>> particles;
    std::array<std::unique_ptr<Quadtree>, 4> children;

    void subdivide() {
        const float x = bounds.left;
        const float y = bounds.top;
        const float width = bounds.width / 2;
        const float height = bounds.height / 2;

        children[0] = std::make_unique<Quadtree>(level + 1, sf::FloatRect(x, y, width, height));
        children[1] = std::make_unique<Quadtree>(level + 1, sf::FloatRect(x + width, y, width, height));
        children[2] = std::make_unique<Quadtree>(level + 1, sf::FloatRect(x, y + height, width, height));
        children[3] = std::make_unique<Quadtree>(level + 1, sf::FloatRect(x + width, y + height, width, height));

        divided = true;
    }
};

#endif // QUADTREE_HPP