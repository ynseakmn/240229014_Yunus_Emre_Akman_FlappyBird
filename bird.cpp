#include "bird.hpp"

Kus::Kus() {
    kusSekli.setRadius(20.f);
    kusSekli.setFillColor(sf::Color::Yellow);
    kusSekli.setPosition(sf::Vector2f(100.f, 300.f));
    velocity = 0.f;
    gravity = 0.5f;
    jumpHeight = -10.f;
}

void Kus::zipla() {
    velocity = jumpHeight;
}
void Kus::guncelle() {
    velocity += gravity;
    kusSekli.move(sf::Vector2f(0.f, velocity));
}

void Kus::ciz(sf::RenderWindow& pencere) {
    pencere.draw(kusSekli);
}

sf::FloatRect Kus::getBounds() {
    return kusSekli.getGlobalBounds();
}
