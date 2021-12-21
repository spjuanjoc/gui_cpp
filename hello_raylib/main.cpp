#include <raylib.h>

int main(int argc, char** argv)
{
  InitWindow(640, 480, "raylib basic window");
  SetTargetFPS(60);

  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    BeginDrawing();
    {
      ClearBackground(BLACK);
      DrawText("Hello world from RayLib!", 190, 200, 20, LIGHTGRAY);
    }
    EndDrawing();
  }

  CloseWindow();  // Close window and OpenGL context

  return 0;
}
