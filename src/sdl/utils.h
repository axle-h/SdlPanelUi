#pragma once


/*
 * Recurse through the list of arguments to clean up, cleaning up
 * the first one in the list each iteration.
 */
template<typename T, typename... Args>
void sdlCleanup(T *t, Args &&... args) {
    //Cleanup the first item in the list
    sdlCleanup(t);
    //Recurse to clean up the remaining arguments
    sdlCleanup(std::forward<Args>(args)...);
}

template<> void sdlCleanup<SDL_Cursor>(SDL_Cursor *cursor);
template<> void sdlCleanup<SDL_Surface>(SDL_Surface *surface);