#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "formas.h"
#include "braco.h"
#include "camera.h"
#include "fisica.h"
#include "timing.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

GLfloat ambiente[4][4];
GLfloat difusao[4][4];  // degradê
GLfloat especular[4][4]; // brilho
GLfloat posicaoLuz[4][4];
bool enable[4];

void initIluminacao() {
    posicaoLuz[0][0] = 10.0f;
    posicaoLuz[0][1] = 5.0f;
    posicaoLuz[0][2] = 0.0f;
    posicaoLuz[0][3] = 0.0;

    especular[1][0] = 0.5;
    especular[1][1] = 0.5;
    especular[1][2] = 0.5;
    especular[1][3] = 1.0;

    posicaoLuz[1][0] = -10.0;
    posicaoLuz[1][1] = 5.0;
    posicaoLuz[1][2] = 0.0;
    posicaoLuz[1][3] = 1.0;

    // Spot
    posicaoLuz[2][3] = 1.0;

    posicaoLuz[3][0] = -20.0;
    posicaoLuz[3][1] = 5.0;
    posicaoLuz[3][2] = 0.0;
    posicaoLuz[3][3] = 1.0;

    difusao[1][0] = 0.4;
    difusao[1][1] = 0.4;
    difusao[1][2] = 0.4;
    difusao[1][3] = 1.0;

    difusao[2][0] = 1.0;
    difusao[2][1] = 1.0;
    difusao[2][2] = 1.0;
    difusao[2][3] = 1.0;

    difusao[3][0] = 0.5;
    difusao[3][1] = 0.5;
    difusao[3][2] = 0.5;
    difusao[3][3] = 1.0;

    ambiente[1][0] = 0.2;
    ambiente[1][1] = 0.2;
    ambiente[1][2] = 0.2;
    ambiente[1][3] = 1.0;

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING); // liga a luz

    enable[0] = 0;
    enable[1] = 1;
    enable[2] = 1;
    enable[3] = 0;

}

void iluminacao() {
        if(enable[0]) {
            glEnable(GL_LIGHT0); // define a luz 0
        } else {
            glDisable(GL_LIGHT0);
        }

        if(enable[1]) {
            glEnable(GL_LIGHT1); // define a luz 1
        } else {
            glDisable(GL_LIGHT1);
        }

        if(enable[2]) {
            glEnable(GL_LIGHT2); // define a luz 2 (spot)
        } else {
            glDisable(GL_LIGHT2);
        }

        if(enable[3]) {
            glEnable(GL_LIGHT3); // define a luz 3
        } else {
            glDisable(GL_LIGHT3);
        }

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente[1]);
        //glLightfv(GL_LIGHT0, GL_DIFFUSE, difusao[1]);
        //glLightfv(GL_LIGHT0, GL_SPECULAR, especular[1]);
        //glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz[0]);

        glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente[1]);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, difusao[1]);
        glLightfv(GL_LIGHT1, GL_SPECULAR, especular[1]);
        glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz[1]);

        glLightfv(GL_LIGHT2, GL_DIFFUSE, difusao[2]);
        glLightfv(GL_LIGHT2, GL_SPECULAR, especular[1]);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 30);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20);

        glLightfv(GL_LIGHT3, GL_DIFFUSE, difusao[3]);
        glLightfv(GL_LIGHT3, GL_SPECULAR, especular[1]);
        glLightfv(GL_LIGHT3, GL_POSITION, posicaoLuz[2]);
}

int main( int argc, char* args[] ) {
    SDL_Window* window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO |
                SDL_INIT_EVENTS |
                SDL_INIT_TIMER) < 0) {
        printf("Erro de inicialização do SDL: %s\n",
                SDL_GetError());
    } else {
        // SDL
        window = SDL_CreateWindow(
                "The Claw",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_OPENGL);

        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        SDL_Event e;

        Uint32 tempoAtual, tempoPassado;
        float dt;

        tempoAtual = SDL_GetTicks();

        bool quit;
        quit = false;

        const Uint8* keys = NULL;
        keys = SDL_GetKeyboardState(NULL);

        // OpenGL
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);


        initIluminacao();

        SDL_Surface *textura = SDL_LoadBMP("gama_2.bmp");
        SDL_Surface *brazuca = SDL_LoadBMP("brazuca.bmp");

        GLuint piso, esfera = 0;
        glGenTextures(1, &piso);
        glGenTextures(1, &esfera);

        // Programa
        Fisica* fisica = new Fisica();
        Camera* camera = new Camera();
        Braco* braco = new Braco();

        LoopTimer* exponentTimer = new LoopTimer(60.0f, 120.0f, 5.0f);

        while(!quit) {
            tempoPassado = tempoAtual;
            tempoAtual = SDL_GetTicks();
            dt = (tempoAtual - tempoPassado) / 1000.0f;

            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            if(!keys[SDL_SCANCODE_C]) {
                                braco->selecionarJunta(1);
                            }
                            break;
                        case SDLK_DOWN:
                            if(!keys[SDL_SCANCODE_C]) {
                                braco->selecionarJunta(-1);
                            }
                            break;
                        case SDLK_x:
                            camera->alterarProjecao();
                            break;
                        case SDLK_1:
                            enable[0] = !enable[0];
                            break;
                        case SDLK_2:
                            enable[1] = !enable[1];
                            break;
                        case SDLK_3:
                            enable[2] = !enable[2];
                            break;
                        case SDLK_4:
                            enable[3] = !enable[3];
                            break;
                        default:
                            break;
                    }
                } else if(e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            if(keys[SDL_SCANCODE_C]) {
                if(keys[SDL_SCANCODE_UP]) {
                    camera->alterarDirecao(0, 1);
                }
                if(keys[SDL_SCANCODE_DOWN]) {
                    camera->alterarDirecao(0, -1);
                }
                if(keys[SDL_SCANCODE_LEFT]) {
                    camera->alterarDirecao(1, 0);
                }
                if(keys[SDL_SCANCODE_RIGHT]) {
                    camera->alterarDirecao(-1, 0);
                }
            } else {
                if(keys[SDL_SCANCODE_LEFT]) {
                    braco->rotacionarSelecao(1);
                }

                if(keys[SDL_SCANCODE_RIGHT]) {
                    braco->rotacionarSelecao(-1);
                }
            }

            if(keys[SDL_SCANCODE_Z]) {
                if(keys[SDL_SCANCODE_LSHIFT]) {
                    camera->alterarZoom(-1);
                } else {
                    camera->alterarZoom(1);
                }
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera->atualizar(dt, braco);
            braco->atualizar(dt);
            fisica->atualizar(dt, braco);

            exponentTimer->atualizar(dt);

            // Projeção -------------

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            camera->projetar();

            // Renderização ----------------------------------

            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            iluminacao();

            camera->posicionar();

            glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, (int) exponentTimer->valor);

            Formas::grade(300.0f, 10.0f, textura, piso);

            glPushMatrix();
                braco->renderizar();
                posicaoLuz[2][0] = 0;
                posicaoLuz[2][1] = 0;
                posicaoLuz[2][2] = 0;
                glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz[2]);
            glPopMatrix();

            glColor3f(1.0, 0.0, 0.0);

            // Física ------------------------------------
            btTransform trans;
            fisica->fallRigidBody->getMotionState()->getWorldTransform(trans);

            btScalar m[16];
            trans.getOpenGLMatrix(m);

            glPushMatrix();
                glMultMatrixf((GLfloat*)m);

                Formas::cubo(1.0f);
            glPopMatrix();

            fisica->fallRigidBody2->getMotionState()->getWorldTransform(trans);
            trans.getOpenGLMatrix(m);


            glPushMatrix();
                glMultMatrixf((GLfloat*)m);

                Formas::cubo(1.0f);
            glPopMatrix();

            fisica->fallRigidBody3->getMotionState()->getWorldTransform(trans);
            trans.getOpenGLMatrix(m);

            glPushMatrix();
                glMultMatrixf((GLfloat*)m);

                Formas::cubo(1.0f);
            glPopMatrix();

            fisica->ballRigidBody->getMotionState()->getWorldTransform(trans);
            trans.getOpenGLMatrix(m);

            glPushMatrix();
                glMultMatrixf((GLfloat*)m);

                Formas::esfera(0.6, brazuca, esfera);
            glPopMatrix();

            SDL_GL_SwapWindow(window);

            glFlush();
        }

        SDL_FreeSurface(textura);
        SDL_FreeSurface(brazuca);
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);

        fisica->remover();
    }

    SDL_Quit();

    return 0;
}
