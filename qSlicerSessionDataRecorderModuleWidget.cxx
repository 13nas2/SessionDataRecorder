

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
#include "qSlicerSessionDataRecorderModuleWidget.h"
#include "ui_qSlicerSessionDataRecorderModule.h"
#include "qSlicerIO.h"
#include "qSlicerIOManager.h"
#include "qSlicerApplication.h"
#include <QtGui>

// MRMLWidgets includes
#include <qMRMLUtils.h>

#include "vtkSlicerSessionDataRecorderLogic.h"
#include "vtkMRMLLinearTransformNode.h"

#include "qMRMLNodeComboBox.h"
#include "vtkMRMLViewNode.h"
#include "vtkSlicerSessionDataRecorderLogic.h"
#include "vtkMRMLTransformBufferNode.h"

//#include <sqlite3.h>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

//include Slicer code 
#include <qSlicerSaveDataDialog.h>


//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_SessionDataRecorder
class qSlicerSessionDataRecorderModuleWidgetPrivate: public Ui_qSlicerSessionDataRecorderModule
{
  Q_DECLARE_PUBLIC( qSlicerSessionDataRecorderModuleWidget ); 

protected:
  qSlicerSessionDataRecorderModuleWidget* const q_ptr;
public:
  qSlicerSessionDataRecorderModuleWidgetPrivate( qSlicerSessionDataRecorderModuleWidget& object );
  ~qSlicerSessionDataRecorderModuleWidgetPrivate();

  vtkSlicerSessionDataRecorderLogic* logic() const;

  // Add embedded widgets here
  qSlicerTransformBufferWidget* TransformBufferWidget;
  qSlicerRecorderControlsWidget* RecorderControlsWidget;
  qSlicerMessagesWidget* MessagesWidget;
};

//-----------------------------------------------------------------------------
// qSlicerSessionDataRecorderModuleWidgetPrivate methods

qSlicerSessionDataRecorderModuleWidgetPrivate::qSlicerSessionDataRecorderModuleWidgetPrivate( qSlicerSessionDataRecorderModuleWidget& object ) : q_ptr(&object)
{
}

//-----------------------------------------------------------------------------

qSlicerSessionDataRecorderModuleWidgetPrivate::~qSlicerSessionDataRecorderModuleWidgetPrivate()
{
}


vtkSlicerSessionDataRecorderLogic* qSlicerSessionDataRecorderModuleWidgetPrivate::logic() const
{
  Q_Q( const qSlicerSessionDataRecorderModuleWidget );
  return vtkSlicerSessionDataRecorderLogic::SafeDownCast( q->logic() );
}


//-----------------------------------------------------------------------------
// qSlicerSessionDataRecorderModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerSessionDataRecorderModuleWidget::qSlicerSessionDataRecorderModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerSessionDataRecorderModuleWidgetPrivate( *this ) )
{
}


qSlicerSessionDataRecorderModuleWidget::~qSlicerSessionDataRecorderModuleWidget()
{
}

void qSlicerSessionDataRecorderModuleWidget::setup()
{
  Q_D(qSlicerSessionDataRecorderModuleWidget);

  d->setupUi(this);

  // If adding widgets, embed widgets here: eg: //d->TransformBufferWidget = qSlicerTransformBufferWidget::New( d->logic() );
  
  this->Superclass::setup();

  // GUI refresh: updates every 10ms
  QTimer *t = new QTimer( this );
  connect( t,  SIGNAL( timeout() ), this, SLOT( updateWidget() ) );
  t->start(10);

  //connect button
  connect( d->saveButton, SIGNAL( clicked() ), this, SLOT( onSaveButtonClicked() ) ); 
  connect(d->pushButtonCreate, SIGNAL( clicked() ), this, SLOT( onCreateButtonClicked() ) ); 
  connect(d->pushButtonLogin, SIGNAL( clicked() ), this, SLOT( onLoginButtonClicked() ) ); 
  connect(d->OkButton, SIGNAL( clicked() ), this, SLOT(onOKButtonClicked()));
  connect(d->saveSceneButton, SIGNAL(clicked()), this, SLOT( onSaveSceneButtonClicked()) );
  
  d->groupBox->hide();
}


void qSlicerSessionDataRecorderModuleWidget::enter()
{
  this->Superclass::enter();
  this->updateWidget();
}

void qSlicerSessionDataRecorderModuleWidget
::updateWidget()
{
  Q_D( qSlicerSessionDataRecorderModuleWidget );   
}

void qSlicerSessionDataRecorderModuleWidget
::onCreateButtonClicked()
{
	Q_D( qSlicerSessionDataRecorderModuleWidget );

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
			QMessageBox::information(0, "Creating Table users	", "Executed create query");
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


void qSlicerSessionDataRecorderModuleWidget
::onLoginButtonClicked()
{
	/*user enters login information and clicks "login"
	  check that the lineEdit fields are not empty
	  if user/password pair exists in the database, user is now logged in - display a message either way.
    */

	// after user created or logged in, hide authentication box.
	Q_D( qSlicerSessionDataRecorderModuleWidget );

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
			if((d->lineEditUsername->text() == "admin") && ( d->lineEditPassword->text() == "default"))
			{
				//create users table and add admin user
				QSqlQuery query;
				query.exec("CREATE table users(username varchar(30) primary key, password varchar(30));");

				query.prepare("INSERT INTO users (username, password) " "VALUES (:username, :password)");
				query.bindValue(":username", "admin");
				query.bindValue(":password", "default");
				query.exec();

				QMessageBox::information(0, "Login successful", "You are now logged in as admin");
				d->groupBoxAuthentication->setTitle("Admininstration: Create New User Accounts");
				d->pushButtonLogin->hide();
				d->pushButtonCreate->setEnabled(true);
				d->pushButtonCreate->setAutoDefault(true);
				d->lineEditPassword->setText("");
				d->lineEditUsername->setText("");
				d->groupBox->show();
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
						QMessageBox::information(0, "Login successful", "You are now logged in as admin");
						d->groupBoxAuthentication->setTitle("Admininstration: Create New User Accounts");
						d->pushButtonLogin->hide();
						d->pushButtonCreate->setEnabled(true);
						d->pushButtonCreate->setShortcut(Qt::Key_Return);
						d->lineEditPassword->setText("");
						d->lineEditUsername->setText("");
						d->lineEditUsername->setFocus();
					}
					else
					{
						QMessageBox::information(0, "Login successful", "You are now logged in.");
						d->groupBoxAuthentication->hide();
					}
					d->groupBox->show();
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

void qSlicerSessionDataRecorderModuleWidget
::onOKButtonClicked()
{
	Q_D( qSlicerSessionDataRecorderModuleWidget );
	d->groupBox->show();
}

void qSlicerSessionDataRecorderModuleWidget
::onSaveButtonClicked()
{
	Q_D( qSlicerSessionDataRecorderModuleWidget );

	//mrml scene's root directory is C:/Users/Nisrin/Desktop
	//when user clicks SAVE the mrml scene is automatically saved to a given location.

	//save the studentID in the database, 
	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("PerkTutorSessions.db");
	if(database.open())
	{
		//if database opens successfully, check whether there is a students/trainee table.
		//if not, then create one.
		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("students"))
		{
			QSqlQuery query;
			query.exec("CREATE table students(id int primary key, name varchar(30));");
			QMessageBox::information(0, "Creating Table students	", "Executed create query");
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
				//ask user for student's name and other information. *** TO DO***
				QSqlQuery query;
				query.prepare("INSERT INTO students(id, firstname) " "VALUES (:id, :firstname)");
				query.bindValue(":id", d->lineEditStudentID->text());
				query.bindValue(":firstname", d->lineEditFirstName->text());
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
	
	QDir directory = "/";

	//select a directory using file dialog 
    //QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), directory.path());
   
	/*
	if ( path.isNull() == false )
    {
        d->MessageLabel->setText(path);
		this->updateWidget();
    }
	//write to the given directory
	ofstream myfile (path.toStdString().append("/example.txt").c_str());
	if (myfile.is_open())
	{
		myfile << "User logged in: " <<  d->lineEditUsername->text().toStdString().c_str();
		cout << "Saved username to file";
		myfile.close();
	}
	else cout << "Unable to open myfile";
	*/
}

void qSlicerSessionDataRecorderModuleWidget
::onSaveSceneButtonClicked()
{
	Q_D( qSlicerSessionDataRecorderModuleWidget );
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

	//create training session "sessions" table with fields "user_id", "datetime", "directory", "filename"
	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("PerkTutorSessions.db");
	if(database.open())
	{
		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("sessions"))
		{
			QSqlQuery query;
			query.exec("CREATE table sessions(sessionID integer primary key autoincrement, userID varchar[20], timestamp datetime default current_timestamp, filepath varchar(64));");
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