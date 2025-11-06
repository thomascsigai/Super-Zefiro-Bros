#pragma once

#include <scene/Scene.h>
#include <scene/UI/UIText.h>
#include <core/debug/Log.h>

#include <gameobjects/menu/Background.h>

namespace ZefirApp
{
	class MenuScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			m_Cam.zoom = 2.0f;

			AddUIToScene(std::make_unique<Zefir::UIText>(
				0.0f, -2.0f, // Position
				std::string("Press Return to Play"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			
			//AddUIToScene(std::make_unique<Zefir::UIText>(
			//	0.0f, -2.0f, // Position
			//	std::string("Press R to Change Resolution"), // Text
			//	m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
			//	40, SDL_Color(100, 100, 100, 255) // Font Size, Color
			//));

			//Background
			AddObjectToScene(std::make_unique<ZefirApp::MenuBackground>(
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\menu.png"))
			);
		}

		void OnUnload() override
		{

		}

		void OnUpdate() override
		{

		}

		void OnSceneEvent(const SDL_Event& e)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_RETURN)
				{
					SDL_Event e = { UserEvents::SWITCH_FIRST_SCENE };
					SDL_PushEvent(&e);

					m_EngineContext->soundManager->PlaySound(
						m_EngineContext->resourceManager->GetSound("resources\\sounds\\smb_1-up.wav")
					);
				}
			}
		}
	};
}