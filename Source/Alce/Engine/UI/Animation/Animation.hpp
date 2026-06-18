#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class Animation : public UIElement
    {
    public:

        Animation() : UIElement("Animation")
        {
            
        }

        void AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight, int numFrames = -1);

        void DeleteAnimation(String name);

        void SetOriginMode(OriginMode originMode);

        void PlayAnimation(String name, AnimationMode mode = AnimationMode::LoopForwards);

        void SetAnimationMode(AnimationMode mode);

        void SetTimePerFrame(Time timePerFrame);

        void SetTimePerFrame(float ms);

        void Pause(bool flag = true);

        bool IsPlaying();

        String GetCurrentAnimation();

        void Init();

        void Start();

        void Render();

        void Update();

    private:
        
        Dictionary<String, List<RectShape*>> animations;
        Dictionary<String, sf::Sprite*> spritesheets;

        String currentAnimation;
        AnimationMode currentMode;
        bool isPlaying = false;
        OriginMode originMode = OriginMode::Center;

        int numFrames;
        int msPerFrame = 100;
        int msSinceLastFrame;
        int currentFrameNum;

        bool paused = false;
        bool flipHorizontal = false;
        bool flipVertical = false;
        
        void DetermineNumFrames();
        void DetermineFirstFrameNum();
        void DetermineNextFrameNum();
        void SetTextureRectForFrame();
        bool IsDrawable();
    };

    typedef std::shared_ptr<Animation> AnimationPtr;
}