
#ifndef ARRS_SERVICE_H
#define ARRS_SERVICE_H
#include <stdbool.h>
#include "types.h"

void initService();
void printRideInfos();
bool enterAmusementPark(int pinNumber);
bool isValidDateTicket(Ticket* ticket);
void rideDone(int rideId, int pinNumber);
void reserveRide(int pinNumber, int rideId);



#endif //ARRS_SERVICE_H
