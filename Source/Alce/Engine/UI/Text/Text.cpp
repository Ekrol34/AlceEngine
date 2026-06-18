#include "Text.hpp"

using namespace alce;

#include <regex>
#include <stack>
#include <sstream>
#include <algorithm>

void Text::Init()
{
    
}

void Text::Start()
{

}

void Text::SetNewText(String s)
{
    this->str = s.ToSFMLString();
}

void Text::AddText(String s)
{
    this->str += s.ToSFMLString();
}

void Text::SetBackgroundTexture(String path, bool keepAspect)
{
    path = String("./Assets/" + path.ToAnsiString());

    if (!backgroundTexture.loadFromFile(path.ToAnsiString()))
    {
        hasBackgroundTexture = false;
        return;
    }

    hasBackgroundTexture = true;
    keepAspectRatio = keepAspect;

    backgroundSprite.setTexture(backgroundTexture);
}

void Text::RemoveBackgroundTexture()
{
    hasBackgroundTexture = false;
}

void Text::EnableFixedBox(Vector2 boxSize)
{
    useFixedBox = true;
    fixedBoxSize = boxSize;
}

void Text::DisableFixedBox()
{
    useFixedBox = false;
}

bool Text::IsUsingFixedBox()
{
    return useFixedBox;
}

void Text::Render()
{
    // Background drawing (image or rectangle with/without border or radius) using boxPos and size
    if (hasBackgroundTexture)
    {
        sf::FloatRect target(boxPos.x, boxPos.y, size.x, size.y);
        sf::Vector2u texSize = backgroundTexture.getSize();

        float texW = static_cast<float>(texSize.x);
        float texH = static_cast<float>(texSize.y);

        float scaleX = target.width / texW;
        float scaleY = target.height / texH;

        float drawScaleX, drawScaleY;
        float offsetX = 0.f, offsetY = 0.f;

        if (keepAspectRatio)
        {
            float scale = std::min(scaleX, scaleY);
            drawScaleX = drawScaleY = scale;

            offsetX = (target.width - texW * scale) / 2.f;
            offsetY = (target.height - texH * scale) / 2.f;
        }
        else
        {
            float scale = std::max(scaleX, scaleY);
            drawScaleX = drawScaleY = scale;

            offsetX = (target.width - texW * scale) / 2.f;
            offsetY = (target.height - texH * scale) / 2.f;
        }

        sf::RectangleShape texturedBox;
        texturedBox.setPosition(target.left, target.top);
        texturedBox.setSize(sf::Vector2f(target.width, target.height));
        texturedBox.setTexture(&backgroundTexture);

        texturedBox.setTextureRect(sf::IntRect(
            static_cast<int>(-offsetX / drawScaleX),
            static_cast<int>(-offsetY / drawScaleY),
            static_cast<int>(target.width / drawScaleX),
            static_cast<int>(target.height / drawScaleY)
        ));

        Alce.GetWindow().draw(texturedBox);
    }
    else
    {
        if (borderRadius > 0)
        {
            int totalPoints = CIRCLE_QUALITY * 4;

            sf::ConvexShape roundedBox;
            roundedBox.setPointCount(totalPoints);

            float angleStep = 90.f / CIRCLE_QUALITY;
            int pointIndex = 0;

            auto addCorner = [&](float cx, float cy, float startAngle) {
                for (int i = 0; i < CIRCLE_QUALITY; ++i, ++pointIndex)
                {
                    float angle = startAngle + i * angleStep;
                    float rad = angle * (3.14159f / 180.f);
                    float x = cx + borderRadius * cos(rad);
                    float y = cy + borderRadius * sin(rad);
                    roundedBox.setPoint(pointIndex, sf::Vector2f(x, y));
                }
            };

            addCorner(size.x - borderRadius, borderRadius, -90);
            addCorner(size.x - borderRadius, size.y - borderRadius, 0);
            addCorner(borderRadius, size.y - borderRadius, 90);
            addCorner(borderRadius, borderRadius, 180);

            roundedBox.setPosition(boxPos.ToVector2f());
            roundedBox.setFillColor(backgroundColor.ToSFMLColor());
            roundedBox.setOutlineThickness(borderWidth);
            roundedBox.setOutlineColor(borderColor.ToSFMLColor());

            Alce.GetWindow().draw(roundedBox);
        }
        else 
        {
            sf::RectangleShape border;

            border.setPosition(boxPos.ToVector2f());
            border.setSize(size.ToVector2f());
            border.setOutlineThickness(borderWidth);
            border.setOutlineColor(borderColor.ToSFMLColor());
            border.setFillColor(backgroundColor.ToSFMLColor());
            
            Alce.GetWindow().draw(border);
        }
    }

    // Dibuja el texto (richText)
    Alce.GetWindow().draw(richText);
}

void Text::Update() 
{
    if (!enabled) return;

    std::string rawText = ToAnsiString();

    // === FIXED BOX ===
    if (useFixedBox)
    {
        size = fixedBoxSize;

        float contentW = fixedBoxSize.x - padding.x * 2.f;
        float contentH = fixedBoxSize.y - padding.y * 2.f;

        if (contentW <= 0.f || contentH <= 0.f)
        {
            richText = sfe::RichText(*Alce.GetFont(font).get());
            richText.setCharacterSize(fontSize);
            boxPos = transform.position;
            richText.setPosition(boxPos.x + padding.x, boxPos.y + padding.y);
            richText.setRotation(transform.rotation);
            return;
        }

        sf::Font* f = Alce.GetFont(font).get();
        sf::Text measure("", *f, fontSize);

        float lineHeight = f->getLineSpacing(fontSize);
        int maxLines = std::max(0, static_cast<int>(std::floor(contentH / lineHeight)));
        if (maxLines == 0)
        {
            richText = sfe::RichText(*f);
            richText.setCharacterSize(fontSize);
            boxPos = transform.position;
            richText.setPosition(boxPos.x + padding.x, boxPos.y + padding.y);
            richText.setRotation(transform.rotation);
            return;
        }

        struct Token { bool isTag=false; bool isClosing=false; std::string tagName, tagValue, text; };
        std::vector<Token> tokens;
        std::regex tagRegex(R"(<(\/?)([a-zA-Z]+)(?:='([^']+)')?>)");
        std::sregex_iterator it(rawText.begin(), rawText.end(), tagRegex), end;
        std::size_t lastPos = 0;

        for (; it != end; ++it)
        {
            auto m = *it;
            if (m.position() > lastPos)
            {
                Token t; t.text = rawText.substr(lastPos, m.position()-lastPos);
                tokens.push_back(t);
            }
            Token tg;
            tg.isTag = true;
            tg.isClosing = (m[1] == "/");
            tg.tagName = m[2].str();
            std::transform(tg.tagName.begin(), tg.tagName.end(), tg.tagName.begin(), ::tolower);
            tg.tagValue = m[3].str();
            tokens.push_back(tg);
            lastPos = m.position() + m.length();
        }
        if (lastPos < rawText.size())
        {
            Token t; t.text = rawText.substr(lastPos);
            tokens.push_back(t);
        }

        std::vector<Token> out;
        int lines = 0; bool stop = false;
        std::string lineBuffer;

        auto measureW = [&](const std::string &s) {
            measure.setString(sf::String::fromUtf8(s.begin(), s.end()));
            return measure.getGlobalBounds().width;
        };

        for (size_t i=0; i<tokens.size() && !stop; i++)
        {
            Token &tk = tokens[i];
            if (tk.isTag) { out.push_back(tk); continue; }

            if (wordWrap)
            {
                std::istringstream iss(tk.text);
                std::string word;
                while (iss >> word)
                {
                    std::string candidate = lineBuffer.empty()? word : lineBuffer + " " + word;
                    if (measureW(candidate) <= contentW)
                    {
                        if (!lineBuffer.empty()) { Token sp; sp.text=" "; out.push_back(sp); }
                        Token w; w.text = word; out.push_back(w);
                        lineBuffer = candidate;
                    }
                    else
                    {
                        Token nl; nl.text="\n"; out.push_back(nl);
                        lines++; lineBuffer.clear();
                        if (lines >= maxLines) { stop=true; break; }

                        if (measureW(word) <= contentW)
                        {
                            Token w; w.text = word; out.push_back(w);
                            lineBuffer = word;
                        }
                    }
                }
            }
            else
            {
                const std::string &txt = tk.text;
                size_t p = 0;
                while (p < txt.size() && !stop)
                {
                    unsigned char c = txt[p];
                    size_t clen = (c&0x80)? ((c&0xE0)==0xC0?2: (c&0xF0)==0xE0?3:4):1;
                    if (p+clen > txt.size()) clen=1;
                    std::string ch = txt.substr(p,clen); p+=clen;

                    if (ch=="\n")
                    {
                        Token nl; nl.text="\n"; out.push_back(nl);
                        lineBuffer.clear(); lines++;
                        if (lines>=maxLines) { stop=true; break; }
                        continue;
                    }

                    std::string candidate=lineBuffer+ch;
                    if (measureW(candidate)<=contentW)
                    {
                        Token nt; nt.text=ch; out.push_back(nt);
                        lineBuffer=candidate;
                    }
                    else
                    {
                        Token nl; nl.text="\n"; out.push_back(nl);
                        lines++; lineBuffer.clear();
                        if (lines>=maxLines) { stop=true; break; }
                        if (measureW(ch)<=contentW) { Token nt; nt.text=ch; out.push_back(nt); lineBuffer=ch; }
                        else { stop=true; break; }
                    }
                }
            }
        }

        richText = sfe::RichText(*f);
        richText.setCharacterSize(fontSize);

        sf::Color currColor = color.ToSFMLColor();
        bool bold=false, italic=false, under=false, strike=false;

        auto applyStyle=[&](){
            sf::Text::Style st=sf::Text::Regular;
            if (bold) st=(sf::Text::Style)(st|sf::Text::Bold);
            if (italic) st=(sf::Text::Style)(st|sf::Text::Italic);
            if (under) st=(sf::Text::Style)(st|sf::Text::Underlined);
            if (strike) st=(sf::Text::Style)(st|sf::Text::StrikeThrough);
            return st;
        };

        for (auto &tk: out)
        {
            if (tk.isTag)
            {
                if (!tk.isClosing)
                {
                    if (tk.tagName=="bold") bold=true;
                    else if (tk.tagName=="italic") italic=true;
                    else if (tk.tagName=="underlined"||tk.tagName=="underline") under=true;
                    else if (tk.tagName=="strikethrough") strike=true;
                    else if (tk.tagName=="color" && !tk.tagValue.empty()) currColor=MapColorFromString(tk.tagValue);
                }
                else
                {
                    if (tk.tagName=="bold") bold=false;
                    else if (tk.tagName=="italic") italic=false;
                    else if (tk.tagName=="underlined"||tk.tagName=="underline") under=false;
                    else if (tk.tagName=="strikethrough") strike=false;
                    else if (tk.tagName=="color") currColor=color.ToSFMLColor();
                }
                continue;
            }

            richText << currColor << applyStyle() << sf::String::fromUtf8(tk.text.begin(), tk.text.end());
        }

        // posición de la caja = transform.position (esquina superior izquierda)
        boxPos = transform.position;

        sf::FloatRect tb = richText.getLocalBounds();

        std::string align = horizontalAlign.ToAnsiString();
        std::transform(align.begin(), align.end(), align.begin(), ::tolower);

        float textX = boxPos.x + padding.x;
        if (align=="center"||align=="centre"||align=="middle")
            textX = boxPos.x + (fixedBoxSize.x - tb.width)/2.f;
        else if (align=="right")
            textX = boxPos.x + fixedBoxSize.x - tb.width - padding.x;

        float textY = boxPos.y + padding.y;
        richText.setPosition(textX - tb.left, textY - tb.top);
        richText.setRotation(transform.rotation);

        return;
    }

    // === AUTO-SIZE (comportamiento original de Text) ===
    richText = sfe::RichText(*Alce.GetFont(font).get());
    richText.setCharacterSize(fontSize);

    Vector2 pos = transform.position + padding;
    richText.setPosition(pos.ToVector2f());
    richText.setRotation(transform.rotation);
    richText.setScale(transform.scale.ToVector2f());

    std::regex tagRegex(R"(<(\/?)([a-zA-Z]+)(?:='([^']+)')?>)");
    std::stack<sf::Text::Style> styleStack;
    std::stack<sf::Color> colorStack;
    sf::Text::Style currentStyle = sf::Text::Regular;
    sf::Color currentColor = color.ToSFMLColor();

    bool isBold = false, isItalic = false, isUnderlined = false, isStrikeThrough = false;

    std::sregex_iterator iter(rawText.begin(), rawText.end(), tagRegex);
    std::sregex_iterator end;
    std::size_t lastPos = 0;

    for (; iter != end; ++iter) 
    {
        auto match = *iter;
        std::string tag = match[2].str();
        bool isClosingTag = match[1].str() == "/";
        std::string tagValue = match[3].str();
        std::size_t posi = match.position();

        if (posi > lastPos) 
        {
            currentStyle = sf::Text::Regular;
            if (isBold) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::Bold);
            if (isItalic) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::Italic);
            if (isUnderlined) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::Underlined);
            if (isStrikeThrough) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::StrikeThrough);

            richText << currentColor << currentStyle << sf::String::fromUtf8(rawText.begin() + lastPos, rawText.begin() + posi);
        }

        if (!isClosingTag) 
        {
            if (tag == "bold") 
            {
                styleStack.push(currentStyle);
                isBold = true;
            } 
            else if (tag == "italic") 
            {
                styleStack.push(currentStyle);
                isItalic = true;
            } 
            else if (tag == "underlined") 
            {
                styleStack.push(currentStyle);
                isUnderlined = true;
            } 
            else if (tag == "strikeThrough") 
            {
                styleStack.push(currentStyle);
                isStrikeThrough = true;
            } 
            else if (tag == "color") 
            {
                colorStack.push(currentColor);
                currentColor = MapColorFromString(tagValue);
            }
        } 
        else 
        {
            if (tag == "bold") 
            {
                currentStyle = styleStack.top();
                styleStack.pop();
                isBold = false;
            } 
            else if (tag == "italic") 
            {
                currentStyle = styleStack.top();
                styleStack.pop();
                isItalic = false;
            } 
            else if (tag == "underlined") 
            {
                currentStyle = styleStack.top();
                styleStack.pop();
                isUnderlined = false;
            } 
            else if (tag == "strikeThrough") 
            {
                currentStyle = styleStack.top();
                styleStack.pop();
                isStrikeThrough = false;
            } 
            else if (tag == "color") 
            {
                currentColor = colorStack.top();
                colorStack.pop();
            }
        }

        lastPos = posi + match.length();
    }

    if (lastPos < rawText.size()) 
    {
        currentStyle = sf::Text::Regular;
        if (isBold) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::Bold);
        if (isItalic) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::Italic);
        if (isUnderlined) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::Underlined);
        if (isStrikeThrough) currentStyle = static_cast<sf::Text::Style>(currentStyle | sf::Text::StrikeThrough);

        richText << currentColor << currentStyle << sf::String::fromUtf8(rawText.begin() + lastPos, rawText.end());
    }

    size = Vector2(richText.getGlobalBounds().width, richText.getGlobalBounds().height);
    size += (padding * 2);

    boxPos = transform.position;
}
