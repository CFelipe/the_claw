#include <SDL_opengl.h>
#include <math.h>
#include "formas.h"

const float EPSILON = 0.0001f;

void Formas::xyz(GLfloat tamanho, GLfloat altura) {
    glLineWidth(3);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0, altura, 0);
        glVertex3f(tamanho, altura, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0, altura, 0);
        glVertex3f(0, tamanho, 0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0, altura, 0);
        glVertex3f(0, altura, tamanho);
    glEnd();
}

void Formas::grade(GLfloat tamanho, GLfloat espaco) {
    glLineWidth(1);
    glColor3f(0, 1.0, 0.0);
    glBegin(GL_LINES);
        float i;

        i = -tamanho;
        while(i <= tamanho + EPSILON) {
            glVertex3f(i, 0, -tamanho);
            glVertex3f(i, 0,  tamanho);

            glVertex3f(-tamanho, 0, i);
            glVertex3f( tamanho, 0, i);
            i += espaco;
        }
    glEnd();
}

void Formas::cilindro(GLfloat raio, GLfloat altura, int lados) {
    glPushMatrix();
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    int i;
    float lado = 360.0f / lados;
    float rad = M_PI / 180.0f;

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0, 0.0);
        for(i = 0; i <= lados; i++) {
            glVertex3f(raio * cosf(i * lado * rad), 0, raio * sinf(i * lado * rad));
        }
    glEnd();

    for(i = 0; i <= lados; i++) {
        glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(raio * cosf(i * lado * rad), 0, raio * sinf(i * lado * rad));
            glVertex3f(raio * cosf(i * lado * rad), altura, raio * sinf(i * lado * rad));
            glVertex3f(raio * cosf((i + 1) * lado * rad), 0, raio * sinf((i + 1) * lado * rad));
            glVertex3f(raio * cosf((i + 1) * lado * rad), altura, raio * sinf((i + 1) * lado * rad));
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, altura, 0.0);
        for(i = 0; i <= lados; i++) {
            glVertex3f(raio * cosf(i * lado * rad), altura, raio * sinf(i * lado * rad));
        }
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void Formas::piramide(GLfloat base, GLfloat altura) {
    glPushMatrix();
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0, 0.0);
        glNormal3f(base,0,base);
        glVertex3f(base,0,base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(-base,0,base);
        glVertex3f(-base,0,base);
        glNormal3f(-base,0,base);

        glColor3f(0, 1.0, 0.0);
        glVertex3f(-base,0,base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(-base,0,-base);
        glVertex3f(-base,0,-base);
        glNormal3f(-base,0,-base);

        glColor3f(0, 0, 1.0);
        glVertex3f(-base,0,-base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(base,0,-base);
        glVertex3f(base,0,-base);
        glNormal3f(base,0,-base);

        glColor3f(0, 1.0, 1.0);
        glVertex3f(base,0,-base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(base,0,base);
        glVertex3f(base,0,base);

    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}
