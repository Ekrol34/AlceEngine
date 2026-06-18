#pragma once

#include "../../Modules/Modules.hpp"

namespace alce
{
    class Text : public UIElement, public String
    {
    public:
        
        Text(): UIElement("Text")
		{
			this->str = sf::String("");
		}

        Text(const char* cstr) : UIElement("Text")
		{
			this->str = sf::String(cstr);
		}

		Text(const wchar_t* cstr) : UIElement("Text")
		{
			this->str = sf::String(cstr);
		}

		Text(std::wstring str) : UIElement("Text")
		{
			this->str = sf::String(str);
		}

		Text(std::string str) : UIElement("Text")
		{
			this->str = sf::String(str);
		}

		Text(sf::String str) : UIElement("Text")
		{
			this->str = str;
		}

		Text(size_t size) : UIElement("Text")
		{
			this->str = sf::String(std::to_string(size));
		}

		Text(bool boolean) : UIElement("Text")
		{
			boolean ? this->str = sf::String("true") : this->str = sf::String("false");
		}

		Text(int integer) : UIElement("Text")
		{
			this->str = sf::String(std::to_string(integer));
		}

		Text(long long_int) : UIElement("Text")
		{
			this->str = sf::String(std::to_string(long_int));
		}

		Text(double dec) : UIElement("Text")
		{
			this->str = sf::String(std::to_string(dec));
		}

		Text(float dec) : UIElement("Text")
		{
			this->str = sf::String(std::to_string(dec));
		}

        void Init();

        void Start();

        void Render();

        void Update();

		void SetNewText(String str);

        void AddText(String str);

        void SetBackgroundTexture(String path, bool keepAspect = true);

        void RemoveBackgroundTexture();

        void EnableFixedBox(Vector2 boxSize);

        void DisableFixedBox();

        bool IsUsingFixedBox();

        String horizontalAlign = String("left");
        bool wordWrap = true;

        Color color = Colors::White;
        sf::Text::Style style = sf::Text::Regular;
        unsigned int fontSize = 17;

        String font = "fonts/Basic-Regular/Basic-Regular.ttf";

		Color borderColor = Colors::White;
        float borderWidth = 1.0f;

		float borderRadius = 0.0f;
        Color backgroundColor = Colors::Transparent;
        
    protected:

		Vector2 size;
        sfe::RichText richText;

		bool hasBackgroundTexture = false;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bool keepAspectRatio = true;

        bool useFixedBox = false;
        Vector2 fixedBoxSize;

        Vector2 boxPos;
    };

    typedef std::shared_ptr<Text> TextPtr; 
};