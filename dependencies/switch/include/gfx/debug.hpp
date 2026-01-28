#include "drawable.hpp"
#include "bindable.hpp"

class Scissor : public Bindable {
public:
    Scissor(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    ~Scissor() = default;

    virtual void Bind(nvn::CommandBuffer* buffer) override {
        buffer->SetScissor(x, y, w, h);
    }

private:
    int x, y, w, h;
};

class ClearColor : public Drawable {
public:
    ClearColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    ~ClearColor() = default;

    virtual void Draw(nvn::CommandBuffer* buffer) override {
        float color[] = { r, g, b, a };
        buffer->ClearColor(0, color, nvn::ClearColorMask::RGBA);
    }

    virtual void Update(nvn::CommandBuffer*) override {}

private:
    float r, g, b, a;
};