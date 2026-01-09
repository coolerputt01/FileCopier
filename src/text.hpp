#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "config.hpp"

struct Label{
    std::string textData;
    sf::Text text;

    Label(const std::string& str) : textData(str),text(font){
        text.setString(textData);
        text.setFillColor(sf::Color::Black);
    }
    void setPosition(const float &x,const float &y){
        text.setPosition({x,y});
    }
    void setTextSize(unsigned int &size){
        text.setCharacterSize(size);
    }
    void setText(const std::string& textChar){
        textData = textChar;
        text.setString(textData);
    }
};