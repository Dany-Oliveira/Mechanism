#pragma once
#include <vector>
#include "Mechanism/Actor.h"
#include "Mechanism/Window.h"

    class GameLevel
    {
    public:
        GameLevel(Mechanism::Window& window);
        ~GameLevel();

        void Render();
        void UpdateGameLevel(float deltaTime);

       
        void SpawnEnemy(float x, float y);

        void AddBackground(float x, float y);

        
        void ClearAllActors();

        void SetBackground();

    private:
        void* m_Renderer;
        std::vector<Mechanism::Actor*> m_Actors;
        Mechanism::Actor* m_Player;
    };

