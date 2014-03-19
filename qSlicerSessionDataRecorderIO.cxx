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

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// Qt includes

// SlicerQt includes
#include "qSlicerSessionDataRecorderIO.h"

// Logic includes
#include "vtkSlicerSessionDataRecorderLogic.h"

// MRML includes

// VTK includes
#include <vtkSmartPointer.h>

//-----------------------------------------------------------------------------
class qSlicerSessionDataRecorderIOPrivate
{
public:
  vtkSmartPointer<vtkSlicerSessionDataRecorderLogic> SessionDataRecorderLogic;
};

//-----------------------------------------------------------------------------
qSlicerSessionDataRecorderIO::qSlicerSessionDataRecorderIO( vtkSlicerSessionDataRecorderLogic* newSessionDataRecorderLogic, QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerSessionDataRecorderIOPrivate)
{
  this->setSessionDataRecorderLogic( newSessionDataRecorderLogic );
}

//-----------------------------------------------------------------------------
qSlicerSessionDataRecorderIO::~qSlicerSessionDataRecorderIO()
{
}

//-----------------------------------------------------------------------------
void qSlicerSessionDataRecorderIO::setSessionDataRecorderLogic(vtkSlicerSessionDataRecorderLogic* newSessionDataRecorderLogic)
{
  Q_D(qSlicerSessionDataRecorderIO);
  d->SessionDataRecorderLogic = newSessionDataRecorderLogic;
}

//-----------------------------------------------------------------------------
vtkSlicerSessionDataRecorderLogic* qSlicerSessionDataRecorderIO::SessionDataRecorderLogic() const
{
  Q_D(const qSlicerSessionDataRecorderIO);
  return d->SessionDataRecorderLogic;
}

//-----------------------------------------------------------------------------
QString qSlicerSessionDataRecorderIO::description() const
{
  return "Transform Buffer";
}

//-----------------------------------------------------------------------------
qSlicerIO::IOFileType qSlicerSessionDataRecorderIO::fileType() const
{
  return QString("Transform Buffer");
}

//-----------------------------------------------------------------------------
QStringList qSlicerSessionDataRecorderIO::extensions() const
{
  return QStringList() << "Transform Buffer (*.xml)";
}

//-----------------------------------------------------------------------------
bool qSlicerSessionDataRecorderIO::load(const IOProperties& properties)
{
  Q_D(qSlicerSessionDataRecorderIO);
  Q_ASSERT( properties.contains("fileName") );
  QString fileName = properties["fileName"].toString();
  
  vtkSmartPointer< vtkMRMLTransformBufferNode > importBufferNode;
  importBufferNode.TakeReference( vtkMRMLTransformBufferNode::SafeDownCast( this->mrmlScene()->CreateNodeByClass( "vtkMRMLTransformBufferNode" ) ) );
  importBufferNode->SetScene( this->mrmlScene() );
  this->mrmlScene()->AddNode( importBufferNode );
  d->SessionDataRecorderLogic->ImportFromFile( importBufferNode, fileName.toStdString() );

  return true; // TODO: Check to see read was successful first
}
