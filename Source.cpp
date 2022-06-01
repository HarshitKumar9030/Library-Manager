//LIBRARY MANAGEMENT SOFTWARE

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstring>
#include<conio.h>
using namespace std;


class BookOperation
{
public:
	void bookDetailsEntry()
	{
		int book_id;
		char book_name[50], book_author[50];
		fstream fobj("lib_book_details.dat", ios::out | ios::app);

		cout << "\nEnter book ID : ";
		cin >> book_id;

		cout << "\nEnter book name : ";
		cin.ignore();
		cin.getline(book_name, 50);

		cout << "\nEnter book author : ";
		cin.getline(book_author, 50);


		fobj << " " << book_id << "      " << book_name << "      " << book_author << endl;
		fobj.close();

		cout << "\n--------Successfully Saved--------";
	}

	void searchBookDetails()
	{
		fstream fobj1("lib_book_details.dat", ios::in);
	label_search:
		cout << "\n\nSEARCH MENU ";
		cout << "\n1. Display all";
		cout << "\n2. Search";
		cout << "\n3. Exit";

		cout << "\nEnter your choice (1-3) : ";

		int choose;
		cin >> choose;
		switch (choose)
		{
		case 1:
			char str_line[500];
			char str_line1[500];
			if (fobj1.getline(str_line1, 500))
			{
				cout << "\n\n================================================================================";
				
				cout << "\n\n" << str_line1;

				while (fobj1.getline(str_line, 500))
				{
					cout << "\n\n" << str_line;
				}
				cout << "\n\n================================================================================\n\n";
			}
			else
				cout << "\nNo books found.";
			break;

		
		case 2:
			char str_line2[500], str_line5[500];
			cout << "\nEnter book name : ";
			char bookname[10];
			cin.ignore();
			cin.getline(bookname, 50);
			if (fobj1.getline(str_line2, 500))
			{
				fobj1.seekg(0, ios::beg);
				int s = 1;
				cout << "\n\n================================================================================";
				while (fobj1.getline(str_line2, 500))
				{
					if (strstr(str_line2, bookname) != NULL )
					{
						cout << "\n\n" << str_line2;
						s = 0;
					}
				}
				if (s == 1)
				{
					cout << "\nBook not found";
				}
				cout << "\n\n================================================================================\n\n";
			}
			else
				cout << "\nBook not found";
			break;

		
		case 3:
			Sleep(500);
			cout << "\n\nExiting ";
			for (int i = 0; i <= 4; i++)
			{
				Sleep(500);
				cout << ".";
			}
			exit(0);
			break;

		default:
			cout << "\n....Invalid Choice....";
			goto label_search;
			break;
		}
		fobj1.close();
	}

	void delete_book()
	{
		char temp_str[500];
		fstream fin("lib_book_details.dat", ios::in);

		cout << "\nEnter the full book name to delete that book data : ";
		char temp_search[500], temp_search1[500];
		cin.ignore();
		cin.getline(temp_search, 500);
		
		if (fin.getline(temp_search1, 500))
		{
			fin.seekg(0, ios::beg);
			char q;
			cout << "\nAre you sure you want to delete the record (Y/N)? ";
			cin >> q;
			if (q == 'Y' | q == 'y')
			{
				fstream fout("temp_lib.dat", ios::out | ios::app);
				fout.seekg(0, ios::beg);
				
				while (fin.getline(temp_str, 500))
				{
					if (strstr(temp_str, temp_search) == NULL)
					{
						fout << temp_str << endl;
					}
				}
				fin.close();
				fout.close();
				remove("lib_book_details.dat");
				rename("temp_lib.dat", "lib_book_details.dat");
				cout << "\n....Successfully Deleted....";
			}
		}
		else
			cout << "\nNo books are found to be deleted";
	}


	void admin_menu()
	{
	label_admin:
		char c = ' ';
		string admin_pass = "";
		cout << "\nEnter Administrator Password : ";
		while (c != 13)
		{
			c = _getch();
			if (c != 13)
			{
				admin_pass += c;
				cout << "*";
			}
		}
		

		
		if (admin_pass == "admin")
		{
			cout << "\a";
			cout << "\n\nADMINISTRATOR MENU";
			cout << "\n1. Delete Book Data";
			cout << "\n2. Reset Program";
			cout << "\n3. Exit Program";

			cout << "\nEnter choice (1-3) : ";

			int choose_admin;
			cin >> choose_admin;
			BookOperation bookop;
			switch (choose_admin)
			{
			case 1:
				bookop.delete_book();
				break;
			
			case 2:
			{
				char q_reset;
				cout << "\nAll saved data will be deleted and the program will be restored to defaults. Continue anyway? (Y/N) : ";
				cin >> q_reset;
				if (q_reset == 'Y' | q_reset == 'y')
				{
					cout << "\nResetting";
					for (int i = 0; i < 5; i++)
					{
						Sleep(500);
						cout << ".";
					}
					remove("lib_book_details.dat");
					remove("lib_issue_return.dat");
					remove("temp_id.dat");
					remove("issue_return.dat");
					remove("temp_return.dat");
					cout << "\n....Restored to defaults....";
				}
				break;
			}
			case 3:
				Sleep(500);
				cout << "\n\nExiting ";
				for (int i = 0; i <= 4; i++)
				{
					Sleep(500);
					cout << ".";
				}
				exit(0);
				break;
			default:
				cout << "\n....Invalid Choice....";
				break;
			}
		}
		else
		{
			cout << "\n....Invalid Password....";
			goto label_admin;
		}
	}
};

class BookIssueReturn
{
public:
	char date1[10];

	void issue_return()
	{
		char c = ' ';
		string lib_pass = "";
		cout << "\nEnter library password : ";
		while (c != 13)
		{
			c = _getch();
			if (c != 13)
			{
				lib_pass += c;
				cout << "*";
			}
		}
		if (lib_pass == "library")
		{
			cout << "\a";
			BookIssueReturn bIR;
			cout << "\nISSUE AND RETURN SECTION";
			cout << "\n1. Issue book";
			cout << "\n2. Return book";
			cout << "\n3. Issue and Return status";
			cout << "\n4. Exit Program";

			cout << "\nEnter your choice (1-4) : ";

			int bir;
			cin >> bir;
			switch (bir)
			{
			case 1:
				bIR.issue_book();
				break;
			case 2:
				bIR.return_book();
				break;
			case 3:
			{
				fstream BIR("lib_issue_return.dat", ios::in);
				fstream BIR2("lib_issue_return.dat", ios::in);
				char tempstr[500], tempstr1[500];
				if (BIR.getline(tempstr1, 500))
				{
					cout << "\n\n===================================================================================================\n\n";
					while (BIR2.getline(tempstr, 500))
					{
						cout << tempstr << endl;
					}
					cout << "\n===================================================================================================";
					BIR.close();
					BIR2.close();
				}
				else
					cout << "\nNo books have been issued or returned.";
				break;
			}
			case 4:
			{
				Sleep(500);
				cout << "\n\nExiting ";
				for (int i = 0; i <= 4; i++)
				{
					Sleep(500);
					cout << ".";
				}
				exit(0);
				break;
			}
			default:
				cout << "\n....Invalid Choice....";
				break;
			}
		}
		else
		{
			cout << "\n....Wrong Password....";
		}

	}

	void issue_book()
	{
		ifstream File;
		string filepath = "temp_id.dat";
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		File.close();
		int len = 0, i, j, serial, bookid;
		char book_name_copy[50], str_copy[50];
		fstream bi_in("lib_issue_return.dat", ios::out | ios::in | ios::app);
		fstream temp_id("temp_id.dat", ios::out | ios::app);
		fstream bd_out("lib_book_details.dat", ios::in);
		fstream ir("issue_return.dat", ios::in);
		fstream ir2("issue_return.dat", ios::out | ios::app);
		char temp_copy[500], stu_name[50], book_id[10];
		cout << "\nEnter serial number : ";
		cin >> serial;
		cout << "\nEnter the name of the user you want to issue book to : ";
		cin.ignore();
		cin.getline(stu_name, 50);
		cout << "\nEnter the ID of the book you want to issue to the user : ";
		cin >> bookid;
		temp_id << " " << bookid << "  " << endl;
		fstream temp_id2("temp_id.dat", ios::in);
		temp_id2.seekg(0, ios::beg);
		temp_id2.getline(book_id, 10);
		cout << book_id << endl;
		temp_id2.close();
		remove("temp_id.dat");
		len = strlen(book_id);
		int flag1 = 0;
		while (bd_out.getline(temp_copy, 500))
		{
			
			char num[10];
				int len2 = 0;
				for (int op = 0; op < len; op++) {
					num[op] = temp_copy[op];
				}for (int op = len; op < 10; op++) {
					num[op] = '\0';
				}
				
				if (strstr(num, book_id) != NULL)
				{
					flag1 = 1;
					for (i = len; temp_copy[i] != '\0'; i++)
						len2++;
					for (i = len + 4, j = 0; temp_copy[i] != '\0', j < len2; i++, j++)
						book_name_copy[j] = temp_copy[i];

			}
		}

		int flag = 0;
		char temp[500];
		while (ir.getline(temp, 500))
		{
			if (strstr(temp, book_name_copy) == NULL)
				continue;
			else
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0 && flag1 == 1)
		{
			cin.ignore();
			bi_in << " " << serial << "    " << stu_name << "    " << book_name_copy << "    " << _strdate(date1) << endl;
			ir2 << book_name_copy << endl;
			bi_in.close();
			bd_out.close();
			ir.close();
			ir2.close();
			remove("temp_id.dat");
			remove("temp_id2.dat");
			cout << "\n....Book Issued....";
		}
		else
		{
			bi_in.close();
			bd_out.close();
			ir.close();
			ir2.close();
			remove("temp_id.dat");
			remove("temp_id2.dat");
			cout << "\nBook not available for issue.";
		}
	}


	void return_book()
	{
		

		char temp_str[500];
		char date2[10];
		cout << "\nRETURN MENU";
		cout << "\n1. Return by serial no.";
		cout << "\n2. Return by full book name";
		cout << "\nEnter your choice (1-2) : ";
		int choose_return;
		cin >> choose_return;
		switch (choose_return)
		{
		case 1:
		{ifstream File;
		string filepath = "temp_id.dat";
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		File.close();
			int serial;
			cout << "\nEnter serial no of the issue return list : ";
			cin >> serial;
			fstream ser("temp.dat", ios::out | ios::app);
			ser.seekg(0, ios::beg);
			cin.ignore();
			ser << " " << serial << "    ";
			ser.close();
			char serial_copy[50];
			fstream ser1("temp.dat", ios::in);
			ser1.seekg(0, ios::beg);
			ser1.getline(serial_copy, 50);
			ser1.close();
			remove("temp.dat");
			int len = 0;
			len = strlen(serial_copy);
			fstream out_book_return("lib_issue_return.dat", ios::in);
			char book_return[500], temp_copy[500];
			while (out_book_return.getline(book_return, 500))
			{
				char num[10];
				int len2 = 0;
				for (int op = 0; op < len; op++) {
					num[op] = book_return[op];
				}for (int op = len; op < 10; op++) {
					num[op] = '\0';
				}

				if (strstr(num, serial_copy) != NULL)
				{
					
					int i;
					for (i = len; book_return[i] != '\0'; i++)
						len2++;
					int j;
					for (i = len + 4, j = 0; book_return[i] != '\0', j < len2; i++, j++)
						temp_copy[j] = book_return[i];
				}
			}
			out_book_return.close();
			fstream check("issue_return.dat", ios::in);
			char str_cpy[500];
			int flag = 0;
			while (check.getline(str_cpy, 500))
			{
				if (strstr(temp_copy, str_cpy) == NULL)
					continue;
				else
				{
					cout << "Book returned successfully\n";
					flag = 1;
					break;
				}
			}
			check.close();
			if (flag == 1)
			{
				fstream book_rn("lib_issue_return.dat", ios::in);
				fstream bo_return("temp_ir.dat", ios::out | ios::app);
				while (book_rn.getline(book_return, 500))
				{
					if (strstr(book_return, serial_copy) == NULL)
						bo_return << book_return << endl;
					else
						bo_return << book_return << "    " << _strdate(date2) << endl;
				}
				book_rn.close();
				bo_return.close();
				remove("lib_issue_return.dat");
				rename("temp_ir.dat", "lib_issue_return.dat");
			}
			else
			{
				cout << "\nNo such book have been issued.";
			}
			break;
		}

		case 2:
		{
			fstream br_out("lib_issue_return.dat", ios::in);
			fstream temp_return("temp_return.dat", ios::out | ios::app);
			int flag = 0;
			char temp_bn[50], temp[500], temp1[500];
			fstream ir("issue_return.dat", ios::in);
			fstream teir("issue_return.dat", ios::in);
			cout << "\nEnter full book name : ";
			cin.ignore();
			cin.getline(temp_bn, 50);
			ir.seekg(0, ios::beg);
			if (!teir.getline(temp1, 500))
			{

			}
			else
			{
				ir.seekg(0, ios::beg);
				while (ir.getline(temp1, 500))
				{
					if (strstr(temp1, temp_bn) != NULL)
					{
						flag = 1;
						break;
					}
				}
			}
			teir.close();
			ir.close();
			if (flag == 0)
				cout << "\nNo books are found to be returned";
			else
			{
				fstream ir2("issue_return_temp.dat", ios::out | ios::app);
				cin.ignore();
				while (br_out.getline(temp, 500))
				{
					if (strstr(temp, temp_bn) != NULL)
					{
						temp_return << temp;
						temp_return << "    " << _strdate(date2) << endl;
					}
					else
					temp_return << temp << endl;
				}
				
				while (ir2.getline(temp1, 500))
				{
					if (strstr(temp1, temp_bn) == NULL)
						ir2 << temp_bn << endl;
				}
				br_out.close();
				remove("lib_issue_return.dat");
				temp_return.close();
				rename("temp_return.dat", "lib_issue_return.dat");
				ir2.close();
				remove("issue_return.dat");
				rename("issue_return_temp.dat", "issue_return.dat");
				cout << "\n....Book Returned....";
			}
			break;
		}

		default:
			cout << "\n....Invalid Choice....";
			break;
		}
		
	}
};

void about()
{
	fstream about_out("lib_about.dat", ios::in);
	char about_str[500];
	cout << "\n\n==========================================================================================\n\n";
	about_out.seekg(0, ios::beg);
	while (about_out.getline(about_str, 500))
	{
		cout << about_str << endl;
	}
	cout << "\n==========================================================================================\n";
	about_out.close();
}

int main()
{
	system("COLOR 1F");
	char date[10];
	cout << "\n                                   ** LIBRARY MANAGEMENT SOFTWARE **                                   " << _strdate(date);
	BookOperation bo;
	BookIssueReturn bir;
	string pass = "";
label_main:
	char c = ' ';
	cout << "\nEnter Program Password : ";
	while (c != 13)
	{
		c = _getch();
		if (c != 13)
		{
			pass += c;
			cout << "*";
		}
	}
	if (pass == "project")
	{
		cout << "\a";
		int choice;
		while (1)
		{
			cout << "\n\nMAIN MENU";
			cout << "\n1. Book Details Entry";
			cout << "\n2. Search Book Details";
			cout << "\n3. Administrator Menu";
			cout << "\n4. Issue and Return Section";
			cout << "\n5. About";
			cout << "\n6. Exit Program";

			cout << "\nEnter your choice (1-6) : ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				bo.bookDetailsEntry();
				break;
			case 2:
				bo.searchBookDetails();
				break;
			case 3:
				bo.admin_menu();
				break;
			case 4:
				bir.issue_return();
				break;
			case 5:
				about();
				break;
			case 6:
				Sleep(500);
				cout << "\n\nExiting ";
				for (int i = 0; i <= 4; i++)
				{
					Sleep(500);
					cout << ".";
				}
				exit(0);
				break;
			default:
				cout << "\n....Invalid Choice....";
			}
		}
	}
	else
	{
		cout << "\n....Invalid Password....";
		goto label_main;
	}
}
