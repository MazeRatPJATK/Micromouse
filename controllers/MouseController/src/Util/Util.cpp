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