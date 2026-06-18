#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
	class TextRenderer : public Component, public String
	{
	public:

		TextRenderer(): Component("TextRenderer")
		{
			this->str = sf::String("");

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

        TextRenderer(const char* cstr) : Component("TextRenderer")
		{
			this->str = sf::String(cstr);

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(const wchar_t* cstr) : Component("TextRenderer")
		{
			this->str = sf::String(cstr);

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(std::wstring str) : Component("TextRenderer")
		{
			this->str = sf::String(str);

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(std::string str) : Component("TextRenderer")
		{
			this->str = sf::String(str);

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(sf::String str) : Component("TextRenderer")
		{
			this->str = str;

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(size_t size) : Component("TextRenderer")
		{
			this->str = sf::String(std::to_string(size));

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(bool boolean) : Component("TextRenderer")
		{
			boolean ? this->str = sf::String("true") : this->str = sf::String("false");

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(int integer) : Component("TextRenderer")
		{
			this->str = sf::String(std::to_string(integer));

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(long long_int) : Component("TextRenderer")
		{
			this->str = sf::String(std::to_string(long_int));

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(double dec) : Component("TextRenderer")
		{
			this->str = sf::String(std::to_string(dec));

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		TextRenderer(float dec) : Component("TextRenderer")
		{
			this->str = sf::String(std::to_string(dec));

			cardinals.Set("top-left", std::make_shared<Vector2>());
    		cardinals.Set("top-right", std::make_shared<Vector2>());
    		cardinals.Set("bottom-left", std::make_shared<Vector2>());
    		cardinals.Set("bottom-right", std::make_shared<Vector2>());
		}

		void Init();

		void Start();

		void Render();

		void Update();

		void SetNewText(String str);	

		void AddText(String str);	

		void SetBackgroundTexture(String path, bool keepAspect = false);

		void RemoveBackgroundTexture();

		Dictionary<String, Vector2Ptr> GetCardinals();

		void EnableFixedBox(Vector2 boxSize);

    	void DisableFixedBox();

    	bool IsUsingFixedBox() 
		{ 
			return useFixedBox; 
		}

        Color color = Colors::White;
        sf::Text::Style style = sf::Text::Regular;
        unsigned int fontSize = 17;

		String horizontalAlign = "left";
		bool wordWrap = true;

        String font = "fonts/Basic-Regular/Basic-Regular.ttf";

		Color borderColor = Colors::White;
        float borderWidth = 0.0f;

		float borderRadius = 0.0f;
        Color backgroundColor = Colors::Transparent;

		Vector2 padding = Vector2(0, 0);
		Vector2 offset = Vector2(0, 0);

	protected:

		Vector2 size;
		Vector2 boxPos;
		sfe::RichText richText;

		Dictionary<String, Vector2Ptr> cardinals;

		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		bool hasBackgroundTexture = false;
		bool keepAspectRatio = true;

		bool useFixedBox = false;
		Vector2 fixedBoxSize;

	private:

	};

	typedef std::shared_ptr<TextRenderer> TextRendererPtr;
}

