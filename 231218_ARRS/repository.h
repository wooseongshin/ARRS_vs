
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "types.h"

typedef struct {
    Ticket* tickets;
    Ride* rides;
    int rideId;
    int pinNumber;
    size_t size;
    size_t capacity;
} Repository;

void hello();
void initRepository();
Ticket createTicket(char* userName, time_t usageDate, PassType passType, int magicPassUsageCount);
void saveTicket(Ticket ticket);
Ticket* getTicketByPin(int pinNumber);
Ride createRide(char* name, int maxRiders, RideStatus status);
void saveRide(Ride ride);
Ride* getRideById(int rideId);
Ride* getAllRides();
Repository* getRepository();
void saveRepositoryToFile();
void getTicketsFromFile();
void getRidesFromFile();

#endif //REPOSITORY_H

