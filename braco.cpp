#include "braco.h"
#include "formas.h"
#include <iostream>

const GLfloat ELO_H = 15.0f;
const GLfloat ELO_R = 2.0f;

Braco::Braco() {
    juntaSelecionada = 0;

    juntas.push_back(new JuntaRotacional());
    juntas.push_back(new JuntaTorcional());
    juntas.push_back(new JuntaRevolvente());
}

void Braco::atualizar(float dt) {
    std::vector<Junta*>::iterator it;
    for(it = juntas.begin(); it != juntas.end(); ++it) {
        (*it)->atualizar(dt);
    }
}


void Braco::renderizar() {
    // Base
    Formas::cilindro(25.0f, 5.0f, 16);
    glTranslatef(0.0f, 5.0f, 0.0f);
    Formas::cilindro(ELO_R, ELO_H, 16);
    glTranslatef(0.0f, ELO_H, 0.0f);

    std::vector<Junta*>::iterator it;
    for(it = juntas.begin(); it != juntas.end(); ++it) {
        (*it)->renderizar();
    }
}

void Braco::selecionarJunta(int i) {
    if(i == -1 && juntaSelecionada > 0) {
        juntaSelecionada--;
    } else if(i == 1 && juntaSelecionada < juntas.size() - 1) {
        juntaSelecionada++;
    }
}

void Braco::rotacionarSelecao(int i) {
    juntas.at(juntaSelecionada)->rotacionar(i);
}
