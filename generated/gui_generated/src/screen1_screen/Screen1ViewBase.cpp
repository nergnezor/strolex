/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include "BitmapDatabase.hpp"

Screen1ViewBase::Screen1ViewBase()  
{
    rolex_urtavla.setXY(0, 0);
    rolex_urtavla.setBitmap(Bitmap(BITMAP_ROLEX1_URTAVLA_390_ID));

    rolex_ring.setXY(0, 0);
    rolex_ring.setBitmap(Bitmap(BITMAP_ROLEX1_RING_390_ID));

    button1.setPosition(0, 0, 170, 60);
    button1.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_SMALL_PRESSED_ID));

    add(rolex_urtavla);
    add(rolex_ring);
    add(button1);
}
