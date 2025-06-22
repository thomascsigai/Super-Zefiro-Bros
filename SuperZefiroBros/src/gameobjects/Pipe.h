#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Pipe : public Zefir::GameObject
	{
	public:
		Pipe(float x, float y, float w, float h, std::shared_ptr<Zefir::Texture> texture)
			: GameObject("Pipe", x, y)
		{
			SetTexture(texture);

			m_Transform2D.SetSize(w, h);

			m_UsePhysics = true;
			m_BodyDef.type = b2_staticBody;
			m_BodyDef.position = { x, y };
			m_Box = b2MakeBox(w / 2, h / 2);
			m_ShapeDef.enableContactEvents = true;
			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;
		}

		void Update(double deltaTime) override {}
		void HandleEvent(const SDL_Event& e) override {}
	};
}