#ifndef JUNTA_H
#define JUNTA_H

#include <SDL_opengl.h>

class Junta {
    public:
        Junta(GLfloat rotacaoMax = 45.0f,
              GLfloat atrito = 0.95f);
        void rotacionar(GLfloat graus);
        void atualizar();
        virtual void renderizar() = 0;

    protected:
        GLfloat rotacaoMax;
        GLfloat rotacao;
        GLfloat atrito;
        GLfloat vel;
        GLfloat acel;
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
