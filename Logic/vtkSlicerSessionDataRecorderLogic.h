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

// .NAME vtkSlicerSessionDataRecorderLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerSessionDataRecorderLogic_h
#define __vtkSlicerSessionDataRecorderLogic_h

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

#include "vtkSlicerSessionDataRecorderModuleLogicExport.h"



/// \ingroup Slicer_QtModules_SessionDataRecorder
class VTK_SLICER_SESSIONDATARECORDER_MODULE_LOGIC_EXPORT vtkSlicerSessionDataRecorderLogic :
  public vtkSlicerModuleLogic
{
public:
  vtkTypeMacro(vtkSlicerSessionDataRecorderLogic,vtkSlicerModuleLogic);

  static vtkSlicerSessionDataRecorderLogic *New();

  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkSlicerSessionDataRecorderLogic();
  virtual ~vtkSlicerSessionDataRecorderLogic();

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

  vtkSlicerSessionDataRecorderLogic(const vtkSlicerSessionDataRecorderLogic&); // Not implemented
  void operator=(const vtkSlicerSessionDataRecorderLogic&);               // Not implemented
  // Reference to the module MRML node.

  double Clock0;

};

#endif

