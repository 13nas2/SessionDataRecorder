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
