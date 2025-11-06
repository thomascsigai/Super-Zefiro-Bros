#pragma once

#include <scene/Scene.h>
#include <scene/UI/UIText.h>
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
#include <gameobjects/BoxCoin.h>
#include <gameobjects/Ennemi.h>
#include <gameobjects/Gloomba.h>

namespace ZefirApp
{
	SDL_Texture* text;

	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene load");
			m_Cam.zoom = 2.0f;
			m_Timer = Zefir::Timer();
			m_Timer.Start();

			//UI

			AddUIToScene(std::make_unique<Zefir::UIText>(
				-7.0f, 6.0f, // Position
				std::string("MARIO"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UIScoreLabel = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());
			
			AddUIToScene(std::make_unique<Zefir::UIText>(
				-7.0f, 5.0f, // Position
				std::string("0"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UIScore = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());


			AddUIToScene(std::make_unique<Zefir::UIText>(
				-2.5f, 6.0f, // Position
				std::string("COINS"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UIPiecesLabel = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());
			
			AddUIToScene(std::make_unique<Zefir::UIText>(
				-2.5f, 5.0f, // Position
				std::string("0"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UIPieces = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());


			AddUIToScene(std::make_unique<Zefir::UIText>(
				2.5f, 6.0f, // Position
				std::string("WORLD"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UIWorldLabel = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());
			
			AddUIToScene(std::make_unique<Zefir::UIText>(
				2.5f, 5.0f, // Position
				std::string("1-1"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UIWorld = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());


			AddUIToScene(std::make_unique<Zefir::UIText>(
				7.0f, 6.0f, // Position
				std::string("TIME"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UITimeLabel = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());
			
			AddUIToScene(std::make_unique<Zefir::UIText>(
				7.0f, 5.0f, // Position
				std::string("400"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				50, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			m_UITime = static_cast<Zefir::UIText*>(std::prev(m_UIObjects.end())->second.get());

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
			const int numberOfBricks = 3;

			std::array<Zefir::Vector2, numberOfBricks> brickCoords = {
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

			// Boxs & items
			const int numberOfBoxes = 4;

			std::array<Zefir::Vector2, numberOfBoxes> boxCoords = {
				Zefir::Vector2(5.5, -2.0),
				Zefir::Vector2(11.5, -2.0),
				Zefir::Vector2(13.5, -2.0),
				Zefir::Vector2(12.5, 2.0)
			};

			std::array<BoxItemType, numberOfBoxes> boxItems = {
				BoxItemType::Coin,
				BoxItemType::Mushroom,
				BoxItemType::Coin,
				BoxItemType::Coin
			};

			for (int i = 0; i < numberOfBoxes; i++)
			{
				AddObjectToScene(std::make_unique<ZefirApp::Box>(
					boxCoords[i].x, boxCoords[i].y,
					m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\box.png"),
					m_EngineContext->resourceManager->GetTexture("resources\\textures\\box-broken.png"),
					boxItems[i]
				));
			}

			// Enemies

			AddObjectToScene(std::make_unique<ZefirApp::Gloomba>(
				30, 0,
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\gloomba.png"),
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\gloomba-die.png")
			));

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
			UpdateScoreUI();
			UpdateTimer();
		}

		void OnSceneEvent(const SDL_Event& e)
		{
			if (e.type == UserEvents::BOX_ITEM_SPAWN)
			{
				BoxItemType* item = static_cast<BoxItemType*>(e.user.data1);
				Zefir::Vector2* pos = static_cast<Zefir::Vector2*>(e.user.data2);

				if (*item == BoxItemType::Mushroom)
				{
					AddObjectToScene(std::make_unique<Mushroom>(
						pos->x, pos->y + 1,
						m_EngineContext->resourceManager->GetTexture("resources\\textures\\mushroom.png"),
						m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mushroom-spawning.png")
					));
				}
				else if (*item == BoxItemType::Coin)
				{
					AddObjectToScene(std::make_unique<BoxCoin>(
						pos->x, pos->y + 1.5,
						m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\box-coin-spawning.png")
					));
					m_Pieces++;
					m_Score += 200;
				}
				else
				{
					APP_LOG_WARN("Trying to spawn unknow item : ", item);
				}

				delete item;
				delete pos;
			}

			if (e.type == UserEvents::PLAYER_GROW)
			{
				GrowPlayerSize();
				m_Score += 100;
			}
			
			if (e.type == UserEvents::PLAYER_SHRINK)
			{
				ShrinkPlayerSize();
			}

			if (e.type == UserEvents::PAUSE_ANIM_PLAYING)
			{
				// Put here the behavior of go when a player anim is playing
			}
			
			if (e.type == UserEvents::ENEMI_KILLED)
			{
				m_Score += 100;
			}
		}

		void CameraUpdatePosition()
		{
			if (ptr_Player->m_Transform2D.position.x > 0 && ptr_Player->m_Transform2D.position.x < 191)
			{
				m_Cam.position.x = ptr_Player->m_Transform2D.position.x;

				// Update UI Position
				m_UIScoreLabel->m_Position.x = -7.0f + m_Cam.position.x;
				m_UIPiecesLabel->m_Position.x = -2.5f + m_Cam.position.x;
				m_UIWorldLabel->m_Position.x = 2.5f + m_Cam.position.x;
				m_UITimeLabel->m_Position.x = 7.0f + m_Cam.position.x;
				
				m_UIScore->m_Position.x = -7.0f + m_Cam.position.x;
				m_UIPieces->m_Position.x = -2.5f + m_Cam.position.x;
				m_UIWorld->m_Position.x = 2.5f + m_Cam.position.x;
				m_UITime->m_Position.x = 7.0f + m_Cam.position.x;
			}
		}

		void UpdateScoreUI()
		{
			m_UIScore->SetText(std::to_string(m_Score));
			m_UIPieces->SetText(std::to_string(m_Pieces));
			m_UITime->SetText(std::to_string(m_Time));
		}

		void UpdateTimer()
		{
			if (m_Timer.GetTicks() > 1000)
			{
				m_Time -= 1;
				m_Timer.Stop();
				m_Timer.Start();
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

		void ShrinkPlayerSize()
		{
			AddObjectToScene(std::make_unique<ZefirApp::Player>(
				ptr_Player->m_Transform2D.position.x, ptr_Player->m_Transform2D.position.y + 0.5f,
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\mario-run.png"),
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\mario-jump.png")
			));

			RemoveObject(ptr_Player->m_BodyId.index1);

			ptr_Player = std::prev(m_SceneObjects.end())->second.get();
		}

		Zefir::GameObject* ptr_Player;

		Zefir::UIText* m_UIScoreLabel;
		Zefir::UIText* m_UIScore;
		Zefir::UIText* m_UIPiecesLabel;
		Zefir::UIText* m_UIPieces;
		Zefir::UIText* m_UIWorldLabel;
		Zefir::UIText* m_UIWorld;
		Zefir::UIText* m_UITimeLabel;
		Zefir::UIText* m_UITime;

		int m_Score = 0;
		int m_Pieces = 0;
		int m_Time = 400;

		Zefir::Timer m_Timer;
	};
}