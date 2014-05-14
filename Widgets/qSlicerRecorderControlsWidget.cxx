/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerRecorderControlsWidget.h"

#include <QtGui>


//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_CreateModels
class qSlicerRecorderControlsWidgetPrivate
  : public Ui_qSlicerRecorderControlsWidget
{
  Q_DECLARE_PUBLIC(qSlicerRecorderControlsWidget);
protected:
  qSlicerRecorderControlsWidget* const q_ptr;

public:
  qSlicerRecorderControlsWidgetPrivate( qSlicerRecorderControlsWidget& object);
  ~qSlicerRecorderControlsWidgetPrivate();
  virtual void setupUi(qSlicerRecorderControlsWidget*);
};

// --------------------------------------------------------------------------
qSlicerRecorderControlsWidgetPrivate
::qSlicerRecorderControlsWidgetPrivate( qSlicerRecorderControlsWidget& object) : q_ptr(&object)
{
}

qSlicerRecorderControlsWidgetPrivate
::~qSlicerRecorderControlsWidgetPrivate()
{
}


// --------------------------------------------------------------------------
void qSlicerRecorderControlsWidgetPrivate
::setupUi(qSlicerRecorderControlsWidget* widget)
{
  this->Ui_qSlicerRecorderControlsWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerRecorderControlsWidget methods

//-----------------------------------------------------------------------------
qSlicerRecorderControlsWidget
::qSlicerRecorderControlsWidget(QWidget* parentWidget) : Superclass( parentWidget ) , d_ptr( new qSlicerRecorderControlsWidgetPrivate(*this) )
{
}


qSlicerRecorderControlsWidget
::~qSlicerRecorderControlsWidget()
{
}


qSlicerRecorderControlsWidget* qSlicerRecorderControlsWidget
::New( qSlicerTransformBufferWidget* newBufferWidget )
{
  qSlicerRecorderControlsWidget* newRecorderControlsWidget = new qSlicerRecorderControlsWidget();
  newRecorderControlsWidget->BufferWidget = newBufferWidget;
  newRecorderControlsWidget->updatingCheckedTransforms = false;
  newRecorderControlsWidget->BufferStatus = newBufferWidget->BufferStatus;
  newRecorderControlsWidget->BufferActiveTransformsStatus = newBufferWidget->BufferActiveTransformsStatus;
  newRecorderControlsWidget->setup();
  return newRecorderControlsWidget;
}


void qSlicerRecorderControlsWidget
::setup()
{
  Q_D(qSlicerRecorderControlsWidget);

  d->setupUi(this);
  this->setMRMLScene( this->BufferWidget->SessionManagerLogic->GetMRMLScene() );

  connect( d->TransformCheckableComboBox, SIGNAL( checkedNodesChanged() ), this, SLOT( onCheckedTransformsChanged() ) );

  connect( d->StartButton, SIGNAL( clicked() ), this, SLOT( onStartButtonClicked() ) );
  connect( d->StopButton, SIGNAL( clicked() ), this, SLOT( onStopButtonClicked() ) );
  connect( d->ClearButton, SIGNAL( clicked() ), this, SLOT( onClearButtonClicked() ) );

  this->updateWidget();

  // GUI refresh: updates every 10ms
  QTimer *t = new QTimer( this );
  connect( t,  SIGNAL( timeout() ), this, SLOT( updateWidget() ) );
  t->start(10); 
}


void qSlicerRecorderControlsWidget
::enter()
{
}


void qSlicerRecorderControlsWidget
::onActiveTransformsUpdated()
{
  Q_D(qSlicerRecorderControlsWidget);

}


void qSlicerRecorderControlsWidget
::onCheckedTransformsChanged()
{
  Q_D(qSlicerRecorderControlsWidget);

  
}



void qSlicerRecorderControlsWidget
::onStartButtonClicked()
{
  Q_D(qSlicerRecorderControlsWidget);  
  
  // The observed transforms should be dealt with in the SessionManager logic
  
  
  this->updateWidget();
}


void qSlicerRecorderControlsWidget
::onStopButtonClicked()
{
  Q_D(qSlicerRecorderControlsWidget);  
  
  this->updateWidget();
}


void qSlicerRecorderControlsWidget
::onClearButtonClicked()
{
  Q_D(qSlicerRecorderControlsWidget);

  
  this->updateWidget();
}


void qSlicerRecorderControlsWidget
::updateWidget()
{
  Q_D(qSlicerRecorderControlsWidget);

  if ( this->BufferWidget->SessionManagerLogic == NULL )
  {
    return;
  }

 

  this->onActiveTransformsUpdated();
}
