#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

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
    // hand.setWidth(width);
    // hand.setHeight(height);
    // hand.setXY(110, 0);
    hand.setWidth(390);
    hand.setHeight(390);
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
    Image *image = &rolex1_ring_3901;
    rolex_urtavla.setClickAction(ImageClickedCallback);
    int16_t width = image->getWidth();
    int16_t height = image->getHeight();
    // setupHand(humidity, BITMAP_BLUE_BUTTONS_ROUND_SMALL_ID, 390 / 2, 390 / 2,390 / 2, 390 / 2, width, height);  //Placing the rotation centor of humidity hand at (103, 195)
    setupHand(humidity, image->getBitmap(), 390 / 2, 390 / 2, width / 2, 390 / 2, width, height); //Placing the rotation centor of humidity hand at (103, 195)
    // setupHand(humidity2, BITMAP_ROLEX1_RING_390_ID, 390 / 2, 390 / 2, 390 / 2, 390 / 2); //Placing the rotation centor of humidity hand at (103, 195)
    humidity.setTextureMapperAnimationEndedAction(animationEndedCallback);
    // remove(rolex_ring);
    remove(*image);

    add(humidity);
    // textBgBox.setFadeAnimationEndedAction(animationEndedCallback);

    // add(humidity2);
    // Rotate(humidity);

    // circle.setCenter(390 / 2, 390 / 2);
    // // circle.setArc();
    // circle.setRadius(390 / 2);
    // circle.setLineWidth(10);
    // circle.setVisible(true);
    // circle.invalidate();

    // updateTxt(5);
    // box.drawCanvasWidget(box.getMinimalRect());
    // myPainter.setColor(Color::getColorFrom24BitRGB(0xFF, 0x0, 0x0));
    // box.setPosition(100, 100, 10, 10);
    // box.setPainter(myPainter);
    // add(box);
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
        src.setupAnimation(AnimationTextureMapper::SCALE, src.getScale() * 2, 20, 0);
        src.startAnimation();
        isAnimating = true;
        //Move CoverBox to x:550, y:210 with BounceOut easing in 90 Ticks
        //        rolex_ring.startMoveAnimation(rolex_urtavla.getX(), rolex_urtavla.getY(), 90, EasingEquations::bounceEaseOut, EasingEquations::bounceEaseOut);
    }
}

void Screen1View::ImageClickHandler(const Image &b, const ClickEvent &evt)
{
    // humidity.setCameraDistance(200);
    // humidity.invalidate();
    // ClickEvent::ClickEventType erik = evt.getType();
    if (&b == &rolex_urtavla && (&evt)->getType() == ClickEvent::ClickEventType::PRESSED)
    {
        //When HiddenBox is clicked move CoverBox
        // Check if CoverBox is already moving
        if (looping)
        {
            looping = false;
        }
        else if (!isAnimating)
        {
            Rotate(humidity);
            // humidity.setCameraDistance(humidity.getCameraDistance() - 10);

            // TypedText tt = new TypedText();
            // textArea1.setTypedText(humidity.getCameraDistance());
            // looping = true;
        }
        // Rotate(humidity2);
    }
}

void Screen1View::animationEndedCallbackHandler(const touchgfx::AnimationTextureMapper &src)
{
    if (&src == &humidity)
    {
        isAnimating = false;
        if (looping)
            Rotate(humidity);
        //animationEnded
        //When animation animation ended execute C++ code
        //Execute C++ code
        // animation.startAnimation(!animation.isReverse(), false, true);
    }
}
float ang = 0.0f;
void Screen1View::handleTickEvent()
{
    // ang += 0.1f;
    // int distance = 390 / 2;
    // int x = cos(ang) * distance;
    // int y = sin(ang) * distance;
    // if (tickCounter % 10 == 0)
    {
        // rolex_ring.moveTo(x, y);
        // textArea1.setWideTextAction(WideTextAction::WIDE_TEXT_CHARWRAP_DOUBLE_ELLIPSIS);
        int text_x = textArea1.getX();
        if (text_x <= -390)
        {
            text_x = 390;
            textBgBox.setAlpha(0);
            textBgBox.startFadeAnimation(250, 2000);
        }
        textArea1.moveTo(text_x - 3, 0);
        textArea2.moveTo(text_x, textArea1.getY());

        // textBgAlpha = textBgBox.
        // textArea2.startFadeAnimation(textArea2.getAlpha() - 3, 10);
    }
}
