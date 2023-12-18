
#include "service.h"
#include "controller.h"

void httpRideDone(RideDoneRequest* request) {
    rideDone(request->rideId, request->pinNumber);
}

void httpReserveRide(int pinNumber, int rideId) {
    //stub
    RideReservationRequest request = {pinNumber, rideId};
    printf("예약전송 완료.\n\n");
    
    //rideClient->send(request);
}

