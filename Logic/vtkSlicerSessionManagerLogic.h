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

// .NAME vtkSlicerSessionManagerLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerSessionManagerLogic_h
#define __vtkSlicerSessionManagerLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"
#include "vtkMRML.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLScene.h"
#include "vtkObjectFactory.h"

#include "vtkSmartPointer.h"

// MRML includes
// class vtkMRMLIGTLConnectorNode;
class vtkMRMLViewNode;
// STD includes
#include <cstdlib>

#include "vtkSlicerSessionManagerModuleLogicExport.h"



/// \ingroup Slicer_QtModules_SessionManager
class VTK_SLICER_SESSIONMANAGER_MODULE_LOGIC_EXPORT vtkSlicerSessionManagerLogic :
  public vtkSlicerModuleLogic
{
public:
  vtkTypeMacro(vtkSlicerSessionManagerLogic,vtkSlicerModuleLogic);

  static vtkSlicerSessionManagerLogic *New();

  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkSlicerSessionManagerLogic();
  virtual ~vtkSlicerSessionManagerLogic();

  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);
  
public:
  /// Initialize listening to MRML events
  void InitializeEventListeners();

  void ProcessMRMLNodesEvents( vtkObject* caller, unsigned long event, void* callData );
  

  
private:

  vtkSlicerSessionManagerLogic(const vtkSlicerSessionManagerLogic&); // Not implemented
  void operator=(const vtkSlicerSessionManagerLogic&);               // Not implemented
  // Reference to the module MRML node.

  double Clock0;

};

#endif

