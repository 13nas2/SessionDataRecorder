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

// SessionManager includes
#include "vtkSlicerSessionManagerLogic.h"

//include for creating directories
#include<direct.h> //only works on Windows

#include "qSlicerIO.h"
#include "qSlicerIOManager.h"
#include "qSlicerApplication.h"

#include "qSlicerDataDialog.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerSessionManagerLogic);
////----------------------------------------------------------------------------
vtkSlicerSessionManagerLogic::vtkSlicerSessionManagerLogic()
{
}
////----------------------------------------------------------------------------
vtkSlicerSessionManagerLogic::~vtkSlicerSessionManagerLogic()
{
}


//get/set methods

QStringList vtkSlicerSessionManagerLogic::getFilenames()
{
  return filenames;
}

void vtkSlicerSessionManagerLogic::setSessionNode(QString traineeID, QString studyname, int assignmentid)
{
  //session node should be initialized elsewhere ( maybe in logic constructor)

}

QString vtkSlicerSessionManagerLogic
::saveSession(QString studyname, QString traineeID, int assignmentid)
{
  QString trainee_netid = traineeID.split(',').first();

  //create mrml node, register and add to scene
  //vtkMRMLTrainingSessionNode* sessionNode = vtkMRMLTrainingSessionNode::New();
  //this->GetMRMLScene()->RegisterNodeClass( sessionNode );
  //this->GetMRMLScene()->AddNode(sessionNode);
  //sessionNode->Delete();

  vtkMRMLTrainingSessionNode* thisnode = (vtkMRMLTrainingSessionNode*)this->GetMRMLScene()->GetNodeByID("vtkMRMLTrainingSessionNodeSingleton");
  if(thisnode)
  {
     thisnode->setStudyName(studyname.toStdString());
     thisnode->setTraineeID(trainee_netid.toStdString());
  }

  /*TO DO: Note: Directory structure created elsewhere. Write a "getPath" method so that the following format is not hardcoded in several places*/
  QString home = QDir::toNativeSeparators(QDir::homePath());
  QString path = home + "\\Study-" + studyname + "\\" + trainee_netid;

  //get the number of sessions in the given student's directory
  QDir dir(path);
  dir.setFilter(QDir::Files | QDir::NoSymLinks);
  QFileInfoList list = dir.entryInfoList();
  int filenum = list.size() + 1;

  path = path + QDateTime::currentDateTime().date().toString("'\\'yyyy-MM-dd-Session'") + QString::number(filenum) + ".mrb";

  //save scene and mrml node
  qSlicerIO::IOProperties properties_map;
  properties_map["fileName"] = path;
  qSlicerApplication::application()->ioManager()->saveNodes("SceneFile",properties_map);  //saves the sessionNode as well since it was added to the scene in the Widget class

  return path;
}

QStringList vtkSlicerSessionManagerLogic::getFilePaths(QString studyname, QString traineename)
{
  QStringList list;

  QString home = QDir::toNativeSeparators(QDir::homePath());
  QString traineeid = traineename.split(',').first();
  QString path = home + "\\Study-" + studyname + "\\" + traineeid;  

  qSlicerIO::IOProperties properties_map;
  properties_map["fileName"] = path;

  qSlicerApplication::application()->ioManager()->openAddDataDialog(); //or pass in QString filename?
  
   //qSlicerApplication::application()->ioManager();
   //qSlicerDataDialog* dataDialog;
   //dataDialog->exec(properties_map);  //creates runtime error "Variable dataDialog being used without initialization"

   //determine the file path and add it to the dataDialog. Is this possible?
   //exec does not allow us to do this but possibly DropEvent?
   //alternatively,create your own dialog?

   //show the files instead of creating the file dialog
   QDir dir(path);
   dir.setFilter(QDir::Files | QDir::NoSymLinks);
   QFileInfoList filelist = dir.entryInfoList();

   for(int i = 1; i< filelist.size(); i++)
   {
     list << filelist.at(i).fileName();   
   }

  return list;
}

//logic
/*
Input: QString filepath (location of the CSV file)
Output: QStringList with the the students information ( to be added to the user interface)
*/
QString vtkSlicerSessionManagerLogic::getStudyNameAndMakeDirectory(QString filepath)
{
   QFile file(filepath); // filepath contains full file path name
   QString filename;
   if (file.exists())
    {
      QFileInfo fileInfo(file);
      filename = fileInfo.fileName(); // Return only a file name
      filename.truncate(filename.indexOf("Grades"));
      filenames << filename;  //add CSV filename to list of filenames

      //make directory for filename
      std::string path = QDir::homePath().toStdString() + "/Study-" + filename.toStdString();
      int result = _mkdir(path.c_str());
      if( result == 0)
        printf("Directory %s created",path.c_str());
      else
        printf("Study directory already exists or could not be created");

    }
    return filename;
}

/*
Input: QString filepath (location of the CSV file)
Output: QStringList with the the trainees' information ( to be added to the UI). Also, a subdirectory is created for each trainee.
*/
QStringList vtkSlicerSessionManagerLogic::getTraineeInformation(QString filepath, QString studyname)
{
	//read file and save usernames in a QStringList
	ifstream inputFile;

	inputFile.clear();
	inputFile.open(filepath.toStdString().c_str(), ios::in);

	//exit and prompt error message if file could not be opened
	if (!inputFile){
		qDebug() << "File could not be opened" << endl;
		//d->label_output->setText("File could not be opened");
	}// end if

	//count number of lines in the data file
	int number_of_students = 0;

	//first line is the "headers": NetId, First Name, Surname, Student Number, "Assignment:..." 
	std::string header;
	getline(inputFile, header); // gets the header line

	QStringList studentlist;
	std::string studentline;

    //get study path
    std::string studypath = QDir::homePath().toStdString() + "/Study-" + studyname.toStdString();

	while (getline(inputFile,studentline))  //read through the file and add students to QStringList
	{
        //make directory for student using student id
        std::string sub = studentline.substr(0,studentline.find_first_of(','));
        std::string path = studypath + "//" + sub;
        _mkdir(path.c_str());

        //split string using the commas
        // 1st element: student id , 2nd element: first name, 3rd element: last name

        QString line(studentline.c_str());
        QStringList studentdata = line.split(",");

        number_of_students++;
        studentlist << QString(studentdata.at(0) + ", " + studentdata.at(1) + " " + studentdata.at(2)); 
	}
	inputFile.close();
	return studentlist;
}

bool vtkSlicerSessionManagerLogic::createUser(QString databaseName, QString username, QString password)
{
	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(databaseName);
	if(database.open())
	{
		//check whether there is a users table, if not create one
		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("users"))
		{
			QSqlQuery query;
			query.exec("CREATE table users(username varchar(30) primary key, password varchar(30));");
		}

		//check that user does not already exist in the database
		QSqlQuery checkUserQuery(database);
		checkUserQuery.prepare("Select * from users where username = ?");
		checkUserQuery.bindValue(0, username);
		checkUserQuery.exec();

		if(!checkUserQuery.next()) //could not find the user
		{
			//add username and password to table
			QSqlQuery query;
			query.prepare("INSERT INTO users (username, password) " "VALUES (:username, :password)");
			query.bindValue(":username",username);
			query.bindValue(":password", password);
			query.exec();
			database.close();
			return true;
		}
	}
	database.close();
	return false;
}

/*
Return: name of logged in user, or empty string if login failed.
*/
QString vtkSlicerSessionManagerLogic::LoginUser(QString databaseName, QString username, QString password)
{
	QString user = "";
	
	//retrieve database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("PerkTutorSessions.db");
	if(database.open())
	{
		//if database opens successfully, check whether there is a users table. If not, create one.
		QStringList tables = database.tables(QSql::Tables);
		if(!tables.contains("users"))
		{
			//create users table and add admin user
			QSqlQuery query;
			query.exec("CREATE table users(username varchar(30) primary key, password varchar(30));");
			query.prepare("INSERT INTO users (username, password) " "VALUES (:username, :password)");
			query.bindValue(":username", "admin");
			query.bindValue(":password", "default");  /** TO DO: Password should not be stored as plaintext**/
			query.exec();
		}
		else
		{
			if(( username != "") && (password != ""))
			{
				//check if user/password combination exists in the database
				QSqlQuery checkUserQuery(database);
				checkUserQuery.prepare("Select * from users where username = ? and password = ?");
				checkUserQuery.bindValue(0, username);
				checkUserQuery.bindValue(1, password);
				checkUserQuery.exec();

				if(checkUserQuery.next())//found username/password pair.
				{
					user = username;
				}
			}
		}
	}
	else{
		//QMessageBox::critical(0, QObject::tr("Database Error"),database.lastError().text());
	}
	database.close();
	return user;
}