#include "Renderer.hpp"

using namespace alce;

IntroScene::Renderer::Renderer()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void IntroScene::Renderer::Init()
{
	camera = std::make_shared<Camera>();
	AddComponent(camera);

	spriteRenderer = std::make_shared<SpriteRenderer>();
	spriteRenderer->AddTexture("logo.png", "EngineLogo");
	spriteRenderer->AddTexture("Ekrol34.png", "Ekrol34Logo");
	AddComponent(spriteRenderer);

	textRenderer = std::make_shared<TextRenderer>();
	textRenderer->borderWidth = 0;
	textRenderer->color = Colors::White;
	AddComponent(textRenderer);
}

void IntroScene::Renderer::Start()
{
	Alce.stanby = false;
	Alce.SetClearColor(Color(0, 0, 0));
	spriteRenderer->SetAlpha(0);
	spriteRenderer->SetTexture("Ekrol34Logo");

	textRenderer->SetNewText("Ekrol34");
	transform.scale = Vector2(1, 1);
	textRenderer->offset = Vector2(-9, 165);
	textRenderer->font = "fonts/Basic-Regular/Basic-Regular.ttf";
	textRenderer->fontSize = 80;

	elapsed = 0.0f;
	step = 0;
}

void IntroScene::Renderer::Update()
{
	if(step == 1) 
	{
		step = 2;
		elapsed = 0.0f;
		spriteRenderer->SetTexture("EngineLogo");
		transform.scale = Vector2(0.8f, 0.8f);
		textRenderer->SetNewText("Alce Engine");
		textRenderer->style = sf::Text::Style::Bold;
		textRenderer->offset = Vector2(0, 280);
		textRenderer->fontSize = 50;
		textRenderer->font = "fonts/Merriweather/Merriweather-Bold.ttf";
	}

	elapsed += Chrono.deltaTime.ToMiliseconds();
	float fadeDuration = 2000.0f;

	if(elapsed < 2000.0f)
	{
		float progress = elapsed / fadeDuration;
		if(progress > 1.0f) progress = 1.0f;

		uint8_t alpha = static_cast<uint8_t>(progress * 255.0f);
		spriteRenderer->SetAlpha(alpha);

		auto color = textRenderer->color;
		textRenderer->color = Color(color.GetRed(), color.GetGreen(), color.GetBlue(), alpha);
	}

	if(elapsed > 3000.0f && elapsed < 3000.0f + fadeDuration)
    {
        float progress = (elapsed - 3000.0f) / fadeDuration;
        if(progress > 1.0f) progress = 1.0f;

        uint8_t alpha = static_cast<uint8_t>((1.0f - progress) * 255.0f);
        spriteRenderer->SetAlpha(alpha);

		auto color = textRenderer->color;
		textRenderer->color = Color(color.GetRed(), color.GetGreen(), color.GetBlue(), alpha);
    }

	if(elapsed >= 5000) 
	{
		if(step == 0) step = 1;
		if(step == 2) 
		{
			Alce.SetCurrentScene("Sample");
		}
	}
}

void IntroScene::Renderer::SetterManager(String name, String value)
{
	if(name == "position")
	{
		transform.position = Vector2(value.Split(",").First().ParseFloat(), value.Split(",").Last().ParseFloat());
	}

	if(name == "text_offset")
	{
		textRenderer->offset = Vector2(value.Split(",").First().ParseFloat(), value.Split(",").Last().ParseFloat());
	}

	if(name == "font_size")
	{
		textRenderer->fontSize = value.ParseInt();
	}

	if(name == "scale")
	{
		transform.scale = Vector2(value.Split(",").First().ParseFloat(), value.Split(",").Last().ParseFloat());
	}
}

String IntroScene::Renderer::GetterManager(String name)
{

	return "undefined";
}

#pragma endregion