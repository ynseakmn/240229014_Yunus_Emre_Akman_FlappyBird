#include "oyun.hpp"
#include <ctime> 
#include <iostream> // Skoru terminale yazdırır
#include <string>   // Sayıları yazıya (string) çevirir

// SFML 3.0 ÇÖZÜMÜ: skorYazisi(font) eklenerek yazı oluşturulurken font peşinen verildi!
Oyun::Oyun() : pencere(sf::VideoMode({800, 600}), "Flappy Bird KOU"), oyunBitti(false), skor(0), skorYazisi(font) {
    pencere.setFramerateLimit(60);
    srand(time(NULL)); // Rastgelelik sağlar

    // YENİ: FONT VE YAZI AYARLARI
    if (!font.openFromFile("font.ttf")) {
        std::cout << "HATA: font.ttf dosyasi bulunamadi!" << std::endl;
    }
    
    skorYazisi.setString("0");                  // Başlangıçta 0 yazsın
    skorYazisi.setCharacterSize(50);            // Yazı boyutu
    skorYazisi.setFillColor(sf::Color::White);  // Yazı rengi beyaz olsun
    skorYazisi.setPosition({10.f, 10.f});       // Sol üst köşede dursun
}

// Oyunu sıfırlar
void Oyun::sifirla() {
    kus = Kus();               // Kuşu başlangıç ayarlarına (yukarıya) döndürür
    borular.clear();           // Ekrandaki tüm boruları siler
    boruZamanlayici.restart(); // Zamanlayıcıyı baştan başlatır
    oyunBitti = false;         // Oyunu devam ettir
    skor = 0;                  // Oyun sıfırlandığında skor da sıfırlanır
    skorYazisi.setString("0"); // Oyun sıfırlanınca ekrandaki yazı da sıfırlanır
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
        // Üst borunun yüksekliği rastgele 100 ile 300 piksel arası
        float rastgeleY = (rand() % 200) + 100.f;
        
        // Ekranın en sağına (X=800), rastgele deliğe sahip ve boşluk boyutu 150 olan bir boru ekler
        borular.push_back(Pipe(800.f, rastgeleY, 150.f)); 
        
        boruZamanlayici.restart(); // Saati sıfırlar
    }

    // Listedeki tüm boruları sola kaydırır
    for (size_t i = 0; i < borular.size(); i++) {
        borular[i].guncelle();

        if (kusKutusu.findIntersection(borular[i].getUstBounds()) || 
            kusKutusu.findIntersection(borular[i].getAltBounds())) {
            oyunBitti = true; // Çarptık!
        }

        if (!borular[i].isGecildi() && kusKutusu.position.x > borular[i].getUstBounds().position.x + borular[i].getUstBounds().size.x) {
            skor++; // Skoru 1 artırır
            borular[i].setGecildi(); // Boruyu "geçildi" olarak işaretler
            skorYazisi.setString(std::to_string(skor)); // Skoru ekrandaki yazıya ata
            std::cout << "Guncel Skor: " << skor << std::endl; // Terminale yazar
        }

        // Eğer boru ekranın solundan tamamen çıktıysa onu listeden siler
        if (borular[i].ekrandanCiktiMi()) {
            borular.erase(borular.begin() + i);
            i--; // Listeden eleman sildiğimiz için sayacı bir geri alır
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
    pencere.draw(skorYazisi); // Skor yazısını ekrana çizer
    pencere.display();
}