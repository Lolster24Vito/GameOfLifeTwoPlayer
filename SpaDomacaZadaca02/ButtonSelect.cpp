#include "ButtonSelect.h"

ButtonSelect::ButtonSelect()
{
    button.setSize({ 90,200 });
    button.setPosition(0,0);
    textName.setFillColor(sf::Color::Red);
    textName.setString("");
    textName.setCharacterSize(15);
    textName.setPosition(0,0);
    spriteImage.setPosition(0, 0);

}

void ButtonSelect::drawTo(sf::RenderWindow& window)
{
    window.draw(button);
    window.draw(spriteImage);
    window.draw(textName);
}

void ButtonSelect::setPosition( sf::Vector2f pos)
{
    button.setPosition(pos);
    textName.setPosition(pos);
    spriteImage.setPosition(sf::Vector2f(pos.x,pos.y+45));

}



void ButtonSelect::setTexture(sf::Texture texturee)
{
    texture = texturee;
    spriteImage.setTexture ( texture);
}



void ButtonSelect::setName(std::string namee)
{
    name = namee;
    textName.setString(name);
}

void ButtonSelect::setButtonColor(sf::Color color)
{
}

void ButtonSelect::setFont(sf::Font& font)
{
    textName.setFont(font);
}

bool ButtonSelect::isMouseOver(float mousePosX, float mousePosY)
{
    //sfml funkcija 
    if (button.getGlobalBounds().contains({ mousePosX,mousePosY })) {
        button.setFillColor(sf::Color(200, 200, 200));
        return true;
    }
    else {
        button.setFillColor(sf::Color::White);
        return false;
    }


}
