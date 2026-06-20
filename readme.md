<p align="center">
<img src="./Build/Assets/engine_logo.png" style="width:40%">
</p>

<h1 align="center">Alce Game Engine</h1>

<p align="center">
<img src="https://img.shields.io/badge/C++-20-00599C?style=flat-square&logo=c%2B%2B">
<img src="https://img.shields.io/badge/SFML-v2.6.1-8CC445?logo=SFML&style=flat-square">
<a href="LICENSE"><img src="https://img.shields.io/badge/license-MIT-informational?style=flat-square"/></a>
</p>

Alce is a 2D game engine built on top of SFML and Box2D. It provides a component-based architecture with built-in support for physics, animations, lighting, tilemaps, UI elements, and persistent storage — with the goal of keeping project setup and iteration fast.

---

## News

> [Full changelog](Documentation/News/News.md)

__**TileMap component** *(6/9/2025)*:__
Renders tile-based maps exported from PyxelEdit directly on a GameObject. Handles tilesets, layers, flips, and rotations automatically, and updates bounding corners for scene culling. [Docs](Source/Alce/Engine/Components/TileMap/TileMap.md)

__**TextRenderer component** *(24/8/2025)*:__
Renders styled text in world space with support for formatting, colors, backgrounds, and borders. [Docs](Source/Alce/Engine/Components/TextRenderer/TextRenderer.md)

__**Candle lighting integration** *(3/8/2025)*:__
Adds 2D dynamic lighting via [Candle](https://github.com/MiguelMJ/Candle) (radial and directional lights, fog areas, and custom light meshes). Integrates with the engine's component system and includes debug visualization.

---

## Documentation

> Documentation is still a work in progress.

Each component and module has its own `.md` file in the source tree. A consolidated reference is available on the [project wiki](https://github.com/Ekrol34/AlceEngine/wiki).

---

## Contributing

Contributions are welcome — bug reports, feature proposals, or code. See the [TODO list](Documentation/TODO/EN.txt) for open tasks.

---

## Components

- [Animation2d](Source/Alce/Engine/Components/Animation2d/Animation2D.md) — Spritesheet-based 2D animation with configurable playback modes, frame timing, and origin.
- [Camera](Source/Alce/Engine/Components/Camera/Camera.md) — 2D camera with zoom, viewport config, and smooth follow.
- [ParticleSystem](Source/Alce/Engine/Components/ParticleSystem/ParticleSystem.md) *(Box2D)* — Physics-based particle emitter for effects like smoke, sparks, or explosions.
- [Raycast2d](Source/Alce/Engine/Components/Raycast2d/Raycast2D.md) *(Box2D)* — Raycasting along a direction with hit/miss callbacks.
- [Rigidbody2d](Source/Alce/Engine/Components/Rigidbody2d/Rigidbody2D.md) *(Box2D)* — Full Box2D rigid body integration: shapes, forces, impulses, and transform sync.
- [SpriteRenderer](Source/Alce/Engine/Components/SpriteRenderer/SpriteRenderer.md) — Renders a 2D sprite with multi-texture support, position, scale, and rotation.
- [Light2D](Source/Alce/Engine/Components/Light2D/Light2D.md) *(Candle)* — Radial or directional light source with configurable range, intensity, and beam angle.
- [LightMesh2D](Source/Alce/Engine/Components/LightMesh2D/LightMesh2D.md) *(Candle)* — Light-blocking geometry (rectangle, circle, or polygon) with transform sync and debug mode.
- [LightingArea2D](Source/Alce/Engine/Components/LightingArea2D/LightingArea2D.md) *(Candle)* — Fog-like 2D lighting area with dynamic size, color, and opacity.
- [TileMap](Source/Alce/Engine/Components/TileMap/TileMap.md) *(PyxelEdit)* — Renders PyxelEdit JSON tilemaps with tileset slicing, flip/rotation handling, and culling support.
- [TextRenderer](Source/Alce/Engine/Components/TextRenderer/TextRenderer.md) — World-space text with styling, color, backgrounds, and borders.

## Modules

- [Core](Source/Alce/Engine/Modules/Core/) — Window, scene management, asset loading, input, and the main loop.
- [Audio](Source/Alce/Engine/Modules/Audio/Audio.md) — Channel-based audio playback with per-channel volume, pitch, and loop control.
- [Storage](Source/Alce/Engine/Modules/Storage/Storage.md) — JSON-based persistent storage with segmented files and size-limit enforcement.
- [Chrono](Source/Alce/Engine/Modules/Chrono/Chrono.md) — Time utility class with ms-level precision and arithmetic operators.
- [Debug](Source/Alce/Engine/Modules/Debug/Debug.md) — Color-coded console logging with optional async file output and rate limiting.
- [Input](Source/Alce/Engine/Modules/Input/Input.md) — Keyboard, mouse, and joystick state tracking with edge detection and enable/disable control.
- [Math](Source/Alce/Engine/Modules/Math/) — Math utilities, RNG, 2D vectors, and geometry classes (rect, polygon, circle).
- [Color](Source/Alce/Engine/Modules/Color/Color.md) — SFML color wrapper with RGB/RGBA/hex/string constructors, blending, and predefined constants.

## Utilities

- [Collections](Source/Alce/Engine/Modules/Collections/Collections.md) — Generic List, Pair, and Dictionary with filtering and manipulation methods.
- [String](Source/Alce/Engine/Modules/String/) — SFML string wrapper with parsing, trimming, splitting, regex, and conversion utilities.
- [Json](Source/Alce/Engine/Modules/Json/Json) — RapidJSON wrapper for parsing, get/set, validation, and serialization.
- [FileSystem](Source/Alce/Engine/Modules/FileSystem/FileSystem.md) — File and folder operations via `std::filesystem` with exception handling.

## UI Elements

- [Animation](Source/Alce/Engine/UI/Animation/Animation.md) — Spritesheet animation for UI elements with loop and single-play modes.
- [Button](Source/Alce/Engine/UI/Button/Button.md) — Interactive button with text, mouse event callbacks, and click handling.
- [Image](Source/Alce/Engine/UI/Image/Image.md) — UI image element with multi-texture support and origin offset.
- [Text](Source/Alce/Engine/UI/Text/Text.md) — Styled text element with font, color, size, borders, and background.
- [TextInput](Source/Alce/Engine/UI/TextInput/) — Text input field with placeholder, cursor, and submit callback.

## CLI

- [Alce CLI](Documentation/CLI/cli.md) — Command-line tool to compile, run, and generate Alce projects without a full IDE setup.
- [ARL](Documentation/ARL/ARL.md) — In-game scripting prompt for iterative debug workflows without recompilation.

---

## Setup

See the [setup tutorial](./Documentation/Tutorials/setup.md) for installation. Once set up:
```bash
cd build                 
./alce init <---- run once
./alce compile alias=dev
./alce run alias=dev
```

---

## Requirements

- GCC 32-bit v13.1.0+ (g++, mingw32-make, gdb)
- Windows 10 or 11
- Python 3.1.0+
- [PyxelEdit](https://pyxeledit.com/) *(optional, recommended for tilemaps)*

---

## Contact

Professional inquiries: gabrielbeguren@outlook.com  
Bugs and ideas: use GitHub Issues.

---

## Third-party libraries

| Library | License |
|---|---|
| [SFML](https://github.com/SFML/SFML) | [zlib](https://github.com/SFML/SFML?tab=Zlib-1-ov-file#readme) |
| [Box2D](https://github.com/erincatto/box2d) | [MIT](https://github.com/erincatto/box2d?tab=MIT-1-ov-file#readme) |
| [Candle](https://github.com/MiguelMJ/Candle) | [MIT](https://github.com/MiguelMJ/Candle?tab=MIT-1-ov-file#readme) |
| [RichText](https://github.com/skyrpex/RichText) | Public domain |
| [rapidjson](https://github.com/Tencent/rapidjson) | [MIT](https://github.com/Tencent/rapidjson?tab=License-1-ov-file#readme) |