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
  Superclass::SetAttribute("TraineeID", trainee.c_str());
  //trainee_id = trainee;
}
void vtkMRMLTrainingSessionNode
::setStudyName(std::string study){
  Superclass::SetAttribute("Study Name", study.c_str());
  //study_name = study;
}

void vtkMRMLTrainingSessionNode::setAssignmentID(std::string assignment){
  Superclass::SetAttribute("AssignmentID", assignment.c_str());
  //assignment_id = assignment;
}

void vtkMRMLTrainingSessionNode::setSessionStatus(std::string sessionstatus){
  Superclass::SetAttribute("Status", sessionstatus.c_str());
}

void vtkMRMLTrainingSessionNode::setComments(std::string comments){
  Superclass::SetAttribute("Comments", comments.c_str());
}



//GET methods
std::string vtkMRMLTrainingSessionNode::getTraineeID(){
  return std::string(Superclass::GetAttribute("TraineeID"));
  //return trainee_id;
}

std::string vtkMRMLTrainingSessionNode::getStudyName(){
  return std::string(Superclass::GetAttribute("Study Name"));
  //return study_name;
}

std::string vtkMRMLTrainingSessionNode::getAssignmentID(){
  return std::string(Superclass::GetAttribute("AssignmentID"));
  //return assignment_id;
}

std::string vtkMRMLTrainingSessionNode::getSessionStatus(){
  return std::string(Superclass::GetAttribute("Status"));
}

std::string vtkMRMLTrainingSessionNode::getComments(){
  return std::string(Superclass::GetAttribute("Comments"));
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

void vtkMRMLTrainingSessionNode::PrintSelf( ostream& os, vtkIndent indent ) /*TO DO: print all attributes*/
{
  vtkMRMLNode::PrintSelf(os,indent); // This will take care of referenced nodes

  os << indent << "NODE NAME: " << this->GetName() << std::endl;
}


void vtkMRMLTrainingSessionNode::ReadXMLAttributes( const char** atts )
{
  Superclass::ReadXMLAttributes(atts);

  /*
  const char* attName;
  const char* attValue;

  while(*atts !=NULL)
  {
    attName = *(atts++);
    attValue = *(atts++);

    if(!strcmp(attName, "StudyName"))
    {
      this->study_name = std::string(attValue);
    }
    if(!strcmp(attName, "TraineeID"))
    {
      this->trainee_id = std::string(attValue);
    }
    if(!strcmp(attName, "AssignmentID"))
    {
      this->assignment_id = attValue;
    }
  }
  */
  this->Modified();
}

void vtkMRMLTrainingSessionNode::WriteXML( ostream& of, int nIndent )
{
  Superclass::WriteXML(of, nIndent); 
/*
  vtkIndent indent(nIndent);
  
  of << indent << " StudyName=\"" << this->study_name << "\"";
  of << indent << " TraineeID=\"" << this->trainee_id << "\"";
  of << indent << " AssignmentID=\"" << this->assignment_id << "\"";
  */
}

void vtkMRMLTrainingSessionNode::Copy( vtkMRMLNode *anode )
{
  Superclass::Copy(anode ); // This will take care of referenced nodes

  /*
  vtkMRMLTrainingSessionNode *node = ( vtkMRMLTrainingSessionNode* ) anode;
  
  // Anything we want in the MRML file we must copy here
  this->Modified();

  this->study_name = node->study_name;
  this->trainee_id = node->trainee_id;
  this->assignment_id = node->assignment_id;
*/
  this->Modified();

}

void vtkMRMLTrainingSessionNode::SetSingletonTag(const char * c)
{
  vtkMRMLNode::SetSingletonTag(c);
}

