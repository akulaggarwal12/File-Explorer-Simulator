#include "raylib.h"
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
namespace fs = std::filesystem;

// Global Variables
int dirCount=0;
int fileCount=0;

// Class of Data
class Data {
    public:
        std::string Names;
        bool isDirectory;
        Rectangle clickArea;
        
        Data (std::string name , bool isDir) : Names (name), isDirectory (isDir) {}
};

// Back-End
void LoadDirectory(std::string path, std::vector<Data>& fileList) {
    
    fileList.clear();
    dirCount = 0;
    fileCount = 0;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            fileList.push_back(Data (entry.path().filename().string() , entry.is_directory()));
            
            if (entry.is_directory())
            dirCount++;
            else
            fileCount++;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        fileList.push_back(Data("Error reading directory!",false));
    }
}

// Main Body
int main() {
    std::string currentPath = "/media/akul_aggarwal/Data/C language";
    std::vector<Data> fileNames;
    
    int fontX;
    LoadDirectory (currentPath, fileNames);
    Rectangle backButton = {20,20,40,20};
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(1000, 700, "Project Aether - Milestone 3");
    SetWindowMinSize(400, 300);
    SetTargetFPS(60);
    
    // Textures Adjustment
    Image folderImage = LoadImage("folder.png");
    Image fileImage = LoadImage("file.png");
        
    ImageResize(&folderImage,50,40);
    ImageResize(&fileImage,50,40);
       
    Texture2D folderIcon = LoadTextureFromImage(folderImage);
    Texture2D fileIcon = LoadTextureFromImage(fileImage);
        
    UnloadImage(folderImage);
    UnloadImage(fileImage);
  
    
    int scrollOffset = 0;
    
    while (!WindowShouldClose()) {
        
        
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
    
        Vector2 mousePos = GetMousePosition();
            
        // Back Button
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mousePos, backButton)) {
                currentPath=fs::path(currentPath).parent_path().string();
                scrollOffset = 0;
                LoadDirectory(currentPath, fileNames);
            }
            else {
                for (size_t i = 0; i < fileNames.size(); i++) {
                
                    if (CheckCollisionPointRec(mousePos, fileNames[i].clickArea)) {
                        
                        // If it's a directory, update the path and reload!
                        if (fileNames[i].isDirectory) {
                            // Append the clicked folder to the current path
                            currentPath = currentPath + "/" + fileNames[i].Names;
                            LoadDirectory(currentPath, fileNames);
                            scrollOffset = 0;
                            break;
                        }
                        else if (!fileNames[i].isDirectory) {
                            std::string filePath = currentPath + "/" + fileNames[i].Names;
                            std::string command = "xdg-open \"" + filePath + "\" &";
                            system(command.c_str());
                        }
                    }
                }
            }    
        }
        
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
    
        DrawRectangle(0, 0, screenWidth, 50, GRAY);
        DrawText(currentPath.c_str(), 80, 20, 20, BLACK);
        DrawRectangle(20, 20, 40, 20, DARKGRAY);
        fontX=MeasureText("BACK",10);
        DrawText("BACK", 40-fontX/2, 25, 10, BLACK);
        
        BeginScissorMode(0, 60, screenWidth, screenHeight - 60);

        
        // Loop through our vector and draw each name
        
        int X = 40;
        int Y;
        
        if (scrollOffset > 0)
        Y = 60;
        else
        Y = 60 + scrollOffset;
        
        
                
        // Scrolling
        if(scrollOffset > 0)  
        scrollOffset = 0;
        else if (Y + ((int)fileNames.size())/((int)screenWidth/100 - 2)*80 < screenHeight && GetMouseWheelMove() < 0)
        scrollOffset += 0;
        else
        scrollOffset += (int)GetMouseWheelMove()*20;

        
        
        int fontSize = 15;
        for (size_t i = 0; i < fileNames.size(); i++) {
        
            // Directory
            if(fileNames[i].isDirectory) {
            
                // Resetting Folders / Files
                if (X + 100 > screenWidth) {
                    X = 40;
                    Y += 80;
                }
                
                
                // Name, Icon and Collision Box
                fontX = MeasureText(fileNames[i].Names.c_str(), fontSize);
                
                fileNames[i].clickArea = {(float)(X-5), (float)Y, 60, 60};
                if (CheckCollisionPointRec(mousePos, fileNames[i].clickArea))
                DrawRectangleRec(fileNames[i].clickArea, LIGHTGRAY);
                
                DrawTexture(folderIcon, X, Y, RAYWHITE);
                if (fontX>100) {
                    fontX=MeasureText(TextFormat("%.*s...",8,fileNames[i].Names.c_str()),fontSize);
                    DrawText(TextFormat("%.*s...",8,fileNames[i].Names.c_str()), X+30-fontX/2, Y+45, fontSize, BLUE);
                }
                else
                DrawText(fileNames[i].Names.c_str(), X+30-fontX/2, Y+45, fontSize, BLUE);
                X += 100;
            } 
        }
        for (size_t i = 0; i < fileNames.size(); i++) {
            
            // Files
            if(!fileNames[i].isDirectory) {
            
                if (X + 100 > screenWidth) {
                    X = 40;
                    Y += 80;
                }
                
                
                fontX=MeasureText(fileNames[i].Names.c_str(), fontSize);
                
                fileNames[i].clickArea = {(float)(X-5), (float)Y, 60, 60};
                if (CheckCollisionPointRec(mousePos, fileNames[i].clickArea))
                DrawRectangleRec(fileNames[i].clickArea, LIGHTGRAY);
                
                DrawTexture(fileIcon, X, Y, BLUE);
                if (fontX>100) {
                    fontX=MeasureText(TextFormat("%.*s...",8,fileNames[i].Names.c_str()),fontSize);
                    DrawText(TextFormat("%.*s...",8,fileNames[i].Names.c_str()), X+30-fontX/2, Y+45, fontSize, BLACK);
                }
                else
                DrawText(fileNames[i].Names.c_str(), X+30-fontX/2, Y+45, fontSize, BLACK);
                X += 100;
            }        
        }
        EndScissorMode();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
