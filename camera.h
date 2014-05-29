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
        void alterarZoom(int direcao);
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
        GLfloat acelX, acelY, acelZoom;
        GLfloat velX, velY, velZoom;
        GLfloat rotacaoX, rotacaoY;
        GLfloat zoom;

        void orthoPro();
        void perspPro(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);
};

#endif
