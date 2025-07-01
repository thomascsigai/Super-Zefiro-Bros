#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class BoxCoin : public Zefir::GameObject
	{
	public:
		BoxCoin(float x, float y, std::shared_ptr<Zefir::Texture> anim)
			: GameObject("BoxCoin", x, y)
		{
			SetTexture(anim);

			m_Transform2D.SetSize(1, 2);

			m_UsePhysics = true;
			m_BodyDef.type = b2_staticBody;
			m_BodyDef.position = { x, y };
			m_Box = b2MakeBox(0.5, 0.5);
			m_ShapeDef.enableContactEvents = true;
			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;
		}

		void Update(double deltaTime) override
		{
			m_UsePhysics = true;

			if (m_AnimEnded)
			{
				SDL_Event e;
				e.type = Zefir::EngineEvents::SCENE_REMOVE_OBJECT;
				e.user.data1 = new int(m_BodyId.index1);
				SDL_PushEvent(&e);
			}
		}

		void HandleEvent(const SDL_Event& e) override {}

		void OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold) override {}
	};
}