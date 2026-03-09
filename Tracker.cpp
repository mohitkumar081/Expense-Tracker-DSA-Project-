#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits> 
#include <thread>
#include <cstring>
using namespace std;
class Categories;
class RecordingExpenses;
class SettingBudgets;
int MAX_SIZE = 100; 
int static n=4;
string* category;
using namespace std;
class User
{

public:
	void registerUser(const string& username, const string& password) {
		ofstream userFile(username + ".txt");
		if (userFile.is_open()) {
			userFile << password << endl;
			userFile.close();
			std::cout << "User '" << username << "' created successfully." << endl;
		}
		else {
			cout << "Error creating user." << endl;
		}
	}

	bool authenticateUser(const string& username, const string& password) {
		ifstream userFile(username + ".txt");
		if (userFile.is_open()) {
			string storedPassword;
			userFile >> storedPassword;
			userFile.close();
			return (storedPassword == password);
		}
		return false;
	}
};

class node
{
public:
	char* date_time;
	int amount;
	string name;
	double budget;
	string description;
	node* next;

	node()
	{
		next = NULL;

	}
	node(int a, string c, string d, char* dt, double b)
	{
		date_time = dt;
		amount = a;
		name = c;
		description = d;
		budget = b;
				 next=NULL;
	}

};


class Categories
{
public:


	void RemoveCategory(int j)
	{


		for (int i = 0; i < n; i++)
		{
			if (i == j)
			{
				while (i + 1 != n)
				{

					category[i] = category[i + 1];
					i++;
				}
				break;


			}
		}


		n--;
	
		cout << "Category deleted successfully!";





	}
	void EditCategory()
	{
		bool flag = false;
		int c;
		string edited;
		getCategories();
		cout << "Enter Category you wanna Edit : ";
		cin >> c;
		for (int i = 0; i < n; i++)
		{
			if (c == i)
			{
				cout << "enter edited name for the category:" << endl;
				cin >> edited;
				category[i] = edited;
				flag = true;
break;
			}

		}
		if (flag == false)
		{

			cout << "category doesnot exits" << endl;
			return;
		}

	}
	void getCategories()
	{

		cout << "Categories : " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << i << ". " << category[i] << endl;

		}
	}
	void viewCategory(node* temp){
	
	if(temp==NULL)
	{
		return;
	}
		

		while (temp != NULL)
		{


			cout << "Name:" << temp->name << endl << "Amount : " << temp->amount << endl << "Description : " << temp->description << endl << "Date & Time : " << temp->date_time;
			cout << endl << endl;


			temp = temp->next;
		}




	}


};
class TrackingBudget
{
public:
	double* budgetAmounts;
	TrackingBudget() {

		budgetAmounts = new double[n];
		for (int i = 0; i < n; i++) {
			budgetAmounts[i] = 0;
		}
	}

	~TrackingBudget() {
		delete[] budgetAmounts;
	}

	void NotifyBudgetExceeded(string category, double exceededAmount) {
		cout << "Budget exceeded for category " << category << " by Rs" << exceededAmount << endl;

	}


	void TrackBudget(node* temp) {

		if (temp == NULL)
		{
			cout << "No category exists" << endl;
			return;
		}
		else
		{
			while (temp != NULL)
			{
				if (temp->budget < temp->amount) {
					NotifyBudgetExceeded(temp->name, temp->amount - temp->budget);
				}


				temp = temp->next;
			}

		}
	}





	void GetBudgetSummary(node* temp) {
		double totalBudget = 0.0;
		double totalExpenses = 0.0;


		while (temp != NULL) {
			totalBudget += temp->budget;
			totalExpenses += temp->amount;
			temp = temp->next;
		}

		double remainingBudget = totalBudget - totalExpenses;

		double budgetThreshold = 0.3;// 30% of total budget

		if (remainingBudget < 0) {

			cout << "Budget exceeded by Rs " << abs(remainingBudget) << ". You've exceeded the budget threshold." << endl;
		}
		else if (remainingBudget >= totalBudget * budgetThreshold) {

			cout << "Good budget level. You're within the budget threshold." << endl;
		}
		else {

			cout << "Approaching budget threshold. Remaining budget is Rs " << remainingBudget << endl;
		}
	}


};

class SettingBudgets
{
public:

	SettingBudgets()
	{

	}

	void EditBudgets(node* temp)
	{
		double am;
		string str;

		cout << "Enter the name of the category : " << endl;
		cin >> str;

		if (temp != NULL)
		{
			while (temp != NULL && temp->name != str)
			{
				temp = temp->next;
			}
			cout << "enter the New budget for " << str << " category" << endl;
			cin >> am;
			temp->budget = am;
			cout << "Budget for " << str << " edited to Rs" << am << endl;
			return;
		}
		else
		{
			cout << "No category Exists..Can't Edit'" << endl;
			return;
		}


	}

	void ViewBudgets(node* temp)
	{

		if (temp == NULL)
		{
			cout << "NO CATEGORY EXITS" << endl;
			return;
		}
		else {


			cout << "Budget " << setw(50) << "Category" << endl;
			while (temp != NULL)
			{
				cout << temp->budget << setw(50) << temp->name << endl;
				temp = temp->next;
			}
		}

	}


	void DeleteBudget(node*& head)
	{
		string str;
		cout << "Enter the name of the category : ";
		cin >> str;
		node* temp = head;
		if (head == NULL)
		{
			cout << "No Category exists ";
			return;
		}
		else if (head->name == str)
		{

			head = temp->next;
			cout << "Budget deleted successfully!";
			delete temp;

			return;
		}
		else
		{
			node* temp = head;
			while (temp->next != NULL)
			{

				if (temp->next->name == str)
				{
					node* store = temp->next;
					temp->next = temp->next->next;
					delete store;
					cout << "Budget deleted successfully!";
					return;
				}
				temp = temp->next;
			}

			cout << "ERROR ! No budget Exists For Such Category " << endl;
			return;


		}
	}

	 
};
class RecordingExpenses :public Categories, public SettingBudgets, public TrackingBudget
{
public:

	node* head;

	int number;

	RecordingExpenses()
	{

		head = NULL;
		category = new string[MAX_SIZE];
	}


	int recordExpense()
	{

		int c;

		getCategories();
		cout << "Enter the no. of Category : ";
		cin >> c;

		if (c == 0)
		{
	         n = n + 1;

			category[n-1] = AddCategory();
		
return n-1;
		}
		return c;
	}
	void	insert(int a, string str, string d, char* dt, double am)
	{

		node* newnode = new node(a, str, d, dt, am);
		if (head == NULL)
		{
			head = newnode;
			return;
		}
		else
		{
			node* temp = head;
			

				while (temp->next != NULL)
				{
				 							
					temp = temp->next;
				}
				temp->next = newnode;
				newnode->next = NULL;
			
		}

	}


	string AddCategory()
	{

		string S;
		cout << "enter the  new category: " << endl;
		cin >> S;



		return S;

	}
	void viewExpenses()
	{
		node* temp = head;
		if (head == NULL)
		{  	
			return;
		}

		while (temp != NULL)
		{
			cout << temp->name << " " << temp->amount << " " << temp->description << " " << temp->date_time;
			cout << endl;
			temp = temp->next;
		}
		 return;

	}


	int hash(int key)
	{
		return key % n;
	}

	double calculateTotalExpenses(int total)
	{
		if (head == NULL)
		{
	
			return 0;
		}
		node* temp = head;

		while (temp != NULL)
		{
			total = total + temp->amount;
			temp = temp->next;
		}
		return total;
	}
	double CategoryExpense()
	{
		int v = 0;
		node* temp = head;
		if (head == NULL)
		{
			cout << "ERROR ! The category doesnot contain any expenses " << endl;
			return 0;
		}



		else
		{

			while (temp != NULL)
			{
				
				v = v + temp->amount;
				temp = temp->next;
			}
			return v;
		}


	}
	void editExpense()
	{
		node* temp = head;
		if (head == NULL)
		{
			cout << "No expense recorded ! ";
			return;
		}
		temp = head;
		while (temp != NULL)
		{
			cout << temp->name << endl;
			temp=temp->next;
		}

		int v;
		string str;
		cout << "enter name in lower case : ";
		cin >> str;
		temp=head;
 
		while (temp->name != str&&temp!=NULL)
		{
			cout<<"checl";
			temp = temp->next;
		}
	
		cout << "Enter the number of the detail want to edit : " << endl;
		cout << 1 << ". amount" << endl << 2 << ". name" << endl << 3. << "Description ";
		cin >> v;
		if (v == 1)
		{
			cout << "Enter amount : ";
			cin >> temp->amount;
		}
		else if (v == 2)
		{
			cout << "Enter name: ";
			cin >> temp->name;                 ////
		}
		else if (v == 3)
		{
			cout << "Enter description : ";
			cin >> temp->description;
		}
		else
		{
			cout << "Wrong input ! ";
		}




	}


	void deleteExpense()
	{
		string str;
		if (head == NULL)
		{
			cout << "No expense recorded ! ";
			return;
		}
		node* temp = head;
		while (temp != NULL)
		{
			cout << temp->name << endl;
			temp=temp->next;
		}

		cout << "Enter the name of the expense u want to delete in this category : ";
		cin >> str;
temp = head;

		if (head->name == str)
		{

			head = temp->next;
			delete temp;

			return;
		}
		else
		{
			
			while (temp->next != NULL)
			{

				if (temp->next->name == str)
				{
					node* dlt = temp->next;
					temp->next = temp->next->next;
					delete dlt;
					cout << "Expense deleted successfully!";
					return;
				}
				temp = temp->next;
			}

			cout << "ERROR ! The category doesnot contain any expense of this name!" << endl;
			return;


		}
	}


};

class Goal {
public:
    string goalname;
    double targetamount;
    string targetdate;
    bool achieve;
    Goal* next;

    Goal() {
        goalname = " ";
        targetamount = 0;
        targetdate = " ";
        next = NULL;
    }

    Goal(string gn, double ta, string td) {
        goalname = gn;
        targetamount = ta;
        targetdate = td;
        next = NULL;
    }
};

class Financial_Goal {
private:
    static const int max_goals = 100;
    Goal* goals[max_goals];

public:
    Financial_Goal() {
        for (int i = 0; i < max_goals; i++) {
            goals[i] = nullptr;
        }
    }

    ~Financial_Goal() {
        for (int i = 0; i < max_goals; i++) {
            delete goals[i];
        }
    }

    int hashfunction(string key) {
        int hash = 0;
        for (int i = 0; i < key.length(); ++i) {
            char ch = key[i];
            hash += ch;
        }
        return hash % max_goals;
    }

    void set_Goal(string gn, double ta, string td) {
        int hash_val = hashfunction(gn);
        int init = -1;
        int delindex = -1;
        int i = 0;

        while (hash_val != init && (goals[hash_val] == NULL || (goals[hash_val] != NULL && goals[hash_val]->goalname != gn))) {
            if (init == -1)
                init = hash_val;

            if (goals[hash_val] == NULL) {
                delindex = hash_val;
            } else {
                hash_val = (hash_val + i) % max_goals;
                i++;
            }
        }

        if (goals[hash_val] == NULL || hash_val == init) {
            if (delindex != -1) {
                delete goals[delindex];
                goals[delindex] = new Goal(gn, ta, td);
            } else {
                goals[hash_val] = new Goal(gn, ta, td);
            }
        }

        if (init != hash_val) {
            if (goals[hash_val] != NULL) {
                if (goals[hash_val]->goalname == gn) {
                    goals[hash_val]->targetamount = ta;
                    goals[hash_val]->targetdate = td;
                }
            } else {
                goals[hash_val] = new Goal(gn, ta, td);
            }
        }
    }

    void Track_Progress() {
        for (int i = 0; i < max_goals; i++) {
            if (goals[i] != NULL) {
                cout << goals[i]->goalname << "->" << goals[i]->targetamount << "->" << goals[i]->targetdate << "->" << goals[i]->achieve << endl;
            }
        }
    }

    void Edit_Goal(string gn) {
        int hash_value = hashfunction(gn);
        int init = hash_value;
        int i = 0;

        while (goals[hash_value] != nullptr && goals[hash_value]->goalname != gn) {
            hash_value = (init + i) % max_goals;
            i++;

            if (hash_value == init) {
                cout << "No Data exist" << endl;
                return;
            }
        }

        if (goals[hash_value] == nullptr || goals[hash_value]->goalname != gn) {
            cout << "No Data exist" << endl;
            return;
        } else {
            if (goals[hash_value] != NULL && goals[hash_value]->goalname == gn) {
                int c;
                string d;
                double a;

                cout << "What do you want to change:" << endl;
                cout << "1. Date" << endl;
                cout << "2. Amount" << endl;
                cout << "3. Both Date and Amount" << endl;
                cin >> c;

                if (c == 1) {
                    cout << "Enter new Date:" << endl;
                    cin >> d;
                    goals[hash_value]->targetdate = d;
                } else if (c == 2) {
                    cout << "Enter new Amount:" << endl;
                    cin >> a;
                    goals[hash_value]->targetamount = a;
                } else if (c == 3) {
                    cout << "Enter new Date" << endl;
                    cin >> d;
                    cout << "Enter new Amount:" << endl;
                    cin >> a;
                    goals[hash_value]->targetdate = d;
                    goals[hash_value]->targetamount = a;
                }

                return;
            }
        }

        cout << "Goal Does not Exist" << endl;
    }

    void Complete_Goal(string gn) {
        for (int i = 0; i < max_goals; ++i) {
            if (goals[i] != nullptr && goals[i]->goalname == gn) {
                goals[i]->achieve = true;
                cout << "Goal '" << gn << "' marked as complete!" << endl;
                return;
            }
        }

        cout << "Goal '" << gn << "' not found." << endl;
    }
};
int same(RecordingExpenses& R)
{
	int i;
	R.getCategories();
	cout << "Enter the no. of the category : ";
	cin >> i;
	if (i >= n)
	{
		cout << "category doesnot exits" << endl;
	}
	return i;
}
void displayCenteredText(const std::string& text) {
    std::cout << std::string(40, '\n');
    std::string spaces(40 - text.length() / 2, ' ');
    std::cout << spaces << text << std::endl;
}
void displayExpenseTracker() {
	string str;
    std::cout << std::string(4, '\n');
    system("color 0B");
    std::cout<<endl;
    std::cout<<endl;
    std::cout<<endl;
    std::cout<<endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t######  ##     ##  #######  ####### ##         ## ##### ######  " << std::endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t##       ##   ##   ##   ##  ##      ####       ## ##    ##         "         << std::endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t##        ## ##    ##   ##  ##      ##  ##     ## ##    ##" << std::endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t######    ## ##    #######  ####### ##    ##   ## ##### ###### " << std::endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t##         ##      ##       ##      ##      ## ##    ## ##      " << std::endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t##       ##   ##   ##       ##      ##       ####    ## ##" << std::endl;
    std::cout <<setw(49)<<"               \t\t\t\t\t\t######  ##     ##  ##       ####### ##         ## ##### ######   " << std::endl;
    std::cout << std::string(1, '\n');
   
    std::cout <<setw(122)<< "  ########   #######   #######  ########  ##      ##  ######## ####### " << std::endl;
    std::cout <<setw(122)<< "     ##      ##   ##   ##   ##  ##        ##   ##     ##       ##   ## " << std::endl;
    std::cout <<setw(122)<< "     ##      ##   ##   ##   ##  ##        ##  ##      ##       ##   ## " << std::endl;
    std::cout <<setw(122)<< "     ##      #######   #######  ##        ###         ######## ####### " << std::endl;
    std::cout <<setw(122)<< "     ##      ##  ##    ##   ##  ##        ## ##       ##       ## ##   " << std::endl;
    std::cout <<setw(122)<< "     ##      ##   ##   ##   ##  ##        ##    ##    ##       ##   ## " << std::endl;
    std::cout <<setw(123)<< "     ##      ##    ##  ##   ##  ########  ##       ## ######## ##    ## " << std::endl;
	//this_thread::sleep_for(chrono::milliseconds(3000));
	cout<<"PRESS ANY KEY TO CONTINUE: "<<endl;
	cin>>str;
	system("CLS");
}
int main() {
    int i,sum=0,j;
    string n1,n2,n3;
    double a1;
    string d1;
	RecordingExpenses R1[MAX_SIZE];
	RecordingExpenses R;
	 Financial_Goal h1;
	User U;
	int a,b,index;
	double am;
	int y;
	string password;
	char character;
	string d, str;
	int choice;
	string username;
	int total=0;		
	int t;
	bool containsNumbers = false;
	int choice1;	  				 
								  
		system("color 0B");
	  // Set console color to black background and bright green text
	  displayExpenseTracker();
     system("CLS");
     cout<<setw(50)<<"Enter ANY OPTION: "<<setw(50)<<endl;
     cout<<setw(50)<<"1.SIGN UP "<<endl<<setw(50)<<"2.LOGIN IN"<<endl<<setw(46)<<"3.EXIT"<<endl;
     cin>>choice;
     switch (choice){
//--------------------------------------------SIGN UP PART----------------------------------------------------------------------------------
   	    case 1:
     		{
     			cout << "Enter username: ";
	            cin >> username;
                ifstream checkFile(username + ".txt");
	        if (!checkFile){
		             cout << "User is new. Please create a password: (max 8 characters)";
		             cin >> password;
		        if (password.length() > 8) {
			           cout << "Your password exceeds 8 characters" << endl;
		                  }
		        else {
			    U.registerUser(username, password);
			    cout << "Authentication successful!" << endl;
				 			    	char character;
									  				   	  	 int i=0; 	  
									ifstream f3("category.txt");	
									 if (f3.is_open()) {
									 		 cout<<"heh";
										  f3>>n;
											f3.get(character);
	  		                       		 			 
                           	while (getline(f3, category[i])) {
									cout<<"jdhf";
									i++;
									}
									 	 						 					  	f3.close()	;  
									}
									 	else {
					cout << "Unable to open the file.\n";
				}

									 
				cout<<"PRESS ANY KEY TO CONTINUE: ";
                cin>>str;
			do{
				system("CLS");
				cout<<setw(50)<<"CHOOSE ANY OPTION FROM THE MENU"<<endl;
				cout<<setw(50)<<"1.RECORD EXPENSE "<<endl<<setw(50)<<"2.DELETE EXPENSE "<<endl<<setw(47)<<"3.VIEW EXPENSE"<<endl<<setw(47)<<"4.EDIT EXPENSE"<<endl<<setw(57)<<"5.CATEGORY TOTAL EXPENSE"<<endl<<setw(51)<<"6.CATEGORY EXPENSE"
				<<endl<<setw(51)<<"7.REMOVE CATEGORY "	<<endl<<setw(49)<<"8.EDIT CATEGORY "<<endl<<setw(49)<<"9.VIEW CATEGORY "<<endl<<setw(48)<<"10.EDIT BUDGET "<<endl<<setw(50)<<"11.DELETE BUDGET "<<endl<<setw(48)<<"12.VIEW BUDGET "
				<<endl<<setw(49)<<"13.TRACK BUDGET "	<<endl<<setw(51)<<"14.BUDGET SUMMARY "<<endl<<setw(46)<<"15.SET A GOAL"<<endl<<setw(47)<<"16.EDIT A GOAL"<<endl<<setw(54)<<"17.MARK COMPLETE GOAL"<<endl<<setw(55)<<"18.TRACE YOUR PROGRESS"<<endl<<setw(40)<<"19.EXIT"<<endl;
				cin>>choice1;
				  
			    cout<<"PRESS ANY KEY TO CONTINUE: "<<endl;
                cin>>str;
				system("CLS");
				  switch(choice1)
				  {
				  	case 1:
				  		{
				  				
				  	  int i;
 				
					  
				
	i = R.recordExpense();
	int index = R.hash(i);
	int a;
	double am;
	string d, str;
	cout << "Enter Amount : ";
	cin >> a;

	cout << "Enter description: ";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, d);
    

    cout << "Enter name: ";
    
    getline(cin, str);

    for (int i = 0; i < str.length(); ++i) {
					        char c = str[i];
					        if (std::isdigit(c)) {
					            containsNumbers = true;
					            break;
					        }
					    }
					
					    if (containsNumbers) {
					        std::cout << "Invalid Input! The category name contains numbers." << std::endl;
					    } 
	
	cout << "enter your  budget for this category:" << endl;
	cin >> am;
	time_t now = time(0);
	char* dt = ctime(&now);
	 
	   j=index;
	R1[index].insert(a, str, d, dt, am);
	
					    
	                     break;
                    }
			
					case 2:
						{
							cout<<"delete EXPENSE :"<<endl;
                            i=	same(R);
                            R1[i].deleteExpense();
                            break;
						}
					case 3:
				  		{
				  			cout<<"VIEW EXPENSE :"<<endl;
                         for(i=0;i<n;i++)
				{		
						 	  	
			 	  	R1[i].viewExpenses();
				  cout<<endl;
				  }	
	
                            break;
				  	    }
					case 4:
						{
						  	cout<<"edit :"<<endl;
                            i=same(R);
                            R1[i].editExpense();	
                            break;
					    }
					case 5:
				  		{
				  		 for(i=0;i<n;i++){			 	  	
							total=0;	 
			 	  	        t=R1[i].calculateTotalExpenses(total);
					 	    sum=sum+t;											 		 	   				   
					 					}	
				            cout<<sum; 
				            break;
						 }
					case 6:
						{
						 i=same(R);
						 double s= R1[i].	CategoryExpense();
						 cout<<s;
						  break;	
					    }
			    	case 7:
				  		{
				  		  int i,j;
 				
					  
	cout<<"Remove :"<<endl;
i=same(R);
	 R1[i].head=NULL;
 
 	for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				while (j + 1 != n)
				{

					R1[j].head = R1[j + 1].head;
								  	 		 
					j++;
				}
				break;


			}
		}
		 R1[i].RemoveCategory(i);
                          break;
				  	}
					case 8:
						{
					
	                    R.EditCategory();
                          break;	
					    }
					case 9:
				  		{
				  		  cout<<"view :"<<endl;
                          i=same(R);
                          R1[i].viewCategory(R1[i].head);
                          break;
				  			
						 }
					case 10:
						{
						  i=same(R);
                          R1[i].EditBudgets(R1[i].head);
                          break;	
					    }
				    case 11:
				  		{
				  		  i=same(R);
				  		  R1[i].DeleteBudget(R1[i].head);
				  		  break;
						 }
					case 12:
						{
						  i=same(R);
				  		  R1[i].ViewBudgets(R1[i].head);
				  		  break;
						  		
					    }
					case 13:
				  		{
				  		 i=same(R);
				  		 R1[i].TrackBudget(R1[i].head);
				  		 break;
						 }
					case 14:
						{
						 i=same(R);
						 R1[i].GetBudgetSummary(R1[i].head);
	                     break;
					    }
					case 15: 
					    {
			            cout << "Enter Goal Name:" << endl;
			            cin.ignore();
			            getline(cin, n3);
			
			            cout << "Target Amount:" << endl;
			            cin >> a1;
			
			            cout << "Target Date:" << endl;
			            cin >> d1;
			
			            h1.set_Goal(n3, a1, d1);
			            break;
					        }
					case 16:
					   {
				        cout << "Enter a Goal name you want to edit" << endl;
				        cin.ignore();
				        getline(cin, n1);
				        h1.Edit_Goal(n1);
				        break;
					    }
                    case 17: 
					    {
					    	string s;
				        cout << "Enter Goal You Completed:" << endl;
				        cin.ignore()
;				        getline(cin,s);
				        h1.Complete_Goal(s);
				        break;
                       }
			        case 18:
			        	{
			            h1.Track_Progress();
			            break;
					    }
					    case 19:
					    	{
					    		 i=0;
 fstream f4("category.txt");
	if (f4.is_open()) {
		f4 << n;
		f4 << '\n';
		for(int i=0;i<n;i++)
		{
		 	f4<<category[i]<<'\n';
						  	
			}	
							
    f4.close();
	}
		else {
		cout << "Unable to open the file.\n";
	}

fstream f1(username + ".txt");

	if (f1.is_open()) {
		f1 << password;
		f1 << '\n';

		for (int i = 0; i < n; i++) {
			 
			 
			node* temp = R1[i].head;
			if (temp == nullptr){
							cout<<i;
				f1 << '\n';
				continue;
			}

			while (temp != nullptr) {
				f1 <<temp->amount<< " " << temp->budget<<'\n' << temp->name <<'\n'<< temp->description << '\n'  ;
									if(temp->next==NULL && j==i)
						 		 		{
											f1<< temp->date_time;				 	 															  	  												    	     	   							
										 } 
										 else
										 {
										  	  		f1<< temp->date_time<<'\n';																																									 	
										  }	 
					  	 if(temp->next!=NULL)
						 	{		  	
							 	f1<<'-';	
						    }					 	
																		 		  						 
				temp = temp->next;
			
		}
	}
		f1.close();

}
	else {
		cout << "Unable to open the file.\n";
	}
exit(0);
							}
		             default:
					    	{
					    	cout<<"Invalid Input!!"<<endl;
					    	exit(0);
							}
						}   
				        cout<<endl<<"Do You want to Continue(press 1 for yes and 0 for no):"<<endl;
						cin>>y;
						if(y!=0 &&y!=1){
							cout<<"Invalid Input"<<endl;	
				           }  
				  }while(y!=0||y!=19);
		       }
		   }

else
{
	cout<<"Please Try again..User Already Exists: "<<endl;
		}		break;
	}
	//---------------------------------------------LOGIN PART--------------------------------------------------------------------------		  
	 case 2:
			{
			cout << "Enter username: ";
	        cin >> username;
            ifstream checkFile(username + ".txt");
			if (checkFile) {
		           cout << "ACCOUNT ALREADY EXISITS. Please enter your password: ";
		           cin >> password;
		           if (password.length() > 8) {
		           cout << "Your password exceeds 8 characters" << endl;
                    }
		    else {
                if (U.authenticateUser(username, password)) {
				cout << "Authentication successful!" << endl;
					  	  				char character;
									  							 	   	  	 int i=0; 	  
									ifstream f3("category.txt");	
									 if (f3.is_open()) {
									 	
										  f3>>n;
											f3.get(character);
	  		                       		 
                           	while (getline(f3, category[i])) {
									
									i++;
									}
									 	 						 					  	f3.close()	;  
									}
									 	else {
					cout << "Unable to open the file.\n";
				}

									 
									 				
			
				ifstream f2(username + ".txt");
				string str, d;
				int a;
					 	 double b;
				char* dt;
				i=0;
				if (f2.is_open()) {
					string password;
					char character;

					f2 >> password;
					f2.get(character);
	  		string line;	 		 
	while (getline(f2, line)) {
    // Check if the line is empty
    if (line.empty()) {
 
    	R1[i].head=NULL;
    	i++;
        // Skip this line
        //cout<<"skip"<<i;
        continue;
    }

    stringstream ss(line);
    ss >> a >> b ;
    
getline(f2, line);
str=line;

getline(f2, line);
d=line;
  	const int bufferSize = 25;
							char buffer[bufferSize];
							f2.getline(buffer, bufferSize);
							char* dt = new char[strlen(buffer) + 1];
							strcpy(dt, buffer);
cout<<i;

    R1[i].insert(a, str, d, dt, b);
    	f2.get(character);
    	if(character != '-')
    	{
    		f2.unget();
    		i++;
		 }
    		
    
}
	f2.close();
		cout<<"PRESS ANY KEY TO CONTINUE: "<<endl;cin>>str;
				do{
				system("CLS");
				cout<<setw(50)<< "CHOOSE ANY OPTION FROM THE MENU"<<endl;
				cout<<setw(50)<<"1.RECORD EXPENSE "<<endl<<setw(50)<<"2.DELETE EXPENSE "<<endl<<setw(47)<<"3.VIEW EXPENSE"<<endl<<setw(47)<<"4.EDIT EXPENSE"<<endl<<setw(57)<<"5.CATEGORY TOTAL EXPENSE"<<endl<<setw(51)<<"6.CATEGORY EXPENSE"
				<<endl<<setw(51)<<"7.REMOVE CATEGORY "	<<endl<<setw(49)<<"8.EDIT CATEGORY "<<endl<<setw(49)<<"9.VIEW CATEGORY "<<endl<<setw(48)<<"10.EDIT BUDGET "<<endl<<setw(50)<<"11.DELETE BUDGET "<<endl<<setw(48)<<"12.VIEW BUDGET "
				<<endl<<setw(49)<<"13.TRACK BUDGET "	<<endl<<setw(51)<<"14.BUDGET SUMMARY "<<endl<<setw(46)<<"15.SET A GOAL"<<endl<<setw(47)<<"16.EDIT A GOAL"<<endl<<setw(54)<<"17.MARK COMPLETE GOAL"<<endl<<setw(55)<<"18.TRACE YOUR PROGRESS"<<endl<<setw(40)<<"19.EXIT"<<endl;
				cin>>choice1;
				cout<<"PRESS ANY KEY TO CONTINUE: "<<endl;
                cin>>str;
				system("CLS");
				switch(choice1)
				  {
				  	case 1:
				  		{
					    int i;
 				
					  
				
	i = R.recordExpense();
	int index = R.hash(i);
	int a;
	double am;
	string d, str;
	cout << "Enter Amount : ";
	cin >> a;

	cout << "Enter description: ";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, d);
    
cout<<d<<endl;
    cout << "Enter name: ";
    
    getline(cin, str);
    cout<<str;
    for (int i = 0; i < str.length(); ++i) {
					        char c = str[i];
					        if (std::isdigit(c)) {
					            containsNumbers = true;
					            break;
					        }
					    }
					
					    if (containsNumbers) {
					        std::cout << "Invalid Input! The category name contains numbers." << std::endl;
					    } 
	
	cout << "enter your  budget for this category:" << endl;
	cin >> am;
	time_t now = time(0);
	char* dt = ctime(&now);
	 
	   j=index;
	    cout<<index;
	R1[index].insert(a, str, d, dt, am);
	
					    
//								cout << "Authentication failed. Incorrect password." << endl;
							//}
				    system("CLS"); 
				    break;
					}
					case 2:
					   {
						cout<<"delete EXPENSE :"<<endl;
	                    i=	same(R);
	                    R1[i].deleteExpense();
	                    break;
						  		
					    }
					case 3:
				  	   {
				  		cout<<"VIEW EXPENSE :"<<endl;
                            for(i=0;i<n;i++)
				{		
						 	  	
			 	  	R1[i].viewExpenses();
				  cout<<endl;
				  }	
                        break;
				  			
						 }
					case 4:
						{
						 cout<<"edit :"<<endl;
						 i=same(R);
						 R1[i].editExpense();	
						 break;
					    }
					case 5:
				  		{
				  		 for(i=0;i<n;i++){			 	  	
								total=0;	 
				 	  	        t=R1[i].calculateTotalExpenses(total);
						 	    sum=sum+t;											 		 	   				   
					 		      }	
				          cout<<sum; 
				          break;
						 }
					case 6:
						{
						 i=same(R);
						 R1[i].CategoryExpense();
						 break;	
					    }
					case 7:
				  		{
				  		 int i,j;
 				
					  
	cout<<"Remove :"<<endl;
i=same(R);
	 R1[i].head=NULL;
 
 	for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				while (j + 1 != n)
				{

					R1[j].head = R1[j + 1].head;
								  	 		 //cout<<R1[i].head->amount; 
					j++;
				}
				break;


			}
		}
		 R1[i].RemoveCategory(i);
                          break;
				  		}
					case 8:
						{
					  	 
                         R.EditCategory();
                         break;	
					    }
					case 9:
				  		{
				  		 cout<<"view :"<<endl;
                         i=same(R);
                         R1[i].viewCategory(R1[i].head);
                         break;
				  		}
					case 10:
						{
	                     i=same(R);
                         R1[i].EditBudgets(R1[i].head);
                         break;	
				       }
					case 11:
				  		{
			  			 i=same(R);
			  			 R1[i].DeleteBudget(R1[i].head);
			  			 break;
						 }
					case 12:
						{
						 i=same(R);
			  			 R1[i].ViewBudgets(R1[i].head);
			  			 break;
						}
					case 13:
				  		{
		  				 i=same(R);
			  			 R1[i].TrackBudget(R1[i].head);
			  			 break;
						 }
					case 14:
						{
						 i=same(R);
					  	 R1[i].GetBudgetSummary(R1[i].head);
                       	break;
					    }
					case 15: 
					    {
			            cout << "Enter Goal Name:" << endl;
			            cin.ignore();
			            getline(cin, n3);
			
			            cout << "Target Amount:" << endl;
			            cin >> a1;
			
			            cout << "Target Date:" << endl;
			            cin >> d1;
			
			            h1.set_Goal(n3, a1, d1);
			            break;
					        }
					case 16:
					   {
				        string n1;
				        cout << "Enter a Goal name you want to edit" << endl;
				        cin.ignore();
				        getline(cin, n1);
				        h1.Edit_Goal(n1);
				        break;
					    }
                    case 17: 
					    {
				        string s;
				        cout << "Enter Goal You Completed:" << endl;
				        cin.ignore();
				        getline(cin,s);
				        h1.Complete_Goal(s);
				        break;
                       }
			        case 18:
			        	{
			            h1.Track_Progress();
			            break;
					    }  
						case 19:
						{
							 i=0;
 fstream f4("category.txt");
	if (f4.is_open()) {
		f4 << n;
		f4 << '\n';
		for(int i=0;i<n;i++)
		{
		 	f4<<category[i]<<'\n';
						  	
			}	
							
    f4.close();
	}
		else {
		cout << "Unable to open the file.\n";
	}

fstream f1(username + ".txt");

	if (f1.is_open()) {
		f1 << password;
		f1 << '\n';

		for (int i = 0; i < n; i++) {
			 
			 
			node* temp = R1[i].head;
			if (temp == nullptr){
						
				f1 << '\n';
				continue;
			}

			while (temp != nullptr) {
				f1 <<temp->amount<< " " << temp->budget<<'\n' << temp->name <<'\n'<< temp->description << '\n'  ;
									if(temp->next==NULL && j==i)
						 		 		{
											f1<< temp->date_time;				 	 															  	  												    	     	   							
										 } 
										 else
										 {
										  	  		f1<< temp->date_time<<'\n';																																									 	
										  }	 
					  	 if(temp->next!=NULL)
						 	{		  	
							 	f1<<'-';	
						    }					 	
																		 		  						 
				temp = temp->next;
			
		}
	}
		f1.close();

}
	else {
		cout << "Unable to open the file.\n";
	}
exit(0);
						  }  
					default:
					    	{
					    	cout<<"Inavlid Input"<<endl;	
																		  	  i=0;
fstream f4("category.txt");
	if (f4.is_open()) {
		f4 << n;
		f4 << '\n';
		for(int i=0;i<n;i++)
		{
		 	f4<<category[i]<<'\n';
						  	
			}	
							
    f4.close();
	}
		else {
		cout << "Unable to open the file.\n";
	}

fstream f1(username + ".txt");

	if (f1.is_open()) {
		f1 << password;
		f1 << '\n';

		for (int i = 0; i < n; i++) {
			 
			 
			node* temp = R1[i].head;
			if (temp == nullptr){
							cout<<i;
				f1 << '\n';
				continue;
			}

			while (temp != nullptr) {
				f1 <<temp->amount<< " " << temp->budget<<'\n' << temp->name <<'\n'<< temp->description << '\n' << temp->date_time<<'\n' ;
								
					  	 if(temp->next!=NULL)
						 	{		  	
							 	f1<<'-';	
						    }					 	
																		 		  						 
				temp = temp->next;
			
		}
	}
		f1.close();

}
	else {
		cout << "Unable to open the file.\n";
	}
      
					    	exit(0);
							}
						}
						cout<<endl<<"Do You want to Continue(press 1 for yes and 0 for no):"<<endl;
						cin>>y;
						if(y!=0 &&y!=1){
							cout<<"Invalid Input"<<endl;	
					}
				}while(y!=0||y!=19);
						 break;			 									
				}
			   else {
			
		
				
				cout << "Unable to open the file.\n";
				}
				 		  	ofstream F( "category.txt", ios::trunc);

				if (F.is_open()) {
				
					F.close();
					//cout << "File " << filename << " has been emptied." << std::endl;
				}
				else {
					cout << "Unable to open file for truncation." << std::endl;
				}

				ofstream f(username + ".txt", ios::trunc);

				if (f.is_open()) {
				
                  //  }
					f.close();
					//cout << "File " << filename << " has been emptied." << std::endl;
				}
				else {
					cout << "Unable to open file for truncation." << std::endl;
				}

			}
			else {
				cout << "Authentication failed. Incorrect password." << endl;
			}
		
	
}
}
}
									 
									 
									 				
			
			
//---------------------------------------------EXIT PART------------------------------------------------------------------------------------
	
	case 3:
			{
            
			exit(0);	
			}
		}
		
				return 0;
}