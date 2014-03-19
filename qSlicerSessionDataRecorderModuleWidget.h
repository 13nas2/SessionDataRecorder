
#ifndef __qSlicerSessionDataRecorderModuleWidget_h
#define __qSlicerSessionDataRecorderModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"
#include <QtGui>
#include "qSlicerSessionDataRecorderModuleExport.h"
#include "qSlicerTransformBufferWidget.h"
#include "qSlicerMessagesWidget.h"
#include "qSlicerRecorderControlsWidget.h"


class qSlicerSessionDataRecorderModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLSessionDataRecorderNode;


/// \ingroup Slicer_QtModules_SessionDataRecorder
class Q_SLICER_QTMODULES_SESSIONDATARECORDER_EXPORT qSlicerSessionDataRecorderModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerSessionDataRecorderModuleWidget(QWidget *parent=0);
  virtual ~qSlicerSessionDataRecorderModuleWidget();

  // This widget will keep track if the buffer is changed
  unsigned long BufferStatus;
  // These quantities might be repeated by different buffers, so we still need the above
  unsigned long BufferTransformsStatus;
  unsigned long BufferMessagesStatus;
  
protected:
  QScopedPointer<qSlicerSessionDataRecorderModuleWidgetPrivate> d_ptr;
  
  virtual void setup();
  virtual void enter();

protected slots:

  void updateWidget();
  void onSaveButtonClicked();
  void onCreateButtonClicked();
  void onLoginButtonClicked(); 
  void onOKButtonClicked();
  void onSaveSceneButtonClicked();

private:
  Q_DECLARE_PRIVATE(qSlicerSessionDataRecorderModuleWidget);
  Q_DISABLE_COPY(qSlicerSessionDataRecorderModuleWidget);

  bool selectionsInitialized;
};

#endif
