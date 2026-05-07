#ifndef KUS_HPP
#define KUS_HPP

#include <SFML/Graphics.hpp>

class Kus {
    
private:
    sf::CircleShape kusSekli;
    float velocity;
    float gravity;
    float jumpHeight;

public:
    Kus(); 
    void zipla();
    void guncelle();
    void ciz(sf::RenderWindow& pencere);
    sf::FloatRect getBounds();


};

#endif