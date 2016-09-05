#ifndef SDLCALLER_H
#define SDLCALLER_H

extern "C" {
#include <SDL.h>
#include <SDL_image.h>
}

/*
 * This is a wrapper class for the SDL2 libraries,
 * used internally to abstract out dependencies on C code.
 * Should NOT be used by client code.
 */
class SDLCaller {
public:

	inline bool initialiseSDL(Uint32 flags) {
		if (SDL_WasInit(flags) == 0) {
			return SDL_Init(flags) == 0;
		}
		return true;
	}

	inline bool initialiseSDLImage(Uint32 flags) {
		return (IMG_Init(flags) & flags);
	}

	inline void quitSDL() {
		return SDL_Quit();
	}

	inline void quitSDLImage() {
		return IMG_Quit();
	}

	inline SDL_Window* createSDLWindow(const char* windowTitle, int windowX, int windowY, int windowWidth, int windowHeight, Uint32 flags) {
		return SDL_CreateWindow(windowTitle, windowX, windowY, windowWidth, windowHeight, flags);
	}

	inline SDL_Renderer* createSDLRenderer(SDL_Window* window, int index, Uint32 flags) {
		return SDL_CreateRenderer(window, index, flags);
	}

	inline SDL_Texture* loadSDLImageTexture(SDL_Renderer* renderer, const char* filepath) {
		return IMG_LoadTexture(renderer, filepath);
	}

	inline int querySDLTexture(SDL_Texture* texture, Uint32* format, int* access, int* width, int* height) {
		return SDL_QueryTexture(texture, format, access, width, height);
	}

	inline void destroySDLWindow(SDL_Window* window) {
		SDL_DestroyWindow(window);
	}

	inline void destroySDLRenderer(SDL_Renderer* renderer) {
		SDL_DestroyRenderer(renderer);
	}

	inline void destroySDLTexture(SDL_Texture* texture) {
		SDL_DestroyTexture(texture);
	}

	inline const char* getSDLError() {
		return SDL_GetError();
	}

	inline int renderSDLTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* dst) {
		return SDL_RenderCopy(renderer, texture, clip, dst);
	}

	inline int renderSDLRect(SDL_Renderer* renderer, SDL_Rect rect, int r, int g, int b, int a) {
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		return SDL_RenderDrawRect(renderer, &rect);
	}

	inline int clearSDLRenderer(SDL_Renderer* renderer) {
		return SDL_RenderClear(renderer);
	}

	inline void presentSDLRenderer(SDL_Renderer* renderer) {
		SDL_RenderPresent(renderer);
	}

};

#endif /* SDLCALLERIMPL_H */

