#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

class GameManager {
private:
    Terminal* terminal;
    Timer* timer;

    AnsiImage* outputImage;
    uint32_t tickDuration;

    GameState* gameState;

public:
    /// Construct a GameManager using terminal and timer dependencies.
    GameManager(Terminal* terminal, Timer* timer, uint32_t outputWidth,
                uint32_t outputHeight, uint32_t tickDuration) {
        this->terminal = terminal;
        this->timer = timer;

        this->outputImage = new AnsiImage(outputWidth, outputHeight);
        this->tickDuration = tickDuration;
    }

    /// Set the game state.
    inline void setState(GameState* state) {
        this->gameState = state;
    }

    /// Get the output image.
    inline AnsiImage* getOutputImage() {
        return this->outputImage;
    }


    /// Stop the game manager.
    inline void stop() {
        this->gameState = NULL;
    }

    /// Start with a given start state.
    void start(GameState* startState);
    
    /// Draw the output image to the terminal.
    void drawOutputImage();
};

#endif
