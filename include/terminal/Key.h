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
    virtual uint8_t getChar() = 0;

    /// True if key is 'w' or ','
    virtual bool isUp() = 0;

    /// True if key is 's' or 'o'
    virtual bool isDown() = 0;

    /// True if key is 'a'
    virtual bool isLeft() = 0;

    /// True if key is 'd' or 'e'
    virtual bool isRight() = 0;

    /// True if key is ' '
    virtual bool isSelect() = 0;
};

#endif
