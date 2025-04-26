/**
 * @file main.cpp
 * @brief Punkt wejścia do edytora scen 2D z wykorzystaniem SDL i ImGui.
 *
 * Ten plik zawiera główną funkcję programu, która inicjalizuje silnik gry (`Engine`),
 * tworzy graficzny interfejs użytkownika edytora (`EditorUI`), a następnie uruchamia pętlę edytora.
 */

#include "Engine.h"
#include "EditorUI.h"
#include <iostream>

 /**
  * @brief Główna funkcja aplikacji.
  *
  * Tworzy instancję silnika gry oraz edytora. Inicjalizuje biblioteki,
  * uruchamia główną pętlę edytora oraz przeprowadza procedurę sprzątania po zakończeniu pracy programu.
  *
  * @param argc Liczba argumentów wiersza poleceń (nieużywane).
  * @param argv Tablica argumentów wiersza poleceń (nieużywane).
  * @return Zwraca 0 w przypadku pomyślnego zakończenia lub -1 jeśli wystąpił błąd inicjalizacji silnika.
  */
int main(int argc, char* argv[]) {
    // Tworzenie instancji silnika gry
    Engine engine;
    if (!engine.Initialize()) {
        std::cerr << "Błąd inicjalizacji silnika!\n";
        return -1;
    }

    // Tworzenie edytora i przekazanie wskaźnika do silnika
    EditorUI editor(&engine);
    editor.InitializeImGui();

    // Uruchomienie głównej pętli edytora
    editor.Run();

    // Czyszczenie i zakończenie działania
    engine.Shutdown();
    return 0;
}
