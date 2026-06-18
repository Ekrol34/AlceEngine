#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class Particle : public GameObject
    {
    public:

        Particle();

        ~Particle();

        bool SetDensity(float density);

        bool SetFriction(float friction);

        bool SetRestitution(float restitution);

        bool SetRestitutionThreshold(float restitutionThreshold);

        bool ApplyForce(Vector2 force, bool wake = true);

        bool ApplyLinearForce(Vector2 force, bool wake = true);

        bool SetLinearVelocity(Vector2 linearVelocity);

        bool SetHorizontalVelocity(float vy);

        bool SetVerticalVelocity(float vx);

        bool SetAngularVelocity(float va);

        bool SetAngularDamping(float ad);

        bool SetLinearDamping(float ld);

        bool ApplyAngularImpulse(float impulse);

        bool ApplyTorque(float torque, bool wake = true);

        bool SetAngle(float angle);

        bool SetFixedRotation(bool flag = true);

        void SetLifetime(Time lifetime);

        Time GetLifeTime();

        void Update();

    private:

        friend class ParticleSystem;

        void Create(Vector2 position, bool enableCollision);

        void Config(std::function<void(Particle&)> configLambda)
        {
            if(configLambda) configLambda(*this);
        }

        std::function<void(Particle&)> updateLambda;

        Time lifetime = Time({
            {"seconds", 1.0f}
        });

        float density = 10.0f;
        float friction = 1.0f;
        float restitution = 0.0f;
        float restitutionThreshold = 0.0f;
        float radius = 0;

        b2Body* body = nullptr;
        b2Fixture* fixture;
        B2WorldPtr world = nullptr;
        ContactListenerPtr contactListener;

        RectShapePtr shape;
        Vector2 shapePos;
    };

    typedef std::shared_ptr<Particle> ParticlePtr;

    class ParticleSystem : public Component
    {
    public:

        ParticleSystem();
        
        void Update();

        void Render();

        void DebugRender();

        void SetDelay(Time delay);

        void SetEmitArea(ShapePtr emitArea);

        bool Emit(bool flag = true);

        void SetStart(std::function<void(Particle&)> startLambda)
        {
            this->startLambda = startLambda;
        }

        void SetUpdate(std::function<void(Particle&)> updateLambda)
        {
            this->updateLambda = updateLambda;
        }

        void EnableCollision(bool flag = true)
        {
            enableCollision = flag;
        }

        Vector2 offset = Vector2(0.0f, 0.0f);

    private:

        Dictionary<float, TexturePtr> textures;
        List<ParticlePtr> particles;

        bool enableCollision = false;

        std::function<void(Particle&)> startLambda = [](Particle& particle) {
            particle.ApplyForce(Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)) * 0.1f);
            particle.SetLifetime(Time({
                {"seconds", 2.0f}
            }));
            particle.sortingLayer = 1;
            particle.SetDensity(1.0f);
            particle.SetFixedRotation();
        };

        std::function<void(Particle&)> updateLambda = [](Particle& particle) { };

        ShapePtr emitArea = std::make_shared<alce::RectShape>(30.0f, 30.0f);

        Time delay;
        Time elapsed;

        bool emit = false;
    };

    typedef std::shared_ptr<ParticleSystem> ParticleSystemPtr;
}