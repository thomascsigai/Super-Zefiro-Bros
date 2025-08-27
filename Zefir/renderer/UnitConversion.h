#pragma once

#include <core/math/Vector2.h>

namespace Zefir
{
    constexpr int PIXELS_PER_METER = 50.0f;

    // ZEFIR AXIS :
    // ORIGIN AT THE CENTER OF THE SCREEN
    // RIGHT HANDED - Y UP

    // Convert the position from world coordinates to camera related position
    inline Vector2 WorldToCamera(const Vector2& position, const Camera& cam)
    {
        return { position.x - cam.position.x, position.y - cam.position.y };
    }

    // Convert World Coordinates (meters) to screen coordinates (pixels).
    inline Vector2 WorldToScreenPosition(const Vector2& worldPos, int screenWidth, int screenHeight, const Camera& cam)
    {
        Vector2 pos = WorldToCamera(worldPos, cam);

        const float scale = PIXELS_PER_METER + cam.zoom;
        const float halfW = 0.5f * static_cast<float>(screenWidth);
        const float halfH = 0.5f * static_cast<float>(screenHeight);

        pos.x = scale * pos.x + halfW;
        pos.y = halfH - scale * pos.y;

        return pos;
    }

    // Given the center position (world coordinates) of a rect and his size, create a SDL_Rect
    // that can be drawn on the screen.
    inline SDL_FRect WorldToScreenRect(const Vector2& center, const Vector2& size, const Camera& cam)
    {
        SDL_FRect rect = {
            center.x - (size.x / 2) * (PIXELS_PER_METER + cam.zoom), center.y - (size.y / 2) * (PIXELS_PER_METER + cam.zoom),
            size.x * (PIXELS_PER_METER + cam.zoom), size.y * (PIXELS_PER_METER + cam.zoom)
        };

        return rect;
    }

    // Convert Screen Coordinates (pixels) to World coordinates (pixels).
    inline Vector2 ScreenToWorld(const Vector2& screenPos, int screenWidth, int screenHeight, const Camera& cam)
    {
        const float scaleInv = 1.0f / (PIXELS_PER_METER + cam.zoom);
        const float halfW = 0.5f * static_cast<float>(screenWidth);
        const float halfH = 0.5f * static_cast<float>(screenHeight);

        Vector2 pos;
        pos.x = (screenPos.x - halfW) * scaleInv;
        pos.y = (halfH - screenPos.y) * scaleInv;

        pos += cam.position;
        return pos;
    }
}