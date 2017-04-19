#include <stdint.h>
#include "timer/Timer.h"
#include "timer/TimerGcc.h"
#include "timer/TimerRasPi3.h"
#include "terminal/Terminal.h"
#include "terminal/TerminalGcc.h"
#include "terminal/TerminalRasPi3.h"

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
    #else
        #error "Compile with '-D INJECT_GCC' or '-D INJECT_RASPI3'"
    #endif

    
    // Initialize and start game manager
    /*
     * GameManager gameManager = new GameManager(terminal, timer);
     * gameManager.start();
     */

    terminal->printStr("Hello, world! Let's count to 10:\r\n");
    for (int i = 0; i < 10; i++) {
        timer->start();
        terminal->printNumDec(i);
        for (int j = 0; j < 4; j++) {
            timer->waitElapsedMilli(250);
            terminal->printChar('.');
        }
        terminal->printStr("\r\n");
    }
    terminal->printStr("10!");

    return 0;
}
