#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include <iostream>

const int   SCREEN_WIDTH = 800;
const int   SCREEN_HEIGHT = 600;
const float ACEL = 0.2f;
const float MAX_VEL = 3.0f;
const float VEL_DEC = 0.85;
const float ACEL_RESET = 0.85;

void cam1(GLfloat x, GLfloat y) {
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(y, -1.f, 0.f, 0.f);
    glRotatef(x, 0.f, -1.f, 0.f);
}

void cam2() {
    glScalef(0.5f, 0.5f, 0.5f);
    glRotatef(45, 1.f, 0.f, 0.f);
    glRotatef(45, 0.f, 1.f, 0.f);
}

void grade() {
    glColor3f(0, 1.0, 0.0);
    glBegin(GL_LINES);
        float i;

        i = -2;
        while(i <= 2.05) {
            glVertex3f(i, 0, -2);
            glVertex3f(i, 0,  2);
            i += 0.1;
        }

        i = -2;
        while(i <= 2.05) {
            glVertex3f(-2, 0, i);
            glVertex3f( 2, 0, i);
            i += 0.1;
        }
    glEnd();
}

void piramide() {
    glPushMatrix();
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0, 0.0);
        glNormal3f(1,0,1);
        glVertex3f(1,0,1); //
        glNormal3f(0,2,0); //
        glVertex3f(0,2,0); //
        glNormal3f(-1,0,1); //
        glVertex3f(-1,0,1); //
        glNormal3f(-1,0,1);

        glColor3f(0, 1.0, 0.0);
        glVertex3f(-1,0,1); //
        glNormal3f(0,2,0); //
        glVertex3f(0,2,0); //
        glNormal3f(-1,0,-1); //
        glVertex3f(-1,0,-1); //
        glNormal3f(-1,0,-1);

        glColor3f(0, 0, 1.0);
        glVertex3f(-1,0,-1); //
        glNormal3f(0,2,0); //
        glVertex3f(0,2,0); //
        glNormal3f(1,0,-1); //
        glVertex3f(1,0,-1); //
        glNormal3f(1,0,-1);

        glColor3f(0, 1.0, 1.0);
        glVertex3f(1,0,-1); //
        glNormal3f(0,2,0); //
        glVertex3f(0,2,0); //
        glNormal3f(1,0,1); //
        glVertex3f(1,0,1); //

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

            //cam1(x, y);
            cam2();

            grade();

            piramide();

            glTranslatef(0.0f, 2.0f, 0.0f);
            glRotatef(y, 1.0f, 0.0f, 0.0f);
            glRotatef(x, 0.0f, 1.0f, 0.0f);
            piramide();

            glTranslatef(0.0f, 2.0f, 0.0f);
            glRotatef(x, 0.0f, 1.0f, 0.0f);
            piramide();

            glTranslatef(0.0f, 2.0f, 0.0f);
            glRotatef(x, 0.0f, 1.0f, 0.0f);
            piramide();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-3, 3,      // L, R
                    -3, 3,      // B, T
                    -10, 10);   // N, F

            glFlush();

            SDL_GL_SwapWindow(window);
        }

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}
