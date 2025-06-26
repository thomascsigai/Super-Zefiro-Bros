#pragma once

#include <Zefir.h>
#include <vector>

namespace ZefirApp
{
	class Block : public Zefir::GameObject
	{
	public:
		Block(float x, float y, std::shared_ptr<Zefir::Texture> texture)
			: GameObject("Block", x, y)
		{
			SetTexture(texture);
			m_Transform2D.SetSize(1, 1);

			m_UsePhysics = true;
			m_BodyDef.type = b2_staticBody;
			m_BodyDef.position = { x, y };
			m_Box = b2MakeBox(0.5, 0.5);
			m_ShapeDef.enableContactEvents = true;
			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;
		}

		void Update(double deltaTime) override {}
		void HandleEvent(const SDL_Event& e) override {}

		// Generate a vector of blocks to form a pyramid of given height and direction (1 for right, -1 for left).
		// Use topLength param for a longer top layer.
		static std::vector<std::unique_ptr<Block>> GetPyramidBlocks(Zefir::Vector2 pos, std::shared_ptr<Zefir::Texture> texture, 
			int height, int direction = 1, int topLength = 1)
		{
			std::vector<std::unique_ptr<Block>> blocks;
			blocks.reserve((float)((height * height) + height) / 2); // Reserves number of blocks needed
			int i, j;

			for (i = 0; i < topLength - 1; i++)
			{
				for (j = 0; j < height; j++)
				{
					blocks.emplace_back(std::make_unique<Block>(pos.x + i * direction, pos.y + j, texture));
				}
			}

			for (i = topLength - 1; i < height + topLength; i++)
			{
				for (j = 0; j < height - i + topLength - 1; j++)
				{
					blocks.emplace_back(std::make_unique<Block>(pos.x + i * direction, pos.y + j, texture));
				}
			}

			return blocks;
		}
	};
}