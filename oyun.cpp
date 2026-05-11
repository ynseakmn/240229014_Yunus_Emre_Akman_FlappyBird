#include "oyun.hpp"
#include <ctime>

Oyun::Oyun() : pencere(sf::VideoMode({800, 600}), "Flappy Bird KOU") {
    pencere.setFramerateLimit(60);
    srand(time(NULL)); // Rastgelelik tohumu atılır
}

void Oyun::calistir() {
    while (pencere.isOpen()) { olaylari_isle(); guncelle(); ciz(); }
}

void Oyun::olaylari_isle() {
    while (const std::optional olay = pencere.pollEvent()) {
        if (olay->is<sf::Event::Closed>()) pencere.close();
        if (olay->is<sf::Event::KeyPressed>() && 
            olay->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {
            kus.zipla(); // Boşluk tuşuyla zıplar
        }
    }
}

void Oyun::guncelle() {
    kus.guncelle();

    // 1.5 saniyede bir rastgele Pipe ekler
    if (boruZamanlayici.getElapsedTime().asSeconds() > 1.5f) {
        float rastgeleY = (rand() % 200) + 100.f;
        borular.push_back(Pipe(800.f, rastgeleY, 150.f));
        boruZamanlayici.restart(); // Saati sıfırla
    }

    // Pipe'ları kaydır ve ekrandan çıkanları siler
    for (size_t i = 0; i < borular.size(); i++) {
        borular[i].guncelle();
        if (borular[i].ekrandanCiktiMi()) {
            borular.erase(borular.begin() + i);
            i--; 
        }
    }
}

void Oyun::ciz() {
    pencere.clear(sf::Color::Cyan); // Arka plan
    for (auto& boru : borular) boru.ciz(pencere); // Kuşun arkasında kalsın diye önce borular çizilir
    kus.ciz(pencere); // Kuşu çizer
    pencere.display();
}