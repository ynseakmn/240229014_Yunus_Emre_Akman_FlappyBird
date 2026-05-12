#include "pipe.hpp"

// Boruların konumunu, boyutunu ve rengini ayarlar
Pipe::Pipe(float xPozisyonu, float boslukY, float boslukBoyutu) {
    hiz = 3.0f; // Borunun sola doğru kayma hızı
    gecildiMi = false; // Boru ilk oluştuğunda henüz geçilmemiştir

    // Üst boru ayarları
    ustBoru.setSize(sf::Vector2f(50.f, boslukY)); 
    ustBoru.setFillColor(sf::Color::Green);
    ustBoru.setPosition(sf::Vector2f(xPozisyonu, 0.f)); 

    // Alt boru ayarları 
    float altBoruY = boslukY + boslukBoyutu; 
    altBoru.setSize(sf::Vector2f(50.f, 600.f - altBoruY)); 
    altBoru.setFillColor(sf::Color::Green);
    altBoru.setPosition(sf::Vector2f(xPozisyonu, altBoruY));
}

void Pipe::guncelle() {
    ustBoru.move(sf::Vector2f(-hiz, 0.f));
    altBoru.move(sf::Vector2f(-hiz, 0.f));
}

void Pipe::ciz(sf::RenderWindow& pencere) {
    pencere.draw(ustBoru);
    pencere.draw(altBoru);
}

bool Pipe::ekrandanCiktiMi() {
    return ustBoru.getPosition().x + ustBoru.getSize().x < 0;
}

sf::FloatRect Pipe::getUstBounds() { return ustBoru.getGlobalBounds(); }
sf::FloatRect Pipe::getAltBounds() { return altBoru.getGlobalBounds(); }

//Skoru sadece 1 kere artırmak için kullanılır
bool Pipe::isGecildi() { return gecildiMi; }
void Pipe::setGecildi() { gecildiMi = true; }