#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Brick : public Zefir::GameObject
	{
	public:
		Brick(float x, float y, std::shared_ptr<Zefir::Texture> texture,
			std::shared_ptr<Zefir::Texture> broken)
			: GameObject("Brick", x, y), brokenAnim(broken)
		{
			SetTexture(texture);

			m_Transform2D.SetSize(1, 1);
			initialPos = { x, y };
			isBouncing = false;

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
			if (isBouncing)
			{
				bounceOffset += bounceVelocity * deltaTime;
				bounceVelocity -= 250.0f * deltaTime;

				if (bounceOffset < 0.0f)
				{
					bounceOffset = 0.0f;
					bounceVelocity = 10.0f;
					isBouncing = false;
					m_UsePhysics = true;
					m_BodyDef.position = { initialPos.x, initialPos.y };
				}

				m_Transform2D.position.y = initialPos.y + bounceOffset;
			}
		}

		void HandleEvent(const SDL_Event& e) override {}

		void OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold) override
		{
			if (manifold.normal.y < -0.5 && other->m_Name == "Player")
			{
				float pos = abs(other->m_Transform2D.position.x - m_Transform2D.position.x);

				if (pos < 0.5)
				{
					b2Body_SetLinearVelocity(m_BodyId, { 0, 10 });
					Break();
				}
			}
		}

		virtual void Break()
		{
			m_UsePhysics = false;
			isBouncing = true;
		}

	protected:
		std::shared_ptr<Zefir::Texture> brokenAnim;
		Zefir::Vector2 initialPos;
		
		bool isBouncing;
		float bounceOffset = 0.0f;
		float bounceVelocity = 10.0f;
	};
}