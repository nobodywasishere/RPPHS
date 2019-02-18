#include "intro.h"

Intro::Intro()
{
    crossNeedsReset = false;
}

void Intro::doIntro()
{
    introState = 0;
    introTimer = 0;

    letterCounter[0] = 0;
    letterCounter[1] = 0;
    letterCounter[2] = 0;

    fade = 255;

    g33Splash = vita2d_load_PNG_file("app0:/images/g33Splash.png");
    motoSplash = vita2d_load_PNG_file("app0:/images/motoSplash.png");

    //main intro handler, switch between intros
    while (introState != 3) {
        switch(introState) {
            case 0:
                Intro::introSplash(g33Splash);
                break;
            case 1:
                Intro::introSplash(motoSplash);
                break;
            case 2:
                Intro::saveWarning();
                break;
            default:
                break;
        }
    }

    vita2d_wait_rendering_done();
    vita2d_free_texture(g33Splash);
    vita2d_free_texture(motoSplash);
    saveIcon.cleanUp();
}

void Intro::introSplash(vita2d_texture *splashImage)
{
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if ((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset) {
        introState++;
        introTimer = 0;
        crossNeedsReset = true;
    } else if (!(pad.buttons & SCE_CTRL_CROSS)) {
        crossNeedsReset = false;
    }

    introTimer++;

    if (introTimer > 180) {
        introState++;
        introTimer = 0;
    }

    if (introTimer < 51) {
        if (fade > 0) {
            fade -= 5;
        } else if (fade < 0) {
            fade = 0;
        }
    }

    if (introTimer > 129) {
        fade += 5;

        if (fade > 255)
            fade = 255;
    }

    vita2d_start_drawing();
    vita2d_clear_screen();

    vita2d_draw_texture(splashImage, 0, 0);
    vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(0, 0, 0, fade));

    vita2d_end_drawing();
    vita2d_swap_buffers();
}

void Intro::saveWarning()
{
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    saveIcon.start();

    if ((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset) {
        introTimer = 0;
        introState = 3;
        crossNeedsReset = true;
    } else if(!(pad.buttons & SCE_CTRL_CROSS)) {
        crossNeedsReset = false;
    }

    introTimer++;

    if (introTimer > 180) {
        introTimer = 0;
        introState = 3;
    }

    vita2d_start_drawing();
    vita2d_clear_screen();

    vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, \
      20.0f, "This game saves data automagically") / 2, 262, \
      RGBA8(255,255,255,255), 20.0f, "This game saves data automagically");
    vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, \
      20.0f, "Do not exit or power off when you see this icon") / 2, 282, \
      RGBA8(255,255,244,255), 20.0f, "Do not exit or power off when you see this icon");
      
    saveIcon.doStuff(960 / 2 - 8, 544 / 2 + 40);

    vita2d_end_drawing();
    vita2d_swap_buffers();
}
