#ifndef COMBBRUSH_H_INCLUDED
#define COMBBRUSH_H_INCLUDED

#include "JuceHeader.h"

#include "BasicBrushBase.h"

class CombBrush : public BasicBrushBase
{
public:
    CombBrush();

    void drawPreviewInto(Graphics& g, const Rectangle<int>& bounds) const override;

protected:
    Array<GridPoint> applyBrushToPoint(GridPoint p, GridData& gridData) const override;

    double numberHarmonics_;
    double evenIntensity_;
    double oddIntensity_;
    double taper_;
    double spacing_;
};

#endif // COMBBRUSH_H_INCLUDED