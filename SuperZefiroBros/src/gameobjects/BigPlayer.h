#pragma once

#include <Zefir.h>
#include <gameobjects/Player.h>

namespace ZefirApp
{
	class BigPlayer : public Player
	{
	public:
		BigPlayer(float x, float y,std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk,
			std::shared_ptr<Zefir::Texture> jump, std::shared_ptr<Zefir::Texture> grow)
			: Player(x, y, idle, walk, jump)
		{
			m_Transform2D.SetSize(1, 2);

			isBig = true;
			isGrowing = true;

			SetTexture(grow);

			m_UsePhysics = true;
			m_BodyDef.type = b2_dynamicBody;
			m_BodyDef.fixedRotation = true;
			m_BodyDef.position = {x, y};
			m_BodyDef.gravityScale = 1;
			m_ShapeDef.material.friction = 0.0f;
			m_ShapeDef.material.restitution = 0.0f;
			m_ShapeDef.enableContactEvents = true;
			m_Box = b2MakeRoundedBox(0.4f, 0.99f, 0.01f);
		}
	};
}