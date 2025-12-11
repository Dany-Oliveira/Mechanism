#pragma once
#include <vector>
#include "Mechanism/Actor.h"
#include "Mechanism/Window.h"
#include <memory>  
#include <optional>



    class GameLevel
    {
    public:
        GameLevel(Mechanism::Window& window);
        ~GameLevel();

        void Render();
        void UpdateGameLevel(float deltaTime);

		void SpawnLoner(float x, float y);
		void SpawnRusher(float x, float y);

        void AddBackground();
        void ClearAllActors();


    private:

        void* m_Renderer;

		int m_WindowWidth;
		int m_WindowHeight;

		std::vector<std::unique_ptr<Mechanism::Actor>> m_Actors;// All actors in the level

        Mechanism::Actor* m_Background;
        Mechanism::Actor* m_Loner;
        Mechanism::Actor* m_Rusher;
    };

