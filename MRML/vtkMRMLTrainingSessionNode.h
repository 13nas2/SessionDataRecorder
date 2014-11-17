#ifndef __vtkMRMLTrainingSessionNode_h
#define __vtkMRMLTrainingSessionNode_h

#include <ctime>
#include <iostream>
#include <utility>
#include <vector>
#include "vtkMRMLNode.h"
#include "vtkMRMLScene.h"
#include "vtkObject.h"
#include "vtkObjectBase.h"
#include "vtkObjectFactory.h"

// SessionManager includes
#include "vtkSlicerSessionManagerModuleMRMLExport.h"

class VTK_SLICER_SESSIONMANAGER_MODULE_MRML_EXPORT vtkMRMLTrainingSessionNode: public vtkMRMLNode
{
public:
  vtkTypeMacro( vtkMRMLTrainingSessionNode, vtkMRMLNode );

  // Standard MRML node methods
  static vtkMRMLTrainingSessionNode *New();
  virtual vtkMRMLNode* CreateNodeInstance();
  virtual const char* GetNodeTagName() { return "TrainingSession"; };
  void PrintSelf( ostream& os, vtkIndent indent );
  virtual void ReadXMLAttributes( const char** atts );
  virtual void WriteXML( ostream& of, int indent );
  virtual void Copy( vtkMRMLNode *node );

  virtual void 	SetSingletonTag (const char *c);

  //TrainingSession Get/Set Methods
  void setTraineeID(std::string trainee);
  void setStudyName(std::string study);
  void setAssignmentID(std::string assignmentid);

  std::string getTraineeID();
  std::string getStudyName();
  std::string getAssignmentID();
 
private:
  std::string trainee_id;
  std::string study_name;
  std::string assignment_id;

protected:
  // Constructor/ destructor methods
  vtkMRMLTrainingSessionNode();
  virtual ~vtkMRMLTrainingSessionNode();
  vtkMRMLTrainingSessionNode ( const vtkMRMLTrainingSessionNode& );
  void operator=( const vtkMRMLTrainingSessionNode& );
};

#endif