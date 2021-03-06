#ifndef GRIDDATACHANGEDNOTIFIER_H_INCLUDED
#define GRIDDATACHANGEDNOTIFIER_H_INCLUDED

#include "JuceHeader.h"

#include "GridPoint.h"

class GridDataChangedNotifier
{
 public:
  GridDataChangedNotifier() = default;

  class GridDataResizedListener
  {
   public:
    virtual void gridDataResizedCallback() = 0;
    virtual ~GridDataResizedListener() {}
  };

  class GridDataUpdatedListener
  {
   public:
    virtual void entireGridDataUpdatedCallback() = 0;
    virtual void partialBrushStrokeCallback(const Array<GridPoint>& affectedPoints) = 0;
    virtual void completeBrushStrokeCallback(const Array<GridPoint>& affectedPoints) = 0;
    virtual ~GridDataUpdatedListener() {}
  };

  void addGridDataResizedListener(GridDataResizedListener* listener);
  void removeGridDataResizedListener(GridDataResizedListener* listener);
  void callGridResizedListeners();

  void addGridDataUpdatedListener(GridDataUpdatedListener* listener);
  void removeGridDataUpdatedListener(GridDataUpdatedListener* listener);
  void callGridUpdatedListeners();
  void callGridUpdatedListenersForPartialBrushStroke(const Array<GridPoint>& affectedPoints);
  void callGridUpdatedListenersForCompleteBrushStroke(const Array<GridPoint>& affectedPoints);

 private:
  ListenerList<GridDataResizedListener> gridDataResizedListeners_;
  ListenerList<GridDataUpdatedListener> gridDataUpdatedListeners_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridDataChangedNotifier);
};

#endif  // GRIDDATACHANGEDNOTIFIER_H_INCLUDED
