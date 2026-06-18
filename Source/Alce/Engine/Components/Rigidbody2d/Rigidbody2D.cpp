#include "Rigidbody2d.hpp"

using namespace alce;

Rigidbody2D::Rigidbody2D() : Component("Rigidbody2D")
{

}

Rigidbody2D::~Rigidbody2D()
{
    DestroyBody();   
}

#pragma region implementation

bool Rigidbody2D::CreateBody(ShapePtr shape, BodyType bodyType, bool fixedRotation, MaskType maskType)
{
    if(shape == nullptr)
    {
        Debug.Warning("Rigidbody2D::CreateBody -> Null shape for Component Rigidbody2D");
        return false;
    }

    if(world == nullptr)
    {
        Debug.Warning("Rigidbody2D::CreateBody -> Null B2World for Component Rigidbody2D");
        return false;
    }

    if(body != nullptr)
    {
        Debug.Warning("Rigidbody2D::CreateBody -> Rigidbody2D already has a body");
        return false;
    }

    this->shape = shape;
    this->bodyType = bodyType;

    b2BodyDef bdef;
    bdef.fixedRotation = fixedRotation;

    switch(bodyType)
    {
    case BodyType::dynamic_body:
        bdef.type = b2_dynamicBody;
        break;
    case BodyType::static_body:
        bdef.type = b2_staticBody;
        break;
    case BodyType::kinematic_body:
        bdef.type = b2_kinematicBody;
        break;
    default:
        Debug.Warning("Rigidbody2D::CreateBody -> Invalid shape type");
        return false;
    }

    b2FixtureDef fixDef;
    fixDef.density = density;
    fixDef.friction = friction;
    fixDef.restitution = restitution;
    fixDef.restitutionThreshold = restitutionThreshold;

    B2Mask mask;

    if(maskType == MaskType::mask_0) mask = B2Mask(0x0004, 0);
    else if(maskType == MaskType::mask_1) mask = B2Mask(0x0001, 0x0001 | 0x0002);
    else if(maskType == MaskType::mask_2) mask = B2Mask(0x0002, 0x0001);

    fixDef.filter.categoryBits = mask.GetCategory();
    fixDef.filter.maskBits = mask.GetMask();

    body = world->__world->CreateBody(&bdef); // Create the body at the specified position

    if(shape->GetType() == ShapeType::rect)
    {
        RectShape* bs = (RectShape*) shape.get();
        b2PolygonShape boxShape;
        boxShape.SetAsBox(bs->width / 2 / PPM, bs->height / 2 / PPM); 
        fixDef.shape = &boxShape;
        
        body->CreateFixture(&fixDef);
        fixture = body->GetFixtureList();

        body->attachedObject = owner;
        body->SetTransform(transform->position.Tob2Vec2(), body->GetAngle());
        contactListener = std::make_shared<ContactListener>();
    }
    else if(shape->GetType() == ShapeType::circle)
    {
        CircleShape* cs = (CircleShape*) shape.get();  
        b2CircleShape circleShape;
        circleShape.m_radius = cs->radius;
        circleShape.m_p.Set(0, 0); 
        fixDef.shape = &circleShape;
        radius = cs->radius * PPM;

        body->CreateFixture(&fixDef);
        fixture = body->GetFixtureList();

        body->attachedObject = owner;
        body->SetTransform(transform->position.Tob2Vec2(), body->GetAngle());
        contactListener = std::make_shared<ContactListener>();
    }
    else if(shape->GetType() == ShapeType::polygon)
    {
        PolygonShape* ps = (PolygonShape*) shape.get();
        b2PolygonShape shape;
        shape.Set(ps->GetB2VertexArray(), ps->GetVertexCount());
        fixDef.shape = &shape;

        body->CreateFixture(&fixDef);
        fixture = body->GetFixtureList();

        body->attachedObject = owner;
        body->SetTransform(transform->position.Tob2Vec2(), body->GetAngle());
        contactListener = std::make_shared<ContactListener>();
    }
    else
    {
        Debug.Warning("Rigidbody2D::CreateBody -> Undefined shape");
        return false;
    }

    world->__world->SetContactListener(contactListener.get());

    return true;
}


bool Rigidbody2D::DestroyBody()
{
    if(body != nullptr && world != nullptr) 
    {
        world->__world->DestroyBody(body);
        return true;
    }

    return false;
}

float Rigidbody2D::GetDensity()
{
    return density;
}

bool Rigidbody2D::SetDensity(float density)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetDensity -> Component Rigidbody2D is not enabled");
        return false;
    }

    this->density = density;

    if(body == nullptr) return false;

    fixture->SetDensity(density);
    body->ResetMassData();

    return true;
}

float Rigidbody2D::GetFriction()
{
    return friction;
}

bool Rigidbody2D::SetFriction(float friction)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetFriction -> Component Rigidbody2D is not enabled");
        return false;
    }

    this->friction = friction;

    if(body == nullptr) return false;

    fixture->SetFriction(friction);
    body->ResetMassData();

    return true;
}

float Rigidbody2D::GetRestitution()
{
    return restitution;
}

bool Rigidbody2D::SetRestitution(float restitution)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetRestitution -> Component Rigidbody2D is not enabled");
        return false;
    }

    this->restitution = restitution;

    if(body == nullptr) return false;

    fixture->SetRestitution(restitution);

    return true;
}

float Rigidbody2D::GetRestitutionThreshold()
{
    return restitutionThreshold;
}

bool Rigidbody2D::SetRestitutionThreshold(float restitutionThreshold)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetRestitutionThreshold -> Component Rigidbody2D is not enabled");
        return false;
    }

    this->restitutionThreshold = restitutionThreshold;

    if (body == nullptr) return false;

	fixture->SetRestitutionThreshold(restitutionThreshold);

    return true;
}

bool Rigidbody2D::ApplyForce(Vector2 force, bool wake)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::ApplyForce -> Component Rigidbody2D is not enabled");
        return false;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::ApplyForce -> Component Rigidbody2D has no body created");
        return false;
    }

    body->ApplyForceToCenter(force.Tob2Vec2(), wake);

    return true;
}

bool Rigidbody2D::ApplyLinearForce(Vector2 force, bool wake)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::ApplyLinearForce -> Component Rigidbody2D is not enabled");
        return false;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::ApplyLinearForce -> Component Rigidbody2D has no body created");
        return false;
    }

    body->ApplyLinearImpulseToCenter(force.Tob2Vec2(), wake);

    return true;
}

Vector2 Rigidbody2D::GetLinearVelocity()
{
    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetLinearVelocity -> Component Rigidbody2D has no body created");
        return Vector2(0.0f, 0.0f);
    }

    return Vector2(body->GetLinearVelocity());
}

bool Rigidbody2D::SetLinearVelocity(Vector2 linearVelocity)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetLinearVelocity -> Component Rigidbody2D is not enabled");
        return false;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetLinearVelocity -> Component Rigidbody2D has no body created");
        return false;
    }

    body->SetLinearVelocity(linearVelocity.Tob2Vec2());

    return true;
}

bool Rigidbody2D::SetVerticalVelocity(float vy)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetVerticalVelocity -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetVerticalVelocity -> Component Rigidbody2D has no body created");
        return false;
    }

	float vx = body->GetLinearVelocity().x;
	body->SetLinearVelocity(b2Vec2(vx, vy));

    return true;
}

bool Rigidbody2D::SetHorizontalVelocity(float vx)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetHorizontalVelocity -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetHorizontalVelocity -> Component Rigidbody2D has no body created");
        return false;
    }

	float vy = body->GetLinearVelocity().y;
	body->SetLinearVelocity(b2Vec2(vx, vy));

    return true;
}

bool Rigidbody2D::SetAngularVelocity(float va)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetAngularVelocity -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetAngularVelocity -> Component Rigidbody2D has no body created");
        return false;
    }

    body->SetAngularVelocity(va);

    return true;
}

bool Rigidbody2D::SetAngularDamping(float ad)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetAngularDamping -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetAngularDamping -> Component Rigidbody2D has no body created");
        return false;
    }

	body->SetAngularDamping(ad);
    
    return true;
}

bool Rigidbody2D::SetLinearDamping(float ld)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetLinearDamping -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetLinearDamping -> Component Rigidbody2D has no body created");
        return false;
    }

	body->SetLinearDamping(ld);
    return true;
}

bool Rigidbody2D::ApplyAngularImpulse(float impulse)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::ApplyAngularImpulse -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::ApplyAngularImpulse -> Component Rigidbody2D has no body created");
        return false;
    }

	body->ApplyAngularImpulse(impulse, true);
    return true;
}

bool Rigidbody2D::ApplyTorque(float torque, bool wake)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::ApplyTorque -> Component Rigidbody2D is not enabled");
        return false;
    }

	if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::ApplyTorque -> Component Rigidbody2D has no body created");
        return false;
    }

	body->ApplyTorque(torque, wake);
    return true;
}

float Rigidbody2D::GetAngle()
{
    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetAngle -> Component Rigidbody2D has no body created");
        return 0.0f;
    }

    return body->GetAngle();
}

bool Rigidbody2D::SetAngle(float angle)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetAngle -> Component Rigidbody2D is not enabled");
        return false;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetAngle -> Component Rigidbody2D has no body created");
        return false;
    }

	body->SetTransform(body->GetPosition(), angle);
    return true;
}

float Rigidbody2D::GetInertia()
{
    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetInertia -> Component Rigidbody2D has no body created");
        return 0.0f;
    }

    return body->GetInertia();
}

float Rigidbody2D::GetGravityScale()
{
    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetGravityScale -> Component Rigidbody2D has no body created");
        return 0.0f;
    }

    return body->GetGravityScale();
}

BodyType Rigidbody2D::GetBodyType()
{
    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetBodyType -> Component Rigidbody2D has no body created");
        return BodyType::none_body;
    }

	return bodyType;
}

bool Rigidbody2D::SetBodyType(BodyType bodyType)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetBodyType -> Component Rigidbody2D is not enabled");
        return false;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetBodyType -> Component Rigidbody2D has no body created");
        return false;
    }

    this->bodyType = bodyType;

    switch(bodyType)
	{
	case BodyType::dynamic_body:
		body->SetType(b2_dynamicBody);
		break;
	case BodyType::static_body:
		body->SetType(b2_staticBody);
		break;
	case BodyType::kinematic_body:
		body->SetType(b2_kinematicBody);
		break;
	}

    return true;
}

ShapeType Rigidbody2D::GetShapeType()
{
    if(shape == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetShapeType -> Component Rigidbody2D has no shape defined");
        return ShapeType::none;
    }

	return shape->GetType();
}

Vector2 Rigidbody2D::GetPosition()
{
    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::GetPosition -> Component Rigidbody2D has no body created");
        return Vector2(0.0f, 0.0f);
    }

    return Vector2(body->GetPosition());
}

bool Rigidbody2D::SetPosition(Vector2 position, bool awake)
{
    if(body) 
    {
        body->SetTransform(position.Tob2Vec2(), body->GetAngle());
        transform->position = position;
        body->SetAwake(awake);
    }
    else
    {
        Debug.Warning("Rigidbody2D::SetPosition -> Component Rigidbody2D has no body created");
        return false;
    }

    return true;
}

bool Rigidbody2D::SetPosition(float x, float y, bool awake)
{
    if(body) 
    {
        body->SetTransform(b2Vec2(x, y), body->GetAngle());
        transform->position = Vector2(x, y);
        body->SetAwake(awake);
    }
    else
    {
        Debug.Warning("Rigidbody2D::SetPosition -> Component Rigidbody2D has no body created");
        return false;
    }

    return true;
}

bool Rigidbody2D::SetRotation(float angle, bool awake)
{
    if(body) 
    {
        body->SetTransform(body->GetPosition(), angle);
        transform->rotation = -1.0f * body->GetAngle() * DEG_PER_RAD;
        body->SetAwake(awake);
    }
    else
    {
        Debug.Warning("Rigidbody2D::SetRotation -> Component Rigidbody2D has no body created");
        return false;
    }

    return true;
}

bool Rigidbody2D::SetFixedRotation(bool flag)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetFixedRotation -> Component Rigidbody2D is not enabled");
        return false;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetFixedRotation -> Component Rigidbody2D has no body created");
        return false;
    }

    body->SetFixedRotation(flag);
    return true;
}

void Rigidbody2D::SetTag(String tag)
{
    if(!enabled)
    {
        Debug.Warning("Rigidbody2D::SetTag -> Component Rigidbody2D is not enabled");
        return;
    }

    if(body == nullptr)
    {
        Debug.Warning("Rigidbody2D::SetTag -> Component Rigidbody2D has no body created");
        return;
    }

    body->bodyTag = tag.ToAnsiString();
}

String Rigidbody2D::GetTag()
{
    return String(body->bodyTag);
}

#pragma endregion

#pragma region inherited

void Rigidbody2D::DebugRender()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component Rigidbody2D has no association with any GameObject");
        return;
    }

    if(body == nullptr)
    {
        Debug.Warning("Component Rigidbody2D has no body created");
        return;
    }

    if(shape == nullptr)
    {
        Debug.Warning("Component Rigidbody2D has no shape defined");
        return;
    }
 
    if(shape->GetType() == ShapeType::rect)
    {
        RectShape* bs = (RectShape*) shape.get();
        sf::RectangleShape rs;

        rs.setPosition(shapePos.ToVector2f());
        Vector2 origin(bs->width / 2, bs->height / 2);

        rs.setOrigin(origin.ToVector2f());
        rs.setSize(Vector2(bs->width - 2.0f, bs->height - 2.0f).ToVector2f());   
        rs.setFillColor(sf::Color::Transparent);
        rs.setOutlineColor(Color("#42FF33").ToSFMLColor());
        rs.setOutlineThickness(1.0f);
        rs.setRotation(-1 * body->GetAngle() * DEG_PER_RAD);

        Alce.GetWindow().draw(rs);
        return;
    }

    if(shape->GetType() == ShapeType::circle)
    {
        CircleShape* cs = (CircleShape*) shape.get();
        sf::CircleShape circle;

        Vector2 origin(cs->radius * PPM, cs->radius * PPM);

        circle.setOrigin(origin.ToVector2f());
        circle.setPosition(shapePos.ToVector2f());
        circle.setRadius(cs->radius * PPM);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Green);
        circle.setOutlineThickness(1.0f);

        Alce.GetWindow().draw(circle);
        return;
    }

    if(shape->GetType() == ShapeType::polygon)
    {
        PolygonShape* ps = (PolygonShape*) shape.get();
        sf::ConvexShape cs;

        cs.setPointCount(ps->GetVertexCount());

        for(int i = 0; i < ps->GetVertexCount(); i++)
        {
            Vector2 vertex(ps->GetVertexList()[i]);

            vertex *= PPM;
            vertex.y = -vertex.y;

            cs.setPoint(i, vertex.ToVector2f());
        }

        cs.setPosition(shapePos.ToVector2f());
        cs.setOrigin(Vector2(0.0f, 0.0f).ToVector2f());
        cs.setFillColor(sf::Color::Transparent);
        cs.setOutlineColor(sf::Color::Green);
        cs.setOutlineThickness(1.0f);

        Alce.GetWindow().draw(cs);
        return;
    }
}

void Rigidbody2D::Init()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component Rigidbody2D has no association with any GameObject");
        return;
    }
}

void Rigidbody2D::Start()
{
    if(transform == nullptr)
    {
        Debug.Warning("Component Rigidbody2D has no association with any GameObject");
        return;
    }
}

void Rigidbody2D::Update()
{
    if(this->owner == nullptr) return;
    if(body == nullptr) return;

    transform->position = Vector2(body->GetPosition());
    transform->rotation = -1.0f * body->GetAngle() * DEG_PER_RAD;

    shapePos = Vector2(
        body->GetPosition().x * PPM, 
        Alce.GetScreenResolution().y - (body->GetPosition().y * PPM));
}

#pragma endregion
