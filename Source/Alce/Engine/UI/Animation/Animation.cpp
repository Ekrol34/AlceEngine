#include "Animation.hpp"

using namespace alce;

void Animation::Init()
{
    
}

void Animation::Start()
{
    
}

void Animation::AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight, int numFrames)
{
    spritesheets.Set(name, new sf::Sprite());
    spritesheets[name]->setTexture(*Alce.GetTexture(spritesheetFile));

    List<RectShape*> frames;
    int _numFrames = 0;

    int x = 0, y = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            frames.Add(new RectShape(Vector2(x, y), frameWidth, frameHeight));
            x += frameWidth;
            _numFrames++;

            if(numFrames != -1 && _numFrames >= numFrames) break;
        }

        y += frameHeight;
        x = 0;
    }

    animations.Set(name, frames);
}

void Animation::DeleteAnimation(String name)
{
    animations.RemoveByKey(name);
}

void Animation::SetOriginMode(OriginMode originMode)
{
    this->originMode = originMode;
}

void Animation::PlayAnimation(String name, AnimationMode mode)
{
    if(!enabled) return;

    if(!animations.HasKey(name))
    {
        Debug.Warning("[UI] Animation::PlayAnimation -> There is not animation named \"{}\" in the stack", {name});
        return;
    }

    currentAnimation = name;
    currentMode = mode;
    isPlaying = true;

    msSinceLastFrame = 0;

    DetermineNumFrames();
    DetermineFirstFrameNum();
    SetTextureRectForFrame();
}

void Animation::SetAnimationMode(AnimationMode mode)
{
    currentMode = mode;
}

void Animation::SetTimePerFrame(Time time)
{
    msPerFrame = time.ToMiliseconds();
}

void Animation::SetTimePerFrame(float ms)
{
    msPerFrame = ms;
}

void Animation::Pause(bool flag)
{
    paused = flag;
}

bool Animation::IsPlaying()
{
    return isPlaying;
}

String Animation::GetCurrentAnimation()
{
    return this->currentAnimation;
}

void Animation::DetermineNumFrames()
{
    numFrames = animations[currentAnimation].Length();
}

void Animation::DetermineFirstFrameNum()
{
    switch(currentMode)
    {
    case AnimationMode::LoopForwards:
    case AnimationMode::OnceForwards:
    case AnimationMode::FirstFrameOnly:
        currentFrameNum = 0;
        break;
    case AnimationMode::LoopBackwards:
    case AnimationMode::OnceBackwards:
        currentFrameNum = numFrames - 1;
        break;
    }
}

void Animation::DetermineNextFrameNum()
{
    if(!isPlaying) return;
    if(currentMode == AnimationMode::FirstFrameOnly) return;

    int elapsedFrames = msSinceLastFrame / msPerFrame;

    switch(currentMode)
    {
    case AnimationMode::LoopForwards:
    case AnimationMode::OnceForwards:
        currentFrameNum += elapsedFrames;
        break;
    case AnimationMode::LoopBackwards:
    case AnimationMode::OnceBackwards:
        currentFrameNum -= elapsedFrames;
        break;
    }

    if((currentFrameNum >= numFrames) || (currentFrameNum < 0))
    {
        switch(currentMode)
        {
        case AnimationMode::LoopForwards:
        case AnimationMode::LoopBackwards:
            currentFrameNum = currentFrameNum % numFrames;
            if(currentFrameNum < 0) currentFrameNum = numFrames + currentFrameNum;
            break;
        case AnimationMode::OnceForwards:
            currentFrameNum = numFrames - 1;
            isPlaying = false;
            break;
        case AnimationMode::OnceBackwards:
            currentFrameNum = 0;
            isPlaying = false;
            break;
        }
    }
}

void Animation::SetTextureRectForFrame()
{
    auto rect = animations[currentAnimation].Get(currentFrameNum);
    spritesheets[currentAnimation]->setTextureRect(rect->ToIntRect());

    float originX = 0.0f;
    float originY = 0.0f;

    switch(originMode)
    {
    case OriginMode::TopMiddle:
    case OriginMode::Center:
    case OriginMode::BottomMiddle:
        originX = (float) rect->width / 2.0f;
        break;
    case OriginMode::TopRight:
    case OriginMode::MiddleRight:
    case OriginMode::BottomRight:
        originX = (float) rect->width;
        break;
    }

    switch (originMode)
	{
	case OriginMode::MiddleLeft:
	case OriginMode::Center:
	case OriginMode::MiddleRight:
		originY = (float) rect->width / 2.0f;
		break;
	case OriginMode::BottomLeft:
	case OriginMode::BottomMiddle:
	case OriginMode::BottomRight:
		originY = (float) rect->width;
		break;
	};

    spritesheets[currentAnimation]->setOrigin(Vector2(originX, originY).ToVector2f());
}

bool Animation::IsDrawable()
{
	return (animations.Length() > 0 && animations.HasKey(currentAnimation));
}

#pragma region inherited

void Animation::Render()
{
    if(!enabled) return;
    if(!IsDrawable()) return;

    Alce.GetWindow().draw(*spritesheets[currentAnimation]);
}

void Animation::Update()
{
    if(!enabled) return;
    if(!IsDrawable()) return;

    msSinceLastFrame += Chrono.deltaTime.ToMiliseconds();

    if(!paused && msSinceLastFrame >= msPerFrame)
    {
        DetermineNextFrameNum();
        SetTextureRectForFrame();
        msSinceLastFrame = 0;
    }
    
    Vector2 finalPos = transform.position + padding;
    spritesheets[currentAnimation]->setPosition(finalPos.ToVector2f());

    spritesheets[currentAnimation]->setScale(size.ToVector2f());
    spritesheets[currentAnimation]->setRotation(transform.rotation);

    if(!animations.HasKey(currentAnimation)) return;

    RectShape bounds = *animations[currentAnimation].Get(currentFrameNum);
    Vector2 pixelpos = transform.position;

}

#pragma endregion