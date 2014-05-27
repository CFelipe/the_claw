#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_opengl.h>
#include <math.h>

enum Projecao {PERSPECTIVA,
               ORTOGRAFICA};

class Camera {
    public:
        Camera();
        void alterarDirecao(int horizontal, int vertical);
        void alterarProjecao();
        void atualizar(float dt);
        void posicionar();
        void projetar();
    private:
        Projecao projecao;
        // Constantes
        GLfloat acelMax;
        GLfloat atrito;
        // Variáveis
        GLfloat acelX, acelY;
        GLfloat velX, velY;
        GLfloat rotacaoX, rotacaoY;

        void orthoPro();
        void perspPro(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);
};

#endif
