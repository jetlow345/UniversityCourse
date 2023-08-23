#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class HashTable{
    private:
    vector<string>table;

    public:
    
    int Locate(string key);
    bool searchKey(string key);
    void insertKey(string key);
    void deleteKey(string key);
    void print();
    HashTable();
};    
    
    
    HashTable::HashTable(){
         for(int i=0 ; i<26 ; i++){
            table.push_back("never used");
        }
    }
    
    int HashTable::Locate(string key){ // locate key
        return key.back()-'a';
    }
    
    
    bool HashTable::searchKey(string key){
       unsigned int index= Locate(key);//Locate key
        for(unsigned int i=0 ; i<table.size(); i++){
            if(table[index]==key){
                return true;
            }
        index++;
        if(index==table.size())
        index=0;
        }
        return false;
    }

    void HashTable::insertKey(string key){
        unsigned int index= Locate(key);//locate the key
        
        if(searchKey(key)==true){
        table[index]=="occupied"; //  meaning the key has already been inserted then return
        return;
        }
        for(unsigned int i=0 ; i<table.size(); i++){
            if(table[index]=="never used" || table[index]== "tombstone"){
                table[index]=key;
                return;
            }
            index++;
            if(index==table.size())
            index=0;
        }

    }

     void HashTable::deleteKey(string key){
        unsigned int index=Locate(key);//Locate key
         for(unsigned int i=0 ; i<table.size(); i++){
             if(table[index]==key){
                 table[index]="tombstone";
                 return;
             }
             index++;
             if(index==table.size())
             index=0;
         }
     }

    void HashTable::print(){
        string result="";
        unsigned int i=0;
        while(i<table.size()){
             if(table[i] != "never used" && table[i] != "tombstone"){
                result=table[i];
                cout<<result<<" ";
             }
          i++;
        }
    }


int main(void){
    HashTable table;
    
    string str,output;
    getline( cin, str);
    vector<string> input;
    istringstream enter(str);//string stream for tokenizing
   //we split the input into each opearation
   do {
       enter >> output;
       input.push_back(output);
   } while (enter);
    unsigned int i = 0;

	//If firstChar is A we insert key otherwise remove it.
	while(i < input.size()){
	  if(input[i][0]=='A'){
	    table.insertKey(input[i].substr(1));
	  
	  }else if(input[i][0]=='D'){
	    table.deleteKey(input[i].substr(1));
	  }
	  
	  i++;
	}
   table.print();
    return 0;
}