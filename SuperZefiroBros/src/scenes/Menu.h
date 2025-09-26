#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>

#include <gameobjects/Background.h>

namespace ZefirApp
{
	class MenuScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			m_Cam.zoom = 2.0f;

			
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
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					APP_LOG_INFO("Scene swicth");
				}
			}
		}
	};
}