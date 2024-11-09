#include <iostream>
#include <sstream>
#include <mysql.h>
#include <mysqld_error.h>
#include<windows.h>

using namespace std;
const char *HOST = "localhost";
const char *USER = "root";
const char *PW = "";
const char *DB = "university";

class University {
private:
    int id;
    string name, course;
    float cgpa;

public:
    University() : id(0), name(""), course(""), cgpa(0.0) {}
    void setId(int Id) { 
    
	id = Id; 
	
	}
    void setName(string Name) {
    	
	 name = Name;
	 
	  }
    void setCourse(string Course) { 
    
	course = Course; 
	
	}
    void setCgpa(float Cgpa) { 
    
	cgpa = Cgpa;
	 
	}

    int getId() {
    	
	 return id;
	 
	  }
    string getName() {
	 
	return name;
	
	 }
    string getCourse() { 
    
	return course;
	
	 }
    float getCgpa() { 
    
	return cgpa;
	
	 }
};

//insert student data

void insertData(MYSQL *conn, University u) {
    int id;
    string name, course;
    float cgpa;
    
    cout << "Enter ID: ";
    cin >> id;
    u.setId(id);
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    u.setName(name);
    cout << "Enter Course: ";
    getline(cin, course);
    u.setCourse(course);
    cout << "Enter CGPA: ";
    cin >> cgpa;
    u.setCgpa(cgpa);

    stringstream query;
    query << "INSERT INTO STUDENT (ID, Name, Course, CGPA) VALUES ('" 
          << u.getId() << "', '" << u.getName() << "', '" << u.getCourse() << "', " << u.getCgpa() << ")";

    if (mysql_query(conn, query.str().c_str())) {
        cout << "Insert failed: " << mysql_error(conn) << endl;
    } else {
        cout << "Data inserted successfully!" << endl;
    }
    Sleep(3000);
}

 //display  student data
 
void display(MYSQL *conn) {
    string query = "SELECT * FROM student";
    if (mysql_query(conn, query.c_str())) {
        cout << "Query failed: " << mysql_error(conn) << endl;
    } else {
        MYSQL_RES *res = mysql_store_result(conn);
        if (res) {
            int numFields = mysql_num_fields(res);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                for (int i = 0; i< numFields; i++) {
                    cout << (row[i] ? row[i] : "NULL") << " ";
                }
                cout << endl;
            }
            mysql_free_result(res);
        }
    }
    Sleep(5000);
}

//search for  student 

void searchData(MYSQL *conn) {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    stringstream query;
    query << "SELECT * FROM student WHERE ID='" << id << "'";

    if (mysql_query(conn, query.str().c_str())) {
        cout << "Query failed: " << mysql_error(conn) << endl;
    } else {
        MYSQL_RES *res = mysql_store_result(conn);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                int numFields = mysql_num_fields(res);
                for (int i = 0; i < numFields; i++) {
                    cout << (row[i] ? row[i] : "NULL") << " ";
                }
                cout << endl;
            } else {
                cout << "No data found for ID: " << id << endl;
            }
            mysql_free_result(res);
        }
    }
    Sleep(5000);
}

//  update student data

void updateData(MYSQL *conn, University u) {
    int id;
    string course;
    cout << "Enter ID to update: ";
    cin >> id;
    cin.ignore();
    cout << "Enter New Course: ";
    getline(cin, course);
    u.setCourse(course);

    stringstream query;
    query << "UPDATE student SET Course='" << u.getCourse() << "' WHERE ID=" << id;

    if (mysql_query(conn, query.str().c_str())) {
        cout << "Update failed: " << mysql_error(conn) << endl;
    } else {
        cout << "Data updated successfully!" << endl;
    }
    Sleep(3000);
}

//delete student data 

void deleteData(MYSQL *conn) {
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    stringstream query;
    query << "DELETE FROM student WHERE ID=" << id;

    if (mysql_query(conn, query.str().c_str())) {
        cout << "Delete failed: " << mysql_error(conn) << endl;
    } else {
        cout << "Data deleted successfully!" << endl;
    }
    Sleep(3000);
}


int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Connection failed: " << mysql_error(conn) << endl;
        return 1;
    } else {
        cout << "*********************CONNECTING TO UNIVERSITY!***********************" << endl;
    }
     Sleep(2000);
    University u;
    bool exit = false;

    while (!exit) {
        int choice;
        cout << "\nMenu:\n";
        cout << "1. Insert Data\n";
        cout << "2. Show Data\n";
        cout << "3. Search Data\n";
        cout << "4. Update Data\n";
        cout << "5. Delete Data\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        
        cin >> choice;

        switch (choice) {
            case 1:
                insertData(conn, u);
                break;
            case 2:
                display(conn);
                break;
            case 3:
                searchData(conn);
                break;
            case 4:
                updateData(conn, u);
                break;
            case 5:
                deleteData(conn);
                break;
            case 6:
                exit = true;
                cout << "Exiting program...... Thank you!" << endl;
                Sleep(3000);
                break;
            default:
                cout << "Invalid input, please try again." << endl;
                break;
        }
    }

    mysql_close(conn);
    return 0;
}

