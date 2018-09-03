#include <BitmapDatabase.hpp>
#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>

#define D 390
#define CANVAS_BUFFER_SIZE (3600)

static float angle = 0.0f;
static volatile bool isAnimating = false;
static volatile bool looping = true;
static int demoI = 0;

Screen1View::Screen1View()
    : ImageClickedCallback(this, &Screen1View::ImageClickHandler),
      animationEndedCallback(this, &Screen1View::animationEndedCallbackHandler)

{}

/*
 * Creates a gauge textureMapper using a texture mapper
 */
// void Screen1View::setupTextureMapper(TextureMapper& textureMapper, const
// BitmapId bitmapId,
//                             int16_t clockRotationCenterX,
//                             int16_t clockRotationCenterY,
//                             int16_t rotationCenterX, int16_t rotationCenterY,
//                             int width, int height) {
void Screen1View::setupTextureMapper(TextureMapper& textureMapper,
                                     Image* image) {
  //   Image* image = &rolex1_ring_3901;
  int16_t width = image->getWidth();
  int16_t height = image->getHeight();
  textureMapper.setBitmap(Bitmap(image->getBitmap()));
  textureMapper.setWidth(width);
  textureMapper.setHeight(height);
  //   textureMapper.setWidth(D);
  //   textureMapper.setHeight(D);
  textureMapper.setXY(0, 0);
  textureMapper.setBitmapPosition(D / 2 - width / 2, D / 2 - D / 2);
  textureMapper.setCameraDistance(300.0f);
  textureMapper.setOrigo((float)D / 2, (float)D / 2,
                         textureMapper.getCameraDistance());
  textureMapper.setCamera(textureMapper.getOrigoX(), textureMapper.getOrigoY());
  textureMapper.setRenderingAlgorithm(TextureMapper::BILINEAR_INTERPOLATION);
  //   textureMapper.setVisible(true);
  remove(*image);
}

void Screen1View::setupScreen() {
  rolex_urtavla.setClickAction(ImageClickedCallback);

  setupTextureMapper(textureMapper1, &rolex1_ring_3901);
  textureMapper1.setTextureMapperAnimationEndedAction(animationEndedCallback);
  textureMapper1.setVisible(true);
  add(textureMapper1);
  //   setupTextureMapper(textureMapper2, &rolex_arrow1);
  //   textureMapper2.setTextureMapperAnimationEndedAction(animationEndedCallback);

  remove(rolex_urtavla);
  add(rolex_urtavla);

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
void Screen1View::Rotate(touchgfx::AnimationTextureMapper& src,
                         float endValue) {
  isAnimating = true;
  // if (!isAnimating)
  {
    angle = angle == 0 ? endValue : 0;

    src.setupAnimation(AnimationTextureMapper::Z_ROTATION, angle, 4, 0,
                       //    EasingEquations::cubicEaseInOut);
                       EasingEquations::linearEaseNone);
    // src.setupAnimation(AnimationTextureMapper::SCALE,
    //                    src.getScale() * (D - 80) / D, 20, 0);
    // if (src.getScale() == 1)
    //   src.setupAnimation(AnimationTextureMapper::SCALE, 0.7f, 10, 0);
    // else
    //   src.setupAnimation(AnimationTextureMapper::SCALE, 1.0f, 5, 0);
    src.startAnimation();
  }
}

void Screen1View::animationEndedCallbackHandler(
    const touchgfx::AnimationTextureMapper& src) {
  static bool shrank = false;
  if (&src == &textureMapper1) {
    isAnimating = false;

    if (!shrank) {
      shrank = true;
      Rotate(textureMapper1, 0);
    } else {
      shrank = false;
      textureMapper1.setVisible(false);
      scalableImage1.setVisible(true);
      textureMapper1.invalidate();
      ++demoI;
    }
  }
  //   if (&src == &textureMapper2) {
  //     isAnimating = false;

  //     if (!shrank) {
  //       shrank = true;
  //       Rotate(textureMapper1, 0);
  //     } else {
  //       shrank = false;
  //       textureMapper1.setVisible(false);
  //       scalableImage1.setVisible(true);
  //       scalableImage1.invalidate();
  //       ++demoI;
  //     }
  //   }
}

void Screen1View::bezelRotate(AnimationTextureMapper& src, float endValue) {
  if (!isAnimating) {
    isAnimating = true;
    scalableImage1.setVisible(false);
    src.setVisible(true);
    Rotate(src, endValue);
  }
}

void Screen1View::resize(ScalableImage* src, int speed, int targetSize) {
  //   int rect.width = src->getWidth();
  Rect rect = src->getAbsoluteRect();
  int dd = (1 << speed) * (rect.width > targetSize ? -1 : 1);
  rect.width += dd;
  //   rect.y - dd / 2;
  //   if (abs(rect.width + dd - targetSize) < abs(dd)) {
  if ((rect.width >= targetSize && dd > 0) ||
      (rect.width <= targetSize && dd < 0)) {
    rect.width = targetSize;
    // dd = (targetSize - rect.width) / 2;
    ++demoI;
  }
  //   rect.x -= dd / 2;
  src->setWidth(rect.width);
  src->setHeight(rect.width);
  int x = (D - rect.width) / 2;
  src->setPosition(x, x, rect.width, rect.width);
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
  demoI = demoI % 6;
  switch (demoI) {
    case 0:
      bezelRotate(textureMapper1, 0.01f);
      break;
    case 1:
      resize(&scalableImage1, 2, D - 80);
      break;
    case 2:
      resize(&scalableImage1, 2, D);
      break;
    case 3:
      resize(&scalableImage1, 4, D - 80);
      break;
    case 4:
      scrollText();
      break;
    case 5:
      bezelRotate(textureMapper2, 0.1f);
      break;
    case 6:
      resize(&scalableImage1, 4, D - 80);
      break;
  }
}
