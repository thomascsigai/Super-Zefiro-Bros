#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Player : public Zefir::GameObject
	{
	public:
		Player(float x, float y, std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk,
			std::shared_ptr<Zefir::Texture> jump);

		void Update(double deltaTime) override;

		void HandleEvent(const SDL_Event& e) override;

		void OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold) override;
		void OnCollisionExit(Zefir::GameObject* other) override;

		bool IsOnGround();

		void Grow();
		void Shrink();

		void ProcessKeyboardState();

	protected:
		bool isBig;
		bool isGrowing;

	private:
		std::shared_ptr<Zefir::Texture> m_IdleTexture;
		std::shared_ptr<Zefir::Texture> m_WalkTexture;
		std::shared_ptr<Zefir::Texture> m_JumpTexture;

		float WALK_SPEED = 5.0f;
		float JUMP_HEIGHT = 16.0f;
		Zefir::Vector2 moveDir = { 0, 0 };

		Zefir::Vector2 killEnnemiImpulse = { 0, 3 };

		std::vector<Zefir::GameObject*> groundObjects;
	};
}