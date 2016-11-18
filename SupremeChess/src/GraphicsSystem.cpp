#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem(const char* title, int width, int height, int x, int y) {
    _windowTitle = title;
    _windowWidth = width;
    _windowHeight = height;
    _windowX = x;
    _windowY = y;

    if (!_sdlCaller.initialiseSDL(SDL_INIT_VIDEO)) {
	printf("Could not initialise SDL! SDL_Error: %s\n", _sdlCaller.getSDLError());
    }

    if (!_sdlCaller.initialiseSDLImage(IMG_INIT_PNG)) {
	printf("Could not initialse SDL_image! SDL_Error: %s\n", _sdlCaller.getSDLError());
    }

}

GraphicsSystem::~GraphicsSystem() {
    _sdlCaller.quitSDLImage();
    _sdlCaller.quitSDL();
}

void GraphicsSystem::showWindow() {
    _window = _sdlCaller.createSDLWindow(_windowTitle, _windowX, _windowY, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN);
    if (_window == NULL) {
	printf("Window could not be created! SDL_Error: %s\n", _sdlCaller.getSDLError());
    } else {
	_renderer = _sdlCaller.createSDLRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == NULL) {
	    printf("Could not create renderer! SDL_Error: %s\n", _sdlCaller.getSDLError());
	}
    }
}

void GraphicsSystem::closeWindow() {
    for (std::map<const char*, SDL_Sprite>::iterator it = _sprites.begin(); it != _sprites.end(); ++it) {
	_sdlCaller.destroySDLTexture(it->second.texture);
	delete it->second.clip;
    }
    _sdlCaller.destroySDLRenderer(_renderer);
    _sdlCaller.destroySDLWindow(_window);
}

SDL_Texture* GraphicsSystem::loadTexture(const char* filepath, int* width, int* height) {
    SDL_Texture* loadedTexture = _sdlCaller.loadSDLImageTexture(_renderer, filepath);
    if (loadedTexture == NULL) {
	printf("Could not create texture! SDL_Error: %s\n", _sdlCaller.getSDLError());
	return NULL;
    }
    _sdlCaller.querySDLTexture(loadedTexture, NULL, NULL, width, height);
    return loadedTexture;
}

void GraphicsSystem::loadSprite(const char* name, const char* filepath) {
    int width, height;
    SDL_Texture* loadedTexture = loadTexture(filepath, &width, &height);
    SDL_Sprite sprite;
    sprite.name = name;
    sprite.width = width;
    sprite.height = height;
    sprite.texture = loadedTexture;
    _sprites[name] = sprite;
}

void GraphicsSystem::loadSpritesheet(SpriteProperties spriteProperties, const char* filepath) {
    int width, height;
    SDL_Texture* loadedTexture = loadTexture(filepath);
    for (SpriteProperties::iterator it = spriteProperties.begin(); it != spriteProperties.end(); ++it) {
	SDL_Sprite sprite;
	sprite.name = it->name;
	sprite.width = it->width;
	sprite.height = it->height;
	sprite.texture = loadedTexture;
	SDL_Rect* clip = new SDL_Rect();
	clip->x = it->x;
	clip->y = it->y;
	clip->w = it->width;
	clip->h = it->height;
	sprite.clip = clip;
	_sprites[sprite.name] = sprite;
    }
}

void GraphicsSystem::drawSprite(SDL_Sprite sprite, SDL_Rect dst) {
    _sdlCaller.renderSDLTexture(_renderer, sprite.texture, sprite.clip, &dst);
}

void GraphicsSystem::drawSprite(const char* name, int x, int y) {
    SDL_Sprite sprite = _sprites.at(name);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = sprite.width;
    dst.h = sprite.height;
    drawSprite(sprite, dst);
}

void GraphicsSystem::drawSprite(const char* name, int x, int y, int width, int height) {
    SDL_Sprite sprite = _sprites.at(name);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = width;
    dst.h = height;
    drawSprite(sprite, dst);
}

void GraphicsSystem::drawRect(int x, int y, int width, int height, int r, int g, int b, int a) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	_sdlCaller.renderSDLRect(_renderer, rect, r, g, b, a);
}

void GraphicsSystem::clearRenderer() {
    _sdlCaller.clearSDLRenderer(_renderer);
}

void GraphicsSystem::clearRenderer(Color color) {
	Color oldColor;
	_sdlCaller.getSDLDrawColor(_renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
	_sdlCaller.setSDLDrawColor(_renderer, color.r, color.g, color.b, color.a);
	clearRenderer();
	_sdlCaller.setSDLDrawColor(_renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

void GraphicsSystem::render() {
    _sdlCaller.presentSDLRenderer(_renderer);
}

const GraphicsSystem::Color GraphicsSystem::WHITE = { 255, 255, 255, 255 };
const GraphicsSystem::Color GraphicsSystem::BLACK = { 0, 0, 0, 255 };