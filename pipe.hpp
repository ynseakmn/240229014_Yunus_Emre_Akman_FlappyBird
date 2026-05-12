#ifndef PIPE_HPP
#define PIPE_HPP
#include <SFML/Graphics.hpp>

class Pipe {
private:
    sf::RectangleShape ustBoru, altBoru; // Üst ve alt engeller
    float hiz;                           // Sola kayma hızı
    bool gecildiMi;                      
public:
    Pipe(float xPozisyonu, float boslukY, float boslukBoyutu); // Kurucu
    void guncelle();                     // Her karede sola kaydırır
    void ciz(sf::RenderWindow& pencere); // Ekrana çizer
    bool ekrandanCiktiMi();              // RAM temizliği için kontrol
    sf::FloatRect getUstBounds();        // Çarpışma: Üst sınır
    sf::FloatRect getAltBounds();        // Çarpışma: Alt sınır

    bool isGecildi();                    // Skor kontrolü yapar
    void setGecildi();                   // Skor kontrolü yapar
};
#endif