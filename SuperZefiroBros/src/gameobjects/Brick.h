#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Brick : public Zefir::GameObject
	{
	public:
		Brick(float x, float y, std::shared_ptr<Zefir::Texture> texture)
			: GameObject("Brick", x, y)
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
	};
}