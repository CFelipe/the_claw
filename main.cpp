#include <SDL.h>
#include <SDL_opengl.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main( int argc, char* args[] ) {
    SDL_Window* window = NULL;
    //SDL_Event e;

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
        SDL_Event windowEvent;
        bool quit;

        while(!quit) {
            if(SDL_PollEvent(&windowEvent)) {
                if(windowEvent.type == SDL_QUIT) {
                    quit = true;
                }
            }

            glClearColor(1.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_TRIANGLES);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f( 0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(-1.0f, -1.0f, 1.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(1.0f, -1.0f, 1.0f);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(1.0f, -1.0f, 1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(1.0f, -1.0f, -1.0f);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(1.0f, -1.0f, -1.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(-1.0f, -1.0f, -1.0f);

                glColor3f(1.0f,0.0f,0.0f);
                glVertex3f( 0.0f, 1.0f, 0.0f);
                glColor3f(0.0f,0.0f,1.0f);
                glVertex3f(-1.0f,-1.0f,-1.0f);
                glColor3f(0.0f,1.0f,0.0f);
                glVertex3f(-1.0f,-1.0f, 1.0f);
            glEnd();

            SDL_GL_SwapWindow(window);
        }

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}
