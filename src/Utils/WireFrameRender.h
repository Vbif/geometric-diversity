#pragma once

#include "stdafx.h"

namespace Render {

void DrawWireframeRect(const FRect& rect, float width);
void DrawWireframeLine(const FPoint& x0, const FPoint& x1, float width);
};
