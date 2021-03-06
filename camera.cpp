#include "camera.h"
#include <SDL_opengl.h>
#include <iostream>

Camera::Camera() {
    this->acelMax = 7.0f;
    this->atrito = 0.85f;
    this->rotacaoX = 45.0f;
    this->rotacaoY = 20.0f;
    this->zoom = 0.0f;
    this->velX = 0.0f;
    this->velY = 0.0f;
    this->velZoom = 0.0f;
    this->acelX = 0.0f;
    this->acelY = 0.0f;
    this->acelZoom = 0.0f;
    this->projecao = PERSPECTIVA;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->prevX = 0;
    this->prevY = 0;
    this->prevZ = 0;
}

void Camera::alterarDirecao(int horizontal, int vertical) {
    if(horizontal == 1) {
        acelX = acelMax;
    } else if(horizontal == -1) {
        acelX = -acelMax;
    }

    if(vertical == 1) {
        acelY = acelMax;
    } else if(vertical == -1) {
        acelY = -acelMax;
    }
}

void Camera::alterarZoom(int direcao) {
    if(direcao == 1) {
        acelZoom = acelMax / 100;
    } else if(direcao == -1) {
        acelZoom = -acelMax / 100;
    }
}

void Camera::alterarProjecao() {
    if(this->projecao == PERSPECTIVA) {
        this->projecao = ORTOGRAFICA;
    } else if(this->projecao == ORTOGRAFICA) {
        this->projecao = PERSPECTIVA;
    }
}

void Camera::atualizar(float dt, Braco* b) {
    if(rotacaoY < 10 && acelY < 0) {
        acelY = 0;
    }

    if(rotacaoY > 80 && acelY > 0) {
        acelY = 0;
    }

    x += (b->sel[12] - x) / 15;
    y += (b->sel[13] - y) / 15;
    z += (b->sel[14] - z) / 15;

    velX += acelX;
    velY += acelY;
    velZoom += acelZoom;
    rotacaoX += velX * dt;
    rotacaoY += velY * dt;
    zoom += velZoom * dt;
    velX *= atrito;
    velY *= atrito;
    velZoom *= atrito;

    acelX = 0;
    acelY = 0;
    acelZoom = 0;
}

void Camera::posicionar() {
    glScalef(zoom + 1, zoom + 1, zoom + 1);

    glTranslatef(0.0f, 0.0f, -50.0f);
    glRotatef(rotacaoY, 1.f, 0.f, 0.f);
    glRotatef(rotacaoX, 0.f, 1.f, 0.f);
    glTranslatef(-x, -y, -z);
}

void Camera::projetar() {
    if(projecao == PERSPECTIVA) {
        perspPro(15.0f, 1.5f, 1, 1000);
    } else if(projecao == ORTOGRAFICA) {
        orthoPro();
    }
}

void Camera::orthoPro() {
    glOrtho(-15.0f, 15.0f,  // L, R
            -10.0f, 10.0f,  // B, T
            -500, 500);     // N, F
}

void Camera::perspPro(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far) {
    GLfloat fH, fW;
    fH = tan(fovy / 360 * M_PI) * near;
    fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, near, far);
}
