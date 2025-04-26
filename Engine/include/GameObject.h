/**
 * @file GameObject.h
 * @brief Definicja klasy GameObject, będącej bazą dla obiektów gry.
 *
 * Klasa ta zawiera podstawowe dane transformacji (pozycja, rotacja, skala),
 * flagi aktywności, a także metodę konwertującą obiekt do formatu JSON.
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <vector>

 /**
  * @brief Struktura wektora 2D.
  *
  * Reprezentuje punkt lub kierunek w przestrzeni 2D, z współrzędnymi x i y.
  */
struct Vector2 {
    float x, y;

    Vector2() = default;

    /**
     * @brief Konstruktor wektora.
     *
     * @param _x Wartość współrzędnej X.
     * @param _y Wartość współrzędnej Y.
     */
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    /**
     * @brief Operator dodawania wektorów.
     *
     * @param o Drugi wektor do dodania.
     * @return Vector2 Nowy wektor będący sumą obu wektorów.
     */
    Vector2& operator+=(Vector2 const& o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    /**
     * @brief Operator dodawania wektorów (kopia).
     *
     * @param o Drugi wektor do dodania.
     * @return Vector2 Nowy wektor będący sumą obu wektorów.
     */
    Vector2 operator+ (Vector2 const& o) const {
        return { x + o.x, y + o.y };
    }
};

/**
 * @brief Klasa GameObject reprezentująca obiekt w grze.
 *
 * Zawiera dane transformacji obiektu (pozycja, rotacja, skala) oraz metodę
 * konwertującą obiekt do formatu JSON. Jest to klasa bazowa dla innych obiektów w grze.
 */
class GameObject {
public:
    /**
     * @brief Konstruktor klasy GameObject.
     *
     * Umożliwia ustawienie nazwy obiektu.
     *
     * @param name Nazwa obiektu.
     */
    GameObject(const std::string& name = "GameObject");

    /**
     * @brief Destruktor klasy GameObject.
     */
    virtual ~GameObject();

    /**
     * @brief Metoda aktualizująca obiekt.
     *
     * Zwykle wywoływana na każdą klatkę, aby zaktualizować stan obiektu.
     *
     * @param deltaTime Czas od ostatniej klatki w sekundach.
     */
    virtual void Update(float deltaTime);

    /**
     * @brief Metoda renderująca obiekt.
     *
     * Zwykle wywoływana na każdą klatkę, aby narysować obiekt na ekranie.
     *
     * @param renderer Wskaźnik na renderer SDL, używany do rysowania.
     */
    virtual void Render(SDL_Renderer* renderer);

    /// Współrzędna X i Y obiektu.
    Vector2 position{ 0.0f, 0.0f };

    /// Rotacja obiektu w stopniach.
    float rotation = 0.0f;

    /// Skala obiektu w kierunkach X i Y.
    Vector2 scale{ 1.0f, 1.0f };

    /// Flaga aktywności obiektu.
    bool isActive = true;

    /// Nazwa obiektu.
    std::string name;

    /**
     * @brief Metoda konwertująca obiekt do formatu JSON.
     *
     * Jest to metoda czysto wirtualna, implementowana przez klasy dziedziczące.
     *
     * @return nlohmann::json Reprezentacja obiektu w formacie JSON.
     */
    virtual nlohmann::json ToJson() const = 0;

    /**
     * @brief Zwraca nazwę obiektu.
     *
     * @return const std::string& Nazwa obiektu.
     */
    const std::string& GetName() const { return name; }

};

#endif // GAMEOBJECT_H
