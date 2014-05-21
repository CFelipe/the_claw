#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include <iostream>

const float EPSILON = 0.0001f;

const int   SCREEN_WIDTH = 800;
const int   SCREEN_HEIGHT = 600;
const float ACEL = 0.2f;
const float MAX_VEL = 3.0f;
const float VEL_DEC = 0.85f;
const float ACEL_RESET = 0.85f;
const float PIR_W = 10.0f;
const float PIR_H = 20.0f;
const float CAM_DIST = 70.0f;

void cam1(GLfloat x, GLfloat y) {
    glScalef(0.3f, 0.3f, 0.3f);
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

void xyz(GLfloat tamanho) {
    glLineWidth(5);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(tamanho, 0, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, tamanho, 0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, tamanho);
    glEnd();
}

void grade(GLfloat tamanho, GLfloat espaco) {
    glLineWidth(1);
    glColor3f(0, 1.0, 0.0);
    glBegin(GL_LINES);
        float i;

        i = -tamanho;
        while(i <= tamanho + EPSILON) {
            glVertex3f(i, 0, -tamanho);
            glVertex3f(i, 0,  tamanho);

            glVertex3f(-tamanho, 0, i);
            glVertex3f( tamanho, 0, i);
            i += espaco;
        }
    glEnd();
}

void cilindro(GLfloat raio, GLfloat altura, int lados) {
    glPushMatrix();
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    int i;
    float lado = 360.0f / lados;
    float rad = M_PI / 180.0f;

    glColor3f(1.0, 0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0, 0.0);
        for(i = 0; i <= lados; i++) {
            glVertex3f(raio * cosf(i * lado * rad), 0, raio * sinf(i * lado * rad));
        }
    glEnd();

    for(i = 0; i <= lados; i++) {
        glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(raio * cosf(i * lado * rad), 0, raio * sinf(i * lado * rad));
            glVertex3f(raio * cosf(i * lado * rad), altura, raio * sinf(i * lado * rad));
            glVertex3f(raio * cosf((i + 1) * lado * rad), 0, raio * sinf((i + 1) * lado * rad));
            glVertex3f(raio * cosf((i + 1) * lado * rad), altura, raio * sinf((i + 1) * lado * rad));
        glEnd();
    }

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, altura, 0.0);
        for(i = 0; i <= lados; i++) {
            glVertex3f(raio * cosf(i * lado * rad), altura, raio * sinf(i * lado * rad));
        }
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void piramide(GLfloat base, GLfloat altura) {
    glPushMatrix();
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0, 0.0);
        glNormal3f(base,0,base);
        glVertex3f(base,0,base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(-base,0,base);
        glVertex3f(-base,0,base);
        glNormal3f(-base,0,base);

        glColor3f(0, 1.0, 0.0);
        glVertex3f(-base,0,base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(-base,0,-base);
        glVertex3f(-base,0,-base);
        glNormal3f(-base,0,-base);

        glColor3f(0, 0, 1.0);
        glVertex3f(-base,0,-base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(base,0,-base);
        glVertex3f(base,0,-base);
        glNormal3f(base,0,-base);

        glColor3f(0, 1.0, 1.0);
        glVertex3f(base,0,-base);
        glNormal3f(0,altura,0);
        glVertex3f(0,altura,0);
        glNormal3f(base,0,base);
        glVertex3f(base,0,base);

    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
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

        /*
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glHint (GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
        glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        */

        bool quit;
        float r_mult = 1;
        float x_mult = 1;
        float y_mult = 1;
        GLfloat x, y, x_vel, y_vel, x_acel, y_acel;
        x = y = 0;

        while(!quit) {
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            y_acel = ACEL;
                            y_mult = 1;
                            break;
                        case SDLK_DOWN:
                            y_acel = -ACEL;
                            y_mult = 1;
                            break;
                        case SDLK_LEFT:
                            x_acel = ACEL;
                            x_mult = 1;
                            break;
                        case SDLK_RIGHT:
                            x_acel = -ACEL;
                            x_mult = 1;
                            break;
                        case SDLK_SPACE:
                            r_mult = ACEL_RESET;
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
                        case SDLK_SPACE:
                            r_mult = 1;
                            break;
                    }
                } else if(e.type == SDL_QUIT) {
                    quit = true;
                }
            }

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
            //cam2();

            grade(300.0f, 5.0f);
            xyz(30.0f);

            piramide(PIR_W, PIR_H);

            glTranslatef(0.0f, PIR_H, 0.0f);
            cilindro(1.0f, PIR_H, 16);

            glTranslatef(0.0f, PIR_H, 0.0f);
            glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
            glRotatef(x, 0.0f, 1.0f, 0.0f);
            piramide(PIR_W, PIR_H);

            glTranslatef(0.0f, PIR_H, 0.0f);
            glRotatef(x, 0.0f, 1.0f, 0.0f);
            piramide(PIR_W, PIR_H);

            glTranslatef(0.0f, PIR_H, 0.0f);
            glRotatef(x, 0.0f, 1.0f, 0.0f);
            piramide(PIR_W, PIR_H);

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
