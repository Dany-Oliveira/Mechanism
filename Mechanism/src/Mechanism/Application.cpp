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

			m_Window->GetRenderer().Clear(0, 0, 0);		
			OnRender();
			m_Window->GetRenderer().Present();

			m_Window->OnUpdate();

		}
	}



}


