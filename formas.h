#ifndef FORMAS_H
#define FORMAS_H

class Formas {
    public:
        static void piramide(GLfloat base, GLfloat altura);
        static void cilindro(GLfloat raio, GLfloat altura, int lados);
        static void xyz(GLfloat tamanho, GLfloat altura);
        static void grade(GLfloat tamanho, GLfloat espaco);
        static void base();
};

#endif
