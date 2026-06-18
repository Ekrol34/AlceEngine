#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    enum BodyType
    {
        static_body,
        dynamic_body,
        kinematic_body,
        none_body
    };

    class Rigidbody2D : public Component
    {
    public:

        Rigidbody2D();

        ~Rigidbody2D();

        bool CreateBody(ShapePtr shape, BodyType bodyType = BodyType::dynamic_body, bool fixedRotation = false, MaskType maskType = MaskType::mask_1);

        bool DestroyBody();

        float GetDensity();

        bool SetDensity(float density);

        float GetFriction();

        bool SetFriction(float friction);

        float GetRestitution();

        bool SetRestitution(float restitution);

        float GetRestitutionThreshold();

        bool SetRestitutionThreshold(float restitutionThreshold);

        bool ApplyForce(Vector2 force, bool wake = true);

        bool ApplyLinearForce(Vector2 force, bool wake = true);

        bool SetLinearVelocity(Vector2 linearVelocity);

        Vector2 GetLinearVelocity();

        bool SetVerticalVelocity(float vy);

        bool SetHorizontalVelocity(float vx);

        bool SetAngularVelocity(float va);

        bool SetAngularDamping(float ad);

        bool SetLinearDamping(float ld);

        bool ApplyAngularImpulse(float impulse);

        bool ApplyTorque(float torque, bool wake = true);

        float GetAngle();

        bool SetAngle(float angle);

        float GetInertia();

        float GetGravityScale();

        BodyType GetBodyType();

        bool SetBodyType(BodyType bodyType);

        ShapeType GetShapeType();

        bool SetPosition(Vector2 position, bool awake = true);

        bool SetPosition(float x, float y, bool awake = true);

        bool SetRotation(float rotation, bool awake = true);

        Vector2 GetPosition();

        bool SetFixedRotation(bool flag = true);

        void DebugRender();

        void Init();

        void Start();

        void Update();

        void SetTag(String tag);

        String GetTag();

        bool HasBody()
        {
            return body != nullptr;
        }

    private:

        friend class GameObject;

        float density = 10.0f;
        float friction = 1.0f;
        float restitution = 0.0f;
        float restitutionThreshold = 0.0f;

        BodyType bodyType;
        float radius = 0;

        b2Body* body = nullptr;
        b2Fixture* fixture;
        ContactListenerPtr contactListener;
        B2WorldPtr world = nullptr;

        ShapePtr shape = nullptr;
        Vector2 shapePos;
    };

    typedef std::shared_ptr<Rigidbody2D> Rigidbody2DPtr;
}