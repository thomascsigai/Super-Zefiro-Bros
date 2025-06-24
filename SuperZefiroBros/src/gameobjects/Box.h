#pragma once

#include <Zefir.h>

#include <gameobjects/Brick.h>

namespace ZefirApp
{
	class Box : public Brick
	{
	public:
		Box(float x, float y, std::shared_ptr<Zefir::Texture> texture,
			std::shared_ptr<Zefir::Texture> broken)
			: Brick(x, y, texture, broken)
		{
			m_Name = "Box";
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

		void Break() override
		{
			if (m_Texture == brokenAnim) return;

			m_UsePhysics = false;
			isBouncing = true;

			SetTexture(brokenAnim);
		}
	};
}