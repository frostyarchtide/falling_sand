#include "sandbox.hpp"

#include "raylib-cpp.hpp"

#include <chrono>
#include <random>

std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());

int main() {
    raylib::Window window(1600, 1200, "Falling Sand");

    Sandbox sandbox(40, 30);

    SetTargetFPS(10);

    while (!window.ShouldClose())
    {
        sandbox.update();

        BeginDrawing();

        sandbox.draw();
        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 64, WHITE);

        EndDrawing();
    }
}
