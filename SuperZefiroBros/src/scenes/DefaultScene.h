#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>
#include <vector>

#include <UserEvents.h>

#include <gameobjects/Player.h>
#include <gameobjects/BigPlayer.h>
#include <gameobjects/Background.h>
#include <gameobjects/Ground.h>
#include <gameobjects/Pipe.h>
#include <gameobjects/Brick.h>
#include <gameobjects/Box.h>
#include <gameobjects/EmptyBox.h>
#include <gameobjects/Block.h>
#include <gameobjects/Mushroom.h>

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
			AddObjectToScene(std::make_unique<ZefirApp::Player>(
				-5, -5,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mario-run.png"),
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario-jump.png")
			));
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

			// Blocks pyramids
			std::vector<std::unique_ptr<Block>> pyramid;
			
			pyramid = Block::GetPyramidBlocks(
				{ 127.5, -5 }, m_EngineContext->resourceManager->GetTexture("resources\\textures\\block.png"), 4, -1
			);
			for (auto& block : pyramid)	AddObjectToScene(std::move(block));

			pyramid = Block::GetPyramidBlocks(
				{ 130.5, -5 }, m_EngineContext->resourceManager->GetTexture("resources\\textures\\block.png"), 4
			);
			for (auto& block : pyramid)	AddObjectToScene(std::move(block));

			pyramid = Block::GetPyramidBlocks(
				{ 142.5, -5 }, m_EngineContext->resourceManager->GetTexture("resources\\textures\\block.png"), 4, -1, 2
			);
			for (auto& block : pyramid)	AddObjectToScene(std::move(block));
			
			pyramid = Block::GetPyramidBlocks(
				{ 145.5, -5 }, m_EngineContext->resourceManager->GetTexture("resources\\textures\\block.png"), 4
			);
			for (auto& block : pyramid)	AddObjectToScene(std::move(block));
			
			pyramid = Block::GetPyramidBlocks(
				{ 179.5, -5 }, m_EngineContext->resourceManager->GetTexture("resources\\textures\\block.png"), 8, -1, 2
			);
			for (auto& block : pyramid)	AddObjectToScene(std::move(block));

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

			AddObjectToScene(std::make_unique<ZefirApp::Mushroom>(
				0, 0,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mushroom.png")
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

			if (e.type == UserEvents::PLAYER_GROW)
			{
				GrowPlayerSize();
			}

			if (e.type == UserEvents::PAUSE_ANIM_PLAYING)
			{
				// Put here the behavior of go when a player anim is playing
			}
		}

		void CameraUpdatePosition()
		{
			if (ptr_Player->m_Transform2D.position.x > 0 && ptr_Player->m_Transform2D.position.x < 191)
			{
				m_Cam.position.x = ptr_Player->m_Transform2D.position.x;
			}
		}

		void GrowPlayerSize()
		{
			AddObjectToScene(std::make_unique<ZefirApp::Player>(ZefirApp::BigPlayer(
				ptr_Player->m_Transform2D.position.x, ptr_Player->m_Transform2D.position.y + 0.5f,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario-big.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mario-big-run.png"),
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario-big-jump.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mario-grow.png")
			)));
			
			RemoveObject(ptr_Player->m_BodyId.index1);

			ptr_Player = std::prev(m_SceneObjects.end())->second.get();
		}

		Zefir::GameObject* ptr_Player;
	};
}