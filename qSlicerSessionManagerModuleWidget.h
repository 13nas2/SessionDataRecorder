
#ifndef __qSlicerSessionManagerModuleWidget_h
#define __qSlicerSessionManagerModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"
#include <QtGui>
#include "qSlicerSessionManagerModuleExport.h"
#include "qSlicerTransformBufferWidget.h"
#include "qSlicerMessagesWidget.h"
#include "qSlicerRecorderControlsWidget.h"


class qSlicerSessionManagerModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLSessionManagerNode;


/// \ingroup Slicer_QtModules_SessionManager
class Q_SLICER_QTMODULES_SESSIONMANAGER_EXPORT qSlicerSessionManagerModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerSessionManagerModuleWidget(QWidget *parent=0);
  virtual ~qSlicerSessionManagerModuleWidget();

  // This widget will keep track if the buffer is changed
  //unsigned long BufferStatus;
  // These quantities might be repeated by different buffers, so we still need the above
  //unsigned long BufferTransformsStatus;
  //unsigned long BufferMessagesStatus;
  
protected:
  QScopedPointer<qSlicerSessionManagerModuleWidgetPrivate> d_ptr;
  
  virtual void setup();
  virtual void enter();

  void loadSessionSetup();

protected slots:

  void updateWidget();
  void updateFromMRMLNode();

  void onCreateTraineeButtonClicked();
  void onCreateUserButtonClicked();
  void onLoginButtonClicked();
  void onSaveSceneButtonClicked();
  //void onLogoutButtonClicked();
  void onBrowseButtonClicked();
  void onOKLoadButtonClicked();
  void onFindFilesButtonClicked();
  void onLoadScenesButtonClicked();

private:
  Q_DECLARE_PRIVATE(qSlicerSessionManagerModuleWidget);
  Q_DISABLE_COPY(qSlicerSessionManagerModuleWidget);

  bool selectionsInitialized;
};

#endif
