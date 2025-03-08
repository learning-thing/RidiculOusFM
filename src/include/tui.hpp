#pragma once
#include "vec2.hpp"
#include <vector>
#include <raylib.h>
#include <string>
#include <iostream>


class ListButton {
    private:
        vec2 size;
        std::string text;
        bool clicked = false;
        Color HoverColor = RED;
        vec2 pos = vec2(1000, 0);
        std::string myText;
        
    public:
        vec2 tpos;

        ListButton() {

        }

        void draw();
        bool isHovering();
};

class ButtonList {
    private:
        std::vector<ListButton> ltbns;
        vec2 size;
        int scrollPos = 0;
        int scrollSize = 51;
        vec2 pos;
        void update() {
            //Handle Scrolling
        }
    public:
        ButtonList(vec2 pos, vec2 size) {

        }

        void addButton() {
            ltbns.push_back(ListButton());
        }


        void draw() {
            for (int i = 0; i < ltbns.size(); i++) {
                if (ltbns[i].tpos.y()>=pos.y())
                    ltbns[i].draw();
            }
        }
};



class button {
    public:
        vec2 tpos = vec2(10, 100);
        vec2 pos = vec2(0);
        vec2 size;
        bool clicked = false;
        std::string myText;
        bool HoveringOver = false;
        Color HoverColor = RED;
        Color col = WHITE;

    button(vec2 position, vec2 dimensions) : pos(position), size(dimensions) {
        //tpos.e[0] = pos.x();
    }
    button(vec2 position, vec2 dimensions, const char* text) : pos(position), size(dimensions) {
        //tpos.e[0] = pos.x();
        myText = text;
    }
    button(vec2 position, vec2 dimensions, const char* text, Color normalColor) : pos(position), size(dimensions), col(normalColor) {
        //tpos.e[0] = pos.x();
        myText = text;
    }

    bool isHovering() {
        if (GetMouseX()>tpos.x() && GetMouseX()<tpos.x()+size.x())
            if (GetMouseY()>tpos.y() && GetMouseY()<tpos.y()+size.y())
                return true;
        return false;
    }

    void Draw() {
        clicked = false;
        if (isHovering()) DrawRectangleLines(tpos.x(), tpos.y(), size.x(), size.y(), HoverColor);
        else DrawRectangleLines(tpos.x(), tpos.y(), size.x(), size.y(), col);
        DrawText(myText.c_str(), tpos.x()+5, tpos.y()+size.y()/4, 20, col);
        tpos += vec2(pos.x()-tpos.x(), pos.y()-tpos.y())*.05;//Move from the temporary position towards the desiredposition
        //tpos += pos-tpos*.05;//Move from the temporary position towards the desiredposition


        if (isHovering())
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                clicked = true;

        
    }
};


class TGUI {
    private:
        std::vector<button> btns;
        vec2 last_btn_pos;
        vec2 last_size;
        float totalScrolled = 0;
        
    public:
        float scrollPos = 0;
        float scroll = 0;
        float scrollPerc;

        TGUI() {
            btns.reserve(10);
        }

        void addButton(vec2 size) {
            vec2 apos = last_btn_pos+vec2(last_size.x(), 0);
            btns.emplace_back(apos, last_size);
        }

        void addButton(vec2 pos, vec2 size) {
            last_btn_pos = pos;
            btns.emplace_back(pos, size);
        }

        void addButton(vec2 pos, vec2 size, const char* uText) {
            last_btn_pos = pos;
            btns.emplace_back(pos, size, uText);
        }

        void addButton(vec2 pos, vec2 size, const char* uText, Color hoverColor) {
            last_btn_pos = pos;
            btns.emplace_back(pos, size, uText, hoverColor);
        }

        int Draw() {
            for (int i = 0; i < btns.size(); i++) {
                //check click
                btns[i].Draw();
                btns[i].pos+=vec2(0, scroll);
                

                if (btns[i].clicked) {
                    std::clog << "Clicked button " << i+1 << "\n";
                    return i+1;
                }
            }
            scroll *= .5;
            scrollPos+=scroll;
            scrollPerc = (-scrollPos/(btns.size()*55));
            DrawRectangle(GetScreenWidth()-10, GetScreenHeight()*scrollPerc*2, 20, 10, WHITE);
            
            return 0;
        }

        void clear() {
            scrollPos = 0;
            btns.clear();
        }
};

bool ListButton::isHovering() {
    if (GetMouseX()>tpos.x() && GetMouseX()<tpos.x()+size.x())
        if (GetMouseY()>tpos.y() && GetMouseY()<tpos.y()+size.y())
            return true;
    return false;
}

void ListButton::draw() {
    clicked = false;
    if (isHovering()) DrawRectangleLines(tpos.x(), tpos.y(), size.x(), size.y(), HoverColor);
    else DrawRectangleLines(tpos.x(), tpos.y(), size.x(), size.y(), WHITE);
    DrawText(myText.c_str(), tpos.x()+5, tpos.y()+size.y()/4, 20, WHITE);
    tpos += vec2(0, pos.y()-tpos.y())*.05;//Move from the temporary position towards the desiredposition

    if (isHovering())
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            clicked = true;
}