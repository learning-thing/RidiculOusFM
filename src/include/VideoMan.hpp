#pragma once
#include <filesystem>
#include <iostream>
#include "tui.hpp"
#include <vector>

namespace fs = std::filesystem;

class VideoMan {
    private:
        std::string path = "/home/benji/.asmr/";
        std::vector<fs::path> dirs;
        fs::path last = path;

        std::string onlyFileName(std::string somePath) {
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

        void ls() {
            int i = 0;
            ui.addButton(vec2(15, 10)+vec2(0, 51*i), vec2(1000, 50), last.c_str());
            dirs.push_back(last.c_str());

            i++;
            for (const auto & entry : fs::directory_iterator(path)) {
                i++;
                if (i>10) break;
                std::cout << entry.path() << std::endl;
                dirs.push_back(entry.path());
                ui.addButton(vec2(15, 10)+vec2(0, 51*i), vec2(1000, 50), onlyFileName( entry.path().string()  ).c_str() );
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
            Handle_buttons(ui.Draw());
        }
};


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
            std::string cmdStr = "vlc \"";
            
            cmdStr+=dirs[pressed_button-1];
            cmdStr+="\" --started-from-file ";
            system(cmdStr.c_str());
        }
    }    
}