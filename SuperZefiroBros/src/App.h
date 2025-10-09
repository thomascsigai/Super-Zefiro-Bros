// Defines application behavior
//

#include <Zefir.h>

#include <gameobjects/Player.h>

#include <scenes/DefaultScene.h>
#include <scenes/Menu.h>

namespace ZefirApp
{
	class SandboxApp : public Zefir::Application
	{
	public:
		SandboxApp()
		{}

		void OnInit() override
		{
			//m_SceneManager->LoadScene(std::make_unique<DefaultScene>(), &m_EngineContext);
			m_SceneManager->LoadScene(std::make_unique<MenuScene>(), &m_EngineContext);
			m_Window->SetSettings({ "Super Zefiro Bros. (1024 x 768)", 1024, 768, true });
		}

		void HandleEvents(SDL_Event& e) override
		{
			// Switch to first scene (1-1)
			if (e.type == UserEvents::SWITCH_FIRST_SCENE)
			{
				m_SceneManager->LoadScene(std::make_unique<DefaultScene>(), &m_EngineContext);
			}
		}
	};
}