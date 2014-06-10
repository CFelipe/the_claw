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
        void atualizarMatrizes();
        float base[16],
              junta1[16],
              junta2[16],
              junta3[16],
              juntaTorc[16],
              esq[16],
              dir[16],
              topo[16];
        float* sel;
        bool garraLock;
        float garraX, garraY, garraZ;

    private:
        std::vector<Junta*> juntas;
        unsigned int juntaSelecionada;
        int modeloBase;
};

#endif
