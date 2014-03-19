/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// Qt includes
#include <QtPlugin>

// SessionDataRecorder Logic includes
#include <vtkSlicerSessionDataRecorderLogic.h>

// SessionDataRecorder includes
#include "qSlicerSessionDataRecorderModule.h"
#include "qSlicerSessionDataRecorderModuleWidget.h"
#include "qSlicerSessionDataRecorderIO.h"

// Slicer includes
#include "qSlicerNodeWriter.h"
#include "qSlicerCoreIOManager.h"
#include "qSlicerCoreApplication.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerSessionDataRecorderModule, qSlicerSessionDataRecorderModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_SessionDataRecorder
class qSlicerSessionDataRecorderModulePrivate
{
public:
  qSlicerSessionDataRecorderModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerSessionDataRecorderModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerSessionDataRecorderModulePrivate::qSlicerSessionDataRecorderModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerSessionDataRecorderModule methods

//-----------------------------------------------------------------------------
qSlicerSessionDataRecorderModule::qSlicerSessionDataRecorderModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerSessionDataRecorderModulePrivate)
{
}

//-----------------------------------------------------------------------------
QString qSlicerSessionDataRecorderModule::category()const
{
  // return "Developer Tools";
  return "";
}

//-----------------------------------------------------------------------------

QStringList qSlicerSessionDataRecorderModule::categories() const
{
  return QStringList() << "Perk Tutor";
}
//-----------------------------------------------------------------------------
qSlicerSessionDataRecorderModule::~qSlicerSessionDataRecorderModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerSessionDataRecorderModule::helpText()const
{
  return "The purpose of the Session Data Recorder module is to record and save tool trajectories associated with needle-based interventions. For help on how to use this module visit: <a href='http://www.perktutor.org/'>PerkTutor</a>.";
}

//-----------------------------------------------------------------------------
QString qSlicerSessionDataRecorderModule::acknowledgementText()const
{
  return "This work was was funded by Cancer Care Ontario and the Ontario Consortium for Adaptive Interventions in Radiation Oncology (OCAIRO)";
}


//-----------------------------------------------------------------------------
QStringList qSlicerSessionDataRecorderModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Nisrin Abou-Seido (Queen's University)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerSessionDataRecorderModule::icon()const
{
  return QIcon(":/Icons/SessionDataRecorder.png");
}

//-----------------------------------------------------------------------------
void qSlicerSessionDataRecorderModule::setup()
{
  this->Superclass::setup();

  qSlicerCoreApplication* app = qSlicerCoreApplication::application();
  vtkSlicerSessionDataRecorderLogic* SessionDataRecorderLogic = vtkSlicerSessionDataRecorderLogic::SafeDownCast( this->logic() );
  
  // Register the IO
  app->coreIOManager()->registerIO( new qSlicerSessionDataRecorderIO( SessionDataRecorderLogic, this ) );
  app->coreIOManager()->registerIO( new qSlicerNodeWriter( "SessionDataRecorder", QString( "TransformBuffer" ), QStringList() << "vtkMRMLTransformBufferNode", this ) );
 
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerSessionDataRecorderModule::createWidgetRepresentation()
{
  return new qSlicerSessionDataRecorderModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerSessionDataRecorderModule::createLogic()
{
  return vtkSlicerSessionDataRecorderLogic::New();
}


