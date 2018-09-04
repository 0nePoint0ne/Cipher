#include <stdio.h>
#include <iostream>

using namespace std;

class Cipher{
    int *NV;
    int CV;
    static Cipher* instance;
    Cipher(){}
    
    public:
           
    Cipher(int values[]){           
        NV = new int[3];
        for(int i = 0; i < 3; i++){
        NV[i] = values[i];
        }
        CV = 0;
    }
    
    Cipher(const Cipher& rhs){
        NV = new int[3];
        for(int i = 0; i < 3; i++){
                NV[i] = rhs.NV[i];
        }
        CV = 0;
    }
    
    void increment(){
        CV++;
        if(CV == 3){
            CV = 0;     
        }
    }
    
    int getValue(){
        return NV[CV];
    }
    
    static Cipher* getInstance()
    {
        if (instance == 0)
        {
            instance = new Cipher();
        }
        
        return instance;
    }
    
    ~Cipher(){
        delete [] NV;   
    }
};

string encodeCharacters(string text, Cipher &Ob){
    string newText = text;
    for(int i = 0; i < newText.length(); i++){
        if(newText[i] >= 65 && newText[i] <= 90){
        
            if((newText[i] + Ob.getValue()) > 90){
                   newText[i] -= (26 - Ob.getValue());  
            }
            else{              
                   newText[i] += Ob.getValue();
            }
        }
        else if(newText[i] >= 97 && newText[i] <= 122){
            if((newText[i] + Ob.getValue()) > 122){
                    newText[i] -= (26 - Ob.getValue());  
            }
            else{              
                   newText[i] += Ob.getValue();
            }    
        }
        Ob.increment();
    }
    cout << newText << endl;
    return newText;
}

string decodeCharacters(string text, Cipher &Ob){
    string newText = text;
    for(int i = 0; i < newText.length(); i++){
        if(newText[i] >= 65 && newText[i] <= 90){
            if((newText[i] - Ob.getValue()) < 65 ){
                newText[i] += (26 - Ob.getValue());
            }
            else{
                newText[i] -= Ob.getValue();
            }
        }
        else if(newText[i] >= 97 && newText[i] <= 122){
            if((newText[i] - Ob.getValue()) < 97 ){
                newText[i] += (26 - Ob.getValue());
            }
            else{
                newText[i] -= Ob.getValue();
            }
        }
        Ob.increment();
    }
    cout << newText << endl;
    return newText;
}

Cipher* Cipher::instance = 0;

int main(){
    int values[3] = {10, 2, 7};
    Cipher N(values);
    decodeCharacters(encodeCharacters("This is my text, it will be encoded and decoded.", N), N);
    system("pause");
}
