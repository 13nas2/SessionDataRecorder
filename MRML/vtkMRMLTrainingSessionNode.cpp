#include "vtkMRMLTrainingSessionNode.h"

vtkMRMLTrainingSessionNode* vtkMRMLTrainingSessionNode::New()
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

//constructor
vtkMRMLTrainingSessionNode::vtkMRMLTrainingSessionNode()
{
  this->HideFromEditorsOff();
  this->SetSaveWithScene( true );
  this->Modified();

  this->SetSingletonTag("Singleton");
}

//destructor
vtkMRMLTrainingSessionNode::~vtkMRMLTrainingSessionNode(){
 
}

//SET methods
void vtkMRMLTrainingSessionNode::setTraineeID(std::string trainee){ 
  trainee_id = trainee;
}
void vtkMRMLTrainingSessionNode
::setStudyName(std::string study){
  study_name = study;
}

void vtkMRMLTrainingSessionNode::setAssignmentID(int assignment){
  assignment_id = assignment;
}

//GET methods
std::string vtkMRMLTrainingSessionNode::getTraineeID(){
  return trainee_id;
}

std::string vtkMRMLTrainingSessionNode::getStudyName(){
  return study_name;
}

int vtkMRMLTrainingSessionNode::getAssignmentID(){
  return assignment_id;
}


vtkMRMLNode* vtkMRMLTrainingSessionNode::CreateNodeInstance()
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

void vtkMRMLTrainingSessionNode::PrintSelf( ostream& os, vtkIndent indent )
{
  vtkMRMLNode::PrintSelf(os,indent); // This will take care of referenced nodes

  os << indent << "NODE NAME: " << this->GetName() << std::endl;
}

void vtkMRMLTrainingSessionNode::ReadXMLAttributes( const char** atts )
{
}

void vtkMRMLTrainingSessionNode::WriteXML( ostream& of, int indent )
{
}

void vtkMRMLTrainingSessionNode::Copy( vtkMRMLNode *node )
{
}

void vtkMRMLTrainingSessionNode::SetSingletonTag(const char * c)
{
  vtkMRMLNode::SetSingletonTag(c);
}

