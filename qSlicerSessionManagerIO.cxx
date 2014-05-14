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
#include "qSlicerSessionManagerIO.h"

// Logic includes
#include "vtkSlicerSessionManagerLogic.h"

// MRML includes

// VTK includes
#include <vtkSmartPointer.h>

//-----------------------------------------------------------------------------
class qSlicerSessionManagerIOPrivate
{
public:
  vtkSmartPointer<vtkSlicerSessionManagerLogic> SessionManagerLogic;
};

//-----------------------------------------------------------------------------
qSlicerSessionManagerIO::qSlicerSessionManagerIO( vtkSlicerSessionManagerLogic* newSessionManagerLogic, QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerSessionManagerIOPrivate)
{
  this->setSessionManagerLogic( newSessionManagerLogic );
}

//-----------------------------------------------------------------------------
qSlicerSessionManagerIO::~qSlicerSessionManagerIO()
{
}

//-----------------------------------------------------------------------------
void qSlicerSessionManagerIO::setSessionManagerLogic(vtkSlicerSessionManagerLogic* newSessionManagerLogic)
{
  Q_D(qSlicerSessionManagerIO);
  d->SessionManagerLogic = newSessionManagerLogic;
}

//-----------------------------------------------------------------------------
vtkSlicerSessionManagerLogic* qSlicerSessionManagerIO::SessionManagerLogic() const
{
  Q_D(const qSlicerSessionManagerIO);
  return d->SessionManagerLogic;
}

//-----------------------------------------------------------------------------
QString qSlicerSessionManagerIO::description() const
{
  return "Transform Buffer";
}

//-----------------------------------------------------------------------------
qSlicerIO::IOFileType qSlicerSessionManagerIO::fileType() const
{
  return QString("Transform Buffer");
}

//-----------------------------------------------------------------------------
QStringList qSlicerSessionManagerIO::extensions() const
{
  return QStringList() << "Transform Buffer (*.xml)";
}

//-----------------------------------------------------------------------------
bool qSlicerSessionManagerIO::load(const IOProperties& properties)
{
  Q_D(qSlicerSessionManagerIO);
  Q_ASSERT( properties.contains("fileName") );
  QString fileName = properties["fileName"].toString();

  return true; // TODO: Check to see read was successful first
}
