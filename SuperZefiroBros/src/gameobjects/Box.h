#pragma once

#include <Zefir.h>

#include <gameobjects/Brick.h>

namespace ZefirApp
{
	class Box : public Brick
	{
	public:
		Box(float x, float y, std::shared_ptr<Zefir::Texture> texture,
			std::shared_ptr<Zefir::Texture> broken, std::string itemToSpawn)
			: Brick(x, y, texture, broken)
		{
			m_Name = "Box";
			SetTexture(texture);

			m_ItemToSpawn = itemToSpawn;

			m_Transform2D.SetSize(1, 1);

			m_UsePhysics = true;
			m_BodyDef.type = b2_staticBody;
			m_BodyDef.position = { x, y };
			m_Box = b2MakeBox(0.5, 0.5);
			m_ShapeDef.enableContactEvents = true;
			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;
		}

		void Break() override
		{
			if (m_Texture == brokenAnim) return;

			m_UsePhysics = false;
			isBouncing = true;

			SetTexture(brokenAnim);

			// Push spawning item event
			SDL_Event e;
			e.type = UserEvents::BOX_ITEM_SPAWN;
			e.user.data1 = new std::string(m_ItemToSpawn);
			e.user.data2 = new Zefir::Vector2(m_Transform2D.position);
			SDL_PushEvent(&e);
		}

	private:
		std::string m_ItemToSpawn;
	};
}