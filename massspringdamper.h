#ifndef MASSSPRINGDAMPER_H
#define MASSSPRINGDAMPER_H

#include <QString> // Tambahkan ini untuk teks
#include <cmath>

class MassSpringDamper
{
public:
    MassSpringDamper(double mass, double kSpring, double cDamp, double initialPos);
    void update(double dt);
    double getPosition() const;

    // FUNGSI BARU: Untuk cek status fisika
    QString getStatus() const;

private:
    double m, k, c, x, v;
};

#endif // MASSSPRINGDAMPER_H
