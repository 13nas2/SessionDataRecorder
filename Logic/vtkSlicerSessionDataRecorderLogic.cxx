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

// SessionDataRecorder includes
#include "vtkSlicerSessionDataRecorderLogic.h"


// MRML includes
// #include "vtkMRMLIGTLConnectorNode.h"
#include "vtkMRMLViewNode.h"

// VTK includes
#include <vtkNew.h>

// STD includes
#include <cassert>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerSessionDataRecorderLogic);

//----------------------------------------------------------------------------
vtkSlicerSessionDataRecorderLogic::vtkSlicerSessionDataRecorderLogic()
{
}

//----------------------------------------------------------------------------
vtkSlicerSessionDataRecorderLogic::~vtkSlicerSessionDataRecorderLogic()
{
}



void vtkSlicerSessionDataRecorderLogic::PrintSelf(ostream& os, vtkIndent indent)
{
}



void vtkSlicerSessionDataRecorderLogic::InitializeEventListeners()
{

}



void vtkSlicerSessionDataRecorderLogic::RegisterNodes()
{
  if( ! this->GetMRMLScene() )
  {
    return;
  }

}



void vtkSlicerSessionDataRecorderLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}



void vtkSlicerSessionDataRecorderLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
  assert(this->GetMRMLScene() != 0);
}


void vtkSlicerSessionDataRecorderLogic
::ProcessMRMLNodesEvents( vtkObject* caller, unsigned long event, void* callData )
{
  

}


void vtkSlicerSessionDataRecorderLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
  assert(this->GetMRMLScene() != 0);
}
