
int main()
{
    // Initialize dependencies
    Terminal terminal;
    Timer timer;
    #if defined COMPILE_GCC
        terminal = new TerminalConsole();
        timer = new TimerGcc();
    #elif defined COMPILE_RASPI
        terminal = new TerminalUart();
        timer = new TimerRasPi();
    #else
        #error "Compile with '-D COMPILE_GCC' or '-D COMPILE_RASPI'"
    #endif
    
    // Initialize and start game manager
    /*
     * GameManager gameManager = new GameManager(terminal, timer);
     * gameManager.start();
     */

    return 0;
}
