#pragma once
#include <SFML/Graphics.hpp>
#include "text.hpp"
#include "config.hpp"

struct Button {
    sf::RectangleShape body;
    sf::Text text;

    Button(
        const std::string& caption,
        sf::Vector2f pos,
        sf::Vector2f size
    ) :text(font){
        body.setSize(size);
        body.setPosition(pos);
        body.setFillColor(sf::Color::Blue);

        text.setFont(font);
        text.setString(caption);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);

        // center text
        auto bounds = text.getLocalBounds();
        text.setPosition({
            pos.x + (size.x - bounds.position.y)/3.f,
            pos.y + (size.y - bounds.size.y) / 2.f - 5.f
        });
    }

    bool isHovered(sf::Vector2f mouse) const {
        return body.getGlobalBounds().contains(mouse);
    }

    bool isClicked(sf::Vector2f mouse) const {
        return isHovered(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(body);
        window.draw(text);
    }
};
