#ifndef COLORS_H_
#define COLORS_H_

class Colors {
public:
    static const uint8_t NONE = 0;

    /// Get a color from Red, Green and Blue parts, each ranging from 0 to 5.
    static inline uint8_t fromRgb(uint8_t red, uint8_t green, uint8_t blue) {
        return 16 + (red * 36) + (green * 6) + blue;
    }

    /// Get a color of gray given a brightness, ranging from 0 to 25.
    static inline uint8_t fromGray(uint8_t brightness) {
        if (brightness == 0) {
            return 16; // Black
        } else if (brightness == 25) {
            return 231; // White
        }

        // A shade of gray
        return 231 + brightness;
    }
};

#endif
