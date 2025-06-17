#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Background : public Zefir::GameObject
	{
	public:
		Background(std::shared_ptr<Zefir::Texture> texture)
		{
			SetTexture(texture);
			m_Transform2D.SetPosition(95.5f, 0);
			m_Transform2D.SetSize(211, 15);
		}

		void Update(double deltaTime) override {}

		void HandleEvent(const SDL_Event& e) override {}
	};
}