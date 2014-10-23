#include "vtkMRMLTrainingSessionNode.h"


vtkMRMLTrainingSessionNode* vtkMRMLTrainingSessionNode
::New()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance( "vtkMRMLTrainingSessionNode" );
  if( ret )
  {
    return ( vtkMRMLTrainingSessionNode* )ret;
  }
  // If the factory was unable to create the object, then create it here.
  return new vtkMRMLTrainingSessionNode;
}

//concstructor
vtkMRMLTrainingSessionNode
::vtkMRMLTrainingSessionNode()
{
  this->HideFromEditorsOff();
  this->SetSaveWithScene( true );
  this->Modified();
}


vtkMRMLTrainingSessionNode
::~vtkMRMLTrainingSessionNode()
{
}


vtkMRMLNode* vtkMRMLTrainingSessionNode
::CreateNodeInstance()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance( "vtkMRMLTrainingSessionNode" );
  if( ret )
  {
    return ( vtkMRMLTrainingSessionNode* )ret;
  }
  // If the factory was unable to create the object, then create it here.
  return new vtkMRMLTrainingSessionNode;
}

void vtkMRMLTrainingSessionNode
::PrintSelf( ostream& os, vtkIndent indent )
{
  vtkMRMLNode::PrintSelf(os,indent); // This will take care of referenced nodes

  os << indent << "NODE NAME: " << this->GetName() << std::endl;
}

void vtkMRMLTrainingSessionNode
::ReadXMLAttributes( const char** atts )
{
}

void vtkMRMLTrainingSessionNode
::WriteXML( ostream& of, int indent )
{
}

void vtkMRMLTrainingSessionNode
::Copy( vtkMRMLNode *node )
{
}

