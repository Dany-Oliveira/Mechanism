#include <Mechanism.h>
#include "GameLevel.h"


class TestApp : public Mechanism::Application
{
	public:

		TestApp() : m_CurrentLevel(nullptr)
		{
			printf("Test App created\n");

			auto& window = GetWindow();
			printf("Window size: %d x %d\n", window.GetWidth(), window.GetHeight());

			m_CurrentLevel = new GameLevel(window);
			
		}
		~TestApp()
		{
			printf("TestApp destroyed!\n");
			delete m_CurrentLevel;
		}

		void OnUpdate(float deltaTime) override
		{
			if(m_CurrentLevel)
			{
				m_CurrentLevel->UpdateGameLevel(deltaTime);
			}
		}

		void OnRender() override
		{
			if (m_CurrentLevel)
			{
				m_CurrentLevel->Render();
			}
		}

	private:
		
		GameLevel* m_CurrentLevel;
};

Mechanism::Application* Mechanism::CreateApplication()
{
	return new TestApp();
}