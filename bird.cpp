#include "bird.hpp"

// Kuşun başlangıç değerlerini, rengini ve fizik kurallarını tanımlar.
Kus::Kus() {
    kusSekli.setRadius(20.f);                    // Kuşun boyutu (yarıçap)
    kusSekli.setFillColor(sf::Color::Yellow);    // Kuşun rengi
    kusSekli.setPosition(sf::Vector2f(100.f, 300.f)); // Ekranda doğacağı ilk koordinat (X, Y)

    velocity = 0.f;       // Başlangıç düşme hızı
    gravity = 0.5f;       // Yerçekimi ivmesi (Aşağı doğru çeken kuvvet)
    jumpHeight = -10.f;   // Zıplama gücü 
}

// Kuşun zıplamasını sağlayan yöntem.
// Çağrıldığında yerçekimine karşı anlık bir yukarı yönlü hız (velocity) uygular.
void Kus::zipla() {
    velocity = jumpHeight; 
}

// Oyunun her karesinde (frame) kuşun konumunu ve hızını güncelleyen yöntem.
void Kus::guncelle() {
    velocity += gravity;                        // Her karede hız yerçekimi kadar artar 
    kusSekli.move(sf::Vector2f(0.f, velocity)); // Kuşu hesaplanan yeni hız değeriyle Y ekseninde hareket ettir
}

// Kuşu oyun penceresine çizen yöntem.
void Kus::ciz(sf::RenderWindow& pencere) {
    pencere.draw(kusSekli);
}

// Kuşun çarpışma kutusunu (Bounding Box) döndüren yöntem.
// İleride borularla (pipes) ve zeminle çarpışma kontrolü yaparken kullanılacak.
sf::FloatRect Kus::getBounds() {
    return kusSekli.getGlobalBounds();
}