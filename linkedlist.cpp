#include <iostream>//Lei (Raymond) Chi: Program 2
#include <fstream>
#include <sstream>
#include <list>
#include <string>


using namespace std;


template <typename AnyDataType>
class SimpleList {
    
    private: 
        class Node{// the private node class declaration 
            public: 
                AnyDataType data; 
                Node *next;
                Node(const AnyDataType & d){
                    data = d;
                    next = nullptr;
                }
                Node(const AnyDataType & d, Node * n){
                    data = d;
                    next = n;
                }

        };
    
        Node *HeadNode = nullptr;//setting it as a nullptr first and add on to it 
        Node *TailNode = nullptr;
        int ListSize = 0;// increments as nodes are added in, for the purpose of pop function 
        string name;
    protected:
        explicit SimpleList(const string n){
            name = n; 
        }
        void InsertAtStart(AnyDataType d){ // for stack 
            Node *NewNode = new Node(d);
            if(ListSize == 0){
                HeadNode = NewNode;
                TailNode = NewNode;
            }
            else{
                NewNode -> next = HeadNode;
                HeadNode = NewNode; 
            }
            ListSize ++; 

        }
        void InsertAtEnd(AnyDataType d){//for queue to be pushed from end of it 
            Node *NewNode = new Node(d);
            if(ListSize == 0){
                HeadNode = NewNode;
                TailNode = NewNode;
            }
            else{
               TailNode -> next = NewNode;
               TailNode = NewNode;
            }
            ListSize ++;
        }
        AnyDataType RemoveNode(){//removing head node for both stacks and queues
            Node *OldHeadNode;
            AnyDataType d;
            OldHeadNode = HeadNode;  //changing the order of which one headnode is
            HeadNode = HeadNode->next;
            d = OldHeadNode->data;
            delete OldHeadNode;
            ListSize --;
            return d;
        }
    public:
        virtual AnyDataType pop(){
            return RemoveNode();
        }

        
        string &GetName(void){//accessing private member function 
            return name; 
        }
        int &GetSize(void){//accessing private member function 
            return ListSize; 
        }

        virtual void push(AnyDataType d){} //indicating in derived class


};

template <typename AnyDataType>
class Queue : public SimpleList<AnyDataType>{//derived classes
    public:
        explicit Queue(string n):SimpleList<AnyDataType>(n){};
        void push(AnyDataType d){
            this->InsertAtEnd(d);
        }
};

template <typename AnyDataType>
class Stack : public SimpleList<AnyDataType>{
    public:
        explicit Stack(string n):SimpleList<AnyDataType>(n){};
        void push(AnyDataType d){
            this->InsertAtStart(d);
        }
};

template <typename AnyDataType>//using template to search for the name of simplelist to see if it exist or not 
SimpleList <AnyDataType> * SearchList(list<SimpleList <AnyDataType> *> &lists, string &name){
    string NameOfList;
    for(auto i : lists){
        NameOfList = i->GetName();
        if (NameOfList == name)
        {
            return i; // returning as either a pointer to the list or just a nullptr, to indicate existance 
        }
    }
    return nullptr; 
}


void CommandReading(list<SimpleList <int> *> &IntList, list<SimpleList <double> *> &DouList, list<SimpleList <string> *> &StrList){
    string OutFile;
    string InFile;
    cout << "Enter name of the input file: ";
    cin >> InFile;
    ifstream MyFile;
    MyFile.open(InFile);
    cout << "Enter name of the output file: ";
    cin >> OutFile;
    ofstream OutputFile(OutFile);
    string line;
    string name, command, type;
    stringstream StringObj; 

    while(getline(MyFile, line).good()){// loop until the end of file, so we access all run through 
        //getline(MyFile, line);
        //OutputFile << line << endl;
        StringObj << line << endl; //using stringstream to pipe out each word 
        StringObj >> command;
        StringObj >> name;

        if (command!="pop") {// after stringstream piped out the command i can do comparison with string 
        StringObj >> type;
        
        }

        OutputFile << "PROCESSING COMMAND: " << command << " " << name; //printing in unix style, also leave the end for different variation
        // cout << command << endl;

        // cout << name << endl;

        // cout << type << endl;

        SimpleList <int> * x;//create int, double and string lists seperately

        SimpleList <double> * y;

        SimpleList <string> * z;

        if (name.front() == 'i') {//since only the first letter indicates the type of the list, so name front reads it for me 

            x = SearchList(IntList, name);

        } 
        else if (name.front() == 'd') {

            y = SearchList(DouList, name);
            
        } 
        else if (name.front() == 's') {

            z = SearchList(StrList, name);
 
        }

        if (command == "create") {// seperating all three of the commands to make it act differently 

            OutputFile << " " << type << endl;

            if(name.front() == 'i') {// when creating int list
                if (x == nullptr) {//indicates if the simplelist is already created, the returned pointer
                    if(type == "stack") {
                        IntList.push_back(new Stack<int>(name));//creating according if it is a stack or a queue 

                    } 
                    else if (type == "queue") {
                        IntList.push_back(new Queue<int>(name));
                    }
                } 
                else {
                    OutputFile << "ERROR: This name already exists!" << endl;
                }
            }

            if(name.front() == 'd') {// when creating double list 
                if (y == nullptr) {//indicates if the simplelist is already created, the returned pointer
                    if(type == "stack") {
                        DouList.push_back(new Stack<double>(name));//creating according if it is a stack or a queue 

                    } 
                    else if (type == "queue") {
                        DouList.push_back(new Queue<double>(name));
                    }
                } 
                else {
                    OutputFile << "ERROR: This name already exists!" << endl;
                }
            }

            if(name.front() == 's') {// when creating string list 
                if (z == nullptr) {//indicates if the simplelist is already created, the returned pointer
                    if(type == "stack") {
                        StrList.push_back(new Stack<string>(name));//creating according if it is a stack or a queue 

                    } 
                    else if (type == "queue") {
                        StrList.push_back(new Queue<string>(name));
                    }
                } 
                else {
                    OutputFile << "ERROR: This name already exists!" << endl;
                }
            }

        }
        if (command == "push") { //condition for if the command reads push 

            OutputFile << " " << type << endl;

            if(name.front() == 'i') {//if it is a integer list

                if (x != nullptr) {
                    int num = atoi(type.c_str());// using atoi to convert the read string to an integer
                    x->push(num);
                } 
                else {
                    OutputFile << "ERROR: This name does not exists!\n";
                }
            }

            if(name.front() == 'd') {//if it is a double 
                if (y != nullptr) {
                    double numd = stod(type);// using stod to convert the string to double
                    y->push(numd);
                } 
                else {
                    OutputFile << "ERROR: This name does not exists!\n";
                }
            }

            if(name.front() == 's') {//if it is a string simplelist
                if (z != nullptr) {
                    z->push(type);
                } 
                else {
                    OutputFile << "ERROR: This name does not exists!\n";
                }
            }
        }
        if (command == "pop") {//condition for if the command reads pop
            OutputFile << endl;
            if(name.front() == 'i') {
                if (x != nullptr){
                    if (x->GetSize() > 0){//accessing the size to indicate if the list is empty
                        OutputFile << "Value popped: " << x->pop() << endl; 
                    }
                    else{
                        OutputFile<<"ERROR: This list is empty!"<<endl;
                    }
                }
                else{
                    OutputFile<<"ERROR: This name does not exist!"<<endl;
                }
            }

            if(name.front() == 'd') {
                if (y!= nullptr){
                    if (y->GetSize() > 0){//accessing the size to indicate if the list is empty
                        OutputFile << "Value popped: " << y->pop() << endl; 
                    }
                    else{
                        OutputFile<<"ERROR: This list is empty!"<<endl;
                    }
                }
                else{
                    OutputFile<<"ERROR: This name does not exist!"<<endl;
                }
            }

            if(name.front() == 's') {
                if (z!= nullptr){
                    if (z->GetSize() > 0){//accessing the size to indicate if the list is empty
                        OutputFile << "Value popped: " << z->pop() << endl; 
                    }
                    else{
                        OutputFile<<"ERROR: This list is empty!"<<endl;
                    }
                }
                else{
                    OutputFile<<"ERROR: This name does not exist!"<<endl;
                }
            }
        }
    }
    MyFile.close();
    OutputFile.close();
}

int main (void) {

    list <SimpleList<int>*> ListSLi;
    list <SimpleList<double>*> ListSLd;
    list <SimpleList<string>*> ListSLs;

    CommandReading(ListSLi, ListSLd, ListSLs);

    return 0;
}