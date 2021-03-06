#include"game.h"
#include <psp2/kernel/sysmem.h> 

int main()
{
  vita2d_init_advanced((2 * 1024 * 1024));
  netInit();
	httpInit();
  Game Game;
  Game.init();
  Game.loadFiles();
  checkForUpdate();
  Game.doGame();

  Game.quit();
  httpTerm();
	netTerm();
	sceKernelExitProcess(0);
	return 0;
}
