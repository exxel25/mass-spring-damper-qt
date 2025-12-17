#include "massspringdamper.h"

MassSpringDamper::MassSpringDamper(double mass, double kSpring, double cDamp, double initialPos)
{
    m = mass;
    k = kSpring;
    c = cDamp;
    x = initialPos;
    v = 0.0;
}

void MassSpringDamper::update(double dt)
{
    double force = (-k * x) - (c * v);
    double acceleration = force / m;
    v += acceleration * dt;
    x += v * dt;
}

double MassSpringDamper::getPosition() const
{
    return x;
}

// LOGIKA BARU UNTUK LABEL
QString MassSpringDamper::getStatus() const
{
    // Rumus Critical Damping: Cc = 2 * sqrt(m * k)
    double cc = 2 * std::sqrt(m * k);

    if (c == 0) return "Undamped (Oscillates Forever)";
    if (c < cc) return "Underdamped (Oscillating)";
    if (c > cc) return "Overdamped (Slow Return)";
    return "Critically Damped (Ideal)";
}
