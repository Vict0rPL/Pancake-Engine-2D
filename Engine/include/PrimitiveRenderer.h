/**
 * @file PrimitiveRenderer.h
 * @brief Definicja klasy PrimitiveRenderer do rysowania podstawowych prymitywów 2D przy użyciu SDL.
 *
 * Klasa ta umożliwia rysowanie różnych podstawowych kształtów, takich jak punkty, linie, kwadraty, okręgi, elipsy i wielokąty, oraz ich wypełnianie.
 * Wykorzystuje renderer SDL do wyświetlania tych kształtów na ekranie.
 */

#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <SDL3/SDL.h>
#include <vector>

 /**
  * @brief Klasa PrimitiveRenderer do rysowania prymitywów w przestrzeni 2D.
  *
  * Klasa ta umożliwia rysowanie prymitywów takich jak punkty, linie, kwadraty, okręgi, elipsy oraz wielokąty na ekranie za pomocą SDL.
  * Dodatkowo oferuje metody do wypełniania tych kształtów kolorem.
  */
class PrimitiveRenderer {
public:
    /**
     * @brief Konstruktor klasy PrimitiveRenderer.
     *
     * Inicjalizuje renderer SDL, który będzie używany do rysowania prymitywów.
     *
     * @param renderer Pointer do obiektu SDL_Renderer, który będzie używany do renderowania.
     */
    PrimitiveRenderer(SDL_Renderer* renderer);

    /**
     * @brief Rysuje punkt w przestrzeni 2D.
     *
     * Metoda ta rysuje pojedynczy punkt w zadanej lokalizacji (x, y) z wybranym kolorem.
     *
     * @param x Współrzędna X punktu.
     * @param y Współrzędna Y punktu.
     * @param color Kolor punktu (domyślnie czarny).
     */
    void DrawPoint(int x, int y, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Rysuje linię łączącą dwa punkty.
     *
     * Metoda ta rysuje linię pomiędzy punktami (x0, y0) oraz (x1, y1) z wybranym kolorem.
     *
     * @param x0 Współrzędna X pierwszego punktu.
     * @param y0 Współrzędna Y pierwszego punktu.
     * @param x1 Współrzędna X drugiego punktu.
     * @param y1 Współrzędna Y drugiego punktu.
     * @param color Kolor linii (domyślnie czarny).
     */
    void DrawLine(int x0, int y0, int x1, int y1, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Rysuje kwadrat.
     *
     * Metoda ta rysuje kwadrat o zadanym rozmiarze i współrzędnych (x, y), z wybranym kolorem.
     *
     * @param x Współrzędna X lewego górnego rogu kwadratu.
     * @param y Współrzędna Y lewego górnego rogu kwadratu.
     * @param size Rozmiar boku kwadratu.
     * @param color Kolor kwadratu (domyślnie czarny).
     */
    void DrawSquare(int x, int y, int size, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Wypełnia kwadrat kolorem.
     *
     * Metoda ta rysuje wypełniony kwadrat o zadanym rozmiarze i współrzędnych (x, y).
     *
     * @param x Współrzędna X lewego górnego rogu kwadratu.
     * @param y Współrzędna Y lewego górnego rogu kwadratu.
     * @param size Rozmiar boku kwadratu.
     * @param color Kolor wypełnienia kwadratu (domyślnie czarny).
     */
    void FillSquare(int x, int y, int size, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Rysuje okrąg.
     *
     * Metoda ta rysuje okrąg o zadanym promieniu i współrzędnych środka (x0, y0), z wybranym kolorem.
     *
     * @param x0 Współrzędna X środka okręgu.
     * @param y0 Współrzędna Y środka okręgu.
     * @param radius Promień okręgu.
     * @param color Kolor okręgu (domyślnie czarny).
     */
    void DrawCircle(int x0, int y0, int radius, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Wypełnia okrąg kolorem.
     *
     * Metoda ta rysuje wypełniony okrąg o zadanym promieniu i współrzędnych środka (x0, y0).
     *
     * @param x0 Współrzędna X środka okręgu.
     * @param y0 Współrzędna Y środka okręgu.
     * @param radius Promień okręgu.
     * @param color Kolor wypełnienia okręgu (domyślnie czarny).
     */
    void FillCircle(int x0, int y0, int radius, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Rysuje elipsę.
     *
     * Metoda ta rysuje elipsę o zadanych promieniach w osi X i Y, z wybranym kolorem.
     *
     * @param x0 Współrzędna X środka elipsy.
     * @param y0 Współrzędna Y środka elipsy.
     * @param rx Promień elipsy w osi X.
     * @param ry Promień elipsy w osi Y.
     * @param color Kolor elipsy (domyślnie czarny).
     */
    void DrawEllipse(int x0, int y0, int rx, int ry, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Wypełnia elipsę kolorem.
     *
     * Metoda ta rysuje wypełnioną elipsę o zadanych promieniach w osi X i Y, z wybranym kolorem.
     *
     * @param x0 Współrzędna X środka elipsy.
     * @param y0 Współrzędna Y środka elipsy.
     * @param rx Promień elipsy w osi X.
     * @param ry Promień elipsy w osi Y.
     * @param color Kolor wypełnienia elipsy (domyślnie czarny).
     */
    void FillEllipse(int x0, int y0, int rx, int ry, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Rysuje wielokąt.
     *
     * Metoda ta rysuje wielokąt zdefiniowany przez wektor punktów (SDL_Point) z wybranym kolorem.
     *
     * @param pts Wektor punktów (SDL_Point) definiujących wierzchołki wielokąta.
     * @param color Kolor wielokąta (domyślnie czarny).
     */
    void DrawPolygon(const std::vector<SDL_Point>& pts, SDL_Color color = { 0,0,0,255 });

    /**
     * @brief Wypełnia wielokąt kolorem.
     *
     * Metoda ta rysuje wypełniony wielokąt zdefiniowany przez wektor punktów (SDL_Point), z wybranym kolorem.
     *
     * @param pts Wektor punktów (SDL_Point) definiujących wierzchołki wielokąta.
     * @param color Kolor wypełnienia wielokąta (domyślnie czarny).
     */
    void FillPolygon(const std::vector<SDL_Point>& pts, SDL_Color color = { 0,0,0,255 });

private:
    SDL_Renderer* renderer; ///< Wskaźnik na renderer SDL używany do rysowania prymitywów.
};

#endif // PRIMITIVERENDERER_H
