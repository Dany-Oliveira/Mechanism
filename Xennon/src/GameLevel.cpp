#include "GameLevel.h"
#include <iostream>


    GameLevel::GameLevel(Mechanism::Window& window): Level(0.0f, 0.0f), 
        m_Renderer(&window.GetRenderer()), m_Background(nullptr), m_Loner(nullptr), m_Rusher(nullptr), m_Player(nullptr),
        m_WindowWidth(window.GetWidth()), m_WindowHeight(window.GetHeight())
    {
        printf("\nGameLevel created!\n");

		AddBackground();
		SpawnLoner(100.0f, 100.0f);
		SpawnRusher(300.0f, 300.0f);

        printf("Spawned %zu actors\n", m_Actors.size());
    }

    GameLevel::~GameLevel()
    {
        printf("GameLevel destroyed! Cleaning up %zu actors\n", m_Actors.size());
        ClearAllActors();
    }


 
    void GameLevel::AddBackground ()
    {
        // x   y  col row 0=its the srite in the col0 row0, the first sprite
        auto background = std::make_unique<Mechanism::Actor>(m_Renderer->GetNativeRenderer(), "assets/galaxy2.bmp", 0, 0, 1, 1, 0);

		m_Background = background.get();
        if(m_Background)
        {
            m_Background->ScaleActor(3.0f, 3.0f);
        }  
		m_Actors.push_back(std::move(background));

        printf("\nBackground added\n");        
    }

    void GameLevel::SpawnLoner(float xPos, float yPos)
    {
        // x   y  col row 0=its the srite in the col0 row0, the first sprite
        auto loner = std::make_unique<Mechanism::Actor>(m_Renderer->GetNativeRenderer(), "assets/LonerA.bmp", xPos, yPos, 4, 4, 0);

		// Create physics body
		loner->CreatePhysicsBody(GetBox2DWorld().GetWorldId(), true, false);

        m_Loner = loner.get();
        m_Actors.push_back(std::move(loner));

        printf("\Loner spawned at (%.0f, %.0f)\n", xPos, yPos);
    }

    void GameLevel::SpawnRusher(float xPos, float yPos)
    {
        // x   y  col row 0=its the srite in the col0 row0, the first sprite
        auto rusher = std::make_unique<Mechanism::Actor>(m_Renderer->GetNativeRenderer(), "assets/rusher.bmp", xPos, yPos, 6, 4, 0);

		rusher->CreatePhysicsBody(GetBox2DWorld().GetWorldId(), true, false);

		m_Rusher = rusher.get();
        m_Actors.push_back(std::move(rusher));

        printf("\Rusher spawned at (%.0f, %.0f)\n", xPos, yPos);
    }

    void GameLevel::SpawnPlayer(float x, float y)
    {
		
    }

    void GameLevel::Render()
    {
        // Render all actors
        for (const auto& actor : m_Actors)
        {
            if (actor)
            {
                actor->Render(m_Renderer->GetNativeRenderer());
            }
        }
    }

    void GameLevel::UpdateGameLevel(float deltaTime)
    {
		Level::Update(deltaTime);

        for (const auto& actor : m_Actors)
        {
            if (actor)
            {
                actor->UpdateActor(deltaTime);
            }
        }
    }

    void GameLevel::ClearAllActors()
    {
        m_Actors.clear();
		m_Background = nullptr;
		m_Loner = nullptr;
        m_Rusher = nullptr;
    }


