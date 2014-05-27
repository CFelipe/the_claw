#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>
#include "formas.h"

const float EPSILON = 0.0001f;

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

void Formas::grade(GLfloat tamanho, GLfloat espaco) {
    glLineWidth(1);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(0, 1.0, 0.0);
    glNormal3f(0,1,0);
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
    glDisable(GL_COLOR_MATERIAL);
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

void Formas::base() {
}

/*
void load_obj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements) {
*/
    /*
    ifstream in(filename, ios::in);
    if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }

    string line;
    while (getline(in, line)) {
        if (line.substr(0,2) == "v ") {
        istringstream s(line.substr(2));
        glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
        vertices.push_back(v);
        }  else if (line.substr(0,2) == "f ") {
        istringstream s(line.substr(2));
        GLushort a,b,c;
        s >> a; s >> b; s >> c;
        a--; b--; c--;
        elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#') {}
        else {}
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < elements.size(); i+=3) {
        GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(
        glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
        glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
    */
/*
}
*/
