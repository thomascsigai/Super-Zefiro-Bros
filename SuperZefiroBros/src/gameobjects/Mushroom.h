#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Mushroom : public Zefir::GameObject
	{
	public:
		Mushroom(float x, float y, std::shared_ptr<Zefir::Texture> texture)
			: GameObject("Mushroom", x, y)
		{
			SetTexture(texture);

			m_Transform2D.SetSize(1, 1);

			m_UsePhysics = true;
			m_BodyDef.type = b2_dynamicBody;
			m_BodyDef.position = { x, y };
			m_Box = b2MakeRoundedBox(0.4, 0.4, 0.1);
			m_ShapeDef.enableContactEvents = true;
			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;

			moveDir = { 1, 0 };
		}

		void Update(double deltaTime) override
		{
			b2Body_SetLinearVelocity(m_BodyId, { moveDir.x * moveSpeed, b2Body_GetLinearVelocity(m_BodyId).y});
		}

		void HandleEvent(const SDL_Event& e) override {}

		void OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold)
		{
			if (abs(manifold.normal.y) < 0.1)
			{
				moveDir.x *= -1;
			}
		}

	private:
		Zefir::Vector2 moveDir;
		float moveSpeed = 3;
	};
}