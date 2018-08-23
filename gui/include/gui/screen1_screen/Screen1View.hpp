#ifndef SCREEN1_VIEW_HPP
#define SCREEN1_VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>


class Screen1View : public Screen1ViewBase
{
public:
  Screen1View();
  virtual ~Screen1View() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  // Declaring callback handler for Image
  void ImageClickHandler(const Image& b, const ClickEvent& e);
  void setupHand(TextureMapper& hand, const BitmapId bitmapId, int16_t clockRotationCenterX, int16_t clockRotationCenterY, int16_t rotationCenterX, int16_t rotationCenterY);
  
protected:
  // Declaring callback type of box and clickEvent
  Callback<Screen1View, const Image&, const ClickEvent&> ImageClickedCallback;
};

#endif // SCREEN1_VIEW_HPP
