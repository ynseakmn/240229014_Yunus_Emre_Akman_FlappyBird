#include "pipe.hpp"

// Boruların konum, renk ve boyutlarını ayarlar
Pipe::Pipe(float xPozisyonu, float boslukY, float boslukBoyutu) : hiz(3.0f) {
    ustBoru.setSize(sf::Vector2f(50.f, boslukY));
    ustBoru.setFillColor(sf::Color::Green);
    ustBoru.setPosition(sf::Vector2f(xPozisyonu, 0.f));

    float altBoruY = boslukY + boslukBoyutu;
    altBoru.setSize(sf::Vector2f(50.f, 600.f - altBoruY));
    altBoru.setFillColor(sf::Color::Green);
    altBoru.setPosition(sf::Vector2f(xPozisyonu, altBoruY));
}

void Pipe::guncelle() {
    ustBoru.move(sf::Vector2f(-hiz, 0.f)); // Sola hareket ettir
    altBoru.move(sf::Vector2f(-hiz, 0.f));
}

void Pipe::ciz(sf::RenderWindow& pencere) {
    pencere.draw(ustBoru);
    pencere.draw(altBoru);
}

// Ekranın solundan tamamen çıktıysa "true" döner
bool Pipe::ekrandanCiktiMi() { return ustBoru.getPosition().x + ustBoru.getSize().x < 0; }
sf::FloatRect Pipe::getUstBounds() { return ustBoru.getGlobalBounds(); }
sf::FloatRect Pipe::getAltBounds() { return altBoru.getGlobalBounds(); }