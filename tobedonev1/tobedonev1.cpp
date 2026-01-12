#define _CRT_SECURE_NO_WARNINGS //some weird compiler shit 
#include <iostream>//for input and output
#include <fstream>//files
#include <string>
#include <limits>
#include <ctime> //time related library
#include <vector>

using namespace std;//shortcuts

string filename = "todo_list.txt";
bool running = true;
int option;
//int num_lines;
string todo_item;
string items;//to store lines
string line;//for new lines


//functions
void dis_options(){
    cout<<"choose option"<<endl;
    cout<<""<<endl;
    cout<<"1.read\n2.add\n3.delete\n4.edit\n5.clear\n6.exit";
}

//basic information stream to connect txt to program
vector <string> get_todos(const string & filename) {
	ifstream read_list(filename);//init the object

    //test 
	if (!read_list.is_open()){
		cerr<<"couldn't read file";
	}

    //to extract and store todos
    vector <string> todos;

	while(getline(read_list,todo_item)){
        todos.push_back(todo_item);
	}

	read_list.close();
    return todos;
}

void read_file(vector <string>& todo_items) {
    //should i read from file or vector
    int line_num = 1;

    for (string item : todo_items) {
        ++line_num;
        cout << line_num << ". " << item << endl;
    }

}

void write_to_file(vector <string>& todo_items, string& filename) {

    ofstream out_file(filename);
    if (!out_file) {
        cerr << "cant write to file";
    }
    string line;
    getline(cin, line);
    todo_items.push_back(line);

    //the stored todo_items all write at once to file 
    for (string item : todo_items) {
        out_file << item;
    }
}

void del_item(vector <string>& todo_items,string & filename) {
    
    int del_line;
    cout << "which line would u like to delete: ";
    cin >> del_line;

    auto del_item = (todo_items.begin() + (del_line-1));

    todo_items.erase(del_item);

    ofstream out_file(filename);
    
    for (string item : todo_items) {
        out_file << item << "\n";
    }

}

void clear_todos(vector <string> & todo_items,string & filename) {
    todo_items.erase(todo_items.begin(), todo_items.end());
    ofstream outfile(filename);
    for (string item : todo_items) {
        outfile << item;
    }
}

void edit_line(vector <string> & todo_items,string filename ) {
    cout << "which line would you like to edit" << endl;
    int edit_line;
    cin >> edit_line;

    cin.ignore();
    cout << "write the edit" << endl;
    string replace_line;
    getline(cin, replace_line);

    todo_items.at(edit_line-1) = replace_line;
    ofstream out_file(filename);

    for (string item : todo_items) {
        out_file << item;
    }
}



int main(){
    time_t timestamp;
    time(&timestamp);

    vector <string> todo_things = get_todos("todo_list.txt");

    while(running){
        dis_options();

        cin >> option;

        // clear leftover newline or the stream i think
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(option)
        {
                case 1:{
                    // param vec into read file than loop through the vecter of todos
                    read_file(todo_things);
                    break;
                }

                case 2:{
                    write_to_file(todo_things,filename);
                    break;
                }

                case 3:{
                    del_item(todo_things,filename);
                    break;

                }

                case 4:{
                    //edit get vect change content write to file
                    edit_line(todo_things,filename);
                    break;
                }

                case 5:{
                    clear_todos(todo_things,filename);
                    break;
                }
                case 6:{
                    running = false;//terminate application
                    break;
                }
                    
                default:{
                    cout<<"choose valid option: 1-6";
                    break;
                }
            
            }
    }
   
    return 0;
}

//format the time
//remove words in console
//removing lines
//time of addition of item maybe expected time to finish but that dont align with your values


/*
void read_file() {
	ifstream read_list("todo_list.txt");//init the object
	//test
	if (!read_list.is_open()){
		cerr<<"couldn't read file";
	}

	//go through the file and display all items prolly returns bool
	while(getline(read_list,items)){
		cout<<items<<endl;
	}

	read_list.close();
}

void write_file() {
    ofstream write_file("todo_list.txt",ios::app);

	if (!write_file.is_open()){
		cerr<<"couldn't write to file";
	}

	//adding to file
	getline(cin,line);
    write_file << num_lines << "." << line << " - "; //<< ctime(&timestamp);

	//for safty reasons
	write_file.close();
}
*/

