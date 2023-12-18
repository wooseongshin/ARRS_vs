//
// Created by sure on 2023-12-18.
//

#ifndef ARRS_CONTROLLER_H
#define ARRS_CONTROLLER_H

typedef struct {
    int pinNumber;
    int rideId;
} RideDoneRequest;

typedef struct {
    int pinNumber;
    int rideId;
} RideReservationRequest;

typedef struct RideClient {
    void (*send)(RideReservationRequest request);
} RideClient;
static RideClient* rideClient;

void httpReserveRide(int pinNumber, int rideId);
void httpRideDone(RideDoneRequest* request);

#endif //ARRS_CONTROLLER_H
