#ifndef OYUN_HPP
#define OYUN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include <vector>    
#include <cstdlib>  
#include "bird.hpp" 
#include "pipe.hpp"  

// Main class
class Oyun {
private:
    sf::RenderWindow pencere; // Ana ekran
    Kus kus;                  // Ana karakteri
    
    std::vector<Pipe> borular; // Ekranda görünen tüm boruları tutan dinamik liste
    sf::Clock boruZamanlayici; // Yeni boru üretme süresini ölçecek saat
    
    bool oyunBitti;           // Oyunun bitip bitmediğini takip eder.
    int skor;                 // Oyuncunun skorunu tutar.

    void olaylari_isle();     
    void guncelle();          // Fiziği ve durumları hesaplar.
    void ciz();               // Görüntüleri yansıtır.
    void sifirla();           // Çarpınca oyunu baştan başlatır.

public:
    Oyun();                   
    void calistir();          // Oyunun sonsuz döngüde çalışır.
}; 

#endif