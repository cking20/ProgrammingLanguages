/* 
 * File:   main.cpp
 * Author: Christopher King(cking20)
 *
 * Created on September 30, 2016, 11:50 AM
 * 
 * Description:
 *  This program manages the stock of a small sushi market. 
 *      Boxes of stock are stored in priority queues. Users may stock or buy from
 *      the inventories. All events will be recorded in a command line specified 
 *      logfile. This file is required, because our brother in the impala needs
 *      to know how our buisness is doing. 
 * 
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Queue.h"
#include "Box.h"

using namespace std;

/**/
#ifndef DEBUG
    #define DEBUG = true;
#endif
/**/
static const int QUEUE_SIZE = 10;

void run();    
int getOption();
void proccessInput(int ,Queue<Box> *,Queue<Box> *, Queue<Box> *, Queue<Box> *, 
        ofstream &, Queue<Box> *, Queue<Box> *, Queue<Box> *, Queue<Box> *);
void buy(Queue<Box> *,Queue<Box> *, Queue<Box> *,Queue<Box> *, ofstream &, 
        Queue<Box> *, Queue<Box> *, Queue<Box> *, Queue<Box> *);
void stock(Queue<Box> *,Queue<Box> *,Queue<Box> *,Queue<Box> *, ofstream &);
bool tryToBuy(Queue<Box> *, ofstream &, int , char *);
void checkBackorder(Queue<Box> *,Queue<Box> *,Queue<Box> *,Queue<Box> *, ofstream &, 
        Queue<Box> *, Queue<Box> *, Queue<Box> *,Queue<Box> *);

int main(int argc, char** argv) {
    if(argc > 1){
        cout << argv[1] << endl;
        ofstream log;
        log.open(argv[1]);
        Queue<Box> lobster(QUEUE_SIZE);
        Queue<Box> crab(QUEUE_SIZE);
        Queue<Box> shrimp(QUEUE_SIZE);
        Queue<Box> swordfish(QUEUE_SIZE);
              
        Queue<Box> lobsterRequests(QUEUE_SIZE);
        Queue<Box> crabRequests(QUEUE_SIZE);
        Queue<Box> shrimpRequests(QUEUE_SIZE);
        Queue<Box> swordRequests(QUEUE_SIZE);       
        int choice = 0;
        
        do{
            cout << "(buy/stock/exit)" << endl;
            choice = getOption();
            proccessInput(choice, &lobster, &crab, &shrimp, &swordfish, log, 
                    &lobsterRequests, &crabRequests, &shrimpRequests,
                    &swordRequests);
#ifdef DEBUG
            cout << "lobster" << endl;
            lobster.printEm();
            cout << "crab" << endl;
            crab.printEm();
            cout << "shrimp" << endl;
            shrimp.printEm();
            cout << "sword" << endl;
            swordfish.printEm();
           
#endif            
        }while(choice != 0);
#ifdef DEBUG        
        lobster.printEm();
        log << "test" << endl;
#endif
        log.close();
    } else {
        cout << "Usage: ./transaction example.txt" << endl;
    }
    return 0;
}

int getOption(){
    /*Description:
     *  this reads from stdin and until the input is valid
     *Preconditions: 
     *  -stdin must be readable
     *Postconditions: 
     *  -a valid option will be chosen
     */
    char option[20];
    int val;
    bool verified = false;

    do{   
        cin >> option ;
        if(strcmp(option, "exit") == 0){
            val = 0;
            verified = true;
        }else if(strcmp(option, "buy") == 0){
            val = 1;
            verified = true;
        }else if(strcmp(option, "Buy") == 0){
            val = 1;
            verified = true;
        }else if(strcmp(option, "BUY") == 0){
            val = 1;
            verified = true;
        }else if(strcmp(option, "stock") == 0){
            val = 2;
            verified = true;
        }else if(strcmp(option, "Stock") == 0){
            val = 2;
            verified = true;
        }else if(strcmp(option, "STOCK") == 0){
            val = 2;
            verified = true;
        } else{
            verified = false;
#ifdef DEBUG
            cout << "diagnostic" << endl;
            cout << "val : " << val << endl;
            cout << "option : " << option << endl;
            cout << "verified : " << verified << endl;
#endif
            cin.ignore();
        }
    }while(!verified);   
    return val;
}

void proccessInput(int option,Queue<Box> *lobster,Queue<Box> *crab,
        Queue<Box> *shrimp, Queue<Box> *swordfish, ofstream &logFile, 
        Queue<Box> *lobsterRequests, Queue<Box> *crabRequests, 
        Queue<Box> *shrimpRequests, Queue<Box> *swordRequests){
    /*Description: 
     *  performs the appropriate action based on the option passed in
     *Preconditions:
     *  -a valid option must be chosen
     *  -the queue's must be created
     *  -logFile must be open
     *Postconditions:
     *  -the appropriate action will have been taken.
     *  -the queue's will be adjusted appropriately
     */
    switch(option){
        case 0:
            break;
        case 1: //buy
            buy(lobster, crab, shrimp, swordfish, logFile, lobsterRequests, crabRequests, shrimpRequests,
                    swordRequests);
            break;
        case 2: //stock
            stock(lobster, crab, shrimp, swordfish, logFile);
            //loop through the unfufilled requests and check them
            checkBackorder(lobster, crab, shrimp, swordfish, logFile, lobsterRequests, crabRequests, shrimpRequests,
                    swordRequests);
            break;
    }
}

void buy(Queue<Box> *lobster,Queue<Box> *crab,
        Queue<Box> *shrimp,Queue<Box> *swordfish, ofstream &logFile, 
        Queue<Box> *lobsterRequests, Queue<Box> *crabRequests, 
        Queue<Box> *shrimpRequests, Queue<Box> *swordRequests){
    /*Description: 
     *  reads from stdin and will attempt to remove items from appropriate
     *  queue. If a request cant be satisfied, the request is queued 
     *Preconditions:
     *  -log must be open
     *  -queues must be created
     *Postconditions:
     *  -either the queue's will be adjusted based on user input, 
     *      or a request will be queued
     */
    char type[20];
    char date[11];
    char zero[11];
    int numType;
    bool verifiedType = false;
    bool verifiedAmt = false;
    bool verifiedDate = false;
    int amount;
    int amountSold = 0;
    strcpy(zero,"00/00/0000");
    
   cout << "Date: mm/dd/yyyy\n";
    //verify date expected format mm/dd/yyyy
    do{
        cin >> date;
        if(date[2] == '/' && date[5] == '/'){
            int dayVal = 0;
            int monthVal = 0;
            int yearVal = 0;
            
            dayVal = date[4] -'0';
            dayVal = dayVal + (date[3] -'0') * 10;
            
            monthVal = monthVal + (date[1] -'0');
            monthVal = monthVal + (date[0] -'0') * 10;
            
            yearVal = yearVal + (date[9] -'0');
            yearVal = yearVal + (date[8] -'0') * 10;
            yearVal = yearVal + (date[7] -'0') * 100;
            yearVal = yearVal + (date[6] -'0') * 1000;
#ifdef DEBUG
            cout << "Day of : " << dayVal << endl;
            cout << "Month of : " << monthVal << endl;
            cout << "Year of : " << yearVal << endl;
#endif   
            if((dayVal > 0 && dayVal < 32) && (monthVal > 0 && monthVal < 13) 
                    && (yearVal > 1900))//NO SEA FOOD SHOULD BE OLDER THAN 1900!
                verifiedDate = true; 
            else{
                cin.clear();
                cin.ignore();
            }
        }
    }while(!verifiedDate); 
    
    cout << "(lobster/crab/shrimp/swordfish)" << endl;
    //verify type
    do{
        cin >> type;
        //transform the type for a switch stmt
        if(strcmp(type, "lobster") == 0){
           numType = 1;
           verifiedType = true;
        } else if(strcmp(type, "crab") == 0){
           numType = 2;
           verifiedType = true;
        } else if(strcmp(type, "shrimp") == 0){
           numType = 3;
           verifiedType = true;
        } else if(strcmp(type, "swordfish") == 0){
           numType = 4;
           verifiedType = true;
        } else {
            cin.clear();
            cin.ignore();
            cout << "bad imput" << endl;
            //diagnostic?
        }            
    }while(!verifiedType);
    
    //verify amount
    cout << "Amount" << endl;
    do{
        cin >> amount;
        
        if(amount > 0){
            verifiedAmt = true;
        } else{
            cin.clear();
            cin.ignore();
            cout << "bad input" << endl;
        }   
    }while(!verifiedAmt);
#ifdef DEBUG    
    cout << "Read type = " << type << "." << endl;
    cout << "Read amount = " << amount << "." << endl;
#endif    
    
    //switch for the queues
    Box request;
    switch(numType){
            case 1://lobster
                if(!lobster->isEmpty()){
                    if(!tryToBuy(lobster, logFile, amount, type)){
                         //queue request
                        request.SetDate(zero);
                        request.SetType(numType);
                        request.SetItems(amount);
                        lobsterRequests->push(request);
                        cout << "Not enough Product" << endl;
                    }    
                }else{//queue is empty
                    //queue request
                    request.SetDate(zero);
                    request.SetType(numType);
                    request.SetItems(amount);
                    lobsterRequests->push(request);
                    cout << "No product in stock" << endl;
                }
                break;
            case 2://crab
                if(!crab->isEmpty()){
                    if(!tryToBuy(crab, logFile, amount, type)){
                    //queue request 
                        request.SetDate(zero);
                        request.SetType(numType);
                        request.SetItems(amount);
                        crabRequests->push(request);
                        cout << "Not enough Product" << endl;
                    }                      
                } else{
                    request.SetDate(zero);
                    request.SetType(numType);
                    request.SetItems(amount);
                    crabRequests->push(request);
                    cout << "No product in stock" << endl;
                }
                break;
            case 3://shrimp
                if(!shrimp->isEmpty()){
                    if(!tryToBuy(shrimp, logFile, amount, type)){
                    //queue request    
                        request.SetDate(zero);
                        request.SetType(numType);
                        request.SetItems(amount);
                        shrimpRequests->push(request);
                        cout << "Not enough Product" << endl;
                    }  
                } else{
                    request.SetDate(zero);
                    request.SetType(numType);
                    request.SetItems(amount);
                    shrimpRequests->push(request);
                    cout << "No product in stock" << endl;
                }
                break;
            case 4://sword
                if(!swordfish->isEmpty()){
                    if(!tryToBuy(swordfish, logFile, amount, type)){
                    //queue request    
                        request.SetDate(zero);
                        request.SetType(numType);
                        request.SetItems(amount);
                        swordRequests->push(request);
                        cout << "Not enough Product" << endl;
                    }  
                }else{
                    request.SetDate(zero);
                    request.SetType(numType);
                    request.SetItems(amount);
                    swordRequests->push(request);
                    cout << "No product in stock" << endl;
                }
                break;
        }
}  

void stock(Queue<Box> *lobster,Queue<Box> *crab,
        Queue<Box> *shrimp,Queue<Box> *swordfish, ofstream &logFile){
    /*Description: 
     *  reads from stdin and adds to the applicable queue based on the
     *  type. Prints out all actions taken in log file
     * Preconditions: 
     *  -logFile must be open
     *  -queue's must be created
     *  -stdin can not be at E0F
     * Postconditions:
     *  -specified queue will have a new box in it  
     * 
     */
    char type[20];
    char date[11];
    int numType;
    bool verifiedType = false;
    bool verifiedAmt = false;
    bool verifiedDate = false;
    int amount;
    int amountRecieved = 0;
    
    cout << "Date: mm/dd/yyyy\n";
    //verify date expected format dd/mm/yyyy
    do{
        cin >> date;
        if(date[2] == '/' && date[5] == '/'){
            int dayVal = 0;
            int monthVal = 0;
            int yearVal = 0;
            
            dayVal = date[4] -'0';
            dayVal = dayVal + (date[3] -'0') * 10;
            
            monthVal = monthVal + (date[1] -'0');
            monthVal = monthVal + (date[0] -'0') * 10;
            
            yearVal = yearVal + (date[9] -'0');
            yearVal = yearVal + (date[8] -'0') * 10;
            yearVal = yearVal + (date[7] -'0') * 100;
            yearVal = yearVal + (date[6] -'0') * 1000;
#ifdef DEBUG
            cout << "Day of : " << dayVal << endl;
            cout << "Month of : " << monthVal << endl;
            cout << "Year of : " << yearVal << endl;
#endif   
            if((dayVal > 0 && dayVal < 32) && (monthVal > 0 && monthVal < 13) 
                    && (yearVal > 1900))//NO SEA FOOD SHOULD BE OLDER THAN 1900!
                verifiedDate = true;  
        }
    }while(!verifiedDate);
    
    cout << "(lobster/crab/shrimp/swordfish)" << endl;
    //verify type
    do{
        cin >> type;
        //transform the type for a switch stmt
        if(strcmp(type, "lobster") == 0){
           numType = 1;
           verifiedType = true;
        } else if(strcmp(type, "crab") == 0){
           numType = 2;
           verifiedType = true;
        } else if(strcmp(type, "shrimp") == 0){
           numType = 3;
           verifiedType = true;
        } else if(strcmp(type, "swordfish") == 0){
           numType = 4;
           verifiedType = true;
        } else {
            cin.ignore();
            //diagnostic?
            cout << "bad imput" << endl;
        }            
    }while(!verifiedType);
    
    cout << "Amount" << endl;
    //verify amount
    do{ 
        cin >> amount;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            amount = 0;
        }
        if(amount > 0){
            verifiedAmt = true;
        }    
    }while(!verifiedAmt);
    
#ifdef DEBUG    
    cout << "Read type = " << type << "." << endl;
    cout << "Read amount = " << amount << "." << endl;
#endif    
    //push a box amount times 
        Box temp();
        for(int i = 0; i < amount; i++){
        switch(numType){  
            case 1://lobster
                if(!lobster->isFull()){
                    Box temp(numType, 4, date);
                    temp.SetItems(4);
                    lobster->push(temp);
                    amountRecieved++;
                }else
                    cout << "Inventory Full" << endl;
                break;
            case 2://crab
                if(!crab->isFull()){
                    Box temp(numType, 6, date);
                    temp.SetItems(6);
                    crab->push(temp);
                    amountRecieved++;
                } else
                    cout << "Inventory Full" << endl;
                break;
            case 3://shrimp
                if(!shrimp->isFull()){
                    Box temp(numType, 50, date);
                    temp.SetItems(50);
                    shrimp->push(temp);
                    amountRecieved++;
                } else
                    cout << "Inventory Full" << endl;
                break;
            case 4://sword
                if(!swordfish->isFull()){
                    Box temp(numType, 8, date);
                    temp.SetItems(8);
                    swordfish->push(temp);
                    amountRecieved++;
                }else
                    cout << "Inventory Full" << endl;
                break;
        }
        }
        //Log
        logFile << "stock " << date << " " << type << " " << amountRecieved << '\n';
}

bool tryToBuy(Queue<Box> *toSell, ofstream &logFile, int amount, char type[]){
    /*Description: 
     *  attempts to remove amount from specified queue. type will be written to 
     *  the log file
     *Preconditions: 
     *  -toSell must not be null NOR empty
     *  -logFile must be open
     *Postconditions: 
     *  -actions taken will be written to the log file
     *  -true will be returned if the action could be taken
     *  -false will be returned if the action could not be taken 
     */
    int amountSold = 0;
    Box temp = toSell->pop();
                    //if the box poped +(base amount * num in queue)>amount
                    //peek should always be unopened, thus getItems is the 
                    //same for all other items
                    if((toSell->peek().GetItems() * toSell->getAmt())
                            + temp.GetItems() >= amount){
                        //remove items from temp until empty then pop off 
                        //in to temp again
                        while(amountSold < amount){
                            int tempAmt = 0;
                            while(temp.GetItems() > 0 && amountSold < amount){
                                temp.DecInv();
                                amountSold++;
                                tempAmt++;
                            }
                            logFile << "buy " << " " << temp.GetDate() << " " << type << " " << tempAmt << '\n';
                            if(amountSold < amount)
                                temp = toSell->pop();       
                        }
                        //if there are any left, put back on
                        if(temp.GetItems() > 0)
                            toSell->push(temp);
                        return true;
                    } else {
                        //not enough in queue, so put the box back on
                        toSell->push(temp)
;
                        cout << "Not enough "<< type <<" in stock." << endl;
                        return false;
                    }
}

void checkBackorder(Queue<Box> *lobster,Queue<Box> *crab,
        Queue<Box> *shrimp,Queue<Box> *swordfish, ofstream &logFile, 
        Queue<Box> *lobsterRequests, Queue<Box> *crabRequests, 
        Queue<Box> *shrimpRequests,Queue<Box> *swordRequests){
    /*Description: 
     *  checks each queue to see if there are any old requests 
     *  that could be completed
     *Preconditions:
     *  -logFile must be open
     *  -queues must be created
     *Postconditions:
     *  -1 request of each type will be checked 
     */
    //Check and see if old requests could be taken care of
    //if there is both product and a request
    char lob[10] = "lobster";
    char crb[10] = "crab";
    char smp[10] = "shrimp";
    char swd[10] = "lobster";
    
    if(!lobster->isEmpty() && !lobsterRequests->isEmpty()){
        if(tryToBuy(lobster, logFile, lobsterRequests->peek().GetItems(), lob)){
            lobsterRequests->pop();
        }    
    } 
    if(!crab->isEmpty() && !crabRequests->isEmpty()){
        if(tryToBuy(crab, logFile,  crabRequests->peek().GetItems(), crb)){
            crabRequests->pop();
        }                      
    } 
    if(!shrimp->isEmpty() && !shrimpRequests->isEmpty()){
        if(tryToBuy(shrimp, logFile,  shrimpRequests->peek().GetItems(), smp)){
            shrimpRequests->pop();
        }  
    } 
    if(!swordfish->isEmpty() && !swordRequests->isEmpty()){
        if(tryToBuy(swordfish, logFile,  swordRequests->peek().GetItems(), swd)){
            swordRequests->pop();
        }  
    }
}
