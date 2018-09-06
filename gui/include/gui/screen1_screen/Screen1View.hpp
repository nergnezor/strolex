#ifndef SCREEN1_VIEW_HPP
#define SCREEN1_VIEW_HPP

#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>

class Box10x10 : public CanvasWidget
{
public:
  virtual Rect getMinimalRect() const { return Rect(0, 0, 10, 10); }
  virtual bool drawCanvasWidget(const Rect& invalidatedArea) const
  {
    Canvas canvas(this, invalidatedArea);
    canvas.moveTo(5, 0);
    canvas.lineTo(10, 5);
    canvas.lineTo(5, 10);
    canvas.lineTo(0, 5);
    return canvas.render(); // Shape is automatically closed
  }
};

template<class T>

class SkipRect : public T
{
public:
  void setSkipRect(Rect& r)
  {
    skip = r;
  } // skip this rectangular part of this widget

  // int getWidth() { return 100; }
  // int getHeight() { return 100; }
  // int getWidth();
  // int getHeight();

  virtual void draw(const Rect& dirty) const
  {
    // Rect above(0, 0, getWidth(), skip.y);
    // Rect left(0, skip.y, skip.x, skip.height);
    // Rect right(skip.right(), skip.y, getWidth() - skip.right(), skip.height);
    // Rect below(0, skip.bottom(), getWidth(), getHeight() - skip.bottom());
    Rect above(0, 0, 390, skip.y);
    Rect left(0, skip.y, skip.x, skip.height);
    Rect right(skip.right(), skip.y, 390 - skip.right(), skip.height);
    Rect below(0, skip.bottom(), 390, 390 - skip.bottom());
    T::draw(dirty & above);
    T::draw(dirty & left);
    T::draw(dirty & right);
    T::draw(dirty & below);
  }

  // improve, perhaps choose largest intersection with above, left, right or
  // below

  virtual Rect getSolidRect() const
  {
    return T::getSolidRect() & Rect(0, 0, 390, skip.y);
  }

private:
  Rect skip;
};

class Screen1View : public Screen1ViewBase
{
public:
  Screen1View();
  virtual ~Screen1View() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  virtual void handleTickEvent();

  // Declaring callback handler for Image
  void ImageClickHandler(const Image& b, const ClickEvent& e);
  void animationEndedCallbackHandler(
    const touchgfx::AnimationTextureMapper& src);
  void setupTextureMapper(TextureMapper& hand, Image* image);

protected:
  // Declaring callback type of box and clickEvent
  // AnimationTextureMapper textureMapper1;
  SkipRect<TextureMapper> ring;
  SkipRect<AnimationTextureMapper> textureMapper1;
  AnimationTextureMapper textureMapper2;

  Callback<Screen1View, const Image&, const ClickEvent&> ImageClickedCallback;
  /*
   * Callback Handler Declarations
   */
  // void buttonCallbackHandler(const touchgfx::AbstractButton& src);

  /*
   * Callback Declarations
   */
  Callback<Screen1View, const AnimationTextureMapper&> animationEndedCallback;
  int tickCounter;

private:
  Circle circle;
  TextAreaWithOneWildcard txt;
  Unicode::UnicodeChar txtBuffer[10];
  void updateTxt(int newValue);
  void demo(void);
  void resize(ScalableImage* scalableImage1, int speed, int size);
  void scrollText();
  void textureAnimate(AnimationTextureMapper::AnimationParameter param,
                      AnimationTextureMapper& src,
                      float endValue,
                      int duration);
  void fade(AnimationTextureMapper& src, float endValue, int duration);
};

#endif // SCREEN1_VIEW_HPP
