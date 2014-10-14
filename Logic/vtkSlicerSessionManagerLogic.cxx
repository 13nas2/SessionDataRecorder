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

#include "vtkMRMLViewNode.h"// VTK includes
#include <vtkNew.h>
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

//logic

/*
Input: QString filepath (location of the CSV file)
Output: QStringList with the the students information ( to be added to the user interface)
*/
QStringList vtkSlicerSessionManagerLogic::getTraineeInformation(QString filepath)
{
	//read file and save usernames in a QStringList

	ifstream inputFile;

	inputFile.clear();
	inputFile.open(filepath.toStdString().c_str(), ios::in);

	//exit and prompt error message if file could not be opened
	if (!inputFile){
		qDebug() << "File list could not be opened" << endl;
		//d->label_output->setText("File list could not be opened");
	}// end if

	// count number of lines in the data file
	int number_of_students = 0;

	//first line is the "headers": NetId, First Name, Surname, Student Number, "Assignment:..." 
	std::string header;
	getline(inputFile, header);

	//std::vector<std::string> students;
	QStringList studentlist;
	std::string studentline;

	while (getline(inputFile,studentline))  //read through the file and add students to QStringList
	{
		number_of_students++;
		//students.push_back(studentline);
		studentlist << QString(studentline.c_str());
	}

	inputFile.close();

	//return QStringList
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