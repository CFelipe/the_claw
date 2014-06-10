#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "formas.h"

void Formas::criaTextura(SDL_Surface* image, GLuint id) {

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLint formato = image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, formato,image->w, image->h, 0, formato, GL_UNSIGNED_BYTE, image->pixels);
}


void Formas::esfera(GLfloat raio, SDL_Surface *textura, GLuint id){
    glEnable(GL_TEXTURE_2D);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1.0, 1.0, 1.0);
    criaTextura(textura, id);
    GLUquadricObj *q =  gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);

    gluSphere(q,raio,15,15);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}

void Formas::xyz(GLfloat tamanho, GLfloat altura) {
    glLineWidth(3);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

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

    glDisable(GL_COLOR_MATERIAL);
}

void Formas::grade(GLfloat tamanho, GLfloat espaco, SDL_Surface *textura, GLuint id) {
    int coordMax = 256;

    glEnable(GL_TEXTURE_2D);

    glLineWidth(1);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(1,-1,0);
    criaTextura(textura, id);

    glBegin(GL_QUADS);
        glTexCoord2i(0,0);
        glVertex3f(-256, 0, -256);

        glTexCoord2i(0,coordMax);
        glVertex3f(-256, 0, 256);

        glTexCoord2i(coordMax,coordMax);
        glVertex3f(256, 0, 256);

        glTexCoord2i(coordMax,0);
        glVertex3f(256, 0, -256);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);

}

void Formas::cilindro(GLfloat raio, GLfloat altura, int lados) {
    glPushMatrix();

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    int i;
    float lado = 360.0f / lados;
    float rad = M_PI / 180.0f;

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0, 0.0);
    for(i = 0; i <= lados; i++) {
        glNormal3f(0,-1,0);
        glVertex3f(raio * cosf(i * lado * rad), 0, raio * sinf(i * lado * rad));
    }
    glEnd();

    for(i = 0; i <= lados; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(cosf(i * lado * rad), 0.0, cosf(i * lado * rad));
        glVertex3f(raio * cosf(i * lado * rad), 0, raio * sinf(i * lado * rad));
        glVertex3f(raio * cosf(i * lado * rad), altura, raio * sinf(i * lado * rad));
        glVertex3f(raio * cosf((i + 1) * lado * rad), 0, raio * sinf((i + 1) * lado * rad));
        glVertex3f(raio * cosf((i + 1) * lado * rad), altura, raio * sinf((i + 1) * lado * rad));
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, altura, 0.0);
    for(i = 0; i <= lados; i++) {
        glNormal3f(0,1,0);
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

void Formas::cubo(float lado) {
    glPushMatrix();
    glTranslatef(-lado * 0.5f, -lado * 0.5f, -lado * 0.5f);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_POLYGON);/* f1: front */
        glNormal3f(-lado,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,lado);
        glVertex3f(lado,0.0f,lado);
        glVertex3f(lado,0.0f,0.0f);
    glEnd();
    glBegin(GL_POLYGON);/* f2: bottom */
        glNormal3f(0.0f,0.0f,-lado);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(lado,0.0f,0.0f);
        glVertex3f(lado,lado,0.0f);
        glVertex3f(0.0f,lado,0.0f);
    glEnd();
        glBegin(GL_POLYGON);/* f3:back */
            glNormal3f(lado,0.0f,0.0f);
            glVertex3f(lado,lado,0.0f);
            glVertex3f(lado,lado,lado);
            glVertex3f(0.0f,lado,lado);
            glVertex3f(0.0f,lado,0.0f);
        glEnd();

        glBegin(GL_POLYGON);/* f4: top */
            glNormal3f(0.0f,0.0f,lado);
            glVertex3f(lado,lado,lado);
            glVertex3f(lado,0.0f,lado);
            glVertex3f(0.0f,0.0f,lado);
            glVertex3f(0.0f,lado,lado);
        glEnd();
        glBegin(GL_POLYGON);/* f5: left */
            glNormal3f(0.0f,lado,0.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,lado,0.0f);
            glVertex3f(0.0f,lado,lado);
            glVertex3f(0.0f,0.0f,lado);
        glEnd();
        glBegin(GL_POLYGON);/* f6: right */
            glNormal3f(0.0f,-lado,0.0f);
            glVertex3f(lado,0.0f,0.0f);
            glVertex3f(lado,0.0f,lado);
            glVertex3f(lado,lado,lado);
            glVertex3f(lado,lado,0.0f);
        glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}
