/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicsSystem.h
 * Author: Matthew O'Rourke
 *
 * Created on 11 June 2016, 09:54
 */

#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <stdio.h>
#include <map>
#include <vector>

#include "impl/SDLCaller.h"

class GraphicsSystem {
private:

    struct SDL_Sprite {
		const char* name;
		int width, height;
		SDL_Rect* clip = NULL;
		SDL_Texture* texture;
    };

    // Properties
    int _windowWidth, _windowHeight;
    int _windowX, _windowY;
    const char* _windowTitle;

    // Internal SDL stuff
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::map<const char*, SDL_Sprite> _sprites;

    void drawSprite(SDL_Sprite sprite, SDL_Rect dst);

    SDL_Texture* loadTexture(const char* filepath, int* width = NULL, int* height = NULL);

protected:
    SDLCaller _sdlCaller;

public:

    // External representation of a sprite's properties

    struct SpriteProperty {
		const char* name;
		int x, y;
		int width, height;
    };

	struct Color {
		int r, g, b, a;

		Color() : r(0), g(0), b(0), a(0) {}
		Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
	};

	static const Color WHITE;
	static const Color BLACK;

    typedef std::vector<SpriteProperty> SpriteProperties;

    // Initialises the system
    GraphicsSystem(const char* title, int width, int height, int x = SDL_WINDOWPOS_UNDEFINED,
	    int y = SDL_WINDOWPOS_UNDEFINED);
    ~GraphicsSystem();

    // Window Methods
    // Creates and opens the main window
    void showWindow();
    // Destroys the main window
    void closeWindow();

    // Sprite Methods
    /* Loads a sprite
     * @param name The name to assign the sprite
     * 
     * @param filepath The file path of the sprite image
     */
    void loadSprite(const char* name, const char* filepath);

    /* Loads a spritesheet
     * @param spriteProperties A list of properties to define each sprite in the sheet
     * 
     * @param filepath The file path of the spritesheet image
     */
    void loadSpritesheet(SpriteProperties spriteProperties, const char* filepath);

    /* Creates a draw call for the sprite with the given name at position (x, y)
     * @param name The name of the sprite to draw
     * 
     * @param x The x position on the screen to draw the sprite
     * 
     * @param y The y position on the screen to draw the sprite
     */
    void drawSprite(const char* name, int x, int y);

    /* Creates a draw call for the sprite with the given name at position (x, y) with dimensions (width, height)
     * @param name The name of the sprite to draw
     * 
     * @param x The x position on the screen to draw the sprite
     * 
     * @param y The y position on the screen to draw the sprite
     * 
     * @param width The width of the sprite to draw
     * 
     * @param height The height of the sprite to draw
     */
    void drawSprite(const char* name, int x, int y, int width, int height);

	/* Creates a draw call for an outlined rectangle with the given rgba values at position (x, y)
	 * with dimensions (width, height)
	 *
	 * @param x The x position on the screen to draw the rectangle
	 *
	 * @param y The y position on the screen to draw the rectangle
	 *
	 * @param width The width of the rectangle to draw
	 *
	 * @param height The height of the rectangle to draw
	 *
	 * @param r The red component of the rectangle's colour
	 *
	 * @param g The green component of the rectangle's colour
	 *
	 * @param b The blue component of the rectangle's colour
	 *
	 * @param a The alpha component of the rectangle's colour
	 */
	void drawRect(int x, int y, int width, int height, int r, int g, int b, int a);

    // Renderer Methods
    /* Clears the renderer
     */
    void clearRenderer();
	void clearRenderer(Color color);

    /* Render to the screen
     */
    void render();

};

#endif /* GRAPHICSSYSTEM_H */

