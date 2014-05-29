#ifndef LOAD_H
#define LOAD_H

/*    //#include <windows.h>
   #include <SDL.h>
#include "SDL/SDL.h"
#include "SDL.h"
#include <SDL_opengl.h>
#include <SDL/SDL.h>
#include <GL/glx.h>
//#include <SDL/SDL.h> //check your include folder, it may be just SDL.h

    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <cstdlib>
    #include <vector>
    #include <string>
    #include <algorithm>
    #include <fstream>
    #include <cstdio>
    #include <iostream> */
     
class Load{
	public:
		Load();
		static int loadObject(const char* filename);
};

#endif
