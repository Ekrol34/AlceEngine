#include "ParticleSystem.hpp"
#include "../Light2D/Light2D.hpp"

using namespace alce;

#pragma region Particle

void Particle::Create(Vector2 position, bool enableCollision)
{
    this->shape = std::make_shared<RectShape>(Vector2(25, 25));
    b2BodyDef bdef;

    bdef.position.Set(position.x, position.y);
    bdef.fixedRotation = false;
    bdef.type = b2BodyType::b2_dynamicBody;

    b2FixtureDef fixDef;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fixDef.restitutionThreshold = restitutionThreshold;

    if(enableCollision)
    {
        B2Mask mask = B2Mask(0x0002, 0x0001);
        fixDef.filter.categoryBits = mask.GetCategory();
        fixDef.filter.maskBits = mask.GetMask();
    }
    else
    {
        B2Mask mask = B2Mask(0x0004, 0);
        fixDef.filter.categoryBits = mask.GetCategory();
        fixDef.filter.maskBits = mask.GetMask();
    }

    b2PolygonShape boxShape;
    boxShape.SetAsBox(shape->width / 2 / PPM, shape->height / 2 / PPM);
    fixDef.shape = &boxShape;

    body = world->__world->CreateBody(&bdef);
    body->CreateFixture(&fixDef);
    fixture = body->GetFixtureList();
    body->SetTransform(position.ToMeters().Tob2Vec2(), body->GetAngle());

    body->attachedObject = this;
    contactListener = std::make_shared<ContactListener>();

    world->__world->SetContactListener(contactListener.get());
}

Particle::Particle()
{
    forbiddenComponents = {"Rigidbody2D"};
    AddTag("particle");
}

Particle::~Particle()
{
    if(body && world)
    {
        world->__world->DestroyBody(body);
    }
}

bool Particle::SetDensity(float density)
{
    this->density = density;

    if(!body)
    {
        Debug.Warning("Particle::SetDensity -> Body not created yet");
        return false;
    }

    fixture->SetDensity(density);
    body->ResetMassData();

    return true;
}

bool Particle::SetFriction(float friction)
{
    this->friction = friction;

    if(!body) return false;

    fixture->SetFriction(friction);
    body->ResetMassData();

    return true;
}

bool Particle::SetRestitution(float restitution)
{
    this->restitution = restitution;

    if(!body)
    {
        Debug.Warning("Particle::SetRestitution -> Body not created yet");
        return false;
    }

    fixture->SetRestitution(restitution);

    return true;
}

bool Particle::SetRestitutionThreshold(float restitutionThreshold)
{
    this->restitutionThreshold = restitutionThreshold;

    if(!body)
    {
        Debug.Warning("Particle::SetRestitutionThreshold -> Body not created yet");
        return false;
    }

	fixture->SetRestitutionThreshold(restitutionThreshold);

    return true;
}

bool Particle::ApplyForce(Vector2 force, bool wake)
{
    if(!body)
    {
        Debug.Warning("Particle::ApplyForce -> Body not created yet");
        return false;
    }

    body->ApplyForceToCenter(force.Tob2Vec2(), wake);

    return true;
}

bool Particle::ApplyLinearForce(Vector2 force, bool wake)
{
    if(!body)
    {
        Debug.Warning("Particle::ApplyLinearForce -> Body not created yet");
        return false;
    }

    body->ApplyLinearImpulseToCenter(force.Tob2Vec2(), wake);

    return true;
}

bool Particle::SetLinearVelocity(Vector2 linearVelocity)
{
    if(!body)
    {
        Debug.Warning("Particle::SetLinearVelocity -> Body not created yet");
        return false;
    }

    body->SetLinearVelocity(linearVelocity.Tob2Vec2());

    return true;
}

bool Particle::SetHorizontalVelocity(float vy)
{
    if(!body)
    {
        Debug.Warning("Particle::SetHorizontalVelocity -> Body not created yet");
        return false;
    }

	float vx = body->GetLinearVelocity().x;
	body->SetLinearVelocity(b2Vec2(vx, vy));

    return true;
}

bool Particle::SetVerticalVelocity(float vx)
{
    if(!body) 
    {
        Debug.Warning("Particle::SetVerticalVelocity -> Body not created yet");
        return false;
    }

	float vy = body->GetLinearVelocity().y;
	body->SetLinearVelocity(b2Vec2(vx, vy));

    return true;
}

bool Particle::SetAngularVelocity(float va)
{
    if(!body)
    {
        Debug.Warning("Particle::SetAngularVelocity -> Body not created yet");
        return false;
    }

    body->SetAngularVelocity(va);

    return true;
}

bool Particle::SetAngularDamping(float ad)
{
    if(!body)
    {
        Debug.Warning("Particle::SetAngularDamping -> Body not created yet");
        return false;
    }

	body->SetAngularDamping(ad);

    return true;
}

bool Particle::SetLinearDamping(float ld)
{
    if(!body)
    {
        Debug.Warning("Particle::SetLinearDamping -> Body not created yet");
        return false;
    }

	body->SetLinearDamping(ld);

    return true;
}

bool Particle::ApplyAngularImpulse(float impulse)
{
    if(!body)
    {
        Debug.Warning("Particle::ApplyAngularImpulse -> Body not created yet");
        return false;
    }

    body->ApplyAngularImpulse(impulse, true);

    return true;
}

bool Particle::ApplyTorque(float torque, bool wake)
{
    if(!body)
    {
        Debug.Warning("Particle::ApplyTorque -> Body not created yet");
        return false;
    }

	body->ApplyTorque(torque, wake);

    return true;
}

bool Particle::SetAngle(float angle)
{
    if(!body)
    {
        Debug.Warning("Particle::SetAngle -> Body not created yet");
        return false;
    }

	body->SetTransform(body->GetPosition(), angle);

    return true;
}

bool Particle::SetFixedRotation(bool flag)
{
    if(!body)
    {
        Debug.Warning("Particle::SetFixedRotation -> Body not created yet");
        return false;
    }

    body->SetFixedRotation(flag);

    return true;
}

void Particle::SetLifetime(Time lifetime)
{
    this->lifetime = lifetime;
}

Time Particle::GetLifeTime()
{
    return lifetime;
}

void Particle::Update()
{
    lifetime -= Chrono.deltaTime;

    if(!body) 
    {
        Debug.Warning("Particle::Update -> Body not created yet");
        return;
    }

    shapePos = Vector2(
        body->GetPosition().x * PPM,
        Alce.GetScreenResolution().y - (body->GetPosition().y * PPM)
    );

    transform.position = body->GetPosition();
    transform.rotation = -1.0f * body->GetAngle() * DEG_PER_RAD;

    updateLambda(*this);
}

#pragma endregion

#pragma region ParticleSystem

ParticleSystem::ParticleSystem() : Component("ParticleSystem")
{

}

#pragma region implementation


void ParticleSystem::SetDelay(Time delay)
{
    this->delay = delay;
}

void ParticleSystem::SetEmitArea(ShapePtr emitArea)
{
    this->emitArea = emitArea;

    if(emitArea->GetType() == ShapeType::polygon)
    {
        auto polygon = (PolygonShape*) emitArea.get();
        offset -= polygon->GetAverageEdgeLength() / 2.0f;
    }
}

void ParticleSystem::Emit(bool flag)
{
    if(!startLambda)
    {
        Debug.Warning("ParticleSystem::Emit -> There is no particle behavior defined");
        return;
    }

    if(!flag) 
    {
        if(!emit)
        {
            Debug.Warning("ParticleSystem::Stop -> ParticleSystem is not emitting");
            return;
        }

        emit = false;
        elapsed.Reset();
    }
    else emit = true;
}

#pragma endregion

#pragma region inherited

void ParticleSystem::Update()
{
    if(!emitArea) 
    {
        Debug.Warning("ParticleSystem has no emit area");
        return;
    }

    if(emit && elapsed >= delay)
    {
        ParticlePtr particle = std::make_shared<Particle>();
        particle->world = ((Scene*)((GameObject*) owner)->scene)->GetWorld();
        Vector2 summonPosition;

        if(emitArea->GetType() == ShapeType::rect)
        {
            auto rect = (RectShape*) emitArea.get();
            summonPosition.x = Random.Range(transform->position.x - ((rect->width / 2) / PPM), transform->position.x + ((rect->width / 2) / PPM));
            summonPosition.y = Random.Range(transform->position.y - ((rect->height / 2) / PPM), transform->position.y + ((rect->height / 2) / PPM));
        }

        if(emitArea->GetType() == ShapeType::circle)
        {
            auto circle = (CircleShape*) emitArea.get();
            float angle = Random.Range(0.0f, 2 * Math.PI);
            float radius = Random.Range(0.0f, circle->radius / DEG_PER_RAD * 2.0f);
            summonPosition.x = transform->position.x + radius * Math.Cos(angle);
            summonPosition.y = transform->position.y + radius * Math.Sin(angle);
        }

        if(emitArea->GetType() == ShapeType::polygon)
        {
            auto polygon = (PolygonShape*) emitArea.get();
            List<Vector2> vertexList = polygon->GetVertexList();

            float minX = std::numeric_limits<float>::max();
            float maxX = std::numeric_limits<float>::lowest();
            float minY = std::numeric_limits<float>::max();
            float maxY = std::numeric_limits<float>::lowest();

            for(const Vector2& vertex: vertexList)
            {
                minX = std::min(minX, vertex.x);
                maxX = std::max(maxX, vertex.x);
                minY = std::min(minY, vertex.y);
                maxY = std::max(maxY, vertex.y);
            }

            int maxAttempts = 1000;
            for(int i = 0; i < maxAttempts; i++)
            {
                float randomX = Random.Range(minX, maxX);
                float randomY = Random.Range(minY, maxY);
                Vector2 randomPoint(randomX, randomY);
                
                if(polygon->InArea(randomPoint))
                {
                    summonPosition = randomPoint;
                    summonPosition += transform->position;
                    summonPosition += offset;
                    break;
                }
            }
        }

        particle->Create(summonPosition, enableCollision);
        particle->body->SetTransform(summonPosition.Tob2Vec2(), particle->body->GetAngle());
        particle->scene = ((GameObject*) owner)->scene;
        particle->Config(startLambda);
        if(updateLambda) particle->updateLambda = updateLambda;

        particles.Add(particle);
        Alce.GetCurrentScene()->pendingAdd.Add(particle);
        elapsed.Reset();
    }

    particles.RemoveIf([](ParticlePtr particle) {
        if(particle->lifetime <= 0.0f) particle->Destroy();           
        return particle->lifetime <= 0.0f;
    });

    elapsed += Chrono.deltaTime;
}

void ParticleSystem::Render()
{
    
}

void ParticleSystem::DebugRender()
{
    if(emitArea->GetType() == ShapeType::rect)
    {
        auto rect = (RectShape*) emitArea.get();
        sf::RectangleShape rectShape;
        rectShape.setSize(rect->GetBounds().ToVector2f());

        Vector2 rectShapePos = transform->position.ToPixels();
        rectShapePos.x -= (rect->width / 2);
        rectShapePos.y -= (rect->height / 2);

        rectShape.setPosition(rectShapePos.ToVector2f());
        rectShape.setFillColor(sf::Color::Transparent);
        rectShape.setOutlineColor(Color("#FFFF00").ToSFMLColor());
        rectShape.setOutlineThickness(1.0f);

        Alce.GetWindow().draw(rectShape);
    }

    if(emitArea->GetType() == ShapeType::circle)
    {
        auto circle = (CircleShape*) emitArea.get();
        sf::CircleShape circleShape;
        circleShape.setFillColor(sf::Color::Transparent);
        circleShape.setOutlineColor(Color("#FFFF00").ToSFMLColor());
        circleShape.setOutlineThickness(1.0f);

        Vector2 circleShapePos = transform->position.ToPixels();
        circleShapePos.x -= circle->radius;
        circleShapePos.y -= circle->radius;
        circleShape.setPosition(circleShapePos.ToVector2f());
        circleShape.setRadius(circle->radius);

        Alce.GetWindow().draw(circleShape);
    }

    if(emitArea->GetType() == ShapeType::polygon)
    {
        auto polygon = (PolygonShape*)emitArea.get();
        List<Vector2> vertexList = polygon->GetVertexList();

        sf::ConvexShape polygonShape;
        polygonShape.setPointCount(vertexList.Length());

        for (int i = 0; i < vertexList.Length(); ++i)
        {
            Vector2 vertex = vertexList[i];
            vertex += transform->position;
            vertex += offset;

            sf::Vector2f sfmlVertex = vertex.ToPixels().ToVector2f();
            polygonShape.setPoint(i, sfmlVertex);
        }

        polygonShape.setFillColor(sf::Color::Transparent); 
        polygonShape.setOutlineColor(Color("#FFFF00").ToSFMLColor());
        polygonShape.setOutlineThickness(1.0f);

        Alce.GetWindow().draw(polygonShape);
    }
}

#pragma endregion
