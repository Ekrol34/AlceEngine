#include "Animation2D.hpp"

using namespace alce;

Animation2D::Animation2D() : Component("Animation2d")
{
    cardinals.Set("top-left", std::make_shared<Vector2>());
    cardinals.Set("top-right", std::make_shared<Vector2>());
    cardinals.Set("bottom-left", std::make_shared<Vector2>());
    cardinals.Set("bottom-right", std::make_shared<Vector2>());
}

void Animation2D::AddAnimation(String spritesheetFile, String name, int rows, int cols, int frameWidth, int frameHeight, int numFrames)
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

bool Animation2D::DeleteAnimation(String name)
{
    if(!animations.HasKey(name))
    {
        Debug.Warning("Animation2D::PlayAnimation -> Animation not found: \"{}\"", {name});
        return false;
    }

    animations.RemoveByKey(name);

    return true;
}

void Animation2D::SetOriginMode(OriginMode originMode)
{
    this->originMode = originMode;
}

bool Animation2D::PlayAnimation(String name, AnimationMode mode)
{
    if(!enabled)
    {
        Debug.Warning("Animation2D::PlayAnimation -> Component is disabled");
        return false;
    }

    if(!animations.HasKey(name))
    {
        Debug.Warning("Animation2D::PlayAnimation -> There is not animation named \"{}\" in the stack", {name});
        return false;
    }

    currentAnimation = name;
    currentMode = mode;
    isPlaying = true;

    msSinceLastFrame = 0;

    DetermineNumFrames();
    DetermineFirstFrameNum();
    SetTextureRectForFrame();

    return true;
}

void Animation2D::SetAnimationMode(AnimationMode mode)
{
    currentMode = mode;
}

String Animation2D::GetCurrentAnimation()
{
    return this->currentAnimation;
}

#pragma region AnimationEngine

void Animation2D::DetermineNumFrames()
{
    numFrames = animations[currentAnimation].Length();
}

void Animation2D::DetermineFirstFrameNum()
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

void Animation2D::DetermineNextFrameNum()
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

void Animation2D::SetTextureRectForFrame()
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

bool Animation2D::IsDrawable()
{
	return (animations.Length() > 0 && animations.HasKey(currentAnimation));
}

void Animation2D::SetTimePerFrame(Time time)
{
    msPerFrame = time.ToMiliseconds();
}

void Animation2D::SetTimePerFrame(float ms)
{
    msPerFrame = ms;
}

void Animation2D::Pause(bool flag)
{
    paused = flag;
}

bool Animation2D::IsPlaying()
{
    return isPlaying;
}

Dictionary<String, Vector2Ptr> Animation2D::GetCardinals()
{
    return cardinals;
}


#pragma region inherited

void Animation2D::Render()
{
    if(!enabled) return;
    if(!IsDrawable()) return;

    Alce.GetWindow().draw(*spritesheets[currentAnimation]);
}

void Animation2D::Update()
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

    spritesheets[currentAnimation]->setPosition((transform->position.ToPixels() + offset).ToVector2f());
    spritesheets[currentAnimation]->setScale((transform->scale + scale).ToVector2f());
    spritesheets[currentAnimation]->setRotation(transform->rotation);

    if(!animations.HasKey(currentAnimation)) return;

    RectShape bounds = *animations[currentAnimation].Get(currentFrameNum);
    Vector2 pixelpos = transform->position.ToPixels();

    cardinals["top-left"]->x = pixelpos.x - (bounds.width / 2.0f);
    cardinals["top-left"]->y = pixelpos.y - (bounds.height / 2.0f);

    cardinals["top-right"]->x = pixelpos.x + (bounds.width / 2.0f);
    cardinals["top-right"]->y = pixelpos.y - (bounds.height / 2.0f);

    cardinals["bottom-left"]->x = pixelpos.x - (bounds.width / 2.0f);
    cardinals["bottom-left"]->y = pixelpos.y + (bounds.height / 2.0f);

    cardinals["bottom-right"]->x = pixelpos.x + (bounds.width / 2.0f);
    cardinals["bottom-right"]->y = pixelpos.y + (bounds.height / 2.0f);
}

#pragma endregion