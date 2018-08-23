/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

Screen1ViewBase::Screen1ViewBase()  
{
    rolex_urtavla.setXY(0, 0);
    rolex_urtavla.setBitmap(Bitmap(BITMAP_ROLEX1_URTAVLA_390_ID));

    rolex_ring.setXY(0, 0);
    rolex_ring.setBitmap(Bitmap(BITMAP_ROLEX1_RING_390_ID));

    text.setPosition(110, 0, 170, 60);
    text.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_SMALL_PRESSED_ID));
    text.setLabelText(TypedText(T_SINGLEUSEID2));
    text.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    text.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    add(rolex_urtavla);
    add(rolex_ring);
    add(text);
}
