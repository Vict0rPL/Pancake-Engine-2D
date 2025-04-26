/**
 * @file Scene.h
 * @brief Definicja klasy Scene, która reprezentuje scenę w grze.
 *
 * Klasa ta zarządza obiektami gry, ich aktualizowaniem, renderowaniem oraz serializowaniem i deserializowaniem sceny z pliku JSON.
 */

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "GameObject.h"
#include <SDL3/SDL.h>  // lub <SDL.h> w zależności od konfiguracji SDL

 /**
  * @brief Klasa Scene reprezentująca scenę w grze.
  *
  * Scena to miejsce, w którym znajdują się obiekty gry. Ta klasa umożliwia zarządzanie obiektami gry, ich ładowanie, aktualizowanie oraz renderowanie.
  * Dodatkowo obsługuje serializację i deserializację stanu sceny do i z plików JSON.
  */
class Scene {
public:
    /**
     * @brief Wirtualny destruktor klasy Scene.
     *
     * Destruktor jest wirtualny, aby umożliwić poprawne usuwanie obiektów dziedziczących.
     */
    virtual ~Scene() = default;

    /**
     * @brief Ładuje zasoby i ustawia stan początkowy sceny.
     *
     * Metoda ta jest wywoływana po aktywowaniu sceny. Można zaimplementować w niej ładowanie zasobów i ustawianie początkowego stanu.
     */
    virtual void Load();

    /**
     * @brief Aktualizuje scenę i wszystkie jej obiekty w danym klatce.
     *
     * Metoda ta jest wywoływana w każdej klatce gry. Powinna aktualizować stan obiektów w scenie, na przykład w celu wykonania logiki gry.
     *
     * @param deltaTime Czas, jaki upłynął od ostatniej klatki (w sekundach).
     */
    virtual void Update(float deltaTime);

    /**
     * @brief Renderuje scenę na ekranie.
     *
     * Metoda ta jest wywoływana w każdej klatce gry, aby narysować obiekty w scenie.
     *
     * @param renderer Wskaźnik do renderera SDL, który będzie używany do rysowania.
     */
    virtual void Render(SDL_Renderer* renderer);

    /**
     * @brief Dodaje obiekt gry do sceny.
     *
     * Metoda ta dodaje nowy obiekt gry do listy obiektów w scenie.
     *
     * @param gameObject Unikalny wskaźnik na obiekt gry, który ma zostać dodany do sceny.
     */
    void AddGameObject(std::unique_ptr<GameObject> gameObject);

    /**
     * @brief Oznacza obiekt gry do usunięcia z sceny.
     *
     * Metoda ta pozwala oznaczyć obiekt gry do usunięcia z listy obiektów w scenie.
     *
     * @param obj Wskaźnik na obiekt, który ma zostać usunięty.
     */
    void MarkForRemoval(GameObject* obj);

    /**
     * @brief Serializuje scenę do pliku JSON.
     *
     * Metoda ta zapisuje stan sceny (w tym wszystkie obiekty gry) do pliku JSON.
     *
     * @param filename Nazwa pliku, do którego ma zostać zapisana scena.
     * @return Zwraca wartość true, jeśli operacja zakończyła się sukcesem, w przeciwnym razie false.
     */
    bool SerializeToJson(const std::string& filename) const;

    /**
     * @brief Ładuje scenę z pliku JSON.
     *
     * Metoda statyczna, która ładuje stan sceny z pliku JSON i zwraca wskaźnik do nowej instancji sceny.
     *
     * @param filename Nazwa pliku JSON, z którego ma zostać wczytana scena.
     * @param renderer Wskaźnik do renderera SDL, który będzie używany w scenie.
     * @return Zwraca unikalny wskaźnik na załadowaną scenę.
     */
    static std::unique_ptr<Scene> LoadFromJson(const std::string& filename, SDL_Renderer* renderer);

    /**
     * @brief Zwraca referencję do listy obiektów gry w scenie.
     *
     * Metoda ta pozwala na dostęp do listy obiektów gry, która znajduje się w scenie.
     *
     * @return Zwraca referencję do wektora obiektów gry.
     */
    std::vector<std::unique_ptr<GameObject>>& GetGameObjects() {
        return gameObjects;
    }

    /**
     * @brief Zwraca stałą referencję do listy obiektów gry w scenie.
     *
     * Metoda ta pozwala na dostęp do listy obiektów gry w scenie, ale w trybie tylko do odczytu.
     *
     * @return Zwraca stałą referencję do wektora obiektów gry.
     */
    const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const {
        return gameObjects;
    }

    /**
     * @brief Lista obiektów gry, które zostały oznaczone do usunięcia.
     *
     * Obiekty na tej liście będą usuwane w czasie aktualizacji sceny.
     */
    std::vector<GameObject*> objectsToRemove;

private:
    /**
     * @brief Lista obiektów gry w scenie.
     *
     * Jest to wektor unikalnych wskaźników na obiekty gry, które są aktualnie częścią sceny.
     */
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};

