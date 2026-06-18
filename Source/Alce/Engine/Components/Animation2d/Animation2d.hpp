#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class Animation2D : public Component
    {
    public:

        Animation2D();

        void AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight, int numFrames = -1);

        bool DeleteAnimation(String name);

        void SetOriginMode(OriginMode originMode);

        bool PlayAnimation(String name, AnimationMode mode = AnimationMode::LoopForwards);

        void SetAnimationMode(AnimationMode mode);

        bool SetTimePerFrame(Time timePerFrame);

        bool SetTimePerFrame(float ms);

        void Pause(bool flag = true);

        bool IsPlaying();

        Dictionary<String, Vector2Ptr> GetCardinals();

        String GetCurrentAnimation();

        void Render();

        void Update();

        Vector2 scale = Vector2(1, 1);

        Vector2 offset = Vector2(0, 0);

    private:

        Dictionary<String, List<RectShape*>> animations;
        Dictionary<String, sf::Sprite*> spritesheets;
        Dictionary<String, Vector2Ptr> cardinals;

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

    typedef std::shared_ptr<Animation2D> Animation2dPtr;
}