#pragma once

#include <SDL.h>

namespace ZefirApp
{
	namespace UserEvents
	{
		// Place here your events you have to use in your app
		// const inline Uint32 EVENT_EXEMPLE = SDL_RegisterEvents(1);
		
		const inline Uint32 PLAYER_GROW = SDL_RegisterEvents(1);
		const inline Uint32 PLAYER_SHRINK = SDL_RegisterEvents(1);
		const inline Uint32 PAUSE_ANIM_PLAYING = SDL_RegisterEvents(1);

		const inline Uint32 BOX_ITEM_SPAWN = SDL_RegisterEvents(1);
	}
}