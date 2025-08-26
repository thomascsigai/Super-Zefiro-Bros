#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Ennemi : public Zefir::GameObject
	{
	public:
		Ennemi(float x, float y, std::shared_ptr<Zefir::Texture> texture,
			std::shared_ptr<Zefir::Texture> dieTexture)
			: GameObject("Ennemi", x, y), texture(texture), dieTexture(dieTexture)
		{
			SetTexture(texture);
			m_Transform2D.SetSize(1, 1);

			m_UsePhysics = true;
			m_BodyDef.type = b2_dynamicBody;
			m_BodyDef.fixedRotation = true;
			m_BodyDef.position = { x, y };
			m_BodyDef.gravityScale = 1;

			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;
			m_ShapeDef.enableContactEvents = true;

			m_Box = b2MakeRoundedBox(0.4f, 0.48f, 0.01f);

			moveDir = { -1, 0 };
		}

		void Update(double deltaTime) override
		{
			b2Body_SetLinearVelocity(m_BodyId, { moveDir.x * moveSpeed, b2Body_GetLinearVelocity(m_BodyId).y });

			if (dieTimer.IsStarted() && dieTimer.GetTicks() > timeBeforeDespawn)
			{
				SDL_Event e;
				e.type = Zefir::EngineEvents::SCENE_REMOVE_OBJECT;
				e.user.data1 = new int(m_BodyId.index1);
				SDL_PushEvent(&e);
			}
		}

		void HandleEvent(const SDL_Event& e) override {}

		void OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold)
		{
			if (abs(manifold.normal.y) < 0.1)
			{
				moveDir.x *= -1;
			}
		}

		void Die()
		{
			SetTexture(dieTexture);
			moveDir = { 0, 0 };

			m_UsePhysics = false;
			dieTimer.Start();
		}

	private:
		Zefir::Vector2 moveDir;
		float moveSpeed = 3;

		std::shared_ptr<Zefir::Texture> texture;
		std::shared_ptr<Zefir::Texture> dieTexture;

		Zefir::Timer dieTimer;
		int timeBeforeDespawn = 100; // Time in ms for despawn ennemi when died
	};
}