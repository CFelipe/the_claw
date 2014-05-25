#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "formas.h"
#include "braco.h"

const int   SCREEN_WIDTH = 800;
const int   SCREEN_HEIGHT = 600;
const float ACEL = 0.2f;
const float MAX_VEL = 3.0f;
const float VEL_DEC = 0.85f;
const float ACEL_RESET = 0.85f;
const float PIR_W = 10.0f;
const float PIR_H = 20.0f;
const float CAM_DIST = 70.0f;

GLfloat ambiente[4];
GLfloat difusao[2][4];  // degradê
GLfloat especular[2][4]; // brilho
GLfloat posicaoLuz[2][4];


void cam1(GLfloat x, GLfloat y) {
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, -10.0f, 0.0f);
    glRotatef(y, 1.f, 0.f, 0.f);
    glRotatef(x, 0.f, 1.f, 0.f);
}

void cam2() {
    glScalef(0.5f, 0.5f, 0.5f);
    glRotatef(45, 1.f, 0.f, 0.f);
    glRotatef(45, 0.f, 1.f, 0.f);
}

void persp1() {
    glOrtho(-CAM_DIST, CAM_DIST,        // L, R
            -CAM_DIST, CAM_DIST,        // B, T
            -500, 500);                 // N, F
}

void persp2() {
    //glRotatef(15, 0.f, 1.f, 0.f);
    glFrustum(-3, 3,      // L, R
              -3, 3,      // B, T
              -10, 10);   // N, F
}


void iluminacao(GLfloat x, GLfloat y){
        ambiente[0] = 0.3;
        ambiente[1] = 0.3;
        ambiente[2] = 0.3;
        ambiente[3] = 1.0;

        difusao[0][0] = 0.3;
        difusao[0][1] = 0.3;
        difusao[0][2] = 0.3;
        difusao[0][3] = 1.0;

        especular[0][0] = 0.2;
        especular[0][1] = 0.2;
        especular[0][2] = 0.2;
        especular[0][3] = 1.0;

        posicaoLuz[0][0] = 50.0f;
        posicaoLuz[0][1] = 50.0f;
        posicaoLuz[0][2] = 0.0;
        posicaoLuz[0][3] = 1.0;

        difusao[1][0] = 0.5;
        difusao[1][1] = 0.5;
        difusao[1][2] = 0.5;
        difusao[1][3] = 1.0;

        especular[1][0] = 1.0;
        especular[1][1] = 1.0;
        especular[1][2] = 1.0;
        especular[1][3] = 1.0;

        posicaoLuz[1][0] = 50.0;
        posicaoLuz[1][1] = 50.0;
        posicaoLuz[1][2] = 0.0;
        posicaoLuz[1][3] = 1.0;

        glPushMatrix();
            glTranslatef(posicaoLuz[0][0], posicaoLuz[0][1], posicaoLuz[0][2]);
            Formas::piramide(10.0f, 20.0f);
        glPopMatrix();

        //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambiente);
        //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, especular[0]);
        //glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 10); // componente especular do material

        //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambiente);

        //glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, difusao[0]);
        //glLightfv(GL_LIGHT1, GL_SPECULAR, especular[0]);
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz[0]);

        //glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
        //glLightfv(GL_LIGHT1, GL_DIFFUSE, difusao[1]);
        //glLightfv(GL_LIGHT1, GL_SPECULAR, especular[1]);
        //glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz[1]);

}

int main( int argc, char* args[] ) {
    SDL_Window* window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO |
                SDL_INIT_AUDIO |
                SDL_INIT_EVENTS |
                SDL_INIT_TIMER) < 0) {
        printf("Erro de inicialização do SDL: %s\n",
                SDL_GetError());
    } else {
        window = SDL_CreateWindow(
                "The Claw",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_OPENGL);

        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        SDL_Event e;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_LIGHTING); // liga a luz
        glEnable(GL_LIGHT0); // define qual luz

        //glEnable(GL_LIGHT1); // define qual luz
        //glEnable(GL_COLOR_MATERIAL);

        bool quit;
        float r_mult, x_mult, y_mult;
        GLfloat x, y, x_vel, y_vel, x_acel, y_acel;

        r_mult = x_mult = y_mult = 1;
        x = y = x_vel = y_vel = x_acel = y_acel = 0;
        quit = false;

        const Uint8* keys = NULL;
        keys = SDL_GetKeyboardState(NULL);

        Braco* braco = new Braco();

        while(!quit) {
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            if(keys[SDL_SCANCODE_C]) {
                                y_acel = ACEL;
                                y_mult = 1;
                            } else {
                                braco->selecionarJunta(1);
                            }
                            break;
                        case SDLK_DOWN:
                            if(keys[SDL_SCANCODE_C]) {
                                y_acel = -ACEL;
                                y_mult = 1;
                            } else {
                                braco->selecionarJunta(-1);
                            }
                            break;
                        case SDLK_LEFT:
                            if(keys[SDL_SCANCODE_C]) {
                                x_acel = ACEL;
                                x_mult = 1;
                            }
                            break;
                        case SDLK_RIGHT:
                            if(keys[SDL_SCANCODE_C]) {
                                x_acel = -ACEL;
                                x_mult = 1;
                            }
                            break;
                            /*
                        case SDLK_SPACE:
                            r_mult = ACEL_RESET;
                            break;
                            */
                        default:
                            break;
                    }
                } else if(e.type == SDL_KEYUP) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            y_acel = 0;
                            y_mult = VEL_DEC;
                            break;
                        case SDLK_DOWN:
                            y_acel = 0;
                            y_mult = VEL_DEC;
                            break;
                        case SDLK_LEFT:
                            x_acel = 0;
                            x_mult = VEL_DEC;
                            break;
                        case SDLK_RIGHT:
                            x_acel = 0;
                            x_mult = VEL_DEC;
                            break;
                            /*
                        case SDLK_SPACE:
                            r_mult = 1;
                            break;
                            */
                        default:
                            break;
                    }
                } else if(e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            if(keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_C]) {
                braco->rotacionarSelecao(1);
            }

            if(keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_C]) {
                braco->rotacionarSelecao(-1);
            }

            braco->atualizar();

            if(x_vel > MAX_VEL) {
                x_vel = MAX_VEL;
            } else if(x_vel < -MAX_VEL) {
                x_vel = -MAX_VEL;
            }

            if(y_vel > MAX_VEL) {
                y_vel = MAX_VEL;
            } else if(y_vel < -MAX_VEL) {
                y_vel = -MAX_VEL;
            }

            x_vel *= x_mult;
            y_vel *= y_mult;
            x_vel += x_acel;
            y_vel += y_acel;
            x += x_vel;
            y += y_vel;
            x *= r_mult;
            y *= r_mult;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            cam1(x, y);

            iluminacao(x, y);

            Formas::grade(300.0f, 5.0f);
            Formas::xyz(100.0f, 1.0f);

            braco->renderizar();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            persp1();

            glFlush();

            SDL_GL_SwapWindow(window);
        }

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}
