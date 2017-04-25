#include <stdint.h>
#include "timer/Timer.h"
#include "timer/TimerGcc.h"
#include "timer/TimerRasPi3.h"
#include "terminal/Terminal.h"
#include "terminal/TerminalGcc.h"
#include "terminal/TerminalRasPi3.h"
#include "graphics/AnsiImage.h"
#include "graphics/AnsiImageBuilder.h"

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

    // Draw a smiley face
    AnsiImageBuilder* smileyBuilder = new AnsiImageBuilder(7, 6,
        " YYYYY "
        "YYBYBYY"
        "YYYYYYY"
        "YBYYYBY"
        "YYBBBYY"
        " YYYYY "
    );
    smileyBuilder
        ->mapChar('Y', new AnsiPixel(Colors::fromRgb(5, 5, 0)))
        ->mapChar('B', new AnsiPixel(Colors::fromRgb(0, 0, 5)));

    AnsiImage* smiley = smileyBuilder->build();
    smiley->drawToTerminal(terminal);

    terminal->newLine();
    for (int r = 0; r <= 5; r++) {
        for (int g = 0; g <= 5; g++) {
            for (int b = 0; b <= 5; b++) {
                terminal->setColor(Colors::fromRgb(r, g, b), false);
                terminal->printChar(' ');
            }
            terminal->resetStyling();
            terminal->printChar(' ');
        }
        terminal->newLine();
    }
    terminal->newLine();

    for (int i = 0; i < 25; i++) {
        terminal->setColor(Colors::fromGray(i), false);
        terminal->printChar(' ');
    }
    terminal->resetStyling();
    terminal->newLine();
    
    terminal->resetStyling();
    terminal->printStr("\r\n");
    
    terminal->printStr("Hello, world! Let's count to 10:\r\n");
    for (int i = 0; i < 10; i++) {
        terminal->printNumDec(i);
        for (int j = 0; j < 4; j++) {
            timer->start();
            timer->waitMilli(250);
            terminal->printChar('.');
        }
        terminal->printStr("\r\n");
    }
    terminal->printStr("10!");

    terminal->resetStyling();

    return 0;
}
