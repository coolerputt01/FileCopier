#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#define to_f(x) static_cast<float>(x)

const std::string FONT_PATH = "fonts/Banita.ttf";

template<typename stream>
bool validatePath(stream& fileStream,std::string& filePath){
    if(!fileStream){
        std::cerr<<"Error opening file: "<<filePath<<std::endl;
        return false;
    }
    return true;
}

int main(){
    sf::RenderWindow window(sf::VideoMode({720,480}),"File Copier");


    sf::Font font(FONT_PATH);
    sf::Text text(font);
    sf::Text text2(font);
    sf::Text input1(font);
    sf::Cursor hand(sf::Cursor::Type::Hand);
    sf::Cursor arrow(sf::Cursor::Type::Arrow);
    bool inputactive_1 = false;
    bool inputactive_2 = false;
    std::string inputFilePath;
    std::string inputFilePath2;
    bool submit = false;
    sf::Text input2(font);
    sf::RectangleShape rect({400.f,50.f});
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(0.53);
    rect.setPosition({30.f,80.f});
    sf::RectangleShape rect2({400.f,50.f});
    rect2.setFillColor(sf::Color::Black);
    rect2.setOutlineColor(sf::Color::White);
    rect2.setOutlineThickness(0.53);
    rect2.setPosition({30.f,150.f});
    sf::RectangleShape button({125.f,50.f});
    button.setFillColor(sf::Color::White);
    button.setPosition({310.f,210.f});
    text2.setPosition({340.f,210.f});
    text2.setFillColor(sf::Color::Black);
    text.setPosition({30.f,30.f});
    input1.setPosition({40.f, 90.f});
    input2.setPosition({40.f, 160.f});
    text2.setString("Enter");
    text.setString("Enter the source and destination files.");

    while(window.isOpen()){
        while(const std::optional<sf::Event> event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if(event->is<sf::Event::TextEntered>()){
                char c = static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
                if(event->getIf<sf::Event::TextEntered>()->unicode == U'\b'){
                    if (inputactive_1 && !inputFilePath.empty()){
                        inputFilePath.pop_back();
                    }
                    if (inputactive_2 && !inputFilePath2.empty())
                        inputFilePath2.pop_back();
                }else if(c >= 32 && c < 127){
                    if (inputactive_1)
                        inputFilePath += c;
                    if (inputactive_2)
                        inputFilePath2 += c;
                }

                input1.setString(inputFilePath);
                input2.setString(inputFilePath2);                    

            }
        }
        window.clear();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

            inputactive_1 = rect.getGlobalBounds().contains({to_f(mouse_pos.x),to_f(mouse_pos.y)});
            inputactive_2 = rect2.getGlobalBounds().contains({to_f(mouse_pos.x),to_f(mouse_pos.y)});
            if(submit){
                std::ifstream inputFile(inputFilePath,std::ios::binary);
                if(!validatePath(inputFile,inputFilePath)){
                    return 1;
                };

                std::ofstream outputFile(inputFilePath2,std::ios::binary);
                if(!validatePath(outputFile,inputFilePath2)){
                    return 1;
                };
                outputFile << inputFile.rdbuf();
                text.setString("Sucessfully Copied");
            }
        }
        if(inputactive_1){
            rect.setOutlineThickness(2);
            rect2.setOutlineThickness(1);
        }else if(inputactive_2){
            rect2.setOutlineThickness(2);
            rect.setOutlineThickness(1);
        }
        submit = button.getGlobalBounds().contains({to_f(sf::Mouse::getPosition(window).x),to_f(sf::Mouse::getPosition(window).y)});
        if(submit){
            window.setMouseCursor(hand);
        }else {
            window.setMouseCursor(arrow);
        }
        window.draw(rect);
        window.draw(rect2);
        window.draw(button);
        window.draw(text);
        window.draw(text2);
        window.draw(input1);
        window.draw(input2);
        window.display();
    }


    return 0;
}