
#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>

constexpr double PI = 3.141592;



float normalizeAngle(float a) {
    a = fmodf(a + PI, 2.0f * PI);

    if (a < 0.0f)
        a += 2.0f * PI;

    a -= PI;

    if (fabsf(a) < 1e-6f)
        a = 0.0f;

    return a;
}

float snapToRightAngle(float angle)
{
    const float rightAngle = M_PI / 2.0f;

    float steps = angle / rightAngle;

    float snappedSteps = std::round(steps);

    float snappedAngle = snappedSteps * rightAngle;

    return snappedAngle;
}

float snapTargetAngle(float targetAngle) {
    if (abs(targetAngle) < 0.01f) {
        targetAngle = 0.0f;
    }
    else if (abs(targetAngle - 1.57f) < 0.01f) {
        if (targetAngle < 0.0f) {
            targetAngle = -1.57f;
        }
        else {
            targetAngle = 1.57f;
        }
    }
    else if (abs(targetAngle - 3.13f) < 0.01f) {
        if (targetAngle < 0.0f) {
            targetAngle = -3.13f;
        }
        else {
            targetAngle = 3.13f;
        }
    }
    
    return targetAngle;
}