#ifndef SCREEN1_VIEW_HPP
#define SCREEN1_VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>

class Box10x10 : public CanvasWidget
{
public:
  virtual Rect getMinimalRect() const
  {
    return Rect(0, 0, 10, 10);
  }
  virtual bool drawCanvasWidget(const Rect &invalidatedArea) const
  {
    Canvas canvas(this, invalidatedArea);
    canvas.moveTo(5, 0);
    canvas.lineTo(10, 5);
    canvas.lineTo(5, 10);
    canvas.lineTo(0, 5);
    return canvas.render(); // Shape is automatically closed
  }
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
  void ImageClickHandler(const Image &b, const ClickEvent &e);
  void animationEndedCallbackHandler(const touchgfx::AnimationTextureMapper &src);
  void setupHand(TextureMapper &hand, const BitmapId bitmapId, int16_t clockRotationCenterX, int16_t clockRotationCenterY, int16_t rotationCenterX, int16_t rotationCenterY, int width, int height);

protected:
  // Declaring callback type of box and clickEvent
  AnimationTextureMapper humidity;
  AnimationTextureMapper humidity2;

  Callback<Screen1View, const Image &, const ClickEvent &> ImageClickedCallback;
  /*
     * Callback Handler Declarations
     */
  // void buttonCallbackHandler(const touchgfx::AbstractButton& src);

  /*
     * Callback Declarations
     */
  Callback<Screen1View, const AnimationTextureMapper &> animationEndedCallback;
  int tickCounter;

private:
  void Rotate(touchgfx::AnimationTextureMapper &src);
  Circle circle;
  TextAreaWithOneWildcard txt;
  Unicode::UnicodeChar txtBuffer[10];
  void updateTxt(int newValue);
  // Box10x10 box;
  // PainterRGB888 myPainter;
  // Canvas canvas;
};

#endif // SCREEN1_VIEW_HPP
