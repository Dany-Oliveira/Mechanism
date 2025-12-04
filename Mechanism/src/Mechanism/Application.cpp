#include "Application.h"
#include "SDL3/SDL.h"

namespace Mechanism
{

	Application::Application()
	{
		m_Window = std::make_unique<Window>();
	}

	Application::~Application()
	{
	}

	//Keep the application running
	void Application::Run()
	{
		Uint64 lastTime = SDL_GetTicks();

		while (m_Running)
		{			
			if(m_Window->CloseWindow())
			{
				m_Running = false;
				break;
			}

			//Calculate delta time
			Uint64 currentTime = SDL_GetTicks();
			float deltaTime = (currentTime - lastTime) / 1000.0f;
			lastTime = currentTime;


			OnUpdate(deltaTime);


			// Clear screen to black before rendering
			auto* renderer = static_cast<SDL_Renderer*>(m_Window->GetRenderer());
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			OnRender();

			m_Window->OnUpdate();

		}
	}



}


