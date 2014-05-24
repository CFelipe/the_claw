#ifndef JUNTA_H
#define JUNTA_H

#include <SDL_opengl.h>

class Junta {
    public:
        Junta(GLfloat rotacaoMax = 45.0f,
              GLfloat atrito = 0.75f,
              GLfloat acelMax = 0.15f);
        void atualizar();
        void rotacionar(int i);
        virtual void renderizar() = 0;

    protected:
        // Constantes
        GLfloat rotacaoMax;
        GLfloat acelMax;
        GLfloat atrito;
        // Variáveis
        GLfloat acel;
        GLfloat vel;
        GLfloat rotacao;
};

class JuntaPrismatica : public Junta {
    public:
        JuntaPrismatica() : Junta() {}
        void renderizar();
};

class JuntaRotacional : public Junta {
    public:
        JuntaRotacional() : Junta() {}
        void renderizar();
};

class JuntaTorcional : public Junta {
    public:
        JuntaTorcional() : Junta() {}
        void renderizar();
};

class JuntaRevolvente : public Junta {
    public:
        JuntaRevolvente() : Junta() {}
        void renderizar();
};

#endif
