#ifndef BRACO_H
#define BRACO_H

enum Tipo {PRISMATICA,
           ROTACIONAL,
           TORCIONAL,
           REVOLVENTE};

class Junta {
    public:
        void ~Junta() {}
        virtual void rotacionar(GLfloat graus) = 0;
        virtual void renderizar();

    private:
        GLfloat rotacaoMax;
        GLfloat rotacao;
};

#endif
