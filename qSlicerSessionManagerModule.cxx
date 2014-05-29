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

// SessionManager Logic includes
#include <vtkSlicerSessionManagerLogic.h>

// SessionManager includes
#include "qSlicerSessionManagerModule.h"
#include "qSlicerSessionManagerModuleWidget.h"
#include "qSlicerSessionManagerIO.h"

// Slicer includes
#include "qSlicerNodeWriter.h"
#include "qSlicerCoreIOManager.h"
#include "qSlicerCoreApplication.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerSessionManagerModule, qSlicerSessionManagerModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_SessionManager
class qSlicerSessionManagerModulePrivate
{
public:
  qSlicerSessionManagerModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerSessionManagerModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerSessionManagerModulePrivate::qSlicerSessionManagerModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerSessionManagerModule methods

//-----------------------------------------------------------------------------
qSlicerSessionManagerModule::qSlicerSessionManagerModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerSessionManagerModulePrivate)
{
}

//-----------------------------------------------------------------------------
QString qSlicerSessionManagerModule::category()const
{
  // return "Developer Tools";
  return "";
}

//-----------------------------------------------------------------------------

QStringList qSlicerSessionManagerModule::categories() const
{
  return QStringList() << "Perk Tutor";
}
//-----------------------------------------------------------------------------
qSlicerSessionManagerModule::~qSlicerSessionManagerModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerSessionManagerModule::helpText()const
{
  return "The purpose of the Session Manager module is to allow users to load a Session through authenticationn and associating a Slicer session with a user.";
}

//-----------------------------------------------------------------------------
QString qSlicerSessionManagerModule::acknowledgementText()const
{
  return "This work was was funded by Cancer Care Ontario and the Ontario Consortium for Adaptive Interventions in Radiation Oncology (OCAIRO)";
}


//-----------------------------------------------------------------------------
QStringList qSlicerSessionManagerModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Nisrin Abou-Seido (Queen's University)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerSessionManagerModule::icon()const
{
  return QIcon(":/Icons/SessionManager.png");
}

//-----------------------------------------------------------------------------
void qSlicerSessionManagerModule::setup()
{
  this->Superclass::setup();

  qSlicerCoreApplication* app = qSlicerCoreApplication::application();
  vtkSlicerSessionManagerLogic* SessionManagerLogic = vtkSlicerSessionManagerLogic::SafeDownCast( this->logic() );
  
  // Register the IO
  app->coreIOManager()->registerIO( new qSlicerSessionManagerIO( SessionManagerLogic, this ) );

 
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerSessionManagerModule::createWidgetRepresentation()
{
  return new qSlicerSessionManagerModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerSessionManagerModule::createLogic()
{
  return vtkSlicerSessionManagerLogic::New();
}


