//
// Created by sure on 2023-12-13.
//
#include <stdio.h>
#include "service.h"
#include "repository.h"
#include "input_interface.h"

Ticket* myTicket;

void inputEnterAmusementPark() {
    int pinNumber;
    while(myTicket == NULL) {
        printf("핀번호를 입력하세요: ");
        scanf("%d", &pinNumber);
        printf("핀번호 %d로 입장을 시도합니다. \n", pinNumber);
        if (enterAmusementPark(pinNumber)) {
            myTicket = getTicketByPin(pinNumber);
            printf("%s님이 입장하였습니다. 매직패스횟수 : %d\n\n", myTicket->userName, myTicket->magicPassUsageCount);
            printf("티켓 정보 \n");
            printf("핀번호: %d \n", myTicket->pinNumber);
            printf("이름: %s \n", myTicket->userName);
            char* passTypeString = myTicket->passType == Daily ? "일일권" : "오후권";
            printf("패스타입: %s \n\n", passTypeString);

            break;
        } else {
            printf("유효하지 않은 티켓입니다. 입장할 수 없습니다.\n");
        }
    }

}

void inputReservePage(int rideId) {
    Ride* ride = getRideById(rideId);
    if(ride == NULL) {
        printf("해당 ID의 놀이기구가 없습니다. \n");
        return;
    }
    printf("%s 를 예약 하시겠습니까? (Y/N) \n", ride->name);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'Y' || answer == 'y') {
        reserveRide(myTicket->pinNumber, rideId);
        printf("%s를 예약하였습니다. \n", ride->name);
    }
}

void inputReserveRide() {
    int rideId;
    printRideInfos();
    printf("예약할 놀이기구 ID를 입력하세요: \n");
    scanf("%d", &rideId);
    inputReservePage(rideId);
}

void startCLI(){
    inputEnterAmusementPark();

    while(1) {
        inputReserveRide();
    }
}

