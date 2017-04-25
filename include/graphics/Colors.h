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
            // Normal colors
            case 0x100: return 31; // Red
            case 0x110:
            case 0x120: return 33; // Yellow
            case 0x010: return 32; // Green
            case 0x011:
            case 0x012: return 36; // Cyan
            case 0x001:
            case 0x101: return 34; // Blue
            case 0x201: return 35; // Magenta
            
            // Bright colors
            case 0x200: return 41; // Red
            case 0x210:
            case 0x220: return 43; // Yellow
            case 0x020: return 42; // Green
            case 0x021:
            case 0x022: return 46; // Cyan
            case 0x002: return 44; // Blue
            case 0x102:
            case 0x202: return 45; // Magenta

            // Whites and Blacks
            case 0x000: return 30; // Black
            case 0x111:
            case 0x112:
            case 0x121:
            case 0x211: return 40; // Bright Black
            case 0x122:
            case 0x212:
            case 0x221: return 37; // Normal White
            case 0x222: return 47; // White
        }
    }
};

#endif
