#include <SDL3/SDL.h>
#include <iostream>

#include "GameObject.hpp"

/**
 * @brief Updates and renders a GameObject based on its components.
 * This functions should be extended and revised to take function pointers
 * from components to execute component-specific behavior.
 *
 * @param renderer The SDL_Renderer to draw with.
 * @param obj The GameObject to process.
 */
void updateAndRenderGameObject(SDL_Renderer* renderer, GameObject& obj) {
    // Read data from components.
    std::string shape = obj.getComponent<std::string>("shape");
    SDL_Color color = obj.getComponent<SDL_Color>("color");

    // --- Movement System Logic ---
    // This block only runs if the object has the "moveable" component.
    if (obj.hasComponent("moveable") && obj.getComponent<bool>("moveable")) {
        int x = obj.getComponent<int>("x");
        int velocity = 1; // Default velocity

        if (obj.hasComponent("velocity")) {
            velocity = obj.getComponent<int>("velocity");
        }

        // Update the 'x' component's value.
        x = (x + velocity) % 640;
        obj.setComponent("x", x); // Write the new data back to the component.
    }

    // --- Rendering System Logic ---
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // This block only runs if the object has a "shape" component set to "rectangle".
    if (shape == "rectangle") {
        SDL_FRect rect{
            (float)obj.getComponent<int>("x"), (float)obj.getComponent<int>("y"),
            (float)obj.getComponent<int>("w"), (float)obj.getComponent<int>("h")};
        SDL_RenderFillRect(renderer, &rect);
    }
}


int main(int, char**) {
    // --- Initialization ---
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Component-Based Model", 640, 480, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    if (!window || !renderer) {
        std::cerr << "Failed to create SDL window/renderer: " << SDL_GetError() << "\n";
        return 1;
    }

    // --- Object Creation ---
    // Define a GameObject by giving it a set of components. This could be moved to a factory function
    GameObject rectObj;
    rectObj.setComponent("shape", std::string("rectangle"));
    rectObj.setComponent("color", SDL_Color{255, 0, 0, 255}); // Red
    rectObj.setComponent("moveable", true);
    rectObj.setComponent("velocity", 4);
    rectObj.setComponent("x", 50);
    rectObj.setComponent("y", 200);
    rectObj.setComponent("w", 100);
    rectObj.setComponent("h", 80);

    // --- Game Loop ---
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Process our game object each frame. You will want to extend this functionality to cover more objects
        updateAndRenderGameObject(renderer, rectObj);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // --- Cleanup ---
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}