#ifndef OYUN_HPP
#define OYUN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>  
#include "bird.hpp"  // Kuş oyunda

// Main class
class Oyun {
private:
    sf::RenderWindow pencere; // Oyunu oynadığımız ana ekran
    Kus kus;                  // Oyunun ana karakteri

    void olaylari_isle();     // Klavye ve fare tıklamaları
    void guncelle();          // Fiziği ve durumları hesaplıyor
    void ciz();               // Görüntüleri yansıtıyor

public:
    Oyun();                   // Kurucu 
    void calistir();          // Oyunun sonsuz döngüsünü açar
}; 

#endif