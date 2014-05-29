#include "junta.h"
#include "formas.h"
#include <iostream>

const GLfloat PIR_W = 5.0f;
const GLfloat PIR_H = 1.0f;
const GLfloat ELO_H = 15.0f;
const GLfloat ELO_R = 2.0f;

Junta::Junta(GLfloat rotacaoMax,
             GLfloat atrito,
             GLfloat acelMax) {
    this->rotacaoMax = rotacaoMax;
    this->atrito = atrito;
    this->acelMax = acelMax;
    this->rotacao = 0;
    this->vel = 0;
    this->acel= 0;
}

void Junta::atualizar(float dt) {
    vel += acel;
    rotacao += vel * dt;
    vel *= atrito;

    if(rotacao > rotacaoMax) {
        rotacao = rotacaoMax;
        acel = 0;
        vel = 0;
    } else if(rotacao < -rotacaoMax) {
        rotacao = -rotacaoMax;
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

// Prismática ---------------------

void JuntaPrismatica::renderizar(int braco) {
    //Formas::piramide(PIR_W, PIR_H);
    // TODO
}

// Rotacional ---------------------

void JuntaRotacional::renderizar(int braco) {

    glRotatef(rotacao, 1.0f, 0.0f, 0.0f);
   // Formas::piramide(PIR_W, PIR_H);

    glTranslatef(0.0f, PIR_H, 0.0f);
	glCallList(braco);
    //Formas::cilindro(ELO_R, ELO_H, 16);
   // glTranslatef(0.0f, ELO_H, 0.0f);

}

// Torcional ----------------------

void JuntaTorcional::renderizar(int braco) {

  glRotatef(rotacao, 0.0f, 1.0f, 0.0f);
    //Formas::piramide(PIR_W, PIR_H);
	
   // glTranslatef(0.0f, PIR_H, 0.0f);
      glTranslatef(0.0f, 0, -3.0f);

	glCallList(braco);
    //Formas::cilindro(ELO_R, ELO_H, 16);
    //glTranslatef(0.0f, ELO_H, 0.0f);


}

// Revolvente ---------------------

void JuntaRevolvente::renderizar(int braco) {
//glScalef(20,20,20);
      
glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(rotacao, 0.0f, 1.0f, 0.0f);
    //Formas::piramide(PIR_W, PIR_H);
    glTranslatef(0.0f, PIR_H, 0.0f);

	glCallList(braco);
    //Formas::cilindro(ELO_R, ELO_H, 16);
    glTranslatef(0.0f, ELO_H, 0.0f);
}
