#include "GridBrushAction.h"

GridBrushAction::GridBrushAction(GridData& gridData, AbstractBrushAction* brushAction,
                                 StrokePoint point,
                                 GridDataChangedNotifier& gridDataChangedNotifier)
    : actualGrid_(gridData),
      brushAction_(brushAction),
      point_(point),
      gridDataChangedNotifier_(gridDataChangedNotifier)
{
}

MouseDownGridBrushAction::MouseDownGridBrushAction(GridData& gridData,
                                                   AbstractBrushAction* brushAction,
                                                   StrokePoint point,
                                                   GridDataChangedNotifier& gridDataChangedNotifier)
    : GridBrushAction(gridData, brushAction, point, gridDataChangedNotifier),
      initialGridState_(gridData)
{
}

bool MouseDownGridBrushAction::perform()
{
  DBG("");
  DBG("Mouse down");
  auto affectedPixels = brushAction_->startStroke(point_, actualGrid_);
  gridDataChangedNotifier_.callGridUpdatedListenersForPartialBrushStroke(affectedPixels);
  return true;
}

bool MouseDownGridBrushAction::undo()
{
  actualGrid_ = initialGridState_;
  gridDataChangedNotifier_.callGridUpdatedListeners();
  return true;
}

MouseDragGridBrushAction::MouseDragGridBrushAction(GridData& gridData,
                                                   AbstractBrushAction* brushAction,
                                                   StrokePoint point,
                                                   GridDataChangedNotifier& gridDataChangedNotifier)
    : GridBrushAction(gridData, brushAction, point, gridDataChangedNotifier)
{
}

bool MouseDragGridBrushAction::perform()
{
  auto affectedPixels = brushAction_->continueStroke(point_, actualGrid_);
  gridDataChangedNotifier_.callGridUpdatedListenersForPartialBrushStroke(affectedPixels);
  return true;
}

MouseUpGridBrushAction::MouseUpGridBrushAction(GridData& gridData, AbstractBrushAction* brushAction,
                                               StrokePoint point,
                                               GridDataChangedNotifier& gridDataChangedNotifier)
    : GridBrushAction(gridData, brushAction, point, gridDataChangedNotifier)
{
}

bool MouseUpGridBrushAction::perform()
{
  DBG("MouseUpGridBrushAction started");
  auto affectedPixels = brushAction_->continueStroke(point_, actualGrid_);
  gridDataChangedNotifier_.callGridUpdatedListenersForPartialBrushStroke(affectedPixels);
  DBG("MouseUpGridBrushAction partial brush stroke complete");
  auto allAffectedPixels = brushAction_->finishStroke();
  gridDataChangedNotifier_.callGridUpdatedListenersForCompleteBrushStroke(allAffectedPixels);
  DBG("MouseUpGridBrushAction finished");
  return true;
}