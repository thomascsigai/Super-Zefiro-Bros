#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>
#include <gameobjects/Player.h>
#include <gameobjects/Background.h>

namespace ZefirApp
{
	SDL_Texture* text;

	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene load");

			AddObjectToScene(std::make_unique<ZefirApp::Background>(
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\1-1.png"))
			);
			
			AddObjectToScene(std::make_unique<ZefirApp::Player>(ZefirApp::Player(
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mario-run.png")
			)));
			m_Cam.zoom = 2.0f;
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unload");
		}

		void OnUpdate() override
		{
			
		}

		void OnSceneEvent(const SDL_Event& e)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				
			}
		}
	};
}