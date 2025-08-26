#pragma once

#include <Zefir.h>
#include <gameobjects/Ennemi.h>

namespace ZefirApp
{
	class Gloomba : public ZefirApp::Ennemi
	{
	public:
		Gloomba(float x, float y, std::shared_ptr<Zefir::AnimatedTexture> anim,
			std::shared_ptr<Zefir::Texture> dieTexture)
			: Ennemi(x, y, anim, dieTexture)
		{}
	};
}