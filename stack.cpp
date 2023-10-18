/*
Lei(Raymond) Chi 

This program reads the input file of foobars line by line and then rewrite
them into a output file with the name of the foobars and the strength of it.
The strength is determined by the position and the type of the foobar

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std; 



class FooBar{ //based class
// name, position, strength 
    protected: 
        string Name;
        int Position; 
        int Strength;
    public:
        FooBar(string &name){ //constructor 
            int Position = 0; 
            Name = name;
        }
        void UsePosition(int p) { // to interact with position outside of protected class 
            Position = p;
        }
        virtual int ItsStrength(){
            Strength = Position;
            return Strength; 
        } 
        string &ItsName() {
            return Name;
        }

};

class Foo: public FooBar{ //derived class
    public:
        Foo(string &name) : FooBar(name){}
        int ItsStrength(){
            Strength = Position * 3;
            return Strength;
        }
};

class Bar: public FooBar{
    public:
        Bar(string &name) : FooBar(name){}
        int ItsStrength(){
            Strength = Position + 15;
            return Strength;
        }
};


void SortFooBar(vector<FooBar*> &FooBarVector);
void ReversePosition (vector <FooBar*> & FooBarVector);
void PrintOutFile(vector<FooBar*> &FooBarVector);

int main(){
    vector<FooBar*> foobar;
    SortFooBar(foobar);
    ReversePosition(foobar);
    PrintOutFile(foobar);
    foobar.clear(); 
    return 0;  
}


void SortFooBar(vector<FooBar*> &FooBarVector){
    string InFile;// ask for input file 
    std::cout << "Enter the name of the input file: ";
    std::cin >> InFile;

    ifstream MyFile;
    MyFile.open(InFile);
    std::stringstream Fileline;
    string line; 
    string typeofFooBar;
    string nameofFooBar;

  

    while(!MyFile.eof()){ //run til the end of the file 
        
        getline(MyFile, line);

        //cout << line << endl;

        Fileline << line << endl; 
        //read the foobar or foo or bar, which is the first word of each line
        Fileline >> typeofFooBar; 
        //feed to the string of type of foobar
        typeofFooBar+="\n";

        Fileline >> nameofFooBar;

        if(typeofFooBar == "foobar\n"){
            
            FooBarVector.push_back(new FooBar(nameofFooBar)); 
        }//constructor new create foobar and add it into the vector 

        else if(typeofFooBar == "bar\n"){
            
            FooBarVector.push_back(new Bar(nameofFooBar));
        }

        else if(typeofFooBar == "foo\n"){
            
            FooBarVector.push_back(new Foo(nameofFooBar)); 
        }


        Fileline.str("");

    }

    MyFile.close();

}

void ReversePosition (vector <FooBar*> & FooBarVector){ //
    //int i = FooBarVector.size()-1;

    int j = 0;
  
    for (FooBar* i : FooBarVector) {
        i->UsePosition(FooBarVector.size()-j);
        j++;
    }
}

void PrintOutFile(vector<FooBar*> &FooBarVector) { //write into output file 
    string OutFileName; // get output file
    std::cout << "Enter the name of the output file: ";
    std::cin >> OutFileName;
    ofstream OutFile(OutFileName);


    //OutFile.open(OutFileName);
    for (FooBar* i : FooBarVector) {

        OutFile << i->ItsName();
        OutFile << " ";
        OutFile << i->ItsStrength(); 
        OutFile << "\n";
    }
    OutFile.close();  
}
