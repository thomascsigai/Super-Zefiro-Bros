#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class MenuBackground : public Zefir::GameObject
	{
	public:
		MenuBackground(std::shared_ptr<Zefir::Texture> texture)
		{
			SetTexture(texture);
			m_Transform2D.SetPosition(0, 0);
			m_Transform2D.SetSize(20, 15);
		}

		void Update(double deltaTime) override {}

		void HandleEvent(const SDL_Event& e) override {}
	};
}