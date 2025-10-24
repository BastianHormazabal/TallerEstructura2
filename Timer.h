#pragma once
#include <ctime>

struct Temporizador {
    std::clock_t inicio;
    Temporizador() { inicio = std::clock(); }
    void reiniciar() { inicio = std::clock(); }
    double milisegundos() const {
        return 1000.0 * (std::clock() - inicio) / CLOCKS_PER_SEC;
    }
};
