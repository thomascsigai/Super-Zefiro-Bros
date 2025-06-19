#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Ground : public Zefir::GameObject
	{
	public:
		Ground(float x, float y, float w, float h, std::shared_ptr<Zefir::Texture> texture)
		{
			SetTexture(texture);

			m_Transform2D.SetPosition(x, y);
			m_Transform2D.SetSize(w, h);

			m_UsePhysics = true;
			m_BodyDef.type = b2_staticBody;
			m_BodyDef.position = { x, y };
			m_Box = b2MakeBox(w/2, h/2);
		}

		void Update(double deltaTime) override {}
		void HandleEvent(const SDL_Event& e) override {}

		void Render(Zefir::Renderer* renderer, const Zefir::Camera& cam) override
		{
			if (m_Texture != nullptr)
			{
				for (int rows = 0; rows < m_Transform2D.size.x; rows++)
				{
					for (int cols = 0; cols < m_Transform2D.size.y; cols++)
					{
						Zefir::Vector2 newBlockPos = {
							m_Transform2D.position.x + rows - m_Transform2D.size.x / 2 + 0.5f,
							m_Transform2D.position.y + cols - m_Transform2D.size.y / 2 + 0.5f
						};

						renderer->RenderStaticTexture(
							m_Texture->GetSDLTexture(), 
							newBlockPos,
							{1, 1},
							m_Transform2D.rotation, cam);
					}
				}
			}
			else
			{
				// GO has no texture, render a filled rect
				renderer->RenderFilledRect(m_Transform2D.position, m_Transform2D.size, cam);
			}


#ifndef NDEBUG
			// Draw collider

			if (m_UsePhysics)
			{
				SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 0, 0, 255);
				Zefir::Vector2 pos = Zefir::Vector2(b2Body_GetPosition(m_BodyId).x, b2Body_GetPosition(m_BodyId).y);
				renderer->RenderRect(pos, m_Transform2D.size, cam);
				SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
			}
#endif

		}
	};
}