#include <gameobjects/Player.h>
#include <GameConfig.h>

namespace ZefirApp
{
	Player::Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk)
		: GameObject("Player"), m_IdleTexture(idle), m_WalkTexture(walk)
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
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	void Player::Update(double deltaTime)
	{
		b2Vec2 velocity = b2Body_GetLinearVelocity(m_BodyId);

		if (abs(velocity.x) >= 0.01f)
		{
			if (m_WalkTexture != m_Texture)
				SetTexture(m_WalkTexture);
		}
		else
		{
			SetTexture(m_IdleTexture);
		}

		velocity.x = moveDir.x * WALK_SPEED;

		if (moveDir.y != 0 && IsOnGround())
		{
			velocity.y = JUMP_HEIGHT;
		}
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
		return true;
	}
}