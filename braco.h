#ifndef BRACO_H
#define BRACO_H

#include <vector>
#include "junta.h"

class Braco {
    public:
        Braco();
        void atualizar(float dt);
        void renderizar();
        void selecionarJunta(int i);
        void rotacionarSelecao(int i);

    private:
        std::vector<Junta*> juntas;
        unsigned int juntaSelecionada;
};

#endif
