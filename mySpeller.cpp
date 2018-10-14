//
//  mySpeller.cpp
//  
//
//  Created by Jungsoo Ha on 30/09/2018.
//

#include<fstream>
#include<iostream>
#include<string>

using namespace std;

class StringNode{
    private:
        string element;
        StringNode* next;
    public:
        string getElement() const;
        StringNode* getNext() const;
    
    friend class StringLinkedList;
};

class StringLinkedList{
    private:
        StringNode* head;
    public:
        StringLinkedList();
        ~StringLinkedList();
        bool empty() const; //checks if the list is empty
        void removeFront(); //removes a node in the front
        void addAfter(string word, StringNode* current); //adds a node after the current node
        StringNode* getFront() const; //returns the head of the linkedlist
};

class mySpeller{
    public:
        static int determineMode(string input);
        static void searchFull(StringLinkedList list, string word);
        static void searchPrefix(StringLinkedList list, string word);
        static void searchThree(StringLinkedList list, string word);
        static int findKey(string word); //finds the index of the array of words the code should iterate through
};

int keyLength =52;
char key [52];




/*get dictionary name as input and use that dictionary for the program*/
int main(int argc, char* argv[]){
    for(int i = 0; i<argc; i++){
        cout<<argv[i]<<endl;
    }
    char* dictionaryName = NULL;
    int maxOutput = -1;
    for (int i = 0; i < argc; i++){
        if(strncmp(argv[i],"-d",2) == 0 && i+1 < argc) dictionaryName = argv[i+1];
        if(strncmp(argv[i],"-l",2) == 0 && i+1 < argc) maxOutput = stoi(argv[i+1]);
    }
    if(dictionaryName==NULL || maxOutput == -1){
        cout<<"Usage ./mySpeller -d <dictionaryfilename> -l <numberOfWordsSearch>"<<endl;
        return -1;
    }
    cout<<"We are using "<<dictionaryName<<endl;
    cout<<"Maximum number of output is "<<maxOutput<<endl;
    
    //fill key
    int count = 0;
    for (int j = 'A'; j <= 'Z'; j++){
        key[count] = (char)j;
        count ++;
    }
    for (int k = 'a'; k <= 'z'; k++){
        key[count] = (char)k;
        count ++;
    }
    
//    //test if the key array is correctly filled
//    for(int i = 0; i < 52; i++){
//        cout<<key[i]<<endl;
//    }
    
    //add each word to a array of StringLinkedList. Each linked list involves words that start with a specific letter.
    int length = 53;
    StringLinkedList vocab [length];
    int index = 0;
    StringNode* current = vocab[index].getFront();
    string prev;
//    int a =0;
    ifstream fin(dictionaryName);
    while(fin){
        string line;
        getline(fin, line);
//        cout<<line<<endl;
        if (line.substr(0,1)<"A"){
            if (vocab[index].empty()){
                vocab[index].addAfter(line, current);
                current = vocab[index].getFront();
//                a++;
            }else{
            vocab[index].addAfter(line, current);
            current = current -> getNext();
            }
        }
        else{
            if(prev != line.substr(0,1)){
                index ++;
                current = vocab[index].getFront();
                prev = line.substr(0,1);
            }
            if (vocab[index].empty()){
                vocab[index].addAfter(line, current);
                current = vocab[index].getFront();
            }else{
                vocab[index].addAfter(line, current);
                current = current -> getNext();
            }
        }
    }
////    Test if all words are correctly stored in a linked list
//    for(int i = 0; i<length; i++){
//    while(!vocab[i].empty()){
//        string s = vocab[i].getFront() -> getElement();
//        cout<<s<<endl;
//        vocab[i].removeFront();
//    }
//    cout<<endl;
//    }
    
    
    /*ask for input*/
    string wordInput;
    cout<<"Check Spelling for: ";
    cin>>wordInput;
//    for (int i = 0; i < wordInput.size() ; i++){
//        cout<<wordInput[i];
//    }
//    cout<<endl;
    
    /*check if input is exit or not*/
    while(wordInput.compare("exit") != 0){
        int mode = mySpeller::determineMode(wordInput);
        cout<<mode<<endl;
        int searchIndex = mySpeller::findKey(wordInput);
        cout<<searchIndex<<endl;
        wordInput = "exit";
        
    }
//
//
//
//
    
}

string StringNode:: getElement() const{
    return element;
}
StringNode* StringNode:: getNext() const{
    return next;
}
StringLinkedList::StringLinkedList(){
    head = NULL;
}
StringLinkedList::~StringLinkedList(){
    while(!empty()){
        removeFront();
    }
}
bool StringLinkedList::empty() const{
    return head == NULL;
}
void StringLinkedList::removeFront(){
    if(head!=NULL){
        StringNode* old = head;
        head = head -> next;
        delete old;
    }
}
void StringLinkedList::addAfter(string word, StringNode* current ){
    StringNode* s = new StringNode;
    s -> element = word;
    s -> next = NULL;
    if(current == NULL){
        head = s;
    }
    else{
        current -> next = s;
    }
}

StringNode* StringLinkedList::getFront() const{
    return head;
}
int mySpeller::determineMode(string input){
    int inputLength = input.length();
    if(input[inputLength-1] == '*') return 1;
    for(int i = 1; i < inputLength; i++){
            if(input[i] == '?') return 2;
    }
    return 0;
}
int mySpeller::findKey(string word){
    char firstLetter = word[0];
    for(int i = 0; i < keyLength; i++){
        if (firstLetter == key[i]) return i+1;
    }
    return 0;
}
void mySpeller::searchThree(StringLinkedList list, string word){
    
}

