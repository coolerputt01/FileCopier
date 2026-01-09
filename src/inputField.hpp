#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "text.hpp"
#include "config.hpp"

struct InputField {
    Label label;
    sf::RectangleShape box;
    sf::Text text;
    std::string value;
    bool active = false;

    InputField(
        const std::string& labelText,
        sf::Vector2f labelPos,
        sf::Vector2f boxPos,
        sf::Vector2f size
    )
        : label(labelText),text(font)
    {
        label.setPosition(labelPos.x, labelPos.y);

        box.setSize(size);
        box.setPosition(boxPos);
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(1.f);

        text.setCharacterSize(16);
        text.setPosition({boxPos.x + 10.f, boxPos.y + 12.f});
        text.setFillColor(sf::Color::Black);
    }

    void handleClick(sf::Vector2f mouse) {
        active = box.getGlobalBounds().contains(mouse);
        box.setOutlineThickness(active ? 2.f : 1.f);
    }

    void handleText(int unicode) {
        if (!active) return;

        if (unicode == 8 && !value.empty()) { // backspace
            value.pop_back();
        } else if (unicode >= 32 && unicode < 127) {
            value += static_cast<char>(unicode);
        }
        text.setString(value);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(label.text);
        window.draw(box);
        window.draw(text);
    }
};
