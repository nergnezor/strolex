#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

#define D 390
#define CANVAS_BUFFER_SIZE (3600)
// // Setup the CanvasWidgetRenderer. ONLY needed if you use CanvasWidgets
// // in your application. The CANVAS_BUFFER_SIZE can be adjusted to match
// // your needs in performance vs. RAM usage.
// static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
// CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

Screen1View::Screen1View() : ImageClickedCallback(this, &Screen1View::ImageClickHandler),
                             animationEndedCallback(this, &Screen1View::animationEndedCallbackHandler)

{
}

/*
  * Creates a gauge hand using a texture mapper
  */
void Screen1View::setupHand(TextureMapper &hand, const BitmapId bitmapId, int16_t clockRotationCenterX, int16_t clockRotationCenterY, int16_t rotationCenterX, int16_t rotationCenterY, int width, int height)
{
    hand.setBitmap(Bitmap(bitmapId));
    hand.setWidth(width);
    hand.setHeight(height);
    // hand.setWidth(D);
    // hand.setHeight(D);
    hand.setXY(0, 0);
    hand.setBitmapPosition(clockRotationCenterX - rotationCenterX, clockRotationCenterY - rotationCenterY);
    hand.setCameraDistance(300.0f);
    hand.setOrigo((float)clockRotationCenterX, (float)clockRotationCenterY, hand.getCameraDistance());
    hand.setCamera(hand.getOrigoX(), hand.getOrigoY());
    hand.setRenderingAlgorithm(TextureMapper::BILINEAR_INTERPOLATION);
    hand.setVisible(true);
}

void Screen1View::setupScreen()
{
    Image *image = &rolex_arrow1;
    rolex_urtavla.setClickAction(ImageClickedCallback);
    int16_t width = image->getWidth();
    int16_t height = image->getHeight();
    setupHand(humidity, image->getBitmap(), D / 2, D / 2, width / 2, D / 2, width, height); //Placing the rotation centor of humidity hand at (103, 195)
    humidity.setTextureMapperAnimationEndedAction(animationEndedCallback);
    remove(*image);
    add(humidity);

    bgBox.setColor(Color::getColorFrom24BitRGB(0, 0, 0));

    textArea1.setX(D);
    textArea2.setX(D);
}

void Screen1View::updateTxt(int newValue)
{
    Unicode::snprintf(txtBuffer, 10, "%d", newValue);
    txt.invalidate();
}

void Screen1View::tearDownScreen()
{
}

static float angle = 0.0f;
static volatile bool isAnimating = false;
static volatile bool looping = false;
void Screen1View::Rotate(touchgfx::AnimationTextureMapper &src)
{
    if (!isAnimating)
    {
        angle += 2;
        // src.setupAnimation(AnimationTextureMapper::Z_ROTATION, angle, 10, 0, EasingEquations::cubicEaseInOut);
        src.setupAnimation(AnimationTextureMapper::SCALE, src.getScale() * 0.9, 20, 0);
        isAnimating = true;
    }
}
static int demoI = -1;

void Screen1View::ImageClickHandler(const Image &b, const ClickEvent &evt)
{
    if (&b == &rolex_urtavla && (&evt)->getType() == ClickEvent::ClickEventType::PRESSED)
    {
        looping = !looping;
        ++demoI;
        demoI = demoI % 4;
    }
}

void Screen1View::animationEndedCallbackHandler(const touchgfx::AnimationTextureMapper &src)
{
    if (&src == &humidity)
    {
        isAnimating = false;
        if (looping)
            Rotate(humidity);
    }
}

void Screen1View::bezelShrink()
{
    static int dd = -8;
    int d = scalableImage1.getWidth();
    d += dd;
    // if (d > D)
    //     d = D;

    d = MIN(D, d);
    scalableImage1.setWidth(d);
    scalableImage1.setHeight(d);
    scalableImage1.setPosition(scalableImage1.getX() - dd / 2, scalableImage1.getY() - dd / 2, d, d);
    bgBox.invalidate();
    if (d < (D - 80) || d >= D)
        dd *= -1;
}

void Screen1View::scrollText()
{
    int text_x = textArea1.getX();
    if (text_x <= -D)
    {
        text_x = D;
    }
    textArea1.moveTo(text_x - 3, 0);
    textArea2.moveTo(text_x, textArea1.getY());
}

void Screen1View::handleTickEvent()
{

    if (looping)
    {
        demo();
    }
}

void Screen1View::demo()
{
    switch (demoI)
    {
    case 0:
        bezelShrink();
        break;
    case 2:
        scrollText();
        break;
    }

    // ++demoI;
}
