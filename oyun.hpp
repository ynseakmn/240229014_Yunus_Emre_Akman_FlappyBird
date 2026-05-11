#ifndef OYUN_HPP
#define OYUN_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include <vector>
#include <cstdlib>
#include "bird.hpp"
#include "pipe.hpp" // Pipe sınıfı eklendi

// Oyunun ana motoru
class Oyun {
private:
    sf::RenderWindow pencere;
    Kus kus;
    std::vector<Pipe> borular; // Ekrana çıkacak boruların listesi
    sf::Clock boruZamanlayici; // Yeni boru üretme süresini tutan saat

    void olaylari_isle();
    void guncelle();
    void ciz();
public:
    Oyun();
    void calistir();
};
#endif