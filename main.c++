#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "src/inputField.hpp"
#include "src/button.hpp"

namespace fs = std::filesystem;


const std::string ICON_PATH = "icon/FileCopier.png";

template<typename stream>
bool validatePath(stream& fileStream,std::string& filePath){
    if(!fileStream){
        return false;
    }
    return true;
}

int main(){
    sf::Image icon(ICON_PATH);
    sf::RenderWindow window(sf::VideoMode({720,480}),"File Copier",sf::Style::Titlebar | sf::Style::Close);
    
    window.setIcon(icon);

    InputField sourceInput(
        "Source File:",
        {30.f, 55.f},   // label position
        {250.f, 45.f},  // box position
        {400.f, 45.f}
    );

    InputField destInput(
        "Destination File:",
        {30.f, 120.f},
        {300.f, 110.f},
        {400.f, 45.f}
    );

    Button copyBtn(
        "Copy",
        {30.f, 180.f},   // LEFT aligned button
        {120.f, 45.f}
    );
    Label statusLabel("");
    statusLabel.setPosition(30.f, 260.f);

    while(window.isOpen()){
        while(const std::optional<sf::Event> event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if (event->is<sf::Event::TextEntered>()) {
                auto unicode = event->getIf<sf::Event::TextEntered>()->unicode;
                sourceInput.handleText(unicode);
                destInput.handleText(unicode);
            }
            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = sf::Vector2f(
                    sf::Mouse::getPosition(window)
                );

                sourceInput.handleClick(mouse);
                destInput.handleClick(mouse);

                if (copyBtn.isClicked(mouse)) {
                    if (!fs::exists(sourceInput.value)) {
                        statusLabel.setText("Source file does not exist");
                        continue;
                    }
                
                    if (!fs::exists(destInput.value)) {
                        statusLabel.setText("Destination file does not exist");
                        continue;
                    }
                    std::ifstream in(sourceInput.value, std::ios::binary);
                    std::ofstream out(destInput.value, std::ios::binary | std::ios::trunc);

                    out << in.rdbuf();
                    statusLabel.setText("Copied successfully!");
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }
        window.clear(sf::Color(255, 255, 255));
        sourceInput.draw(window);
        destInput.draw(window);
        copyBtn.draw(window);
        window.draw(statusLabel.text);
        window.display();
    }


    return 0;
}