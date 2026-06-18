#include "Player.hpp"

using namespace alce;

SharedScene::Player::Player()
{
	
}

//Custom methods implementation
#pragma region implementation


#pragma endregion

//Inherited methods
#pragma region inherited

void SharedScene::Player::Init()
{
    AddTag("Player");
    sortingLayer = 1;

    camera = std::make_shared<Camera>();
    AddComponent(camera);

    rigidbody2d = std::make_shared<Rigidbody2D>();
    AddComponent(rigidbody2d);

    animation = std::make_shared<Animation2D>();
    animation->sortingLayer = 2;
    AddComponent(animation);

    leftRaycast2d = std::make_shared<Raycast2D>();
    AddComponent(leftRaycast2d);

    rightRaycast2d = std::make_shared<Raycast2D>();
    AddComponent(rightRaycast2d);

    canvas = std::make_shared<Canvas>();
    AddComponent(canvas);

    Audio.AddChannel("player");
    Audio.GetChannel("player")->Add("gas", "GAS.wav");

	// backgroundRenderer = std::make_shared<SpriteRenderer>();
	// backgroundRenderer->AddTexture("dudegame/player/background.png", "background");
	// backgroundRenderer->SetTexture("background");
	// backgroundRenderer->scale = Vector2(4.0f, 4.0f);
	// AddComponent(backgroundRenderer);

    // light = std::make_shared<Light2D>(Light2D::Type::Radial);
    // light->SetIntensity(0.8f);
    // light->sortingLayer = 1;
    // AddComponent(light);

    // TextRendererPtr label = std::make_shared<TextRenderer>();
    // *label += "<color='green'>aver</color>";
    // label->fontSize = 30;
    // label->borderWidth = 5;
    // label->borderRadius = 6;
    // label->backgroundColor = Colors::Black;
    // label->offset = Vector2(30, 70);
    // AddComponent(label);

	animation->AddAnimation("dudegame/player/char_walk.png", "walk-forward", 3, 3, 192, 116, 8);
	animation->AddAnimation("dudegame/player/idle.png", "idle", 2, 2, 192, 116, 4);
	animation->AddAnimation("dudegame/player/jump_forward.png", "jump-forward", 1, 2, 192, 116, 2);
	animation->AddAnimation("dudegame/player/jump_backward.png", "jump-backward", 1, 2, 192, 116, 2);
	animation->AddAnimation("dudegame/player/running_forward.png", "running-forward", 2, 3, 192, 116, 6);
	animation->AddAnimation("dudegame/player/running_backward.png", "running-backward", 2, 3, 192, 116, 6);
	animation->offset = Vector2(0, 14);
	animation->scale = Vector2(0.075f, 0.075f);
    animation->SetTimePerFrame(125);

    rigidbody2d->CreateBody(
        std::make_shared<RectShape>(Vector2(40.0f, 75.0f)),
        BodyType::dynamic_body,
        true,
        MaskType::mask_2
    );
    rigidbody2d->SetFixedRotation(true);
    
    TextPtr text = std::make_shared<Text>();
    canvas->AddElement(text);
    text->position = Vector2(20, 20);
    text->padding = Vector2(10, 10);

    text->font = "fonts/Merriweather/Merriweather-Regular.ttf";
    text->fontSize = 17;
    *text += "<bold>Alce Engine Sample Project</bold>";
    *text += "\n<bold>by <underlined>@ekrol34</underlined></bold>";
    text->borderRadius = 5;
    text->borderWidth = 3;
    text->borderColor = Colors::Yellow;
    text->backgroundColor = Colors::Black;

    leftRaycast2d->direction = Vector2(-0.447f, -0.894f);
    leftRaycast2d->length = 1.5f;

    rightRaycast2d->direction = Vector2(0.447f, -0.894f);
    rightRaycast2d->length = 1.5f;

    walking = false;
    status = "idle-forward";

	walkSpeed = 0.7f;
	runSpeed = 2.0f;

	running = false;

    ButtonPtr button = std::make_shared<Button>(); 
    canvas->AddElement(button);
    button->font = "fonts/Consolas/CONSOLA.ttf";
    button->zIndex = 5;
    button->position = Vector2(20, 100);
    button->borderRadius = 3;
    button->borderWidth = 2;
    button->text = "Dev Mode: ON ";
    button->borderColor = Colors::White;
	button->backgroundColor = Color("#5EBF28");
	button->mouseOverBackgroundColor = Color("#79D343");
    button->onClick = [button](){
        
		if(Alce.GetCurrentScene()->IsDevelopmentMode())
		{
			button->text = "Dev Mode: OFF";
			button->backgroundColor = Color("#D13C28");
			button->mouseOverBackgroundColor = Color("#E2583F");
			button->onClickBackgroundColor = Color("#E2583F");
			Alce.GetCurrentScene()->DevelopmentMode(false);
		}
		else
		{
			button->text = "Dev Mode: ON ";
			button->backgroundColor = Color("#5EBF28");
			button->mouseOverBackgroundColor = Color("#79D343");
			button->onClickBackgroundColor = Color("#79D343");
			Alce.GetCurrentScene()->DevelopmentMode(true);
		}
    };

    TextPtr label = std::make_shared<Text>();
    canvas->AddElement(label);
    label->positionType = UIElement::Relative;
    label->position = Vector2(0.01, 0.880f);
    label->padding = Vector2(0, 0);

    label->font = "fonts/Merriweather/Merriweather-Regular.ttf";
    label->fontSize = 17;
    label->SetNewText("<bold>New Spell:</bold>");
    label->borderRadius = 0;
    label->borderWidth = 0;
    label->borderColor = Colors::Transparent;
    label->backgroundColor = Colors::Transparent;

    TextInputPtr ti = std::make_shared<TextInput>();
    canvas->AddElement(ti);
    ti->width = 500;
    ti->height = 45;
    ti->backgroundColor = Colors::Black;
    ti->textColor = Colors::White;
    ti->borderWidth = 1;
    ti->cursorColor = Colors::White;
    ti->positionType = UIElement::Relative;
    ti->position = Vector2(0.01, 0.925f);
    ti->fontSize = TextInput::Small;
    ti->onSubmit = [=](){
        Debug.Log(ti->GetText());
        ti->Clear();
    };

    // anima = std::make_shared<Animation>();
    // canvas->AddElement(anima);
	// anima->AddAnimation("dudegame/player/idle.png", "idle", 2, 2, 192, 116, 4);
    // anima->position = Vector2(200, 200);
    // anima->SetTimePerFrame(125);
    // anima->enabled = true;

    // ImagePtr img = std::make_shared<Image>();   
    // img->AddTexture("meteor.png", "meteor");
    // img->SetTexture("meteor");
    // canvas->AddElement(img);
    // img->position = Vector2(400, 200);
    // img->borderWidth = 2;
    // img->borderColor = Colors::Green;
    // img->borderRadius = 3;
    // img->backgroundColor = Colors::Red;

    ps = std::make_shared<ParticleSystem>();
    ps->EnableCollision(true);
    ps->SetStart([](Particle& particle) {

        SpriteRendererPtr p_sr = std::make_shared<SpriteRenderer>();
        particle.AddComponent(p_sr);

        p_sr->enabled = true;
        p_sr->AddTexture("meteor.png", "p_meteor");
        p_sr->SetTexture("p_meteor");

        Light2DPtr light;
        light = std::make_shared<Light2D>();
        light->SetRange(200.0f);
        particle.AddComponent(light);

        particle.SetLifetime(Time({
            {"seconds", 2.0f}
        }));
        particle.ApplyForce(Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)) * 0.3f);
        particle.sortingLayer = 1;
        particle.SetDensity(1.0f);
        particle.SetFixedRotation();

        particle.SetRestitution(0.5f);    
        particle.SetRestitutionThreshold(0.0f);
        particle.SetFriction(0.0f);            
    });

    ps->SetUpdate([](Particle& particle) {
        if(particle.GetLifeTime() < 1000) {
            auto l2d = particle.GetComponent<Light2D>();
            if(l2d) l2d->color = Colors::Green;
        }
    });

    List<Vector2> vertexarr = {
        Vector2(0.0f, 0.0f), 
        Vector2(2.0f, 0.0f),
        Vector2(1.0f, 2.0f) 
    };

    ps->SetEmitArea(std::make_shared<PolygonShape>(vertexarr));
    ps->SetDelay(Time({
        {"seconds", 0.25f}
    }));

    AddComponent(ps);

}

void SharedScene::Player::Start()
{   
    // anima->PlayAnimation("idle");
    Audio.GetChannel("player")->Play("gas");
}

void SharedScene::Player::OnImpact(GameObject* other)
{
    if(other->HasTag("Ground"))
    {
        grounded = true;
        if(status == "jump-forward") status = "idle";
        if(status == "jump-backward") status = "idle";
    }
}

void SharedScene::Player::OnImpactEnd(GameObject* other)
{
    if(other->HasTag("Ground"))
    {
        grounded = false;
        if(status == "idle") status = "jump-forward";
        if(status == "idle") status = "jump-backward";
    }
}

bool toggle = true;

void SharedScene::Player::Update()
{
    if(Input.IsKeyDown(Keyboard::Y))
    {
        ps->Emit(toggle); 
        toggle = !toggle;
    }

    if(grounded) status = "idle";

	velocity = running ? runSpeed : walkSpeed;

	if(Input.IsKeyPressed(Keyboard::LShift))
	{
		running = true;
	}
	else 
	{
		running = false;
	}

    if(Input.IsKeyPressed(Keyboard::Left))
    {
        rigidbody2d->SetHorizontalVelocity(-velocity);
        if(grounded) status = "walk-backward";
        else status = "jump-backward";
    }
    else if(Input.IsKeyPressed(Keyboard::Right))
    {
        rigidbody2d->SetHorizontalVelocity(velocity);
        if(grounded) status = "walk-forward";
        else status = "jump-forward";
    }
    else
    {
        rigidbody2d->SetHorizontalVelocity(0.0f);
        if(grounded) status = "idle";
    }

    if (Input.IsKeyDown(Keyboard::Space) && grounded)
    {
        rigidbody2d->ApplyLinearForce(Vector2(0.0f, 90.0f));

        if(status == "walk-forward") status = "jump-forward";
        if(status == "walk-backward") status = "jump-backward";
        if(status == "idle") status = "jump-forward";
        grounded = false; 
    }

    AnimationManager();
}
#pragma endregion

void SharedScene::Player::SetterManager(String name, String value)
{
    if(name == "velocity") velocity =  value.ParseFloat();
    if(name == "intensity") light->SetIntensity(value.ParseFloat());
    if(name == "range") light->SetRange(value.ParseFloat());
    if(name == "beam") light->SetBeamAngle(value.ParseFloat());
    if(name == "sortingLayer") sortingLayer = value.ParseInt();
	if(name == "animation_offset") animation->offset = Vector2(value.Split(",").First().ParseFloat(), value.Split(",").Last().ParseFloat());
    // if(name == "animation_padding") anima->padding = Vector2(value.Split(",").First().ParseFloat(), value.Split(",").Last().ParseFloat());
}

String SharedScene::Player::GetterManager(String name)
{
    if(name == "velocity") return velocity;
    if(name == "position") return transform.position.ToString();

    return "undefined";
}

void SharedScene::Player::AnimationManager()
{
    if(status == "idle")
    {
        if(animation->GetCurrentAnimation() != "idle")
		{
            animation->PlayAnimation("idle");
		}
    }
	else
	{
		if(status == "walk-forward")
		{
			if(!running)
			{
				if(animation->GetCurrentAnimation() != "walk-forward")
					animation->PlayAnimation("walk-forward");
			}
			else
			{
				if(animation->GetCurrentAnimation() != "running-forward")
					animation->PlayAnimation("running-forward");
			}
		}

		if(status == "walk-backward")
		{
			if(!running)
			{
				if(animation->GetCurrentAnimation() != "walk-forward")
				{
					animation->PlayAnimation("walk-forward");
					animation->SetAnimationMode(AnimationMode::LoopBackwards);
				}
			}
			else
			{
				if(animation->GetCurrentAnimation() != "running-backward")
				{
					animation->PlayAnimation("running-backward");
				}
			}
		}

		if(status == "jump-forward")
		{
			if(animation->GetCurrentAnimation() != "jump-forward")
			{
				animation->PlayAnimation("jump-forward");
				animation->SetAnimationMode(AnimationMode::OnceForwards);
			}
		}

		if(status == "jump-backward")
		{
			if(animation->GetCurrentAnimation() != "jump-backward")
			{
				animation->PlayAnimation("jump-backward");
				animation->SetAnimationMode(AnimationMode::OnceBackwards);
			}
		}
	}
}