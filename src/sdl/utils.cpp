#include <iostream>
#include <SDL.h>

#include "utils.h"

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(const std::string &msg){
    std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

/*
 * These specializations serve to free the passed argument and also provide the
 * base cases for the recursive call above, eg. when args is only a single item
 * one of the specializations below will be called by
 * cleanup(std::forward<Args>(args)...), ending the recursion
 * We also make it safe to pass nullptrs to handle situations where we
 * don't want to bother finding out which values failed to load (and thus are null)
 * but rather just want to clean everything up and let cleanup sort it out
 */

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