#include "terminal/Key.h"

uint8_t Key::getChar(){
    return this->ch;
}

// Note: these strange keys are DEFORAC for WASD

bool Key::isUp(){
    return (this->ch == 'w') ||
           (this->ch == ','); 
}

bool Key::isDown(){
    return (this->ch == 's') ||
           (this->ch == 'o');    
}

bool Key::isLeft(){
    return (this->ch == 'a');
}

bool Key::isRight(){
    return (this->ch == 'd') ||
           (this->ch == 'e');    
}

bool Key::isSelect(){
    return (this->ch == ' ');    
}
