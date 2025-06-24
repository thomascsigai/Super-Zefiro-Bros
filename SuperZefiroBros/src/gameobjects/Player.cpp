#include <gameobjects/Player.h>
#include <GameConfig.h>
#include <algorithm>

namespace ZefirApp
{
	Player::Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk,
		std::shared_ptr<Zefir::Texture> jump)
		: GameObject("Player"), m_IdleTexture(idle), m_WalkTexture(walk), m_JumpTexture(jump)
	{
		m_Transform2D.SetPosition(-5, -5);
		m_Transform2D.SetSize(1, 1);

		SetTexture(m_IdleTexture);

		m_UsePhysics = true;
		m_BodyDef.type = b2_dynamicBody;
		m_BodyDef.fixedRotation = true;
		m_BodyDef.position = { -5, -5 };
		m_BodyDef.gravityScale = 1;
		m_ShapeDef.material.friction = 0.0f;
		m_ShapeDef.material.restitution = 0.0f;
		m_ShapeDef.enableContactEvents = true;
		m_Box = b2MakeRoundedBox(0.4f, 0.5f, 0.01f);
	}

	void Player::Update(double deltaTime)
	{
		b2Vec2 velocity = b2Body_GetLinearVelocity(m_BodyId);

		if (!IsOnGround())
		{
			SetTexture(m_JumpTexture);
		}
		else if (abs(velocity.x) >= 0.01f)
		{
			if (m_WalkTexture != m_Texture)
				SetTexture(m_WalkTexture);
		}
		else
		{
			SetTexture(m_IdleTexture);
		}

		if (moveDir.x != 0) m_Transform2D.horizontalFlip = (moveDir.x < 0);

		velocity.x = moveDir.x * WALK_SPEED;
		if (moveDir.y != 0 && IsOnGround()) velocity.y = JUMP_HEIGHT; 
		moveDir.y = 0;

		b2Body_SetLinearVelocity(m_BodyId, velocity);
	}

	void Player::HandleEvent(const SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT)	moveDir.x -= 1;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT)	moveDir.x += 1;
			if (e.key.keysym.sym == SDLK_SPACE)			moveDir.y += 1;
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT)	moveDir.x += 1;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT)	moveDir.x -= 1;
		}
	}

	bool Player::IsOnGround()
	{
		return (groundObjects.size() != 0);
	}

	void Player::OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold)
	{
		auto it = std::find(groundObjects.begin(), groundObjects.end(), other);
		if (manifold.normal.y < -0.8f && it == groundObjects.end())
		{
			groundObjects.push_back(other);
		}
	}

	void Player::OnCollisionExit(Zefir::GameObject* other)
	{
		auto it = std::find(groundObjects.begin(), groundObjects.end(), other);
		if (it != groundObjects.end())
		{
			groundObjects.erase(it);
		}
	}
}