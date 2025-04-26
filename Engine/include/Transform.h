/**
 * @file Transform.h
 * @brief Definicje struktur i funkcji służących do przekształceń (transformat) 2D, takich jak przesunięcie, obrót i skalowanie.
 *
 * Plik ten zawiera definicje struktur oraz funkcji pomocniczych, które umożliwiają wykonywanie operacji matematycznych
 * na wektorach i macierzach 2D. Są one przydatne w kontekście grafiki komputerowej, gdzie często zachodzi potrzeba
 * transformacji obiektów, takich jak przesunięcie, obrót czy skalowanie.
 */

#pragma once
#include <cmath>

 /**
  * @brief Struktura Mat3 reprezentująca macierz 3x3.
  *
  * Macierz 3x3 jest wykorzystywana do transformacji 2D obiektów w przestrzeni, takich jak:
  * - Przesunięcie
  * - Obrót
  * - Skalowanie
  */
struct Mat3 {
    float m[3][3]; ///< Tablica przechowująca elementy macierzy 3x3.

    /**
     * @brief Tworzy macierz przesunięcia.
     *
     * Macierz ta jest używana do przesunięcia obiektów w przestrzeni 2D.
     *
     * @param tx Wartość przesunięcia w osi X.
     * @param ty Wartość przesunięcia w osi Y.
     * @return Zwraca macierz przesunięcia.
     */
    static Mat3 Translate(float tx, float ty) {
        return Mat3{ {
          {1, 0, tx},
          {0, 1, ty},
          {0, 0, 1 }
        } };
    }

    /**
     * @brief Tworzy macierz obrotu.
     *
     * Macierz ta jest używana do obrotu obiektów w przestrzeni 2D o zadany kąt.
     *
     * @param radians Kąt obrotu w radianach.
     * @return Zwraca macierz obrotu.
     */
    static Mat3 Rotate(float radians) {
        float c = std::cos(radians), s = std::sin(radians);
        return Mat3{ {
          { c, -s, 0 },
          { s,  c, 0 },
          { 0,  0, 1 }
        } };
    }

    /**
     * @brief Tworzy macierz skalowania.
     *
     * Macierz ta jest używana do skalowania obiektów w przestrzeni 2D w osi X i Y.
     *
     * @param sx Wartość skali w osi X.
     * @param sy Wartość skali w osi Y.
     * @return Zwraca macierz skalowania.
     */
    static Mat3 Scale(float sx, float sy) {
        return Mat3{ {
          { sx,  0,  0 },
          {  0, sy,  0 },
          {  0,  0,  1 }
        } };
    }

    /**
     * @brief Mnoży dwie macierze 3x3.
     *
     * Operator mnożenia macierzy wykonuje operację mnożenia dwóch macierzy 3x3.
     *
     * @param o Druga macierz, którą będziemy mnożyć przez bieżącą.
     * @return Zwraca wynik mnożenia dwóch macierzy.
     */
    Mat3 operator*(const Mat3& o) const {
        Mat3 r{};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                r.m[i][j] = m[i][0] * o.m[0][j]
            + m[i][1] * o.m[1][j]
                + m[i][2] * o.m[2][j];
                return r;
    }
};

/**
 * @brief Operator mnożenia macierzy 3x3 i wektora 2D.
 *
 * Operator umożliwia zastosowanie transformacji (np. przesunięcia, obrotu, skalowania) na wektorze 2D za pomocą macierzy 3x3.
 *
 * @param M Macierz transformacji.
 * @param v Wektor 2D, na którym zostanie zastosowana transformacja.
 * @return Zwraca nowy wektor 2D po zastosowanej transformacji.
 */
inline Vector2 operator*(const Mat3& M, const Vector2& v) {
    return {
      M.m[0][0] * v.x + M.m[0][1] * v.y + M.m[0][2],
      M.m[1][0] * v.x + M.m[1][1] * v.y + M.m[1][2]
    };
}
