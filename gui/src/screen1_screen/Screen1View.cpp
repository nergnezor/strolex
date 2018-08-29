#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <touchgfx/EasingEquations.hpp>

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
    rolex_urtavla.setClickAction(ImageClickedCallback);
    int16_t width = rolex_arrow1.getWidth();
    int16_t height = rolex_arrow1.getHeight();
    // setupHand(humidity, BITMAP_BLUE_BUTTONS_ROUND_SMALL_ID, 390 / 2, 390 / 2,390 / 2, 390 / 2, width, height);  //Placing the rotation centor of humidity hand at (103, 195)
    setupHand(humidity, rolex_arrow1.getBitmap(), 390 / 2, 390 / 2, width / 2, 390 / 2, width, height); //Placing the rotation centor of humidity hand at (103, 195)
    // setupHand(humidity2, BITMAP_ROLEX1_RING_390_ID, 390 / 2, 390 / 2, 390 / 2, 390 / 2); //Placing the rotation centor of humidity hand at (103, 195)
    humidity.setTextureMapperAnimationEndedAction(animationEndedCallback);
    // remove(rolex_ring);
    remove(rolex_arrow1);

    add(humidity);
    // add(humidity2);
    // Rotate(humidity);
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
        angle += 2 * PI;
        src.setupAnimation(AnimationTextureMapper::Z_ROTATION, angle, 200, 0, EasingEquations::cubicEaseInOut);
        src.startAnimation();
        isAnimating = true;
        //Move CoverBox to x:550, y:210 with BounceOut easing in 90 Ticks
        //        rolex_ring.startMoveAnimation(rolex_urtavla.getX(), rolex_urtavla.getY(), 90, EasingEquations::bounceEaseOut, EasingEquations::bounceEaseOut);
    }
}

void Screen1View::ImageClickHandler(const Image &b, const ClickEvent &evt)
{
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
            looping = true;
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
    }

    // // if (tickCounter % 108 == 0)
    // if (tickCounter % 10 == 0)
    // {
    // 	if (++seconds >= 60)
    //     {
    //         seconds = 0;
    //         if (++minutes >= 60)
    //         {
    //             minutes = 0;
    //             if (++hours >= 24)
    //             {
    //                 hours = 0;
    //             }
    //         }
    //     }

    //     // Update humidity
    //     // humidityEntropi = ((seconds*seconds+seconds*5+hours) % 180)/360.0f * 2*PI - PI/2;
    //     // humidity.setupAnimation(AnimationTextureMapper::Z_ROTATION, humidityEntropi, 250, 0, EasingEquations::cubicEaseInOut);
    //     // humidity.startAnimation();

    //     // // Update pressure
    //     // pressureEntropi = (((seconds+minutes+hours)*(seconds+minutes+hours)) % 180)/360.0f * 2*PI - PI/2;
    //     // pressure.setupAnimation(AnimationTextureMapper::Z_ROTATION, pressureEntropi, 250, 0, EasingEquations::cubicEaseInOut);
    //     // pressure.startAnimation();

    //     // Update the clock
    //     // analogClock.setTime24Hour(hours, minutes, seconds);
    // }
}
