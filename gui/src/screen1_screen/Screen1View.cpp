#include <BitmapDatabase.hpp>
#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>

#define D 390
#define BEZEL 40
#define D_URTAVLA (390 - (2 * BEZEL))
#define RATIO_URTAVLA (D_URTAVLA / (float)D)
#define CANVAS_BUFFER_SIZE (3600)

static volatile bool isAnimating = false;
static volatile bool looping = true;
static int demoI = 0;

Screen1View::Screen1View()
    : ImageClickedCallback(this, &Screen1View::ImageClickHandler),
      animationEndedCallback(this, &Screen1View::animationEndedCallbackHandler)

{}

void Screen1View::setupTextureMapper(TextureMapper& textureMapper,
                                     Image* image) {
  //   Image* image = &rolex1_ring_3901;
  int16_t width = image->getWidth();
  textureMapper.setBitmap(Bitmap(image->getBitmap()));
  textureMapper.setWidth(D);
  textureMapper.setHeight(D);
  textureMapper.setXY(0, 0);
  textureMapper.setBitmapPosition(D / 2 - width / 2, D / 2 - D / 2);
  textureMapper.setCameraDistance(300.0f);
  textureMapper.setOrigo((float)D / 2, (float)D / 2,
                         textureMapper.getCameraDistance());
  textureMapper.setCamera(textureMapper.getOrigoX(), textureMapper.getOrigoY());
  textureMapper.setRenderingAlgorithm(TextureMapper::BILINEAR_INTERPOLATION);
  //   textureMapper.setVisible(true);
  add(textureMapper);
  textureMapper.setVisible(false);
  remove(*image);
}

void Screen1View::setupScreen() {
  rolex_urtavla.setClickAction(ImageClickedCallback);

  setupTextureMapper(textureMapper1, &rolex1_ring_3901);
  textureMapper1.setTextureMapperAnimationEndedAction(animationEndedCallback);
  scalableImage1.setWidth(D_URTAVLA);

  setupTextureMapper(textureMapper2, &rolex_arrow1);
  textureMapper2.setTextureMapperAnimationEndedAction(animationEndedCallback);
  textureMapper2.setScale(RATIO_URTAVLA);

  //   remove(rolex_urtavla);
  //   add(rolex_urtavla);

  bgBox.setColor(Color::getColorFrom24BitRGB(0, 0, 0));

  textArea1.setX(D);
  textArea2.setX(D);
}

void Screen1View::updateTxt(int newValue) {
  Unicode::snprintf(txtBuffer, 10, "%rect.width", newValue);
  txt.invalidate();
}

void Screen1View::tearDownScreen() {}

void Screen1View::ImageClickHandler(const Image& b, const ClickEvent& evt) {
  if (&b == &rolex_urtavla &&
      (&evt)->getType() == ClickEvent::ClickEventType::PRESSED) {
    // looping = !looping;
    ++demoI;
    demo();
  }
}
void Screen1View::handleTickEvent() {
  if (looping) {
    demo();
  }
}

void Screen1View::animationEndedCallbackHandler(
    const touchgfx::AnimationTextureMapper& src) {
  if (&src == &textureMapper1) {
    textureMapper1.setVisible(false);
  }
  if (&src == &textureMapper2) {
    textureMapper2.setVisible(false);
  }
  isAnimating = false;
  scalableImage1.setVisible(true);
  src.invalidate();
  ++demoI;
}

void Screen1View::textureAnimate(
    AnimationTextureMapper::AnimationParameter param,
    AnimationTextureMapper& src, float endValue, int duration) {
  if (!isAnimating) {
    isAnimating = true;
    scalableImage1.setVisible(false);
    src.setVisible(true);

    src.setupAnimation(param, endValue, duration, 0,
                       //    EasingEquations::cubicEaseInOut);
                       EasingEquations::linearEaseNone);
    src.startAnimation();
    // textArea3.set
    // textArea3Buffer
    // char text[] = "erik";
    // Unicode::UnicodeChar erik[5] = {"bajs"};
    // Unicode::strncpy(erik, text, 5);
    // Unicode::UnicodeChar* const test = textArea3.getWildcard();
    // Unicode::strncpy(test, "Bajs", 5);
    Unicode::strncpy(textArea3Buffer, "Bajs", 5);
    // erik
    // Unicode::snprintf(textArea3Buffer, 10, "%s", "erik");
    // Unicode::snprintf(textArea3Buffer, 10, "%s", erik);
    // Unicode::snprintf(textArea3Buffer, 10, "%s", Unicode::UnicodeChar);
    textArea3.invalidate();
  }
}

void Screen1View::resize(ScalableImage* src, int speed, int targetSize) {
  int width = src->getWidth();
  //   Rect rect = src->getAbsoluteRect();
  int dd = (1 << speed) * (width > targetSize ? -1 : 1);
  width += dd;
  if ((width >= targetSize && dd > 0) || (width <= targetSize && dd < 0)) {
    width = targetSize;
    isAnimating = false;
    ++demoI;
  }
  src->setWidth(width);
  src->setHeight(width);
  int x = (D - width) / 2;
  src->setPosition(x, x, width, width);
  bgBox.invalidate();
}

void Screen1View::scrollText() {
  int text_x = textArea1.getX();
  if (text_x <= -textArea1.getWidth()) {
    ++demoI;
    text_x = D;
  }
  textArea1.moveTo(text_x - 5, 0);
  textArea2.moveTo(text_x, textArea1.getY());
}

void Screen1View::demo() {
  demoI = demoI % 10;
  switch (demoI) {
    case 0:
      textureAnimate(AnimationTextureMapper::SCALE, textureMapper2, 1, 50);
      break;
    case 1:
      textureAnimate(AnimationTextureMapper::Z_ROTATION, textureMapper2,
                     textureMapper2.getZAngle() + 2.2 * PI, 50);
      break;
    case 2:
      textureAnimate(AnimationTextureMapper::SCALE, textureMapper2,
                     RATIO_URTAVLA, 20);
      break;
    case 3:
      resize(&scalableImage1, 4, D);
      break;
    case 4:
      resize(&scalableImage1, 4, D_URTAVLA);
      break;
    case 5:
      scrollText();
      break;
    case 6:
      resize(&scalableImage1, 5, D);
      break;
    case 7:
      textureAnimate(AnimationTextureMapper::Z_ROTATION, textureMapper1, 0.3f,
                     5);
      break;
    case 8:
      textureAnimate(AnimationTextureMapper::Z_ROTATION, textureMapper1, 0, 5);
      break;
    case 9:
      resize(&scalableImage1, 3, D_URTAVLA);
      break;
    case 10:
      break;
  }
}
