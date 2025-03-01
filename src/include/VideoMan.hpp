#pragma once
#include <filesystem>
#include <iostream>
#include "tui.hpp"
#include <vector>
#include <future>
#include <thread>

namespace fs = std::filesystem;

class VideoMan {
    private:
        std::string path = "/";
        std::vector<fs::path> dirs;
        fs::path last = path;

        std::string onlyFileName(std::string somePath);
        std::string upDir(std::string somePath);

        unsigned int padding = 55;

        void ls() {
            int i = 0;
            ui.addButton(vec2(15, 10)+vec2(0, padding*i), vec2(1000, 50), upDir(path).c_str());
            dirs.push_back(upDir(path));

            i++;
            //Add Directories
            for (const auto & entry : fs::directory_iterator(path)) {
                std::string pstring = entry.path().string();
                if (fs::is_directory(entry.path()) && onlyFileName(pstring)[0]!='.') {
                    i++;
                    //if (i>30) break;
                    std::cout << entry.path() << std::endl;
                    dirs.push_back(entry.path());
                    ui.addButton(vec2(15, 10)+vec2(0, padding*i), vec2(1000, 50), onlyFileName( entry.path().string()  ).c_str(), GREEN);
                }
            }

            //Add Directories that start with a .
            for (const auto & entry : fs::directory_iterator(path)) {
                std::string pstring = entry.path().string();
                if (fs::is_directory(entry.path()) && onlyFileName(pstring)[0]=='.') {
                    i++;
                    //if (i>30) break;
                    std::cout << entry.path() << std::endl;
                    dirs.push_back(entry.path());
                    ui.addButton(vec2(15, 10)+vec2(0, padding*i), vec2(1000, 50), onlyFileName( entry.path().string()  ).c_str(), GREEN);
                }
            }

            //Add files
            for (const auto & entry : fs::directory_iterator(path)) {
                if (!fs::is_directory(entry.path())){
                    i++;
                    //if (i>30) break;
                    std::cout << entry.path() << std::endl;
                    dirs.push_back(entry.path());
                    ui.addButton(vec2(15, 10)+vec2(0, padding*i), vec2(1000, 50), onlyFileName( entry.path().string()  ).c_str() );   
                }
            }
        }

    public:
        TGUI ui;
        int pressed_button = 0;

        VideoMan() {
            ls();
        }

        void Handle_buttons(int button_pressed);

        void draw() {
            if (ui.scrollPerc>=0 && GetMouseWheelMoveV().y>0 || ui.scrollPerc<=1 && GetMouseWheelMoveV().y<0 )
                ui.scroll += GetMouseWheelMoveV().y*30;
            
            Handle_buttons(ui.Draw());
        }
};


std::string VideoMan::upDir(std::string somePath) {
    for (int i = somePath.length()-2; i>=1; i--) {
        somePath.pop_back();
        char currChar = somePath[i];
        if (currChar=='/') {
            return somePath;
        }
        
    }
    return somePath;
}

std::string VideoMan::onlyFileName(std::string somePath) {
    std::string out = "";
    for (int i = somePath.length()-1; i>=1; i--) {
        char currChar = somePath[i];
        if (currChar=='/') break;
        out+=somePath[i];   
    }
    std::string a;
    for (int i = out.length()-1; i>=0; i--)
        a+=out[i];
    std::clog << a << "\n";
    return a;
}

void VideoMan::Handle_buttons(int pressed_button) {
    if (pressed_button!=0) {
        std::clog << dirs[pressed_button-1] << "\n";
        if (fs::is_directory(dirs[pressed_button-1])) {//if it's a directory, go into it
            last = path;
            path = dirs[pressed_button-1];
            dirs.clear();
            ui.clear();
            ls();
        } else {
            /*
                std::string cmdStr = "vlc \"";
                
                cmdStr+=dirs[pressed_button-1];
                cmdStr+="\" --started-from-file &";
                std::thread t1(system, cmdStr.c_str());
                t1.join();
                */
            std::string cmdStr = "xdg-open \"";
            
            cmdStr+=dirs[pressed_button-1];
            cmdStr+="\" &";
            std::thread t1(system, cmdStr.c_str());
            t1.join();
        }
    }    
}