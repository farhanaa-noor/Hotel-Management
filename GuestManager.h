#ifndef GUESTMANAGER_H
#define GUESTMANAGER_H


enum RoomType{
    Standard, Comfort
};
enum GuestType{
    Family, Businessman, Rockstar
};
class Guest{
    protected:
    int  roombusydays;
    GuestType guestype;
    RoomType roomtype;
    int stayduration;

    public:
    GuestType GetGuestType(){
        return guestype;
    }
    RoomType GetRoomType(){
        return roomtype;
    }
    int GetBookedDays(){
        return stayduration;
    }
    virtual int GetAdditionalIncome()=0;
    virtual void GetRoomBusyDays()=0;
    
    public:
    Guest(){}
    Guest( GuestType gt, RoomType rt, int sd){
        guestype = gt;
        roomtype = rt;
        stayduration = sd;
    }
    virtual ~Guest(){}
};

class Family;

class Businessman;

class Rockstar; 

class GuestManager; 

#endif
