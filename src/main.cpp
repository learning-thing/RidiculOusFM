#include <iostream>
#include <raylib.h>
#include "VideoMan.hpp"
#include "tui.hpp"

int main() {
    std::cout << "hello world\n";
    InitWindow(1080, 720, "Whatever this is cinema player");
    Shader ppfx = LoadShader(0, "shader/pp.fs");
    int iTimeLoc = GetShaderLocation(ppfx, "iTime");
    RenderTexture ppLayer = LoadRenderTexture(1080, 720);
    u_int8_t padding = 15;

    VideoMan vm;
    SetWindowState(FLAG_VSYNC_HINT);
    float iTime = 0;
    while (!WindowShouldClose()) {
        iTime+=GetFrameTime();
        SetShaderValue(ppfx, iTimeLoc, &iTime, SHADER_UNIFORM_FLOAT);
        //Actual drawing content
        BeginTextureMode(ppLayer);
            //DrawCircle(100, 100, 10, WHITE);//Test Circle
            ClearBackground(BLACK);
            //DrawRectangleLines(padding, 10, GetScreenWidth()-padding*2, 500, WHITE);
            vm.draw();
        EndTextureMode();

        BeginDrawing();//present it to the scren
            ClearBackground((Color){10, 10, 18});
            BeginShaderMode(ppfx);
                DrawTextureRec(ppLayer.texture, (Rectangle){ 0, 0, (float)ppLayer.texture.width, (float)-ppLayer.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
        EndDrawing();
    
    }
    UnloadShader(ppfx);
    UnloadRenderTexture(ppLayer);
    CloseWindow();
    return 0;
}
