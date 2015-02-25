

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
#include <iostream>
// Qt includes

// SlicerQt includes
#include "qSlicerSessionManagerModuleWidget.h"
#include "ui_qSlicerSessionManagerModule.h"
#include <QtGui>

#include <QtDebug>

// MRMLWidgets includes
#include <qMRMLUtils.h>

#include "vtkSlicerSessionManagerLogic.h"
//#include "vtkMRMLLinearTransformNode.h"

//#include "qMRMLNodeComboBox.h"
//#include "vtkMRMLViewNode.h"
#include "vtkSlicerSessionManagerLogic.h"

//#include <sqlite3.h>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

//include Slicer code
#include <qSlicerSaveDataDialog.h>
//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_SessionManager
class qSlicerSessionManagerModuleWidgetPrivate: public Ui_qSlicerSessionManagerModule
{
  Q_DECLARE_PUBLIC( qSlicerSessionManagerModuleWidget );

protected:
  qSlicerSessionManagerModuleWidget* const q_ptr;
public:
  qSlicerSessionManagerModuleWidgetPrivate( qSlicerSessionManagerModuleWidget& object );
  ~qSlicerSessionManagerModuleWidgetPrivate();

  vtkSlicerSessionManagerLogic* logic() const;

private:
	vtkSlicerSessionManagerLogic *SessionManagerLogic;

  // Add embedded widgets here
  //qSlicerMessagesWidget* MessagesWidget;
};

//-----------------------------------------------------------------------------
// qSlicerSessionManagerModuleWidgetPrivate methods

qSlicerSessionManagerModuleWidgetPrivate::qSlicerSessionManagerModuleWidgetPrivate( qSlicerSessionManagerModuleWidget& object ): q_ptr(&object)
{
}

//-----------------------------------------------------------------------------

qSlicerSessionManagerModuleWidgetPrivate::~qSlicerSessionManagerModuleWidgetPrivate()
{
}

vtkSlicerSessionManagerLogic* qSlicerSessionManagerModuleWidgetPrivate::logic() const
{
  Q_Q( const qSlicerSessionManagerModuleWidget );
  return vtkSlicerSessionManagerLogic::SafeDownCast( q->logic() );
}


//---------------------------------------------------------------------------
// qSlicerSessionManagerModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerSessionManagerModuleWidget::qSlicerSessionManagerModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerSessionManagerModuleWidgetPrivate( *this ) )
{
}


qSlicerSessionManagerModuleWidget::~qSlicerSessionManagerModuleWidget()
{
}

void qSlicerSessionManagerModuleWidget::setup()
{
  Q_D(qSlicerSessionManagerModuleWidget);

  d->setupUi(this);

  d->SessionManagerLogic = d->logic();

  // If adding widgets, embed widgets here: eg: //d->TransformBufferWidget = qSlicerTransformBufferWidget::New( d->logic() );
  this->Superclass::setup();

  // GUI refresh: updates every 10ms
  QTimer *t = new QTimer( this );
  connect( t, SIGNAL( timeout() ), this, SLOT( updateWidget() ) );
  t->start(10);

  //connect buttons
  //connect(d->pushButtonCreateTrainee, SIGNAL( clicked() ), this, SLOT( onCreateTraineeButtonClicked() ) );
  //connect(d->pushButtonCreateUser, SIGNAL( clicked() ), this, SLOT( onCreateUserButtonClicked() ) );

  //connect(d->pushButtonLogin, SIGNAL( clicked() ), this, SLOT( onLoginButtonClicked() ) );
 
  //connect(d->pushButtonLogout, SIGNAL(clicked()), this, SLOT( onLogoutButtonClicked()) );

  //connect(d->saveSceneButton, SIGNAL(clicked()), this, SLOT( onSaveSceneButtonClicked()) );
  
  connect(d->pushButtonBrowse, SIGNAL(clicked()), this, SLOT( onBrowseButtonClicked()) );
  connect(d->pushButtonOKLoad, SIGNAL(clicked()), this, SLOT( onOKLoadButtonClicked()) );
  connect(d->pushButtonSaveSessionData, SIGNAL(clicked()), this, SLOT( onSaveSceneButtonClicked()) );

  connect(d->pushButtonFindFiles, SIGNAL(clicked()), this, SLOT (onFindFilesButtonClicked()) );
  
  connect(d->pushButtonLoadScenes, SIGNAL(clicked()), this, SLOT (onLoadScenesButtonClicked()));

  connect(d->pushButtonBrowseSourceDir, SIGNAL(clicked()), this, SLOT (onSourceBrowseButtonClicked()));


  //show groupBoxes
  d->groupBox->show();

}

/*
void qSlicerSessionManagerModuleWidget::onLogoutButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );
  d->groupBoxAuthentication->show();
  d->pushButtonLogin->setEnabled(true);

  //hide everything except login fields
  d->groupBox->hide();
  d->groupBoxTraineeData->hide();
  d->groupBox_loadSession->hide();
}
*/

void qSlicerSessionManagerModuleWidget::loadSessionSetup()//may be unnecessary
{
  Q_D( qSlicerSessionManagerModuleWidget );

  //populate the combo box with student IDs in the database
  //need to open database, check for sessions table, get records with unique user id field.
}

void qSlicerSessionManagerModuleWidget
::updateWidget()
{
  Q_D( qSlicerSessionManagerModuleWidget );
}

void qSlicerSessionManagerModuleWidget
::updateFromMRMLNode()
{
  Q_D( qSlicerSessionManagerModuleWidget );
}


void qSlicerSessionManagerModuleWidget::enter()
{
  this->Superclass::enter();
  this->updateWidget(); 

  // Create a node by default if none already exists
  int numTrainingSessionNodes = this->mrmlScene()->GetNumberOfNodesByClass( "vtkMRMLTrainingSessionNode" );

  if ( numTrainingSessionNodes == 0 )
  {
     vtkMRMLTrainingSessionNode* trainingSessionNode;
     trainingSessionNode = vtkMRMLTrainingSessionNode::New();
     this->mrmlScene()->RegisterNodeClass( trainingSessionNode );
     //TrainingSessionNode.TakeReference( this->mrmlScene()->CreateNodeByClass( "vtkMRMLTrainingSessionNode" ) );

     trainingSessionNode->SetSaveWithScene(true);
     trainingSessionNode->SetName("Training Session Data");
    
     trainingSessionNode->SetScene( this->mrmlScene() );
     this->mrmlScene()->AddNode( trainingSessionNode );
    // TrainingSessionNode = NULL;
     trainingSessionNode->Delete();

  }
  else
  {
    this->updateFromMRMLNode();
  }
}

//pushButtonOKLoad
void qSlicerSessionManagerModuleWidget
::onOKLoadButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );
  QString filepath = d->lineEdit_filename->text();

  //d->lineEdit_filename->clear();
  //d->label_output->setText(filepath);

  QString studyname = d->SessionManagerLogic->getStudyNameAndMakeDirectory(filepath);
  QStringList filenames = d->SessionManagerLogic->getFilenames();
  filenames.removeDuplicates();
  d->ComboBoxStudyNames->clear();
  d->ComboBoxStudyNames_2->clear();
  d->ComboBoxStudyNames->addItems(filenames);
  d->ComboBoxStudyNames_2->addItems(filenames);
  //QMessageBox::information(0, "Created/Updated Study Directory:\n", QDir::homePath() + "/Study-" + studyname);
  QStringList studentlist = d->SessionManagerLogic->getTraineeInformation(filepath, studyname);
  d->ComboBoxTrainees->addItems(studentlist);
  d->ComboBoxTrainees_2->addItems(studentlist);

  QString s = d->ComboBox_Mode->currentText();
  if (s.contains("Save"))
  {
    d->SaveCollapsibleButton->setCollapsed(false);
    d->LoadSessionCollapsibleButton->setCollapsed(true);
  }
  else
  {
    d->LoadSessionCollapsibleButton->setCollapsed(false);
    d->SaveCollapsibleButton->setCollapsed(true);
  }
}

void qSlicerSessionManagerModuleWidget
::onBrowseButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );

  //use QFileDialog to allow user to select the csv file
  QString filepath = QFileDialog::getOpenFileName(this,tr("Open Moodle CSV"), QDir::homePath(), tr("CSV files (*.csv)"));
  d->lineEdit_filename->setText(filepath);
}

void qSlicerSessionManagerModuleWidget
::onSourceBrowseButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );

  //use QFileDialog to allow user to select the directory for extra files
  QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),QDir::homePath(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
  d->lineEdit_directory->setText(dir);
}

void qSlicerSessionManagerModuleWidget
::onSaveSceneButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );

  QString studyname = d->ComboBoxStudyNames->currentText();
  QString trainee_info = d->ComboBoxTrainees->currentText();
  QString status = d->buttonGroupStatus->checkedButton()->text();
  QString comments = d->plainTextEditComments->toPlainText();
  QString externalpath = d->lineEdit_directory->text();

  QString savepath = d->SessionManagerLogic->saveSession(studyname, trainee_info, status, comments, externalpath);
  QMessageBox::StandardButton button = QMessageBox::information(0, "Confirm Save As ", savepath, QMessageBox::Ok, QMessageBox::Cancel);
  if(button == QMessageBox::Ok)
  {
    d->SessionManagerLogic->saveSessionConfirmed(savepath);
    QMessageBox::information(0, "Save successful to ", savepath);
  }
}

void qSlicerSessionManagerModuleWidget
::onFindFilesButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );

  QString studyname = d->ComboBoxStudyNames_2->currentText();
  QString trainee_info = d->ComboBoxTrainees_2->currentText();

  d->listWidgetScenes->clear();
  QStringList list = d->SessionManagerLogic->getFilePaths(studyname, trainee_info);
  //check if the item has already been added to the list
  //
  d->listWidgetScenes->insertItems(0, list);
  
  updateWidget();
}

void qSlicerSessionManagerModuleWidget
::onLoadScenesButtonClicked() /* loads the scenes associated with the selected user and study*/
{
  Q_D( qSlicerSessionManagerModuleWidget);

  //get the contents of the listWidget and open each file.
  QList< QListWidgetItem * > items = d->listWidgetScenes->selectedItems();
  
  QStringList filenames;
  foreach(QListWidgetItem* item, items)
  {
    filenames << item->text();
  } 

  QString file = d->listWidgetScenes->currentItem()->text();
  bool success = d->SessionManagerLogic->loadFile(file);
  if(!success)
    QMessageBox::information(0, "Cannot open the given files", "Error opening files");
}

/*TO DO: remove this code or update so it does not use local db*/
void qSlicerSessionManagerModuleWidget
::onCreateUserButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget);
/*
  bool createdNew;
  createdNew = d->SessionManagerLogic->createUser("PerkTutorSessions.db", d->lineEditUsername->text(), d->lineEditPassword->text());
  if(createdNew == true) //successfully created user
  {
    //clear user entry fields
    d->lineEditUsername->setText("");
    d->lineEditPassword->setText("");
    d->lineEditUsername->setFocus();
  }
  else //user already exists ///MAYBE: ask the user to enter the password again to login?
  {
    QMessageBox::information(0, "Cannot create user", "Error: This username already exists in this database.");
  }
  */
}

/*
TO DO: remove this code or update so it does not use local database?
Purpose: Triggered when user clicks Login. Calls a function to check if user/password combination exists in the database.
*/
void qSlicerSessionManagerModuleWidget
::onLoginButtonClicked()
{
  Q_D( qSlicerSessionManagerModuleWidget );

  /*
  QString user = d->SessionManagerLogic->LoginUser("PerkTutorSessions.db", d->lineEditUsername->text(), d->lineEditPassword->text());
  d->lineEditPassword->setText("");
  d->lineEditUsername->setText("");

  if( user != "")
  {
    d->pushButtonLogin->hide();
    d->groupBox->show();
    d->groupBoxTraineeData->show();
    d->groupBox_loadSession->show();
    d->label_LoggedIn->setText("You are currently logged in as: " + user);
    if( user == "admin")
    {
      d->pushButtonCreateUser->setEnabled(true);
      d->pushButtonCreateUser->setAutoDefault(true);
      d->groupBoxAuthentication->setTitle("Administration: Create New User Accounts");
    }
  }
  else
  {
    QMessageBox::information(0, "Error", "User does not exist or the password is incorrect. Log in as admin to create new user account.");
  }
  */
}

void qSlicerSessionManagerModuleWidget
::onCreateTraineeButtonClicked()
{
  QMessageBox::information(0, "Note", "creating trainee");

  Q_D( qSlicerSessionManagerModuleWidget );

  /*
  //retrieve database
  QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("PerkTutorSessions.db");
  if(database.open())
  {
    //if database opens successfully, check whether there is a students/trainee table.
    QStringList tables = database.tables(QSql::Tables);
    if(!tables.contains("students"))
    {
      QSqlQuery query;
      query.exec("CREATE table students(id varchar(32) primary key, firstname varchar(128), lastname varchar(128));");
    }

    //when user clicks save check that studentID field is not null.
    if(( d->lineEditStudentID->text() != ""))
    {
      //check that user does not already exist in the database
      QSqlQuery checkStudentQuery(database);
      checkStudentQuery.prepare("Select * from students where id = ?");
      checkStudentQuery.bindValue(0, d->lineEditStudentID->text());
      checkStudentQuery.exec();

      if(checkStudentQuery.next())
      {
        //found student
        QMessageBox::information(0, "Student Exists", "Don't need to enter any information, this student exists in the database");
      }
      else{
        QSqlQuery query;
        query.prepare("INSERT INTO students(id, firstname, lastname) " "VALUES (:id, :firstname, :lastname)");
        query.bindValue(":id", d->lineEditStudentID->text());
        query.bindValue(":firstname", d->lineEditFirstName->text());
        query.bindValue(":lastname", d->lineEditLastName->text());
        query.exec();

        QString s = "You have created new student: ";
        s = s.append( d->lineEditFirstName->text());
        QMessageBox::information(0, "Created Student", s);
      }
    }
  }
  else{
    QMessageBox::critical(0, QObject::tr("Database Error"),database.lastError().text());
  }
  database.close();
  */
}


