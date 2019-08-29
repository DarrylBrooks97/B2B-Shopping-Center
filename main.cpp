/**************************************************************
 *
 * GROUP # 4
 * Group Members: Darryl Brooks, Kayla Burke, DeCarlo Carr, Darius Groves, Roderick Harris
 * Date Completed: April 10, 2019
 * Filename: shoppingCart.cpp
 *
 **************************************************************/

#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

struct Address{
    string streetAddress;
    string city;
    string state;
    string zipCode;
};

struct Customer{
    string customerNum;
    string customerName;
    double lineOfCredit;
    Address * corperateAddress;
};

struct Product{
    int itemNo;
    string description;
    double price;
};

struct Memory{
    int position;
    int quantity;
    double cartTotal;
    double remainFunds;
};

vector<string> parse(string, char);
void readData(Customer[],vector<Address>&,vector<Product>&);
void selectionSort(Customer[],vector<Address>&);
int binarySearch(Customer[],int);
int linearSearch(Customer[],string);
int linearSearchInvent(vector<Product>,int);
string upperCaseIt(string);
string generateOrderNum();
int linearSearchAddress(vector<Address>,string);

int main(){
    Memory memObj;
    Customer custInfo[21];
    vector<Address>   custAdd;                  //*************ADDRESS VECTOR************
    vector<Product>  custProd;
    vector<Memory>    custMem;
    int numPos,prodCode,prodPos,quantity,position,ender=1,number;
    string empName,cusName,option;
    string choice,choice2,choice3,temp,temp2,temp3;
    double total,finalTotal;
    double funds;
    
    string fileName;
    fileName=generateOrderNum();                         //Order number is generated
    ofstream outF;
    outF.open(fileName.c_str());                         //Creates output file's name by order number
    
    
    readData(custInfo,custAdd,custProd);                //Loads Structs with file information
    selectionSort(custInfo,custAdd);                    //Sorts Customer numbers Asc->Des
    
    cout<<string(40,'-')<<endl;
    cout<<"     WELCOME TO B2B SHOPPING CENTER"<<endl;
    cout<<string(40,'-')<<endl;
    cout<<"\nHas a customer placed an order? Y/N:";
    getline(cin,choice);
    while( (choice!="Y") && (choice!="y") && (choice!="N") && (choice!="n")  ){
        cout<<"Incorrect input. Try again"<<endl;
        cout<<"Has a customer placed an order? Y/N:";
        getline(cin,choice);
    }
    
    if(choice=="Y" || choice== "y"){
        
        cout<<"Enter Employee name: ";
        getline(cin,empName);
        cout<<"Would you like to search customer by Name or Number?:";
        getline(cin,option);
        option=upperCaseIt(option);                                       //Fixes case sensitivity
        
        while((option!="NAME") && (option!="NUMBER")){
            cout<<"Please enter Name or Number:";
            getline(cin,option);
            option = upperCaseIt(option);                                 //Fixes case sensitivity
        }
        
        if(option=="NAME"){
            
            cout<<"Enter customer's name: ";
            getline(cin,cusName);
            
            numPos = linearSearch(custInfo,cusName);                    //Searches Customer's file for correct name then returns it's position
            
            while(numPos==-1){                                          //Keeps asking the user for the correct customer name
                cout<<"Name not found"<<endl;
                cout<<"Please try again"<<endl;
                cout<<"Enter customer's name: ";
                getline(cin,cusName);
                numPos = linearSearch(custInfo,cusName);                    //Searches Customer's file for correct name then returns it's position
            }
            
        }else if(option=="NUMBER"){
            cout<<"Enter Customer number: ";
            getline(cin,temp);
            number=atoi(temp.c_str());
            numPos = binarySearch(custInfo,number);                     //Searches Customer's file for correct customer number then returns it's position
            
            while(numPos==-1){                                        //Keeps asking the user for the correct Customer number
                cout<<"Customer not found"<<endl;
                cout<<"Please try again"<<endl;
                cout<<"Enter Customer number: ";
                getline(cin,temp);
                number=atoi(temp.c_str());
                numPos = binarySearch(custInfo,number);                 //Searches Customer's file for correct number then returns it's position
            }
            
        }
        funds=custInfo[numPos].lineOfCredit;                      //Sets funds to how much credit the customer has
        //May need another if statement
        cout<<"Would you like add a product? Y/N:";
        getline(cin,choice2);
        
        while( (choice2!="Y") && (choice2!="y") && (choice2!="N") && (choice2!="n")){
            cout<<"Invalid input. Try again Y/N:";
            getline(cin,choice2);
        }
        
        if((choice2=="Y") || (choice2=="y")){
            
            while(ender){
                
                cout<<"Enter Product code: ";
                getline(cin,temp2);
                prodCode=atoi(temp2.c_str());
                prodPos=linearSearchInvent(custProd,prodCode);                  //Searches Inventory file for Item then returns it's Position
                
                while(prodPos==-1){                                                      //Keeps asking the user for the correct Product number
                    cout<<"Item not found"<<endl;
                    cout<<"Please try again"<<endl;
                    cout<<"Enter Product code:";
                    getline(cin,temp2);
                    prodCode=atoi(temp2.c_str());
                    prodPos = linearSearchInvent(custProd,prodCode);                //Searches Inventory file for Item then returns it's Position
                }
                
                cout<<"Enter quantity: ";                                       //Lets user enter quantity
                cin>>quantity;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(256,'\n');
                    cout<<"Enter quantity: ";
                    cin>>quantity;
                }
                cin.ignore(256,'\n');
                
                memObj.position=prodPos;                                        //Records where the product is at
                memObj.quantity=quantity;                                       //Saves quantity of product
                
                memObj.cartTotal=custProd[memObj.position].price * memObj.quantity;
                funds-=memObj.cartTotal;
                
                if(funds<=0){
                    cout<<"Insuffcient funds"<<endl;                            //Doesn't add the product to memory and returns the funds
                    funds+=memObj.cartTotal;
                    
                }else {
                    custMem.push_back(memObj);                                  //Adds the product to memory
                }
                
                cout<<"Would you like to add another product? Y/N:";
                getline(cin,choice3);
                
                while( (choice3!="Y") && (choice3!="y") && (choice3!="N") && (choice3!="n")  ){
                    cout<<"Incorrect input. Try again"<<endl;
                    cout<<"Would you like to add another product? Y/N:";
                    getline(cin,choice3);
                }
                if((choice3=="N") || (choice3=="n")) ender=0;
            }
            
        } else {
            cout<<"Order Cancelled"<<endl; exit(0);       //Customer does not want to order so this ends the program
        }
        
    } else {
        cout<<"Have a nice day"<<endl; exit(0);
    }
    
    
    
    outF<<string(65,'-')<<endl;
    outF<<"B2B Shopping Cart"<<endl;
    outF<<string(65,'-')<<endl;
    outF<<"Order Number: "<<fileName<<endl;
    outF<<"Associate: "<<empName<<endl;
    outF<<"Customer Number: "<<custInfo[numPos].customerNum<<endl;
    outF<<"Customer: "<<custInfo[numPos].customerName<<endl;
    outF<<"Address: "<<custInfo[numPos].corperateAddress->streetAddress<<" |"<<endl;
    outF<<custInfo[numPos].corperateAddress->city<<", "<<custInfo[numPos].corperateAddress->state<<" "<<custInfo[numPos].corperateAddress->zipCode;
    outF<<endl;
    outF<< string(65,'-')<<endl;
    outF<< setw(20) << left << "Item No" << setw(25) << left<< "Description" << setw(10)<< left << "Qty" << setw(5) << "Total" << endl << string(65,'-') << endl;
    
    for(int k=0;k<custMem.size();k++){
        position=custMem[k].position;
        finalTotal+=custMem[k].cartTotal;
        outF<< setw(15) << left << custProd[position].itemNo << setw(30);
        outF<< left << custProd[position].description << left << setw(10);
        outF<< custMem[k].quantity << fixed << setprecision(2)<< "$" << custMem[k].cartTotal << endl;
    }
    
    outF<< string(65,'-') << endl << setw(55) << left << "Total "<< fixed << setprecision(2)<< "$" << finalTotal<< endl << string(65,'-') << endl;
    outF<< setw(55) << left << "Remaining Credit " << fixed << setprecision(2) << "$"<< funds<< endl;
    outF<<endl<<endl<<endl;
    outF<<string(17,' ');
    for (int i = 0; i < 1; i++){
        outF<< "\342\230\272" << "\t";    //Prints smiley face
    }
    outF<<"THANK YOU FOR CHOOSING B2B SHOPPING   ";
    
    for (int i = 0; i < 1; i++){
        outF<< "\342\230\272" << "\t";
    }
    
    outF.close();
    return 0;
}



void readData(Customer cInfo[], vector<Address>&cAdd, vector<Product>&pAdd){
    Address street;
    Customer add;
    Product product;
    vector<string> custInfo;
    vector<string> custAddress;
    vector<string> custProduct;
    ifstream file,stock;
    file.open("customers.dat");
    stock.open("inventory.dat");
    string line,location,inventory;
    int check=-1;
    int index=0;
    int pos=0;
    Address *ptr;
    
    
    while(!stock.eof()) {
        getline(stock,inventory);                      //Gets full lines from inventory.dat file
        custProduct=parse(inventory,',');              //Parse the inventory to go into Product struct
        
        product.itemNo=atoi(custProduct[0].c_str());  //Needed to convert from string to int
        product.description=custProduct[1];
        product.price=atof(custProduct[2].c_str());   //Needed to convert from string to double
        pAdd.push_back(product);                      //Adding objects into Product  vector
    }
    
    
    
    while(!file.eof()) {
        
        getline(file,line);                           //Gets full lines from customers.dat file
        custInfo=parse(line,'|');                     //Parse's "line" until it reaches '|'
        
        
        add.customerNum=custInfo[0];                  //Adds 1st parse to the Struct member
        add.customerName=custInfo[1];                 //Adds 2nd parse to the Struct member
        add.lineOfCredit=atof(custInfo[2].c_str());   //Needed to convert from string to double then places into Struct member
        location=custInfo[3];                         //Adds 3rd parse to a new string so we can parse that string for the Address struct
        
        
        custAddress=parse(location,',');                   //Parse the location to go into Address struct
        check = linearSearchAddress(cAdd,custAddress[0]);  //Checks Address vector to see if there is the same location
        
        street.streetAddress=custAddress[0];               //Adds 1st parse to the Struct member
        street.city=custAddress[1];                        //Adds 2nd parse to the Struct member
        street.state=custAddress[2];                       //Adds 3rd parse to the Struct member
        street.zipCode=custAddress[3];                     //Adds 4th parse to the Struct member
        
        if(check==-1){                                     //If address is not found then add it to the Address vector
            cAdd.push_back(street);                        //*****Adding objects into the ADDRESS VECTOR without duplicates*******
            ptr = &street;
        }
        cInfo[index] = add;
        ++index;
    }
    vector<Address>::iterator increment = cAdd.begin();   //Iterates through address vector
    
    for (int i = 0; i<21; i++){
        if( (i==9) || (i==17) ){
            cInfo[i].corperateAddress = &cAdd[8];
            increment-=1;
        }else {
            cInfo[i].corperateAddress = &(*(increment+i));
        }
    }
    
    
    file.close();                                         //Closes Customers file
    stock.close();                                        //Closes Inventory file
}

void selectionSort(Customer cVector[],vector<Address>&aVector){     //Sorts the customer vector by customer number
    
    int minPos;
    Customer tempObj;
    
    for(int i=0;i<21;i++){
        minPos=i;
        tempObj = cVector[i];
        
        for(int k=i+1;k<21;k++){
            if(cVector[minPos].customerNum>cVector[k].customerNum){
                minPos=k;
                tempObj = cVector[k];
            }
        }
        
        cVector[minPos] = cVector[i];
        cVector[i] = tempObj;
    }
}

int binarySearch(Customer cVector[],int customerNum){   //Searches customer objects for correct customer number
    int lo=0;
    int mid;
    int hi=20;
    bool state=false;
    
    while(lo<=hi){
        mid = (lo + hi) / 2;
        
        if(customerNum==atoi(cVector[mid].customerNum.c_str())){
            state=true;return mid;break;
        }else if(customerNum>atoi(cVector[mid].customerNum.c_str())){
            lo=mid+1;
        }else{
            
            hi=mid-1;
        }
    }
    if(state==false) return -1;
}



int linearSearch(Customer cVector[],string name){       //Searches customer objects for correct name
    
    int pos=-1;
    string nameObj,nameSearch;
    for(int i=0;i<21;i++){
        
        nameObj=upperCaseIt(cVector[i].customerName);    //Fixes case sensitivity
        nameSearch=upperCaseIt(name);                    //Fixes case sensitivity
        
        if(nameObj==nameSearch) pos=i;                   //If both names are equal then hold that position
        
    }
    
    if(pos!=-1) return pos;                              //Sends position of name
    else return -1;
}

int linearSearchAddress(vector<Address> aVector,string street){
    int pos=-1;
    
    for(int i=0; i<aVector.size(); i++){
        if(aVector[i].streetAddress==street) pos = i;
    }
    return pos;
}

int linearSearchInvent(vector<Product> cVector,int code){     //Searches inventory objects for correct product numbers
    
    int pos=-1;
    for(int i=0;i<21;i++){
        if(cVector[i].itemNo==code) pos=i;                    //If both numbers are equal then hold that position
    }
    
    if(pos!=-1) return pos;                                  //Sends position of name
    else return -1;
}

/**************************************************************
 *                             Parse                          *
 * Called by: <fill in>                                       *
 * Passed   : 2 arguments: a string, a character that is the  *
 *            delimiter                                       *
 * Purpose  : Split a given string by its delimiter           *
 * Returns  : String vector                                   *
 **************************************************************/
vector<string> parse(string line, char delimiter){
    
    vector<string> parsedLine;
    istringstream stringStream(line); //create string stream from the line
    
    while (stringStream)//iterate through the stream
        {
            string s;
            //uses getline to get the values from the stream before the delimiting character
            if (getline(stringStream, s, delimiter))
                parsedLine.push_back(s);
        }
    return parsedLine;
}


/**************************************************************
 *                  generateOrderNum                          *
 * Called by: <fill in>                                       *
 * Purpose  : Generate an order number based on epoch         *
 * Returns  : String order number                             *
 **************************************************************/

string generateOrderNum(){
    
    time_t now = time(0); //current time object
    
    string oNum;
    stringstream strstream;
    
    strstream << now; //read the date/time in epoch into the string stream
    strstream >> oNum; //output a string from the string stream
    return oNum;
}

string upperCaseIt(string stringIn)         //Used to fix case sensitivity
{
    string upperCase;
    
    for(int i=0;i<stringIn.length();i++)
        {
        upperCase += toupper(stringIn[i]);
        }
    
    return upperCase;
}



