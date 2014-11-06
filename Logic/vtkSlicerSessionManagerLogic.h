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

// .NAME vtkSlicerSessionManagerLogic - module logic class
// .SECTION Description
// This class manages the logic associated with authenticating users, and saving and loading sessions


#ifndef __vtkSlicerSessionManagerLogic_h
#define __vtkSlicerSessionManagerLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"
#include "vtkMRMLScene.h"
#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"

//QT include
#include <QString>
#include <QtSql>
#include <QStringList>

#include "vtkMRMLTrainingSessionNode.h"

#include "vtkSlicerSessionManagerModuleLogicExport.h"

/// \ingroup Slicer_QtModules_SessionManager
class VTK_SLICER_SESSIONMANAGER_MODULE_LOGIC_EXPORT vtkSlicerSessionManagerLogic :
  public vtkSlicerModuleLogic
{
public:
  vtkTypeMacro(vtkSlicerSessionManagerLogic,vtkSlicerModuleLogic);

  static vtkSlicerSessionManagerLogic *New();


protected:
  vtkSlicerSessionManagerLogic();
  virtual ~vtkSlicerSessionManagerLogic();

  
public:

  //getter function
  QStringList getFilenames();

  //logic functions
  bool createUser(QString databaseName, QString username, QString password);
  QString LoginUser(QString databaseName, QString username, QString password);
  QStringList getTraineeInformation(QString filepath, QString studyname);
  QString getStudyNameAndMakeDirectory(QString filepath);

  //other functions
  void setSessionNode(QString traineeID, QString studyname, int assignmentid);
  
  QString saveSession(QString traineeID, QString studyname, int assignmentid);

private:
	//void openDatabase(QString databasename);
    QStringList filenames; //list of study filenames
    
};

#endif

