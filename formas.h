
#ifndef FORMAS_H
#define FORMAS_H

#include <SDL.h>
#include <SDL_opengl.h>

class Formas {
    public:
        static void piramide(GLfloat base, GLfloat altura);
        static void cilindro(GLfloat raio, GLfloat altura, int lados);
        static void xyz(GLfloat tamanho, GLfloat altura);
        static void grade(GLfloat tamanho, GLfloat espaco, SDL_Surface *textura, GLuint id);
	static void criaTextura(SDL_Surface* image, GLuint id);
	static void esfera(SDL_Surface *textura, GLuint id);
};

#endif
