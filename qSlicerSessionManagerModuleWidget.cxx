

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
#include "qSlicerIO.h"
#include "qSlicerIOManager.h"
#include "qSlicerApplication.h"
#include <QtGui>

// MRMLWidgets includes
#include <qMRMLUtils.h>

#include "vtkSlicerSessionManagerLogic.h"
#include "vtkMRMLLinearTransformNode.h"

#include "qMRMLNodeComboBox.h"
#include "vtkMRMLViewNode.h"
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

  // Add embedded widgets here
  qSlicerTransformBufferWidget* TransformBufferWidget;
  qSlicerRecorderControlsWidget* RecorderControlsWidget;
  qSlicerMessagesWidget* MessagesWidget;
};

//-----------------------------------------------------------------------------
// qSlicerSessionManagerModuleWidgetPrivate methods

qSlicerSessionManagerModuleWidgetPrivate::qSlicerSessionManagerModuleWidgetPrivate( qSlicerSessionManagerModuleWidget& object ) : q_ptr(&object)
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


//-----------------------------------------------------------------------------
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

  // If adding widgets, embed widgets here: eg: //d->TransformBufferWidget = qSlicerTransformBufferWidget::New( d->logic() );
  
  this->Superclass::setup();

  // GUI refresh: updates every 10ms
  QTimer *t = new QTimer( this );
  connect( t,  SIGNAL( timeout() ), this, SLOT( updateWidget() ) );
  t->start(10);

  //connect buttons
  connect(d->pushButtonCreateTrainee, SIGNAL( clicked() ), this, SLOT( onCreateTraineeButtonClicked() ) ); 
  connect(d->pushButtonCreateUser, SIGNAL( clicked() ), this, SLOT( onCreateUserButtonClicked() ) ); 
  connect(d->pushButtonLogin, SIGNAL( clicked() ), this, SLOT( onLoginButtonClicked() ) );
  connect(d->saveSceneButton, SIGNAL(clicked()), this, SLOT( onSaveSceneButtonClicked()) );
  connect(d->pushButtonLogout, SIGNAL(clicked()), this, SLOT( onLogoutButtonClicked()) );

  //set up load session tab with 
  
  //hide everything except login fields
  d->groupBox->hide();
  d->groupBoxTraineeData->hide();
  d->groupBox_loadSession->hide();
}

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

void qSlicerSessionManagerModuleWidget::loadSessionSetup()
{
	Q_D( qSlicerSessionManagerModuleWidget );

	//populate the combo box with student ids in the database
	//need to open database, check for sessions table, get records with unique user id field.
	

	//when user actually selects



	

}

void qSlicerSessionManagerModuleWidget::enter()
{
  this->Superclass::enter();
  this->updateWidget();
}

void qSlicerSessionManagerModuleWidget
::updateWidget()
{
  Q_D( qSlicerSessionManagerModuleWidget );   
}

void qSlicerSessionManagerModuleWidget
::onCreateUserButtonClicked()
{
	Q_D( qSlicerSessionManagerModuleWidget );

	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("PerkTutorSessions.db");
	if(database.open())
	{
		//if database opens successfully, check whether there is a users table.
		//if not, then create one.

		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("users"))
		{
			QSqlQuery query;
			query.exec("CREATE table users(username varchar(30) primary key, password varchar(30));");
		}

		//when user enters information and clicks "Create new user"
		//check that the lineEdit fields are not null
		if(( d->lineEditUsername->text() != "") && (d->lineEditPassword->text() != ""))
		{
			//check that user does not already exist in the database
			QSqlQuery checkUserQuery(database);
			checkUserQuery.prepare("Select * from users where username = ?");
			checkUserQuery.bindValue(0, d->lineEditUsername->text());
			checkUserQuery.exec();

			if(checkUserQuery.next()) //found the user  /*//MAYBE: ask the user to enter the password again to login?...*/
			{
				QMessageBox::information(0, "Cannot create user", "Cannot create new user: This user already exists");
				d->lineEditUsername->setText("");
				d->lineEditPassword->setText("");
				d->lineEditUsername->setFocus();
				
			}
			else
			{
				//add username and password to table
				QSqlQuery query;
				query.prepare("INSERT INTO users (username, password) " "VALUES (:username, :password)");
				query.bindValue(":username", d->lineEditUsername->text());
				query.bindValue(":password", d->lineEditPassword->text());
				query.exec();

				QString s = "You have created new user:  ";
				s = s.append( d->lineEditUsername->text());
				QMessageBox::information(0, "Created User", s);
					
				// after user created, clear username and password fields to allow user to login
				d->lineEditUsername->setText("");
				d->lineEditPassword->setText("");
			}
		}
	}
	else{
		QMessageBox::critical(0, QObject::tr("Database Error"),database.lastError().text());
	}
	database.close();
}




void qSlicerSessionManagerModuleWidget
::onLoginButtonClicked()
{
	/*user enters login information and clicks "login". Check that the lineEdit fields are not empty
	  if user/password pair exists in the database, user is now logged in - display a message either way.
    */
	Q_D( qSlicerSessionManagerModuleWidget );

	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("PerkTutorSessions.db");
	if(database.open())
	{
		//if database opens successfully, check whether there is a users table. If not, create one.
		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("users"))
		{
			if((d->lineEditUsername->text() == "admin") && ( d->lineEditPassword->text() == "default"))
			{
				//create users table and add admin user
				QSqlQuery query;
				query.exec("CREATE table users(username varchar(30) primary key, password varchar(30));");
				query.prepare("INSERT INTO users (username, password) " "VALUES (:username, :password)");
				query.bindValue(":username", "admin");
				query.bindValue(":password", "default");  /** TO DO: Password should not be stored as plaintext**/
				query.exec();

				d->label_LoggedIn->setText("You are currently logged in as: admin");
				d->groupBoxAuthentication->setTitle("Admininstration: Create New User Accounts");
				d->pushButtonLogin->hide();
				d->pushButtonCreateUser->setEnabled(true);
				d->pushButtonCreateUser->setAutoDefault(true);
				d->lineEditPassword->setText("");
				d->lineEditUsername->setText("");
				d->groupBox->show();
				d->groupBoxTraineeData->show();
				d->groupBox_loadSession->show();
			}
			else
			{
				QMessageBox::information(0, "Error", "User does not exist or the password is incorrect. Log in as admin to create new user account.");
			}
		}
		else
		{
			if(( d->lineEditUsername->text() != "") && (d->lineEditPassword->text() != ""))
			{
				//check that user does not already exist in the database
				QSqlQuery checkUserQuery(database);
				checkUserQuery.prepare("Select * from users where username = ? and password = ?");
				checkUserQuery.bindValue(0, d->lineEditUsername->text());
				checkUserQuery.bindValue(1, d->lineEditPassword->text());
				checkUserQuery.exec();

				if(checkUserQuery.next())//found username/password pair.
				{
					if(d->lineEditUsername->text() == "admin")
					{
						d->label_LoggedIn->setText("You are currently logged in as: admin");
						d->groupBoxAuthentication->setTitle("Admininstration: Create New User Accounts");
						d->pushButtonLogin->hide();
						d->pushButtonCreateUser->setEnabled(true);
						d->pushButtonCreateUser->setShortcut(Qt::Key_Return);
						d->lineEditPassword->setText("");
						d->lineEditUsername->setText("");
					}
					else
					{
						d->label_LoggedIn->setText("You are currently logged in as:" + d->lineEditUsername->text());
						d->groupBoxAuthentication->hide();
					}
					d->groupBox->show();
					d->groupBoxTraineeData->show();  //only admin can add trainees?
					d->groupBox_loadSession->show();

				}
				else
				{
					QMessageBox::information(0, "Login failed", "Either the username or password is incorrect.");
					d->lineEditUsername->setText("");
					d->lineEditPassword->setText("");
				}
			}
		}
	}
	else{
		QMessageBox::critical(0, QObject::tr("Database Error"),database.lastError().text());
	}
	database.close();
}


void qSlicerSessionManagerModuleWidget
::onCreateTraineeButtonClicked()
{
	QMessageBox::information(0, "Note", "creating trainee");

	Q_D( qSlicerSessionManagerModuleWidget );

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

				QString s = "You have created new student:  ";
				s = s.append( d->lineEditFirstName->text());
				QMessageBox::information(0, "Created Student", s);	
			}
		}
	}
	else{
		QMessageBox::critical(0, QObject::tr("Database Error"),database.lastError().text());
	}
	database.close();
}


void qSlicerSessionManagerModuleWidget
::onSaveSceneButtonClicked()
{
	Q_D( qSlicerSessionManagerModuleWidget );
	//save scene ( pass in filename and properties array)
	qSlicerIO::IOProperties properties_map;
	//QString filename = "Scene-test.mrb";
	
	// Get absolute filename
	QFileInfo sceneFileInfo = QFileInfo( QDir(qSlicerApplication::application()->mrmlScene()->GetRootDirectory()),
                               QDate::currentDate().toString("yyyy-MM-dd") + "-Scene.mrb");

	QString filename = QDateTime::currentDateTime().date().toString("'/'yyyy-MM-dd'");
	if(d->lineEditStudentID->text().toStdString() != "")
	{
		filename.append("-Session-Student");
		filename.append(d->lineEditStudentID->text());
		filename.append(".mrb");
	}
	else
	{
		filename.append("-Session.mrb");
	}

	filename.prepend(qSlicerApplication::application()->mrmlScene()->GetRootDirectory());
	properties_map["fileName"] = filename;
	qSlicerApplication::application()->ioManager()->saveNodes("SceneFile",properties_map);
	QMessageBox::information(0, "Saved scene to ", filename);

	//create training session "sessions" table with fields "user_id", "datetime", "filepath"   [ADD "associated_study" field?)
	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("PerkTutorSessions.db");
	if(database.open())
	{
		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("sessions"))
		{
			QSqlQuery query;
			query.exec("CREATE table sessions(sessionID integer primary key autoincrement, userID varchar[32], studyname varchar[256], timestamp datetime default current_timestamp, filepath varchar(256));");
			QMessageBox::information(0, "Created new 'sessions' table ","Created new 'sessions' table ");
		}

		//add data to table
		QSqlQuery query;
		query.prepare("INSERT INTO sessions(userID, filepath) " "VALUES (:userID, :filepath)");
		query.bindValue(":userID", d->lineEditStudentID->text());
		query.bindValue(":filepath", filename);
		query.exec();
	}
	//vtkMRMLScene* scene = qSlicerApplication::mrmlScene();  /* illegal call of non-static member function*/
	//qSlicerApplication::application()->ioManager()->openSaveDataDialog();  /* opens up save dialog */
}