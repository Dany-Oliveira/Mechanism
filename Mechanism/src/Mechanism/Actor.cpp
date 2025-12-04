#include "Actor.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace Mechanism
{
    Actor::Actor(void* renderer, const char* texturePath, float x, float y, int gridColumns, int gridRows, int frameIndex)
        : m_Texture(nullptr)
        , m_X(x)
        , m_Y(y)
        , m_GridColumns(gridColumns)
        , m_GridRows(gridRows)
        , m_CurrentFrame(frameIndex)
        , m_TextureWidth(0)
        , m_TextureHeight(0)
        , m_FrameWidth(0)
        , m_FrameHeight(0)
        , m_AnimationTimer(0)
        , m_FrameDuration(0)
        , m_TotalFrames(0)
    {
        if (!renderer)
        {
            std::cerr << "Error: Null renderer" << std::endl;
            return;
        }

        // Load texture
        SDL_Surface* surface = SDL_LoadBMP(texturePath);
        if (!surface)
        {
            std::cerr << "Failed to load: " << texturePath << std::endl;
            std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Store full texture size
        m_TextureWidth = surface->w;
        m_TextureHeight = surface->h;

        // Calculate frame size by dividing texture by grid
        m_FrameWidth = m_TextureWidth / m_GridColumns;
        m_FrameHeight = m_TextureHeight / m_GridRows;

        // Create texture
        SDL_Renderer* sdlRenderer = static_cast<SDL_Renderer*>(renderer);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
        SDL_DestroySurface(surface);

        if (!texture)
        {
            std::cerr << "Failed to create texture" << std::endl;
            return;
        }

        m_Texture = texture;

       
        m_TotalFrames = m_GridColumns * m_GridRows;//calculates the amount of frames in the animation

        m_FrameDuration = 0.1f; //FPS

        std::cout << "\nActor loaded: " << texturePath << std::endl;
        std::cout << "  Texture: " << m_TextureWidth << "x" << m_TextureHeight << std::endl;
        std::cout << "  Grid: " << m_GridColumns << " columns x " << m_GridRows << " rows" << std::endl;
        std::cout << "  Frame size: " << m_FrameWidth << "x" << m_FrameHeight << std::endl;
        std::cout << "  Total frames: " << m_TotalFrames << std::endl;

    }

    Actor::~Actor()
    {
        if (m_Texture)
        {
            SDL_DestroyTexture(static_cast<SDL_Texture*>(m_Texture));
            m_Texture = nullptr;
        }
    }


    void Actor::UpdateActor(float deltaTime)
    {
        if (m_TotalFrames <= 1)
            return;

        // Count time
        m_AnimationTimer += deltaTime;

        // Switch frame when enough time has passed
        if (m_AnimationTimer >= m_FrameDuration)
        {
            m_AnimationTimer = 0.0f;

            ++m_CurrentFrame;

            if (m_CurrentFrame >= m_TotalFrames)
                m_CurrentFrame = 0;  // loop back to start
        }
    }

    void Actor::ScaleActor(float scaleX, float scaleY)
    {
        m_FrameWidth = static_cast<int>(m_FrameWidth * scaleX);
		m_FrameHeight = static_cast<int>(m_FrameHeight * scaleY);
    }

    void Actor::Render(void* renderer)
    {
        if (!m_Texture || !renderer)
            return;

        SDL_Renderer* sdlRenderer = static_cast<SDL_Renderer*>(renderer);
        SDL_Texture* sdlTexture = static_cast<SDL_Texture*>(m_Texture);

        // Calculate which row and column this frame is in
        int col = m_CurrentFrame % m_GridColumns;
        int row = m_CurrentFrame / m_GridColumns;

        // Source rectangle - which sprite to grab from the sheet
        SDL_FRect srcRect = {
            static_cast<float>(col * m_FrameWidth),
            static_cast<float>(row * m_FrameHeight),
            static_cast<float>(m_FrameWidth),
            static_cast<float>(m_FrameHeight)
        };

        // Destination - where to draw on screen
        SDL_FRect destRect = {
            m_X,
            m_Y,
            static_cast<float>(m_FrameWidth),
            static_cast<float>(m_FrameHeight)
        };

        SDL_RenderTexture(sdlRenderer, sdlTexture, &srcRect, &destRect);
    }

    void Actor::SetPosition(float x, float y)
    {
        m_X = x;
        m_Y = y;
    }

    void Actor::SetFrameIndex(int index)
    {
        m_CurrentFrame = index;
    }
}