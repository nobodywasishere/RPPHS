#ifndef _Intro_Class
#define _Intro_Class

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>
#include "saveIcon.h"

class Intro{
private:
  SaveIcon saveIcon;
  SceCtrlData pad;
  bool crossNeedsReset;
  int introState;
  int introTimer;
  int letterCounter[3];
  vita2d_texture *splashImage, *g33Splash, *motoSplash;
  int fade;
public:
  Intro();
  void doIntro();
  void introSplash(vita2d_texture *splashImage);
  void saveWarning();
};

#endif
