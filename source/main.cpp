#include <iostream>
#include <stdint.h>

#include "core/gameapi/GameManager.h"
#include "core/games/GameStateMainMenu.h"

#if defined INJECT_GCC
    #include "gcc/timer/TimerGcc.h"
    #include "gcc/terminal/TerminalGcc.h"
#elif defined INJECT_PI3
    #include "pi3/timer/TimerPi3.h"
    #include "pi3/terminal/TerminalPi3.h"
#else
    #error "Compile with '-D INJECT_GCC' or '-D INJECT_PI3'"
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
    #elif defined INJECT_PI3
        terminal = new TerminalPi3();
        timer = new TimerPi3();
    #endif

    
    // Initialize and start game manager
    GameManager* gameManager = new GameManager(
        terminal, timer,
        60, 25, // Dimensions
        100 // Tick duration (100ms = 10fps)
    );
    GameState* menuState = new GameStateMainMenu();
    gameManager->start(menuState);

    return 0;
}
