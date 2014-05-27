#include <SDL_opengl.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "formas.h"

const float EPSILON = 0.0001f;
const float PI = 3.14;
void Formas::criaTextura(SDL_Surface* image)
{   

    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLint formato = image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, formato,image->w, image->h, 0, formato, GL_UNSIGNED_BYTE, image->pixels);



} 


void Formas::esfera(SDL_Surface *textura){
    
    glEnable(GL_TEXTURE_2D);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1.0, 1.0, 1.0);

    criaTextura(textura);
    GLUquadricObj *q =  gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);

    gluSphere(q,9,15,15);

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

void Formas::grade(GLfloat tamanho, GLfloat espaco, SDL_Surface *textura) {
    
    glEnable(GL_TEXTURE_2D);

    glLineWidth(1);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0, 1.0, 0);
    glNormal3f(0,1,0);
    criaTextura(textura);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3f(-256, 0, -256);

    glTexCoord2i(0,2);
    glVertex3f(-256, 0, 256);

    glTexCoord2i(2,2);
    glVertex3f(256, 0, 256);

    glTexCoord2i(2,0);
    glVertex3f(256, 0, -256);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    /*glBegin(GL_LINES);

        float i;

        i = -tamanho;
        while(i <= tamanho + EPSILON) {
            glVertex3f(i, 0, -tamanho);
            glVertex3f(i, 0,  tamanho);

            glVertex3f(-tamanho, 0, i);
            glVertex3f( tamanho, 0, i);
            i += espaco;
        }
    glEnd();*/
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
