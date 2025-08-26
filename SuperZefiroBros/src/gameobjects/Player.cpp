#include <gameobjects/Player.h>
#include <gameobjects/Ennemi.h>
#include <UserEvents.h>
#include <GameConfig.h>
#include <algorithm>

namespace ZefirApp
{
	Player::Player(float x, float y, std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk,
		std::shared_ptr<Zefir::Texture> jump)
		: GameObject("Player", x, y), m_IdleTexture(idle), m_WalkTexture(walk), m_JumpTexture(jump),
		isBig(false), isGrowing(false)
	{
		m_Transform2D.SetSize(1, 1);

		SetTexture(m_IdleTexture);

		m_UsePhysics = true;
		m_BodyDef.type = b2_dynamicBody;
		m_BodyDef.fixedRotation = true;
		m_BodyDef.position = { x, y };
		m_BodyDef.gravityScale = 1;
		m_BodyDef.enableSleep = false;

		m_ShapeDef.material.friction = 0.0f;
		m_ShapeDef.material.restitution = 0.0f;
		m_ShapeDef.enableContactEvents = true;

		m_Box = b2MakeRoundedBox(0.4f, 0.48f, 0.01f);
	}

	void Player::Update(double deltaTime)
	{
		if (isGrowing)
		{
			m_UsePhysics = false;
			
			if (m_AnimEnded)
			{
				isGrowing = false;
				b2Body_SetGravityScale(m_BodyId, 1);
				m_UsePhysics = true;
			}
			else return;
		}

		ProcessKeyboardState();

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

		// Flip the transform to face walking direction
		if (moveDir.x != 0) m_Transform2D.horizontalFlip = (moveDir.x < 0);

		// Apply velocity
		velocity.x = moveDir.x * WALK_SPEED;
		if (moveDir.y != 0 && IsOnGround()) velocity.y = JUMP_HEIGHT;

		b2Body_SetLinearVelocity(m_BodyId, velocity);
	}

	void Player::HandleEvent(const SDL_Event& e)
	{}

	bool Player::IsOnGround()
	{
		return (groundObjects.size() != 0);
	}

	void Player::OnCollisionEnter(Zefir::GameObject* other, b2Manifold manifold)
	{
		if (other->m_Name == "Mushroom")
		{
			if (!isBig) Grow();
			
			SDL_Event e;
			e.type = Zefir::EngineEvents::SCENE_REMOVE_OBJECT;
			e.user.data1 = new int(other->m_BodyId.index1);
			SDL_PushEvent(&e);
			
			return;
		}

		if (other->m_Name == "Ennemi")
		{
			if (manifold.normal.y < -0.9)
			{
				/*SDL_Event e;
				e.type = Zefir::EngineEvents::SCENE_REMOVE_OBJECT;
				e.user.data1 = new int(other->m_BodyId.index1);
				SDL_PushEvent(&e);*/

				static_cast<ZefirApp::Ennemi*>(other)->Die();
				b2Body_ApplyLinearImpulse(m_BodyId, killEnnemiImpulse.ToB2Vec2(), b2Body_GetLocalCenterOfMass(m_BodyId), true);
				return;
			}
			else
			{
				if (isBig) Shrink();
				else APP_LOG_INFO("Die");
			}
		}

		// Detect if player hit any type of ground
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

	void Player::Grow()
	{		
		SDL_Event e1, e2;

		e1.type = UserEvents::PLAYER_GROW;
		SDL_PushEvent(&e1);

		e2.type = UserEvents::PAUSE_ANIM_PLAYING;
		SDL_PushEvent(&e2);
	}

	void Player::Shrink()
	{
		SDL_Event e1, e2;

		e1.type = UserEvents::PLAYER_SHRINK;
		SDL_PushEvent(&e1);

		e2.type = UserEvents::PAUSE_ANIM_PLAYING;
		SDL_PushEvent(&e2);
	}

	void Player::ProcessKeyboardState()
	{
		const Uint8* keystate = SDL_GetKeyboardState(nullptr);

		moveDir = { 0, 0 };

		if (keystate[SDL_GetScancodeFromKey(MOVE_KEYBIND.LEFT)])  moveDir.x -= 1;
		if (keystate[SDL_GetScancodeFromKey(MOVE_KEYBIND.RIGHT)]) moveDir.x += 1;
		
		if (keystate[SDL_GetScancodeFromKey(JUMP_KEYBIND)])       moveDir.y += 1;
	}
}