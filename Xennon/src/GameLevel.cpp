#include "GameLevel.h"
#include <Mechanism/Actor.h>
#include <Mechanism/Window.h>
#include <iostream>


    GameLevel::GameLevel(Mechanism::Window& window): m_Renderer(window.GetRenderer()), m_Player(nullptr)
    {
        printf("\nGameLevel created!\n");


        // Spawn player in center
        SpawnEnemy(600, 800);


        printf("Spawned %zu actors\n", m_Actors.size());
    }

    GameLevel::~GameLevel()
    {
        printf("GameLevel destroyed! Cleaning up %zu actors\n", m_Actors.size());
        ClearAllActors();
    }

    void GameLevel::SpawnEnemy(float x, float y)
    {
        // Create player actor                                x   y  col row 0=its the srite in the col0 row0, the first sprite
        m_Player = new Mechanism::Actor(m_Renderer, "assets/galaxy2.bmp", 0, 0, 1, 1, 0);
        m_Actors.push_back(m_Player);
        printf("\nPlayer spawned at (%.0f, %.0f)\n", x, y);
    }

    void GameLevel::Render()
    {
        // Render all actors
        for (auto* actor : m_Actors)
        {
            if (actor)
            {
                actor->Render(m_Renderer);
            }
        }
    }

    void GameLevel::UpdateGameLevel(float deltaTime)
    {
        for (auto* actor : m_Actors)
        {
            if (actor)
                actor->UpdateActor(deltaTime);
        }
    }

   

    void GameLevel::ClearAllActors()
    {
        for (auto* actor : m_Actors)
        {
            delete actor;
        }
        m_Actors.clear();
        m_Player = nullptr;
    }

    void GameLevel::SetBackground()
    {
    }

