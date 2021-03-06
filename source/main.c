#include <iostream>
#include <stdint.h>

#include "gameapi/GameManager.h"
#include "games/GameStateMainMenu.h"

#if defined INJECT_GCC
    #include "timer/TimerGcc.h"
    #include "terminal/TerminalGcc.h"
#elif defined INJECT_RASPI3
    #include "timer/TimerRasPi3.h"
    #include "terminal/TerminalRasPi3.h"
#else
    #error "Compile with '-D INJECT_GCC' or '-D INJECT_RASPI3'"
#endif

int32_t main()
{
    // Declare dependencies
    Terminal* terminal;
    Timer* timer;

    // Define dependencies
    #if defined INJECT_GCC
        terminal = new TerminalGcc();
        timer = new TimerGcc();
    #elif defined INJECT_RASPI3
        terminal = new TerminalRasPi3();
        timer = new TimerRasPi3();
    #endif

    
    // Initialize and start game manager
    GameManager* gameManager = new GameManager(
        terminal, timer,
        60, 25, // Dimensions
        200 // Tick duration (100ms = 10fps)
    );
    GameState* menuState = new GameStateMainMenu();
    gameManager->start(menuState);

    return 0;
}
