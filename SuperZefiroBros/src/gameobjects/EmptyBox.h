#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class EmptyBox : public Zefir::GameObject
	{
	public:
		EmptyBox(float x, float y, float w, float h)
			: GameObject("EmptyBox", x, y)
		{
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

		void Render(Zefir::Renderer* renderer, const Zefir::Camera& cam) override
		{
			
#ifndef NDEBUG
			// Draw collider

			if (m_UsePhysics)
			{
				SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 0, 0, 255);
				Zefir::Vector2 pos = Zefir::Vector2(b2Body_GetPosition(m_BodyId).x, b2Body_GetPosition(m_BodyId).y);
				renderer->RenderRect(pos, m_Transform2D.size, cam);
				SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
			}
#endif
		}
	};
}