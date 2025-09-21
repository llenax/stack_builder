#include "math.h"

Vector2 LerpVector2(Vector2 start, Vector2 end, float t)
{
    return (Vector2){
        start.x + (end.x - start.x) * t,
        start.y + (end.y - start.y) * t
    };
}
