#ifndef JUNTA_H
#define JUNTA_H

#include <SDL_opengl.h>
#include "Load.h"

class Junta {
    public:
        Junta(GLfloat rotacaoMax = 45.0f,
              GLfloat rotacaoMin = 0.0f,
              GLfloat rotacaoInicial = 0.0f,
              GLfloat atrito = 0.85f,
              GLfloat acelMax = 3.00f);
        void atualizar(float dt);
        void rotacionar(int i);
        virtual void renderizar() = 0;
        GLfloat rotacao;

    protected:
        // Constantes
        GLfloat rotacaoMax;
        GLfloat rotacaoMin;
        GLfloat acelMax;
        GLfloat atrito;
        // Variáveis
        GLfloat acel;
        GLfloat vel;

        int modelo;
};

class BaseTorcional : public Junta {
    public:
        BaseTorcional();
        void renderizar();
};

class JuntaRotacional1 : public Junta {
    public:
        JuntaRotacional1();
        void renderizar();
};

class JuntaRotacional2 : public Junta {
    public:
        JuntaRotacional2();
        void renderizar();
};

class JuntaRotacional3 : public Junta {
    public:
        JuntaRotacional3();
        void renderizar();
};

class JuntaTorcional : public Junta {
    public:
        JuntaTorcional();
        void renderizar();
};

class Garra : public Junta {
    public:
        Garra();
        void renderizar();
    private:
        int modelo2;
};

#endif
