/**
 * @file Player.cpp
 * @brief Implementacja klasy `Player` reprezentującej gracza w grze.
 *
 * Klasa `Player` zarządza animacjami, ruchem gracza oraz interakcjami z obiektami w grze, takimi jak kolizje z przeszkodami i zbieranie przedmiotów.
 *
 * Gracz porusza się w jednym z czterech kierunków (góra, dół, lewo, prawo) i zbiera przedmioty typu `Circle`. Gra kończy się, gdy gracz zbierze wszystkie kręgi.
 */

#include "Player.h"
#include "Square.h"
#include "Circle.h"
#include "Scene.h"
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp> 
#include <algorithm>
#include <iostream>

 /**
  * @brief Konstruktor klasy `Player`.
  *
  * Tworzy obiekt `Player`, inicjalizując animacje i inne właściwości gracza.
  *
  * @param renderer Renderer do rysowania sprite'a gracza.
  * @param spriteSheetPath Ścieżka do pliku sprite'a.
  * @param scene Wskaźnik na scenę, w której znajduje się gracz.
  */
Player::Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, Scene* scene)
    : SpriteObject(renderer, spriteSheetPath, 32, 32, 4, 0.1f),
    currentDirection(Direction::None),
    speed(100.0f),
    sceneRef(scene)
{
}

/**
 * @brief Obsługuje wejście z klawiatury i ustawia kierunek ruchu gracza.
 *
 * Ta metoda sprawdza, które klawisze są wciśnięte i ustawia kierunek ruchu gracza na podstawie stanu klawiatury.
 *
 * @param keyboardState Tablica stanu klawiszy z SDL, gdzie każdy element wskazuje, czy dany klawisz jest wciśnięty.
 */
void Player::HandleInput(const bool* keyboardState) {
    currentDirection = Direction::None;

    if (keyboardState[SDL_SCANCODE_W]) currentDirection = Direction::Up;
    else if (keyboardState[SDL_SCANCODE_S]) currentDirection = Direction::Down;
    else if (keyboardState[SDL_SCANCODE_A]) currentDirection = Direction::Left;
    else if (keyboardState[SDL_SCANCODE_D]) currentDirection = Direction::Right;
}

/**
 * @brief Aktualizuje stan gracza, obsługując ruch i interakcje.
 *
 * Gracz porusza się w określonym kierunku, sprawdzając kolizje z innymi obiektami, takimi jak kwadraty i kręgi.
 * Po zebraniu wszystkich kręgów gra kończy się wyświetlając komunikat o zwycięstwie.
 *
 * @param deltaTime Czas, który upłynął od ostatniej klatki (w sekundach).
 */
void Player::Update(float deltaTime) {
    if (currentDirection != Direction::None) {
        // Aktualizowanie animacji i pozycji gracza
        SpriteObject::Update(deltaTime);

        float dx = 0.0f, dy = 0.0f;
        switch (currentDirection) {
        case Direction::Up:    dy = -speed * deltaTime; break;
        case Direction::Down:  dy = speed * deltaTime; break;
        case Direction::Left:  dx = -speed * deltaTime; break;
        case Direction::Right: dx = speed * deltaTime; break;
        default: break;
        }
        directionRow = (currentDirection == Direction::Up) ? 0 :
            (currentDirection == Direction::Down) ? 1 :
            (currentDirection == Direction::Left) ? 2 : 3;

        // Przewidywanie przyszłej pozycji gracza (przyszły prostokąt)
        SDL_FRect futureRect = dstRect;
        futureRect.x += static_cast<int>(dx);
        futureRect.y += static_cast<int>(dy);

        bool canMove = true;

        // Sprawdzanie kolizji z kwadratami (blokada ruchu)
        for (auto& obj : sceneRef->GetGameObjects()) {
            if (obj->GetName() == "Square") {
                auto* square = dynamic_cast<Square*>(obj.get());
                if (square) {
                    SDL_FRect squareRect = square->GetRect();
                    if (SDL_HasRectIntersectionFloat(&futureRect, &squareRect)) {
                        canMove = false;
                        break;
                    }
                }
            }
        }

        if (canMove) {
            dstRect.x += static_cast<int>(dx);
            dstRect.y += static_cast<int>(dy);
        }

        // Sprawdzanie zbierania kręgów (oznaczenie do usunięcia)
        for (auto& obj : sceneRef->GetGameObjects()) {
            if (obj->GetName() == "Circle") {
                auto* circle = dynamic_cast<Circle*>(obj.get());
                if (circle) {
                    SDL_FRect circleRect = circle->GetRect();
                    if (SDL_HasRectIntersectionFloat(&dstRect, &circleRect)) {
                        std::cout << "Collected a circle!\n";
                        sceneRef->MarkForRemoval(obj.get());  // Oznacz obiekt do usunięcia
                        break;  // opcjonalnie: przerwij, jeśli tylko jeden krąg może zostać zebrany na raz
                    }
                }
            }
        }

        // Warunek zwycięstwa (brak pozostałych kręgów)
        bool circlesRemaining = std::any_of(
            sceneRef->GetGameObjects().begin(),
            sceneRef->GetGameObjects().end(),
            [](const std::unique_ptr<GameObject>& obj) {
                return obj->GetName() == "Circle";
            }
        );

        if (!circlesRemaining) {
            std::cout << "You collected all the circles! You won!" << std::endl;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory!", "You collected all circles!", nullptr);
            exit(0);  // zatrzymaj grę po wygranej
        }
    }
    else {
        currentFrame = 0;  // Zatrzymaj animację, gdy gracz jest bez ruchu
    }
}

/**
 * @brief Zwraca reprezentację gracza w formacie JSON.
 *
 * Ta metoda generuje dane JSON opisujące stan gracza, takie jak pozycja, rotacja i skala.
 *
 * @return Obiekt JSON zawierający dane gracza.
 */
nlohmann::json Player::ToJson() const {
    nlohmann::json j;
    j["type"] = "Player";
    j["position"] = { {"x", position.x}, {"y", position.y} };
    j["rotation"] = rotation;
    j["scale"] = { {"x", scale.x}, {"y", scale.y} };
    return j;
}
