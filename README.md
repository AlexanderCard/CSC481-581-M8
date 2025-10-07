# A Component-Based Game Object Model

In this assignment, you’ll build a small **component-based** system using **C++**, **CMake**, and **SDL3** to render and move objects. Instead of writing custom classes for every type of object, you'll compose them by attaching data **components**.

You’ll learn how real game engines evolve from object-centric (OO-style) code to data-oriented, **component-driven** systems, which is the foundation of modern ECS (Entity-Component-System) architectures.

## Objectives

By the end of this assignment, you’ll be able to:

  - Understand the **Component-Based Game Object Model**.
  - Manage object data using **maps of components**, not rigid class hierarchies.
  - Extend the system by adding new game entities and components.
  - Recognize the benefits of **data-driven** engine design.

## Setup Instructions

Follow these steps to clone, build, and run the project on your machine:

### 1\. Clone the repository

```bash
git clone https://github.com/AlexanderCard/CSC481-581-M8.git
```

### 2\. Install SDL3

> SDL3 is the latest version of the Simple DirectMedia Layer. You’ll only need the core SDL3 library for this assignment.

#### On **macOS** (with Homebrew):

```bash
brew install sdl3
```

#### On **Ubuntu/Debian**:

```bash
sudo apt install libsdl3-dev
```

#### On **Arch Linux**:

```bash
sudo pacman -S sdl3
```

#### On **Windows**: (unverified)

Use [MSYS2](https://www.msys2.org/) or [vcpkg](https://vcpkg.io/).

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL3
```

### 3\. Build the project

```bash
mkdir build && cd build
cmake ..
make
```

> If CMake cannot find SDL3, make sure SDL3\_DIR is correctly set.

### 4\. Run the example

```bash
./property_model
```

You should see a red rectangle in a window.

-----

## Component-Based Design

### What is a Component-Based Model?

In traditional OOP-based engines, you might define a rigid `GameObject` class like this:

```cpp
class GameObject {
    SDL_FRect shape;
    SDL_Color color;
    float velocity;
    bool moveable;
};
```

This is **object-centric**—the object's class definition dictates its properties. What if you want an object with no velocity? Or a new property like health? You'd have to change the class or create complex inheritance trees.

A **component-based** model flips that idea. A `GameObject` is just a simple container. We attach pieces of data, called **components**, to give it properties and behavior.

| GameObject: `rect1` | |
| :--- | :--- |
| **Component** | **Value** |
| `"shape"` | `"rectangle"` |
| `"color"` | `{255, 0, 0, 255}` |
| `"velocity"` | `4` |
| `"moveable"` | `true` |

This separation helps you:

  - Easily **add new functionality** by defining new components, without modifying the `GameObject` class.
  - Manage behavior in external functions called **"systems"**, which operate on objects that have a specific set of components.
  - Mimic how modern **ECS (Entity-Component-System)** architectures store and process data efficiently.

-----

### Architecture Overview

The provided code uses:

  - `GameObject`: A class that acts as a container, holding a `std::map` of components.
  - `Component`: A `std::variant` that can store different data types (e.g., `int`, `float`, `SDL_Color`, `std::string`).
  - **Systems**: Global functions (like `updateAndRenderGameObject`) that read component data from a `GameObject` to perform logic.

Example from `main.cpp`:

```cpp
// Create an empty GameObject.
GameObject rectObj;

// Add components to define its data and behavior.
rectObj.setComponent("shape", std::string("rectangle"));
rectObj.setComponent("color", SDL_Color{255, 0, 0, 255}); // Red
rectObj.setComponent("moveable", true);
rectObj.setComponent("velocity", 4);
```

At runtime, a "system" like `updateAndRenderGameObject` checks if `rectObj` has a `"moveable"` component. If it does, the system uses the `"velocity"` and position components to update the object's state.

## Your Task

Add a **second game object**: a blue circle that is **non-moveable**.

### Requirements

1.  Create a new `GameObject` instance.
2.  Give it components for a `shape` ("circle" or "rectangle"), position, and size.
3.  Give it a `color` component (blue).
4.  Ensure it does **not** have a `"moveable"` component, so it won't respond to movement logic.
5.  Render both the original rectangle and your new object in the game loop.

-----

### How to Draw a Circle in SDL3

SDL3 doesn’t have a built-in circle drawing function. A simple algorithm is to iterate from `x = -radius` to `x = radius` and `y = -radius` to `y = radius`, and if `x*x + y*y <= radius*radius`, draw a point at `(centerX + x, centerY + y)`. You can implement this logic within the `updateAndRenderGameObject` "system".

## Helpful Resources

  - [SDL3 Docs (official)](https://wiki.libsdl.org/SDL3/FrontPage)
  - [Mike Shah SDL3 Setup Guide](https://www.youtube.com/watch?v=kyD5H6w1x-o)

## Final Notes

Keep your code modular. Try exploring new components like:

  - `"gravity"` (applies to moveable objects)
  - `"bounce"` (reverses direction on collision)
  - `"rotation"` (changes orientation over time)

Each new feature should be implemented by adding new components and updating systems—no new class definitions required. This is the power of a component-based model\!
