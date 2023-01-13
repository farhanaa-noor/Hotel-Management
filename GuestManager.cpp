#include <iostream>
#include <vector>
#include "GuestManager.h"
using namespace std;

class Family : public Guest
{
    int GetAdditionalIncome() override
    {
        return 0;
    }
    void GetRoomBusyDays() override
    {
        roombusydays = stayduration;
    }
    
};
class Businessman : public Guest
{
    int additionalIncome;

    int GetAdditionalIncome() override{
        return additionalIncome;
    } 
    void GetRoomBusyDays() override
    {
        roombusydays = stayduration;
    }
    Businessman(GuestType gt, RoomType rt, int stayduration, int ai):Guest(gt,rt,stayduration) {
        additionalIncome = ai;
        //Businessman:;
    }
};
class Rockstar : public Guest
{
    int GetAdditionalIncome() override
    {
        return 0;
    }
    void GetRoomBusyDays() override
    {
        roombusydays = stayduration + 10;
    }
};
class GuestManager : public Guest
{
    //GuestType guestype;
    //RoomType roomtype;
    int numberOfStandardRooms, numberOfComfortRooms, standardRoomPrice, comfortRoomPrice;
    vector<int> standardRoomBooked;
    vector<int> standardRoompaid;
    vector<int> comfortRoomBooked;
    vector<int> comfortRoompaid;
    vector<int> additionalIncomevector;
    vector<int> aiPerDay;

    public:
    GuestManager(){}
    int GetAdditionalIncome() override{
        return 0;
    }
    void GetRoomBusyDays() override{}
    GuestManager(int OfStandardRooms, int dayPriceStandard, int OfComfortRooms, int dayPriceComfort)
    {
        numberOfStandardRooms = OfStandardRooms;
        standardRoomPrice = dayPriceStandard;
        numberOfComfortRooms = OfComfortRooms;
        comfortRoomPrice = dayPriceComfort;
    }

    
    bool AddGuest(GuestType gt, RoomType rt, int stayDays, int additionalIncome = 0)
    {
        bool available = roomEmpty(rt);
        if(available == true){
             stayduration = stayDays;
             if(gt == Businessman){
                 additionalIncomevector.push_back(additionalIncome*stayDays);
                 aiPerDay.push_back(additionalIncome);
             }
             if( rt == Standard){
                    if(gt == Rockstar){
                    standardRoomBooked.push_back(stayDays+10);
                    standardRoompaid.push_back(stayDays);
                }
                else{
                    standardRoomBooked.push_back(stayDays);
                    standardRoompaid.push_back(stayDays);
                }
             }

             if(rt == Comfort){
                 if(gt == Rockstar){
                    comfortRoomBooked.push_back(stayDays+10);
                    comfortRoompaid.push_back(stayDays);
                }
                else{
                 comfortRoomBooked.push_back(stayDays);
                 comfortRoompaid.push_back(stayDays);
                }
             }
            
            
            return true;
        }
        
       return false;
    }
    bool IsAvailable(RoomType rt, int inDays = 0) 
    {
        //check if the room is free in inDays
        if (rt == Standard)
        {
            if (standardRoomBooked.size() < numberOfStandardRooms)
            {
                return true;
            }
            else if(standardRoomBooked.size()== numberOfStandardRooms){
                for(int i=0; i<standardRoomBooked.size();i++){
                    if(standardRoomBooked[i]<=inDays){
                        return true;
                    }
                }
            }
            else{
                return false;
            }
        }
        if (rt == Comfort)
        {
           if (comfortRoomBooked.size() < numberOfComfortRooms)
            {
                return true;
            }
            else if(comfortRoomBooked.size()== numberOfComfortRooms){
                for(int i=0; i<comfortRoomBooked.size();i++){
                    if(comfortRoomBooked[i]<=inDays){
                        return true;
                    }
                }
            }
            else{
                return false;
            }
        }
        return false;
    }
    int IncomingProfit()
    {
        int totalpay;
        int additionalIncome = sum(additionalIncomevector);
        int totaldaysinStandardRoom = sum(standardRoompaid);
        int totaldaysinComfortRoom = sum(comfortRoompaid);
        totalpay = (standardRoomPrice*totaldaysinStandardRoom)+(comfortRoomPrice*totaldaysinComfortRoom)+ additionalIncome;
        return totalpay;
    }
    float EarningEfficiency()
    {
        float current_per_day_income, max_per_day_income;
        int additionalIncome = sum(aiPerDay);
        max_per_day_income = (numberOfStandardRooms*standardRoomPrice)+(numberOfComfortRooms*comfortRoomPrice);
        current_per_day_income = (standardRoomBooked.size()* standardRoomPrice)+(comfortRoomBooked.size()*comfortRoomPrice)+additionalIncome;
        float earning_efficiency = current_per_day_income / max_per_day_income;
        return earning_efficiency;
    }
    bool operator < (GuestManager B){
         //GuestManager A;
        if(this->IncomingProfit() < B.IncomingProfit()){
            return true;
        }
        else{
            return false;
        }
         
    }
    int sum(vector<int> ai){
        int sum=0;
        for(int i=0; i<ai.size();i++){
            sum = sum+ai[i];
        }
        return sum;
    }
    bool roomEmpty(RoomType rt){
        if(rt == Standard){
            if(standardRoomBooked.size()== numberOfStandardRooms){
                return false;
            }
        }
        if(rt == Comfort){
            if(comfortRoomBooked.size()== numberOfComfortRooms){
                return false;
            }
        }
        return true;
    }
};