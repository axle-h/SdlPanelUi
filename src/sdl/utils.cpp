#include <iostream>
#include <SDL.h>

#include "utils.h"

template<>
void sdlCleanup<SDL_Cursor>(SDL_Cursor *cursor) {
    if (!cursor){
        return;
    }
    SDL_FreeCursor(cursor);
}

template<>
void sdlCleanup<SDL_Surface>(SDL_Surface *surf) {
    if (!surf){
        return;
    }
    SDL_FreeSurface(surf);
}