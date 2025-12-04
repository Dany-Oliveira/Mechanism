#pragma once
#include "Core.h"

namespace Mechanism
{
    class MECHANISM_API Actor
    {
    public:

        
        Actor(void* renderer, const char* texturePath, float x, float y,
            int gridColumns, int gridRows, int frameIndex = 0);
        ~Actor();

        void Render(void* renderer);
        void SetPosition(float x, float y);
        void UpdateActor(float deltaTime);

		void ScaleActor(float scaleX, float scaleY);
        
        void SetFrameIndex(int index);

        float GetX() const { return m_X; }
        float GetY() const { return m_Y; }
        bool IsValid() const { return m_Texture != nullptr; }


        

    private:

        void* m_Texture;

        float m_X;
        float m_Y;

        // Grid info
        int m_GridColumns;     // How many sprites across
        int m_GridRows;        // How many sprites down
        int m_CurrentFrame;    // Which frame to display

        // Calculated from texture and grid
        int m_TextureWidth;    // Full image width
        int m_TextureHeight;   // Full image height
        int m_FrameWidth;      // Width of one sprite 
        int m_FrameHeight;     // Height of one sprite 

        float m_AnimationTimer;
        float m_FrameDuration; //FPS
        int m_TotalFrames;
      
    };
}
