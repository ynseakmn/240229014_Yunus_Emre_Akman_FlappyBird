#include "oyun.hpp"
#include <ctime> 
#include <iostream> // Skoru terminale yazdırır
#include <string>   // Sayıları yazıya (string) çevirir

// Kurucuda oyunBitti değişkenini false ve skoru 0 ile başlatır
Oyun::Oyun() : pencere(sf::VideoMode({800, 600}), "Flappy Bird KOU"), oyunBitti(false), skor(0) {
    std::cout << "[DEBUG] Oyun baslatiliyor... Pencere acildi." << std::endl;
    pencere.setFramerateLimit(60);
    srand(time(NULL)); // Rastgelelik sağlar

    std::cout << "[DEBUG] Font yukleniyor..." << std::endl;
    
    if (!font.openFromFile("font.ttf")) {
        std::cout << "HATA: font.ttf dosyasi bulunamadi! Klasoru kontrol et." << std::endl;
    } else {
        std::cout << "[DEBUG] Font basariyla yuklendi! Yazilar hazirlaniyor..." << std::endl;
        
        // FONT VE YAZI AYARLARI 
        skorYazisi.emplace(font);
        oyunBittiYazisi.emplace(font);
        yenidenBaslaYazisi.emplace(font); // Alt metni hafızada oluşturur

        // SENİN SKOR YAZISI AYARLARIN (Kırmızı ve 50 punto)
        skorYazisi->setString("0");                  
        skorYazisi->setCharacterSize(50);            
        skorYazisi->setFillColor(sf::Color::Red);  
        skorYazisi->setPosition({10.f, 10.f});       

        // SENİN OYUN BİTTİ YAZISI AYARLARIN (Büyük ve Kırmızı)
        oyunBittiYazisi->setString("OYUN BITTI!");
        oyunBittiYazisi->setCharacterSize(100);
        oyunBittiYazisi->setFillColor(sf::Color::Red);
        oyunBittiYazisi->setPosition({200.f, 150.f}); 

        // YENİDEN BAŞLA YAZISI AYARLARI
        yenidenBaslaYazisi->setString("Yeniden baslamak icin Space'e basin");
        yenidenBaslaYazisi->setCharacterSize(30);
        yenidenBaslaYazisi->setFillColor(sf::Color::White); // Ekranda okunaklı olması için beyaz
        yenidenBaslaYazisi->setPosition({210.f, 280.f}); // 100 puntoluk büyük yazının tam altına hizalar
        
        std::cout << "[DEBUG] Yazilar hazir! Oyun dongusune geciliyor." << std::endl;
    }
}

// Oyunu sıfırlar
void Oyun::sifirla() {
    kus = Kus();               // Kuşu başlangıç ayarlarına (yukarıya) döndürür
    borular.clear();           // Ekrandaki tüm boruları siler
    boruZamanlayici.restart(); // Zamanlayıcıyı baştan başlatır
    oyunBitti = false;         // Oyunu devam ettir
    skor = 0;                  // Oyun sıfırlandığında skor da sıfırlanır
    if (skorYazisi) skorYazisi->setString("0"); // Oyun sıfırlanınca ekrandaki yazı da sıfırlanır
}

void Oyun::calistir() {
    while (pencere.isOpen()) {
        olaylari_isle();
        guncelle();
        ciz();
    }
}

void Oyun::olaylari_isle() {
    while (const std::optional olay = pencere.pollEvent()) {
        if (olay->is<sf::Event::Closed>()) {
            pencere.close();
        }
        if (olay->is<sf::Event::KeyPressed>()) {
            if (olay->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {
                // Eğer oyun bittiyse ve boşluğa basılırsa oyunu SIFIRLAR, bitmediyse ZIPLAR
                if (oyunBitti) {
                    sifirla(); 
                } else {
                    kus.zipla(); 
                }
            }
        }
    }
}

void Oyun::guncelle() { 
    // Eğer oyun bittiyse hiçbir şeyin yerini değiştirmez
    if (oyunBitti) return; 

    kus.guncelle(); 

    sf::FloatRect kusKutusu = kus.getBounds();

    if (kusKutusu.position.y + kusKutusu.size.y > 600.f || kusKutusu.position.y < 0.f) {
        oyunBitti = true;
    }

    
    if (boruZamanlayici.getElapsedTime().asSeconds() > 1.5f) {
        float rastgeleY = (rand() % 200) + 100.f;
        borular.push_back(Pipe(800.f, rastgeleY, 150.f)); 
        boruZamanlayici.restart(); 
    }

    // Listedeki tüm boruları sola kaydırır
    for (size_t i = 0; i < borular.size(); i++) {
        borular[i].guncelle();

        if (kusKutusu.findIntersection(borular[i].getUstBounds()) || 
            kusKutusu.findIntersection(borular[i].getAltBounds())) {
            oyunBitti = true; // Çarptık!
        }

        if (!borular[i].isGecildi() && kusKutusu.position.x > borular[i].getUstBounds().position.x + borular[i].getUstBounds().size.x) {
            skor++; 
            borular[i].setGecildi(); 
            if (skorYazisi) skorYazisi->setString(std::to_string(skor)); 
            std::cout << "Guncel Skor: " << skor << std::endl; 
        }

        if (borular[i].ekrandanCiktiMi()) {
            borular.erase(borular.begin() + i);
            i--; 
        }
    }
}

void Oyun::ciz() {
    pencere.clear(sf::Color::Cyan); 
    
    // Listedeki bütün boruları ekrana çizer
    for (size_t i = 0; i < borular.size(); i++) {
        borular[i].ciz(pencere);
    }

    kus.ciz(pencere); 
    if (skorYazisi) pencere.draw(*skorYazisi); 

    // Eğer kuş çarptıysa yazıları ekrana çizer
    if (oyunBitti) {
        if (oyunBittiYazisi) pencere.draw(*oyunBittiYazisi);
        if (yenidenBaslaYazisi) pencere.draw(*yenidenBaslaYazisi); // Alt talimat yazısını da çizer
    }

    pencere.display();
}