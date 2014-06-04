#include "junta.h"
#include "Load.h"
#include <iostream>
#include "iluminacao.h"
#include "formas.h"

Junta::Junta(GLfloat rotacaoMax,
             GLfloat rotacaoMin,
             GLfloat rotacaoInicial,
             GLfloat atrito,
             GLfloat acelMax) {
    this->rotacaoMax = rotacaoMax;
    this->rotacaoMin = rotacaoMin;
    this->rotacao = rotacaoInicial;
    this->atrito = atrito;
    this->acelMax = acelMax;
    this->vel = 0.0f;
    this->acel = 0.0f;
}

void Junta::atualizar(float dt) {
    vel += acel;
    rotacao += vel * dt;
    vel *= atrito;

    if(rotacao > rotacaoMax) {
        rotacao = rotacaoMax;
        acel = 0;
        vel = 0;
    } else if(rotacao < rotacaoMin) {
        rotacao = rotacaoMin;
        acel = 0;
        vel = 0;
    }

    acel = 0;
}

void Junta::rotacionar(int i) {
    if(i == 1) {
        acel = acelMax;
    } else if(i == -1) {
        acel = -acelMax;
    }
}

// Juntas -------------------------

BaseTorcional::BaseTorcional() : Junta(360.0f, -360.0f) {

    modelo = Load::loadObject("modelos/base_junta.obj");
}

void BaseTorcional::renderizar() {
        /*posicaoLuz[2][0] = 0;
        posicaoLuz[2][1] = 2.0;
        posicaoLuz[2][2] = -6;*/

    glRotatef(rotacao, 0.0f, 1.0f, 0.0f);

    glCallList(modelo);

        glTranslatef(0.0f, 1.0f, 0.0f);
        GLfloat d[3] = {0,-1,0};
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,d);






}

JuntaRotacional1::JuntaRotacional1() : Junta(60.0f, 0.0f, 30.0f) {
    modelo = Load::loadObject("modelos/junta_r1.obj");
}

void JuntaRotacional1::renderizar() {

    glRotatef(rotacao, 1.0f, 0.0f, 0.0f);
    glCallList(modelo);
    glTranslatef(0.0f, 0.0f, -3.0f);
GLfloat d[3] = {0,-1,0};
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,d);

}

JuntaRotacional2::JuntaRotacional2() : Junta(0.0f, -30.0f, 0.0f) {
    modelo = Load::loadObject("modelos/junta_r2.obj");
}

void JuntaRotacional2::renderizar() {

    glRotatef(rotacao, 1.0f, 0.0f, 0.0f);
    glCallList(modelo);
    glTranslatef(0.0f, 0.0f, -3.0f);
    GLfloat d[3] = {0,-1,0};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,d);
}

JuntaRotacional3::JuntaRotacional3() : Junta(45.0f, -45.0f) {
    modelo = Load::loadObject("modelos/junta_r3.obj");
}

void JuntaRotacional3::renderizar() {
    glRotatef(rotacao, 1.0f, 0.0f, 0.0f);
    glCallList(modelo);

    glTranslatef(0.3f, -0.6f, 0.0f);
    GLfloat d[3] = {0,-1,0};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,d);

}

JuntaTorcional::JuntaTorcional() : Junta(90.0f, -90.0f) {
    modelo = Load::loadObject("modelos/junta_t.obj");
}

void JuntaTorcional::renderizar() {
    glRotatef(rotacao, 0.0f, 1.0f, 0.0f);
    glCallList(modelo);
    glTranslatef(0.0f, -0.9f, 0.0f);
    GLfloat d[3] = {0,-1,0};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,d);
}

Garra::Garra() : Junta(0.5f, 0.0f, 0.0f, 0.5f, 0.3f) {
    modelo = Load::loadObject("modelos/garra_l.obj");
    modelo2 = Load::loadObject("modelos/garra_r.obj");
}

void Garra::renderizar() {
    glPushMatrix();
        glTranslatef(-0.5f - rotacao, 0, 0);
        glCallList(modelo);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5f + rotacao, 0, 0);
        glCallList(modelo2);
    glPopMatrix();
}
