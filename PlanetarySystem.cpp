#include <iostream>
#include <vector>
#include <cmath>

const double GRAVITY = 6.67259e-11; // N*(m/kg)^2

class Body {
public:
    double mass;
    double x, y;
    double vx, vy;
    double ax, ay;

    Body(double mass, double x, double y, double vx, double vy) :
        mass(mass), x(x), y(y), vx(vx), vy(vy) {
            ax = 0;
            ay = 0;
    }

    void updateAcceleration(std::vector<Body>& bodies) {
        ax = 0;
        ay = 0;
        for (auto& other : bodies) {
            if (this == &other) {
                continue;
            }
            double dx = other.x - x;
            double dy = other.y - y;
            double r = std::sqrt(dx*dx + dy*dy);
            double f = GRAVITY * mass * other.mass / (r*r);
            ax += f * dx / r;
            ay += f * dy / r;
        }
    }

    void updatePosition(double dt) {
        x += vx * dt + 0.5 * ax * dt * dt;
        y += vy * dt + 0.5 * ay * dt * dt;
        vx += ax * dt;
        vy += ay * dt;
    }
};

int main() {
    double dt = 86400; // time step (s)
    double time = 0;
    std::vector<Body> bodies;
    bodies.push_back(Body(5.9722e24, 0, 0, 0, 0)); // Earth
    bodies.push_back(Body(7.342e22, 4.2e8, 0, 0, 1.07e3)); // Moon
    // other planets

    for (int i = 0; i < 365; i++) {
        for (auto& body : bodies) {
            body.updateAcceleration(bodies);
        }
        for (auto& body : bodies) {
            body.updatePosition(dt);
        }
        time += dt;
    }

    for (auto& body : bodies) {
        std::cout << "Body at (" << body.x << ", " << body.y << ") m" << std::endl;
    }

    return 0;
}
