#include "braco.h"
#include "Load.h"
#include <iostream>

Braco::Braco() {
    modeloBase = Load::loadObject("modelos/base.obj");

    juntaSelecionada = 0;
    int i;
    for(i = 0; i < 16; i++) {
        esq[i] = 0;
        dir[i] = 0;
        topo[i] = 0;
    }

    garraLock = false;

    juntas.push_back(new BaseTorcional());
    juntas.push_back(new JuntaRotacional1());
    juntas.push_back(new JuntaRotacional2());
    juntas.push_back(new JuntaRotacional3());
    juntas.push_back(new JuntaTorcional());
    juntas.push_back(new Garra());
}

void Braco::atualizar(float dt) {
    std::vector<Junta*>::iterator it;
    for(it = juntas.begin(); it != juntas.end(); ++it) {
        (*it)->atualizar(dt);
    }

    atualizarMatrizes();
}

void Braco::renderizar() {
    glTranslatef(0.0f, 0.0f, 0.0f);

    glCallList(modeloBase);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0f, 1.0f, 0.0f);

    std::vector<Junta*>::iterator it;
    for(it = juntas.begin(); it != juntas.end(); ++it) {
        if((it - juntas.begin()) == juntaSelecionada) {
            glColor3f(0.0f, 1.0f, 0.0f);
        } else {
            glColor3f(1.0f, 1.0f, 0.0f);
        }

        (*it)->renderizar();
    }

    glDisable(GL_COLOR_MATERIAL);
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

void Braco::atualizarMatrizes() {
    glPushMatrix();
        glLoadIdentity();
        glRotatef(juntas.at(0)->rotacao, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 1.0f, 0.0f);
        glRotatef(juntas.at(1)->rotacao, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -3.0f);
        glRotatef(juntas.at(2)->rotacao, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -3.0f);
        glRotatef(juntas.at(3)->rotacao, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.3f, -0.6f, 0.0f);
        glRotatef(juntas.at(4)->rotacao, 0.0f, 1.0f, 0.0f);

        glPushMatrix();
            glTranslatef(0, -0.2f, 0);
            glGetFloatv(GL_MODELVIEW_MATRIX, topo);
        glPopMatrix();

        glTranslatef(0.0f, -0.9f, 0.0f);

        glPushMatrix();
            glTranslatef(-0.5f - juntas.at(5)->rotacao, 0, 0);
            glGetFloatv(GL_MODELVIEW_MATRIX, esq);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5f + juntas.at(5)->rotacao, 0, 0);
            glGetFloatv(GL_MODELVIEW_MATRIX, dir);
        glPopMatrix();
    glPopMatrix();
}
