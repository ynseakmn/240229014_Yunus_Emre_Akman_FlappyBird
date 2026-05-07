#include "oyun.hpp"

// Oyun sınıfının kurucusu
// 800x600 boyutlarında bir pencere açıp fps'i 60'a sabitler
Oyun::Oyun() : pencere(sf::VideoMode({800, 600}), "Flappy Bird KOU") {
    pencere.setFramerateLimit(60);
}

// Oyun ana döngü
// Pencere açıkken uyar, yeniler ve çizer
void Oyun::calistir() {
    while (pencere.isOpen()) {
        olaylari_isle(); //  Klavyeden veya fareden gelen girdileri okur
        guncelle();      //  Kuşun yerçekimini ve pozisyonunu hesaplar
        ciz();           //  Yeni koordinatlarla kuşu ekrana çizer
    }
}

// Kullanıcının girdilerini ekranda yansıtır
void Oyun::olaylari_isle() {
   
    while (const std::optional olay = pencere.pollEvent()) {
        
        // Çarpı (X) tuşuna basıldığında pencereyi kapatır
        if (olay->is<sf::Event::Closed>()) {
            pencere.close();
        }
        
        // Klavyeden bir tuşa basınca
        if (olay->is<sf::Event::KeyPressed>()) {
            // Basılan tuş Boşluk (Space) tuşu ise kuşu zıplatır
            if (olay->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {
                kus.zipla(); 
            }
        }
    }
}

// Oyun içindeki tüm hareketli nesnelerin (şimdilik sadece kuş) durumunu günceller.
void Oyun::guncelle() { 
    kus.guncelle(); 
}

// Oyun penceresindeki eski kareyi silip yeni kareyi ekrana yansıtan yöntem.
void Oyun::ciz() {
    pencere.clear(sf::Color::Cyan); // Arka planı gökyüzü rengine (Cyan) boyar
    kus.ciz(pencere);               // Kuşu çizer
    pencere.display();              // Çizilen her şeyi ekranda gösterir
}