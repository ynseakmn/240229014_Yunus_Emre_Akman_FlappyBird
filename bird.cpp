#include "bird.hpp"

// Kuşun başlangıç değerlerini, rengini ve fizik kurallarını tanımlar.
Kus::Kus() {
    kusSekli.setRadius(20.f);                    // Kuşun boyutu (yarıçap)
    kusSekli.setFillColor(sf::Color::Yellow);    // Kuşun rengi
    kusSekli.setPosition(sf::Vector2f(100.f, 300.f)); // Ekranda doğacağı ilk koordinat (X, Y)

    velocity = 0.f;       // Başlangıç düşme hızı
    gravity = 0.5f;       // Yerçekimi ivmesi 
    jumpHeight = -10.f;   // Zıplama gücü 
}

// Kuşun zıplamasını sağlar.
// Çağrıldığında yerçekimine karşı anlık bir yukarı yönlü hız uygular.
void Kus::zipla() {
    velocity = jumpHeight; 
}

// Oyunun her karesinde kuşun konumunu ve hızını günceller.
void Kus::guncelle() {
    velocity += gravity;                        // Her karede hız yerçekimi kadar artar 
    kusSekli.move(sf::Vector2f(0.f, velocity)); // Kuşu hesaplanan yeni hız değeriyle Y ekseninde hareket ettir
}

// Kuşu oyun penceresine çizer.
void Kus::ciz(sf::RenderWindow& pencere) {
    pencere.draw(kusSekli);
}

// Kuşun çarpışma kutusunu döndürrür.
// İleride borularla ve zeminle çarpışma kontrolü yaparken kullanılır.
sf::FloatRect Kus::getBounds() {
    return kusSekli.getGlobalBounds();
}