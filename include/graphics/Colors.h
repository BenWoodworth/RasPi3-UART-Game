#ifndef COLORS_H_
#define COLORS_H_

class Colors {
public:
    static const uint32_t NONE = 1 << 31;

    static const uint32_t RED = 0xFF0000;
    static const uint32_t GREEN = 0x00FF00;
    static const uint32_t BLUE = 0x0000FF;

    /// Get a color from Red, Green and Blue parts.
    static inline uint32_t fromRgb(uint8_t red, uint8_t green, uint8_t blue) {
        return (red << 16) | (green << 8) | blue;
    }

    /// Get the Red part of a color.
    static inline uint8_t getR(uint32_t color) {
        return (color >> 16) & 0xFF;
    }

    /// Get the Green part of a color.
    static inline uint8_t getG(uint32_t color) {
        return (color >> 8) & 0xFF;
    }

    /// Get the Blue part of a color;
    static inline uint8_t getB(uint32_t color) {
        return color & 0xFF;
    }
};

#endif
