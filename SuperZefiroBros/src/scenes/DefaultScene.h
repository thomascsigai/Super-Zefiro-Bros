#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>

#include <gameobjects/Player.h>
#include <gameobjects/Background.h>
#include <gameobjects/Ground.h>
#include <gameobjects/Pipe.h>
#include <gameobjects/Brick.h>
#include <gameobjects/Box.h>
#include <gameobjects/EmptyBox.h>

namespace ZefirApp
{
	SDL_Texture* text;

	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene load");
			m_Cam.zoom = 2.0f;

			//Background
			AddObjectToScene(std::make_unique<ZefirApp::Background>(
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\1-1.png"))
			);
			
			// Player
			AddObjectToScene(std::make_unique<ZefirApp::Player>(ZefirApp::Player(
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mario-run.png"),
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario-jump.png")
			)));
			ptr_Player = m_SceneObjects[1].get();

			// Props ----------------------------------------
			//Pipes
			std::array<Zefir::Vector2, 6> pipeCoords = {
				Zefir::Vector2(19, -5.5),
				Zefir::Vector2(29, -4.5),
				Zefir::Vector2(37, -3.5),
				Zefir::Vector2(48, -3.5),
				Zefir::Vector2(154, -5.5),
				Zefir::Vector2(170, -5.5)
			};

			for (auto& pipe : pipeCoords)
			{
				AddObjectToScene(std::make_unique<ZefirApp::Pipe>(
					pipe.x, pipe.y, 2, 4,
					m_EngineContext->resourceManager->GetTexture("resources\\textures\\pipe.png")
					));
			}
			
			//Bricks
			std::array<Zefir::Vector2, 3> brickCoords = {
				Zefir::Vector2(10.5, -2.0),
				Zefir::Vector2(12.5, -2.0),
				Zefir::Vector2(14.5, -2.0)
			};

			for (auto& brick : brickCoords)
			{
				AddObjectToScene(std::make_unique<ZefirApp::Brick>(
					brick.x, brick.y,
					m_EngineContext->resourceManager->GetTexture("resources\\textures\\brick.png"),
					m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\brick-broken.png")
				));
			}

			// Boxs
			std::array<Zefir::Vector2, 4> boxCoords = {
				Zefir::Vector2(5.5, -2.0),
				Zefir::Vector2(11.5, -2.0),
				Zefir::Vector2(13.5, -2.0),
				Zefir::Vector2(12.5, 2.0)
			};

			for (auto& box : boxCoords)
			{
				AddObjectToScene(std::make_unique<ZefirApp::Box>(
					box.x, box.y,
					m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\box.png"),
					m_EngineContext->resourceManager->GetTexture("resources\\textures\\box-broken.png")
				));
			}

			// Grounds
			AddObjectToScene(std::make_unique<ZefirApp::Ground>(
				24.5, -6.5, 69, 2,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\ground.png")
			));
			AddObjectToScene(std::make_unique<ZefirApp::Ground>(
				68.5, -6.5, 15, 2,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\ground.png")
			));
			AddObjectToScene(std::make_unique<ZefirApp::Ground>(
				111, -6.5, 64, 2,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\ground.png")
			));
			AddObjectToScene(std::make_unique<ZefirApp::Ground>(
				173, -6.5, 56, 2,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\ground.png")
			));

			if (!ptr_Player)
			{
				APP_LOG_FATAL("Player not created.");
			}
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unload");
		}

		void OnUpdate() override
		{
			CameraUpdatePosition();
		}

		void OnSceneEvent(const SDL_Event& e)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				
			}
		}

		void CameraUpdatePosition()
		{
			if (ptr_Player->m_Transform2D.position.x > 0 && ptr_Player->m_Transform2D.position.x < 191)
			{
				m_Cam.position.x = m_SceneObjects[1]->m_Transform2D.position.x;
			}
		}

		Zefir::GameObject* ptr_Player;
	};
}