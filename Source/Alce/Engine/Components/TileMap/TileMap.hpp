#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
	class TileMap : public Component
	{
	public:

		TileMap();

		void Init();

		void Start();

		void Render();

		void Update();

		bool Load(String tilemap, String tileset, int tilesPerRow = 8);

		Dictionary<String, Vector2Ptr> GetCardinals();

		Vector2 scale = Vector2(0, 0);
		Vector2 offset = Vector2(0, 0);

	private:

		struct Layer 
		{
			String name;
			sf::VertexArray vertices;
		};

        sf::Texture tileset;
        Vector2 tileSize;
        int tilesWide = 0;
        int tilesHigh = 0;
        int tilesPerRow = 0;

        std::vector<Layer> layers;
		Dictionary<String, Vector2Ptr> cardinals;

        void BuildLayer(Json& layerJson);

	};

	typedef std::shared_ptr<TileMap> TileMapPtr;
}