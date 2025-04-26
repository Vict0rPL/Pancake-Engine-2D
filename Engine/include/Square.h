/**
 * @file Square.h
 * @brief Definicja klasy Square, reprezentującej kwadrat w grze.
 *
 * Klasa Square dziedziczy po klasach GameObject i TransformableObject, umożliwiając tworzenie kwadratów,
 * które mogą być rysowane, przekształcane (przesunięcie, obrót, skalowanie) oraz serializowane do formatu JSON.
 */

#pragma once
#include "GameObject.h" 
#include "TransformableObject.h"
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

 /**
  * @brief Klasa Square reprezentująca kwadrat w grze.
  *
  * Kwadrat jest obiektem gry, który można przekształcać (przesuwać, obracać, skalować) i rysować na ekranie.
  * Klasa dziedziczy po GameObject, co pozwala na zarządzanie jego podstawowymi właściwościami (np. pozycją),
  * oraz po TransformableObject, umożliwiając manipulowanie jego transformacjami.
  */
class Square : public GameObject, public TransformableObject {
public:
    /**
     * @brief Konstruktor klasy Square.
     *
     * Tworzy obiekt kwadratu na podstawie jego pozycji, rozmiaru oraz kolorów wypełnienia i konturu.
     *
     * @param x Pozycja X lewego górnego rogu kwadratu.
     * @param y Pozycja Y lewego górnego rogu kwadratu.
     * @param size Długość boku kwadratu.
     * @param fill Kolor wypełnienia kwadratu.
     * @param outline Kolor konturu kwadratu.
     */
    Square(int x, int y, int size, SDL_Color fill, SDL_Color outline);

    /**
     * @brief Rysuje kwadrat za pomocą renderer'a prymitywów.
     *
     * Metoda ta rysuje kwadrat na ekranie przy użyciu klasy PrimitiveRenderer, uwzględniając jego kolory i transformacje.
     *
     * @param renderer Obiekt PrimitiveRenderer do rysowania kwadratu.
     */
    virtual void Draw(PrimitiveRenderer& renderer) const;

    /**
     * @brief Renderuje kwadrat na ekranie.
     *
     * Metoda ta rysuje kwadrat na ekranie przy pomocy SDL_Renderer.
     *
     * @param renderer Wskaźnik na SDL_Renderer, który renderuje obiekt na ekranie.
     */
    virtual void Render(SDL_Renderer* renderer) override;

    /**
     * @brief Konwertuje obiekt kwadratu na format JSON.
     *
     * Umożliwia zapisanie stanu kwadratu do formatu JSON.
     *
     * @return Obiekt JSON reprezentujący kwadrat.
     */
    virtual nlohmann::json ToJson() const override;

    /**
     * @brief Przesuwa kwadrat o określoną wartość w osi X i Y.
     *
     * Metoda ta zmienia pozycję kwadratu, przesuwając go o podane wartości w poziomie i pionie.
     *
     * @param dx Wartość przesunięcia w osi X.
     * @param dy Wartość przesunięcia w osi Y.
     */
    void Translate(float dx, float dy)          override;

    /**
     * @brief Obraca kwadrat o podany kąt (w radianach).
     *
     * Zmienia orientację kwadratu na ekranie.
     *
     * @param angleRad Kąt obrotu w radianach.
     */
    void Rotate(float angleRad)              override;

    /**
     * @brief Skaluje kwadrat w poziomie i pionie.
     *
     * Zmienia rozmiar kwadratu w obu osiach (X i Y).
     *
     * @param sx Wartość skali w osi X.
     * @param sy Wartość skali w osi Y.
     */
    void Scale(float sx, float sy)          override;

    /**
     * @brief Zwraca pozycję X lewego górnego rogu kwadratu.
     *
     * @return Pozycja X kwadratu.
     */
    int GetX()    const { return x; }

    /**
     * @brief Zwraca pozycję Y lewego górnego rogu kwadratu.
     *
     * @return Pozycja Y kwadratu.
     */
    int GetY()    const { return y; }

    /**
     * @brief Zwraca rozmiar boku kwadratu.
     *
     * @return Długość boku kwadratu.
     */
    int GetSize() const { return size; }

    /**
     * @brief Zwraca prostokąt, który obejmuje kwadrat, z uwzględnieniem transformacji.
     *
     * Zwraca prostokąt o takich wymiarach, który obejmuje kwadrat po skalowaniu.
     *
     * @return Prostokąt obejmujący kwadrat.
     */
    SDL_FRect GetRect() const {
        return {
            GetPosition().x,
            GetPosition().y,
            static_cast<float>(size),
            static_cast<float>(size)
        };
    }

private:
    /**
     * @brief Pozycja X lewego górnego rogu kwadratu.
     */
    int x;

    /**
     * @brief Pozycja Y lewego górnego rogu kwadratu.
     */
    int y;

    /**
     * @brief Długość boku kwadratu.
     */
    int size;

    /**
     * @brief Kolor wypełnienia kwadratu.
     */
    SDL_Color fillColor;

    /**
     * @brief Kolor konturu kwadratu.
     */
    SDL_Color outlineColor;
};
