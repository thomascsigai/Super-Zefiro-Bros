// Defines application behavior
//

#include <Zefir.h>

#include <gameobjects/Player.h>

#include <scenes/DefaultScene.h>

namespace ZefirApp
{
	class SandboxApp : public Zefir::Application
	{
	public:
		SandboxApp()
		{}

		void OnInit() override
		{
			m_SceneManager->LoadScene(std::make_unique<DefaultScene>(), &m_EngineContext);
			m_Window->SetSettings({ "Sandbox", 1080, 720, true });
		}

		void HandleEvents(SDL_Event& e) override
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_1)
				{
					m_SceneManager->LoadScene(std::make_unique<DefaultScene>(), &m_EngineContext);
				}
			}
		}
	};
}