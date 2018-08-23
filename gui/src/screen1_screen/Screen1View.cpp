#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <touchgfx/EasingEquations.hpp>

Screen1View::Screen1View() : // In constructor for callback, bind to this view object and bind which function to handle the event.
                             ImageClickedCallback(this, &Screen1View::ImageClickHandler)
{
}

/*
  * Creates a gauge hand using a texture mapper
  */
void Screen1View::setupHand(TextureMapper &hand, const BitmapId bitmapId, int16_t clockRotationCenterX, int16_t clockRotationCenterY, int16_t rotationCenterX, int16_t rotationCenterY)
{
    hand.setBitmap(Bitmap(bitmapId));
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
    setupHand(humidity, BITMAP_ROLEX1_RING_390_ID, 390/2, 390/2, 390/2, 390/2); //Placing the rotation centor of humidity hand at (103, 195)
    remove(rolex_ring);
    add(humidity);
    //rolex_ring.startMoveAnimation(
}

void Screen1View::tearDownScreen()
{
}
static float angle;
static volatile bool isAnimating = false;
void Screen1View::ImageClickHandler(const Image &b, const ClickEvent &evt)
{
    if (&b == &rolex_urtavla)
    {
        //When HiddenBox is clicked move CoverBox
        // Check if CoverBox is already moving
        if (!isAnimating)
        {
            humidity.setupAnimation(AnimationTextureMapper::Z_ROTATION, angle, 250, 0, EasingEquations::cubicEaseInOut);
            humidity.startAnimation();
            isAnimating = true;
            //Move CoverBox to x:550, y:210 with BounceOut easing in 90 Ticks
            //        rolex_ring.startMoveAnimation(rolex_urtavla.getX(), rolex_urtavla.getY(), 90, EasingEquations::bounceEaseOut, EasingEquations::bounceEaseOut);
        }
    }
    angle += 10;
}

void Screen1ViewBase::animationEndedCallbackHandler(const touchgfx::AnimationTextureMapper &src)
{
    if (&src == &humidity)
    {
        isAnimating = false;
        //animationEnded
        //When animation animation ended execute C++ code
        //Execute C++ code
        // animation.startAnimation(!animation.isReverse(), false, true);
    }
}
