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

    /// Convert the color into one of the 16 colors specified by
    /// the original standard. The result will be within the
    /// ranges of 30-37 or 40-47.
    static uint8_t getBasicAnsiColor(uint32_t color) {
        // Get color levels on a scale of 0-3
        uint8_t red = getR(color) >> 6;
        uint8_t green = getG(color) >> 6;
        uint8_t blue = getB(color) >> 6;

        // Combine 1,2 from original scale, so it's now 0,2
        if (red > 1) red--;
        if (green > 1) green--;
        if (blue > 1) blue--;

        // Combine into 0xRGB
        uint16_t rgb = (red << 8) | (green << 4) | blue;

        // Classify colors
        switch (rgb) {
            case 0x111: return 40; // Bright Black
            case 0x000: return 30; // Normal Black
            case 0x200: return 41; // Bright Red
            case 0x100: return 31; // Normal Red
            case 0x020: return 42; // Bright Green
            case 0x010: return 32; // Normal Green
            case 0x220: return 43; // Bright Yellow
            case 0x110:
            case 0x120:
            case 0x210: return 33; // Normal Yellow
            case 0x002: return 44; // Bright Blue
            case 0x001: return 34; // Normal Blue
            case 0x202: return 45; // Bright Magenta
            case 0x101:
            case 0x102:
            case 0x201: return 35; // Normal Magenta
            case 0x022: return 46; // Bright Cyan
            case 0x011:
            case 0x012:
            case 0x021: return 36; // Normal Cyan
            case 0x222: return 47; // Bright White
            default:    return 37; // Normal White
        }
    }
};

#endif
