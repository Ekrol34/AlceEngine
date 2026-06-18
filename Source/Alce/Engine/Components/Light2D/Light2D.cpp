#include "Light2D.hpp"

using namespace alce;

Light2D::Light2D(Type type) : Component("Light2D")
{
	lightType = type;

    if (type == Type::Radial) 
    {
        light = std::make_shared<candle::RadialLight>();
    } 
    
    if (type == Type::Directed)
    {
        light = std::make_shared<candle::DirectedLight>();
    }

    range = 100;   
    beamWidth = 100;
    beamAngle = 360;
    light->setColor(color.ToSFMLColor());
    light->setIntensity(1.0f);
}

Light2D::~Light2D()
{
    light->destroy = true;
}

bool Light2D::SetFade(bool fade)
{
    if(light != nullptr) light->setFade(fade);
    else
    {
        Debug.Warning("Light2D::SetFade -> Light not initialized");
        return false;
    }

    return true;
}

bool Light2D::IsFading()
{
    return light->getFade();
}

void Light2D::SetRange(float range) 
{
    this->range = range;
}

float Light2D::GetRange()
{
    return range;
}

void Light2D::SetBeamWidth(float width)
{
    beamWidth = width;
}

float Light2D::GetBeamWidth()
{
    return beamWidth;
}

void Light2D::SetBeamAngle(float angle)
{
    beamAngle = angle;
}

float Light2D::GetBeamAngle()
{
    return beamAngle;
}

bool Light2D::SetIntensity(float intensity)
{
    if(intensity > 1.0f || intensity < 0.0f) 
    {
        Debug.Warning("Light2D::SetIntensity -> Light intensity should be between 0.0f and 1.0f");
        return false;
    }

    this->intensity = intensity;
    
    return true;
}

float Light2D::GetIntensity()
{
    return intensity;
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void Light2D::Init()
{
    if(transform == nullptr)
    {
        Debug.Warning("Light2D::Init -> Component Light2D has no association with any GameObject");
    }
}

void Light2D::Start()
{
	if(transform == nullptr)
    {
        Debug.Warning("Light2D::Start -> Component Light2D has no association with any GameObject");
    }
}

void Light2D::Render()
{
    if(transform == nullptr) return;

    Alce.GetWindow().draw(*light.get());
}

void Light2D::Update()
{
    if(!enabled) return;

    light->setPosition(transform->position.ToPixels().ToVector2f());
    light->setRotation(transform->rotation);
    light->setRange(range);
    light->setIntensity(intensity);
    light->setColor(color.ToSFMLColor());

    if(lightType == Type::Directed) 
    {
        std::static_pointer_cast<candle::DirectedLight>(light)->setBeamWidth(beamWidth);
    }

    if(lightType == Type::Radial)
    {
        std::dynamic_pointer_cast<candle::RadialLight>(light)->setBeamAngle(beamAngle);
    }
}

#pragma endregion