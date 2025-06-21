#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Player : public Zefir::GameObject
	{
	public:
		Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk);

		void Update(double deltaTime) override;

		void HandleEvent(const SDL_Event& e) override;

		void OnCollisionEnter(Zefir::GameObject* other) override;
		void OnCollisionExit(Zefir::GameObject* other) override;

	private:
		std::shared_ptr<Zefir::Texture> m_IdleTexture;
		std::shared_ptr<Zefir::Texture> m_WalkTexture;

		float WALK_SPEED = 5.0f;
		float JUMP_HEIGHT = 15.0f;
		Zefir::Vector2 moveDir = { 0, 0 };

		bool IsOnGround = false;
	};
}