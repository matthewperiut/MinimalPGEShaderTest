#define OLC_GFX_OPENGL33
#define OLC_PGE_APPLICATION
#include "shade_shader.h"
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        // Name your application
        sAppName = "Example";
    }

public:
    olc::Shade shade = olc::Shade();
    olc::Effect effect;
    olc::Sprite* sprite = nullptr;
    olc::Decal* decal = nullptr;
    olc::Effect greyscaleEffect;
    bool OnUserCreate() override
    {
        effect = shade.MakeEffect(olc::fx::FX_GREYSCALE);
        sprite = new olc::Sprite(1,1);
        sprite->SetPixel(0,0,olc::BLUE);
        decal = new olc::Decal(sprite);
        // Called once at the start, so create things here
        return true;
    }

    float pos = 0;
    float scalar = 10;
    bool OnUserUpdate(float fElapsedTime) override
    {
        this->Clear(olc::BLACK);

        for (int x = 0; x < ScreenWidth(); x++)
            for (int y = 0; y < ScreenHeight(); y++)
                if (x % 2 == 0 && y % 2 == 0)
                    Draw(x, y, olc::RED);

        pos += fElapsedTime * scalar;
        if (pos > ScreenWidth() || pos < 0) {
            scalar *= -1;
        }

        //How it should render
        //DrawDecal(olc::vf2d(pos,pos), decal);

        shade.Start(&effect);
        shade.DrawDecal(olc::vf2d(pos,pos), decal);
        shade.End();
        return true;
    }
};

int main()
{
    Example demo;
    if (demo.Construct(16, 16, 16, 16, false, true))
        demo.Start();
    return 0;
}