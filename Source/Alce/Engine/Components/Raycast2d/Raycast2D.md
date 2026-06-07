# 🧩 Component: Raycast2D

> <img src="https://box2d.org/images/logo.svg" style="width: 23px; position: relative; top: 1px"> [Built using the Box2d library.](https://github.com/erincatto/box2d)

The ```Raycast2D``` component allows a GameObject to perform 2D raycasting queries against the physics world.
A ray is cast in a specified direction and length, detecting collisions with other physics bodies along its path.

When a collision occurs, the component automatically notifies both the owner object and the impacted object through the OnImpact and OnImpactEnd callbacks.
This makes it useful for mechanics such as line-of-sight detection, laser beams, sensors, or trigger-based interactions.

It also provides a simple debug visualization, drawing the ray as a red line in the scene.

## Fields

* ```float length```: The length of the ray (default: 5.0f).

* ```Vector2 direction```: The normalized direction vector of the ray (default: (0, -1), pointing upwards).


# Constructors

```cpp
Raycast2D()
```

Creates a new Raycast2D instance with default values.

# Behaviour

On every update, the component casts a ray starting at the ```GameObject```'s position and extending in the specified direction for the configured length.

If the ray intersects a fixture, the component triggers ```OnImpact``` on both the owner and the impacted object.

If the ray moves from one object to another, the previous object receives an ```OnImpactEnd``` notification before the new impact is registered.

If the ray no longer intersects any object, ```OnImpactEnd``` is called on the last impacted object, signaling that the interaction has ended.
If no object is hit, ```OnImpactEnd``` is called when leaving the last impacted object.