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
static volatile bool looping = false;
static int demoI = 0;

Screen1View::Screen1View()
    : ImageClickedCallback(this, &Screen1View::ImageClickHandler)
    , animationEndedCallback(this, &Screen1View::animationEndedCallbackHandler)
    , animationEndedCallback2(this, &Screen1View::animationEndedCallbackHandler2)
{
}

void Screen1View::setupAnimation(AnimatedImage& animatedImage)
{
    animatedImage.setXY(0, 0);
    animatedImage.setBitmaps(BITMAP_BEZEL360_00_ID, BITMAP_BEZEL360_44_ID);
    animatedImage.setUpdateTicksInterval(2);
    // animatedImage.startAnimation(false, true, false);
    animatedImage.setDoneAction(animationEndedCallback2);
    add(animatedImage);
}

// void Screen1ViewBase::animationEndedCallbackHandler(const SkipRect<AnimatedImage>& src)
// {
//     if (&src == &animatedImage1) {
//         //Interaction1
//         //When animatedImage1 animation ended call virtual function
//         //Call erik
//         erik();
//     }
// }
void Screen1View::setupTextureMapper(TextureMapper& textureMapper, Image* image)
{
    //   Image* image = &rolex1_ring_3901;
    int16_t width = image->getWidth();
    textureMapper.setBitmap(Bitmap(image->getBitmap()));
    textureMapper.setWidth(D);
    textureMapper.setHeight(D);
    textureMapper.setXY(0, 0);
    textureMapper.setBitmapPosition(D / 2 - width / 2, D / 2 - D / 2);
    textureMapper.setCameraDistance(300.0f);
    textureMapper.setOrigo(
        (float)D / 2, (float)D / 2, textureMapper.getCameraDistance());
    textureMapper.setCamera(textureMapper.getOrigoX(), textureMapper.getOrigoY());
    textureMapper.setRenderingAlgorithm(TextureMapper::BILINEAR_INTERPOLATION);
    add(textureMapper);
    textureMapper.setVisible(false);
    remove(*image);
}

void Screen1View::setupScreen()
{
    Rect rect = Rect(85, 85, 220, 220);

    rolex_urtavla.setClickAction(ImageClickedCallback);

    setupTextureMapper(textureMapper1, &rolex1_ring_3901);
    textureMapper1.setTextureMapperAnimationEndedAction(animationEndedCallback);
    // Rect rect = Rect(0, 0, 390 - 41, 390 - 41);
    scalableImage1.setWidth(D_URTAVLA);
    textureMapper1.setSkipRect(rect);

    setupTextureMapper(textureMapper2, &rolex_arrow1);
    textureMapper2.setTextureMapperAnimationEndedAction(animationEndedCallback);
    textureMapper2.setScale(RATIO_URTAVLA);

    remove(rolex_urtavla);
    add(rolex_urtavla);

    bgBox.setColor(Color::getColorFrom24BitRGB(0, 0, 0));

    textArea1.setX(D);
    textArea2.setX(D);

    /* Test */

    // setupTextureMapper(ring, &rolex1_ring_3901);
    // ring.setVisible(true);
    // ring.setSkipRect(rect);

    // textureMapper1.setVisible(true);
    // textureMapper1.setupAnimation(AnimationTextureMapper::Z_ROTATION,
    //     PI,
    //     180, 0,
    //     EasingEquations::linearEaseNone);
    // textureMapper1.startAnimation();
    // animatedImage1.animationDoneAction(&animatedImage_animationEndedCallback);
    // animatedImage2 = &animatedImage1;

    // SkipRect<AnimatedImage&> animatedImage2 = &animatedImage1;
    // AnimatedImage& animatedImage2 = animatedImage1;
    // (SkipRect<AnimatedImage&>)animatedImage2.sk
    // animatedImage2-> = animatedImage1;
    // (SkipRect<AnimatedImage>)animatedImage1.setSkipRect();
    // AnimatedImage* erik = &animatedImage1;

    // SkipRect <
    // setupAnimation(animatedImage2);
    // animatedImage2.setSkipRect(rect);
    // animatedImage2.startAnimation(false, true, false);
}

void Screen1View::updateTxt(int newValue)
{
    Unicode::snprintf(txtBuffer, 10, "%rect.width", newValue);
    txt.invalidate();
}

void Screen1View::tearDownScreen()
{
}

void Screen1View::ImageClickHandler(const Image& b, const ClickEvent& evt)
{
    if (&b == &rolex_urtavla && (&evt)->getType() == ClickEvent::ClickEventType::PRESSED) {
        // looping = !looping;
        ++demoI;
        demo();
    }
}
void Screen1View::handleTickEvent()
{
    // ring.updateZAngle(ring.getZAngle() + (2.0f * PI) / 360);
    // ring.invalidate();
    if (looping) {
        demo();
    }
}

void Screen1View::animationEndedCallbackHandler(
    const touchgfx::AnimationTextureMapper& src)
{
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

void Screen1View::animationEndedCallbackHandler2(
    const touchgfx::AnimatedImage& src)
{
    animatedImage2.startAnimation(true);
}

void Screen1View::erik()
{
    if (!animatedImage1.isReverse())
        animatedImage1.startAnimation(!animatedImage1.isReverse());
    else {
        animatedImage1.setVisible(false);
        looping = true;
    }
}

void Screen1View::textureAnimate(AnimationTextureMapper::AnimationParameter param,
    AnimationTextureMapper& src,
    float endValue,
    int duration)
{
    if (!isAnimating) {
        isAnimating = true;
        scalableImage1.setVisible(false);
        src.setVisible(true);

        src.setupAnimation(param,
            endValue,
            duration,
            0,
            EasingEquations::cubicEaseInOut);
        // EasingEquations::linearEaseNone);
        src.startAnimation();

        // Unicode::strncpy(textArea3Buffer, "Bajs", 5);
        // textArea3.invalidate();
    }
}

void Screen1View::resize(ScalableImage* src, int speed, int targetSize)
{
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

void Screen1View::scrollText()
{
    int text_x = textArea1.getX();
    if (text_x <= -textArea1.getWidth()) {
        ++demoI;
        text_x = D;
    }
    textArea1.moveTo(text_x - 5, 0);
    textArea2.moveTo(text_x, textArea1.getY());
}

void Screen1View::demo()
{
    demoI = demoI % 12;
    switch (demoI) {
    case 0:
        textureAnimate(AnimationTextureMapper::SCALE, textureMapper2, 1, 50);
        break;
    case 1:
        textureAnimate(AnimationTextureMapper::Z_ROTATION,
            textureMapper2,
            textureMapper2.getZAngle() + 2.2 * PI,
            50);
        break;
    case 2:
        textureAnimate(
            AnimationTextureMapper::SCALE, textureMapper2, RATIO_URTAVLA, 20);
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
        textureAnimate(
            AnimationTextureMapper::Z_ROTATION, textureMapper1, 0.3f, 5);
        break;
    case 8:
        textureAnimate(AnimationTextureMapper::Z_ROTATION, textureMapper1, 0, 5);
        break;
    case 9:
        resize(&scalableImage1, 3, D_URTAVLA);
        break;
    case 10:
        ++demoI;
        looping = false;
        animatedImage1.setVisible(true);
        animatedImage1.startAnimation(false);
        break;
    case 11:
        break;
    }
}
