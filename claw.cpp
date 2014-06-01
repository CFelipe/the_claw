#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "formas.h"
#include "braco.h"
#include "camera.h"
#include "fisica.h"
#include "iluminacao.h"

const int   SCREEN_WIDTH = 800;
const int   SCREEN_HEIGHT = 600;

GLfloat ambiente[4][4];
GLfloat difusao[4][4];  // degradê
GLfloat especular[4][4]; // brilho
GLfloat posicaoLuz[4][4];

void iluminacao() {



        posicaoLuz[0][0] = 10.0f;
        posicaoLuz[0][1] = 5.0f;
        posicaoLuz[0][2] = 0.0f;
        posicaoLuz[0][3] = 0.0;

        difusao[1][0] = 0.7;
        difusao[1][1] = 0.7;
        difusao[1][2] = 0.7;
        difusao[1][3] = 1.0;

        especular[1][0] = 0.8;
        especular[1][1] = 0.8;
        especular[1][2] = 0.8;
        especular[1][3] = 1.0;

        posicaoLuz[1][0] = -10.0;
        posicaoLuz[1][1] = 5.0;
        posicaoLuz[1][2] = 00.0;
        posicaoLuz[1][3] = 1.0;

	posicaoLuz[3][0] = -20.0;
        posicaoLuz[3][1] = 5.0;
        posicaoLuz[3][2] = 0.0;
        posicaoLuz[3][3] = 1.0;

	
	
        posicaoLuz[2][3] = 1.0;
	
	difusao[2][0] = 10.0;
        difusao[2][1] = 10.0;
        difusao[2][2] = 10.0;
        difusao[2][3] = 1.0;

	difusao[3][0] = 0.5;
        difusao[3][1] = 0.5;
        difusao[3][2] = 0.5;
        difusao[3][3] = 1.0;


	ambiente[1][0] = 0.3;
        ambiente[1][1] = 0.3;
        ambiente[1][2] = 0.3;
        ambiente[1][3] = 0.3;
	
        /*glPushMatrix();
            glTranslatef(posicaoLuz[0][0], posicaoLuz[0][1], posicaoLuz[0][2]);
            Formas::piramide(1.0f, 2.0f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(posicaoLuz[1][0], posicaoLuz[1][1], posicaoLuz[1][2]);
            Formas::piramide(1.0f, 2.0f);
        glPopMatrix();


        glPushMatrix();
            glTranslatef(posicaoLuz[3][0], posicaoLuz[3][1], posicaoLuz[3][2]);
            Formas::piramide(0.5f, 1.0f);
        glPopMatrix();
	*/
	

	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambiente[1]);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,especular[1]);
        //glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 20); // componente especular do material
//
      // glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambiente[1]);

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente[1]);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, difusao[1]);
       	glLightfv(GL_LIGHT0, GL_SPECULAR, especular[1]);
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz[0]);

        glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente[1]);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, difusao[1]);
        glLightfv(GL_LIGHT1, GL_SPECULAR, especular[1]);
        glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz[1]);

        //glLightfv(GL_LIGHT3, GL_AMBIENT, ambiente[1]);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, difusao[3]);
        glLightfv(GL_LIGHT3, GL_SPECULAR, especular[1]);
        glLightfv(GL_LIGHT3, GL_POSITION, posicaoLuz[2]);

	


       // glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente[0]);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, difusao[2]);
       glLightfv(GL_LIGHT2, GL_SPECULAR, especular[1]);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT,0);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF,65);


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
        glEnable(GL_TEXTURE_2D);

        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING); // liga a luz
        glEnable(GL_LIGHT0); // define a luz 0
        glEnable(GL_LIGHT1); // define a luz 1
	glEnable(GL_LIGHT3); // define a luz 1

       glEnable(GL_LIGHT2); // define a luz 1
	
        SDL_Surface *textura = SDL_LoadBMP("gama_2.bmp");
        SDL_Surface *brazuca = SDL_LoadBMP("brazuca.bmp");

        GLuint piso, esfera = 0;
        glGenTextures(1, &piso);
        glGenTextures(1, &esfera);

        bool quit;

        Uint32 tempoAtual, tempoPassado;
        float dt;

        tempoAtual = SDL_GetTicks();

        quit = false;

        const Uint8* keys = NULL;
        keys = SDL_GetKeyboardState(NULL);

        Fisica* fisica = new Fisica();
        Camera* camera = new Camera();
        Braco* braco = new Braco();

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

            fisica->atualizar(dt);
            camera->atualizar(dt);
            braco->atualizar(dt);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            // Renderização ----------------------------------

            camera->posicionar();

            iluminacao();

            Formas::grade(300.0f, 10.0f, textura, piso);
            Formas::xyz(100.0f, 0.0f);

            glPushMatrix();
                glTranslatef(4, 0.5, -3);
                Formas::esfera(0.6, brazuca, esfera);
            glPopMatrix();

            glPushMatrix();
                braco->renderizar();
		posicaoLuz[2][0] = 0;
		posicaoLuz[2][1] = 0;
		posicaoLuz[2][2] = 0;	
		glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz[2]);
		 //  Formas::cubo(1.0f);
            glPopMatrix();

            std::cout << braco->posicaoPunho()[0] << std::endl;

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


            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            camera->projetar();

            glFlush();

            SDL_GL_SwapWindow(window);
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
