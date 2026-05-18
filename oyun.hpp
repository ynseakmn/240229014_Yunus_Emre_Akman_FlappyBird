#ifndef OYUN_HPP
#define OYUN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include <vector>    // Boruları bir listede tutmak için eklendi
#include <cstdlib>   // Rastgele sayı üretmek (rand) için eklendi
#include "bird.hpp"  // Kuş oyunda
#include "pipe.hpp"  // Boru sınıfını oyuna dahil ettik

class Oyun {
private:
    sf::RenderWindow pencere; // Oyunu oynadığımız ana ekran
    Kus kus;                  // Oyunun ana karakteri
    
    std::vector<Pipe> borular; // Ekranda görünen tüm boruları tutan dinamik liste
    sf::Clock boruZamanlayici; // Yeni boru üretme süresini ölçecek saat
    
    bool oyunBitti;           // Oyunun bitip bitmediğini takip eder
    int skor;                 // Oyuncunun skorunu tutacak değişken

    sf::Font font;               // Yazı tipi dosyası
    std::optional<sf::Text> skorYazisi;         // Ekranda görünür
    std::optional<sf::Text> oyunBittiYazisi;    // Oyun bittiğinde çıkar
    std::optional<sf::Text> yenidenBaslaYazisi; // Yeniden başlama talimatı verir

    void olaylari_isle();     // Klavye ve fare tıklamaları
    void guncelle();          // Fiziği ve durumları hesaplıyor
    void ciz();               // Görüntüleri yansıtıyor
    void sifirla();           // Çarpınca oyunu baştan başlatmak için

public:
    Oyun();                   // Kurucu 
    void calistir();          // Oyunun sonsuz döngüsünü açar
}; 

#endif