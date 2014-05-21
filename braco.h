#ifndef BRACO_H
#define BRACO_H

#include <list>
#include "junta.h"

class Braco {
    public:
        void ~Braco() {}
        void renderizar();

    private:
        std::list<Junta> juntas;
};

#endif
