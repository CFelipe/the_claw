#ifndef BRACO_H
#define BRACO_H

#include <vector>
#include "junta.h"

class Braco {
    public:
        Braco();
        void atualizar();
        void renderizar();
        void selecionarJunta(int i);
        void rotacionarSelecao(GLfloat graus);

    private:
        std::vector<Junta*> juntas;
        unsigned int juntaSelecionada;
};

#endif
