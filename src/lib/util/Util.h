#pragma once


namespace util {
    static double to_rad(double n) {
        return n * M_PI / 180;
    }

    static double to_deg(double n) {
        return n * 180 / M_PI;
    }
    static int sign(double val) {
        return val > 0 ? 1 : -1;
    }

    static double clamp(double val, double min, double max) {
        if(std::abs(val) < min) {
            return sign(val) * min;
        } else if (std::abs(val) > max) {
            return sign(val) * max;
        }
        return val;
    }
}


