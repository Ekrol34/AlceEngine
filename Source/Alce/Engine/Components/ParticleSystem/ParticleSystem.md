# 🧩 Component: ParticleSystem

The ```ParticleSystem``` component manages the emission, update, and destruction of multiple particles.
It defines when and where particles are spawned, and applies a user-defined configuration function (behavior lambda) to each one.
Typical use cases include explosions, fire, smoke, sparks, or magical effects.

# Behaviour

When ```Emit``` is active, the system periodically spawns new particles inside the defined ```emitArea```.
Each new particle is configured using the provided behavior lambda, then added to the scene and updated every frame.

Particles automatically expire once their lifetime ends, at which point they are destroyed and removed from the system.

A debug visualization is also available, rendering the emission area as an outline in the scene.

# Constructors

```cpp
ParticleSystem()
```

Creates a new ```ParticleSystem``` with no emission. Emission begins only after Emit is called.

# Fields

* ```Time delay```: Interval between consecutive particle emissions.

* ```ShapePtr emitArea```: Area from which particles are spawned (rect, circle, or polygon).

* ```bool enableCollision```: Whether emitted particles participate in collisions.

# Methods

## SetDelay
```cpp
void SetDelay(Time delay)
```

Defines the emission interval.

## SetEmitArea
```cpp
void SetEmitArea(ShapePtr emitArea)
```

Sets the spawn area for new particles.

## Emit
```cpp
bool Emit(bool flag = true)
```

If flag is true, starts emitting particles. If its false, stops emission and resets timer.

Returns true if the process completed successfully.

## SetStart
```cpp
void SetStart(std::function<void(Particle&)> startLambda)
```

Defines a function that is executed once for each particle immediately after it is created.

This lambda is intended for one-time initialization logic, such as:

* Setting initial velocity or impulse

* Applying initial forces

* Configuring physical properties (density, restitution, damping)

* Assigning lifetime values

The function is called exactly once per particle, before it starts updating.

## SetUpdate
```cpp
void SetUpdate(std::function<void(Particle&)> updateLambda)
```

Defines a per-frame update function for each particle.

This lambda is executed every frame after the particle updates its physics state.
It allows custom behavior such as:

* Modifying velocity or forces over time

* Applying additional logic based on lifetime

* Implementing custom motion or visual effects

## EnableCollision
```cpp
void EnableCollision(bool flag = true)
```

Enables or disables collision handling for newly emitted particles.

* If enabled, particles will interact with the physics world according to their collision settings.

* If disabled, particles will be created without collision response and will pass through other objects.

This setting only affects particles created after the call.


# ✳️ Particle

The ```Particle``` entity represents a lightweight physics-driven object with a limited lifetime, typically used for visual effects such as sparks, smoke, or debris.
It exposes basic physical properties (density, friction, restitution, damping, velocity) and can optionally interact with the physics world through collisions.
Particles are managed by a ```ParticleSystem``` and are not intended to behave as full gameplay entities.

# Behaviour

On every update, the particle reduces its lifetime and updates its transform based on the underlying physics body.
Once its lifetime reaches zero, the particle is destroyed and removed from the system.

Particles can receive forces, impulses, velocities, damping, and torque to control their short-lived behavior.

# Constructors

```cpp
Particle()
```

Creates a new ```Particle``` instance with default parameters. The physics body is created when ```Create``` is called.

# Fields

* ```Time lifetime```: Duration until the particle is automatically destroyed.

* ```Transform transform```: Current world position and rotation of the particle.

* ```ShapePtr shape```: Collision shape of the particle (default: 25×25 rectangle).

# Methods

## Create
```cpp
bool Create(Vector2 position, bool enableCollision)
```

Initializes the particle with a physics body at the given position.

Returns true if the process completed successfully.

## SetDensity
```cpp
bool SetDensity(float density)
```

Updates the body’s mass density.

Returns true if the process completed successfully.

## SetFriction
```cpp
bool SetFriction(float friction)
```

Sets surface friction.

Returns true if the process completed successfully.

## SetRestitution
```cpp
bool SetRestitution(float restitution)
```

Sets elasticity for bounces.

Returns true if the process completed successfully.

## SetRestitutionThreshold
```cpp
bool SetRestitutionThreshold(float threshold)
```

Controls minimum collision impulse for restitution.

Returns true if the process completed successfully.

## ApplyForce
```cpp
bool ApplyForce(Vector2 force, bool wake)
```

Applies continuous force at the center.

Returns true if the process completed successfully.

## ApplyLinearForce
```cpp
bool ApplyLinearForce(Vector2 force, bool wake)
```

Applies an instantaneous impulse.

Returns true if the process completed successfully.

## SetLinearVelocity
```cpp
bool SetLinearVelocity(Vector2 velocity)
```

Directly sets velocity.

Returns true if the process completed successfully.

## SetHorizontalVelocity
```cpp
bool SetHorizontalVelocity(float vy) 
```

Adjusts only vertical velocity.

Returns true if the process completed successfully.

## SetVerticalVelocity
```cpp
bool SetVerticalVelocity(float vx)
```

Adjusts only horizontal velocity.

Returns true if the process completed successfully.

## SetAngularVelocity
```cpp
bool SetAngularVelocity(float va)
```

Sets rotation speed.

Returns true if the process completed successfully.

## SetAngularDamping
```cpp
bool SetAngularDamping(float ad)
```

Slows down angular motion.

Returns true if the process completed successfully.

## SetLinearDamping
```cpp
bool SetLinearDamping(float ld)
```

Slows down linear motion.

Returns true if the process completed successfully.

## ApplyAngularImpulse
```cpp
bool ApplyAngularImpulse(float impulse)
```

Applies a rotation impulse.

Returns true if the process completed successfully.

## ApplyTorque
```cpp
bool ApplyTorque(float torque, bool wake)
```

Applies continuous torque.

Returns true if the process completed successfully.

## SetAngle
```cpp
bool SetAngle(float angle)
```

Rotates the body to the given angle.

Returns true if the process completed successfully.

## SetFixedRotation
```cpp
bool SetFixedRotation(bool flag)
```

Locks/unlocks rotation.

Returns true if the process completed successfully.

## SetLifetime
```cpp
void SetLifetime(Time lifetime)
```

Defines how long the particle will live.

## GetLifetime
```cpp
Time GetLifetime()
```

Returs the particle's remaining lifetime.



