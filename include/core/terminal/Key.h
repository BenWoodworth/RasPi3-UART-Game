#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdint.h>

class Key {

private: 
    uint8_t ch;
public:
    /// Constuctor for Key
    Key(uint8_t ch){
        this->ch = ch;
    }
 
    /// Getter for stored key
    uint8_t getChar();

    /// True if key is 'w' or ','
    bool isUp();

    /// True if key is 's' or 'o'
    bool isDown();

    /// True if key is 'a'
    bool isLeft();

    /// True if key is 'd' or 'e'
    bool isRight();

    /// True if key is ' '
    bool isSelect();
};

#endif
