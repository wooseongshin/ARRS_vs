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
    while (myTicket == NULL) {
        printf("�ɹ�ȣ�� �Է��ϼ���: ");
        scanf_s("%d", &pinNumber);
        printf("�ɹ�ȣ %d�� ������ �õ��մϴ�. \n", pinNumber);
        if (enterAmusementPark(pinNumber)) {
            myTicket = getTicketByPin(pinNumber);
            printf("%s���� �����Ͽ����ϴ�. �����н�Ƚ�� : %d\n\n", myTicket->userName, myTicket->magicPassUsageCount);
            printf("Ƽ�� ���� \n");
            printf("�ɹ�ȣ: %d \n", myTicket->pinNumber);
            printf("�̸�: %s \n", myTicket->userName);
            char* passTypeString = myTicket->passType == Daily ? "���ϱ�" : "���ı�";
            printf("�н�Ÿ��: %s \n\n", passTypeString);

            break;
        }
        else {
            printf("��ȿ���� ���� Ƽ���Դϴ�. ������ �� �����ϴ�.\n");
        }
    }

}

void inputReservePage(int rideId) {
    Ride* ride = getRideById(rideId);
    if (ride == NULL) {
        printf("�ش� ID�� ���̱ⱸ�� �����ϴ�. \n");
        return;
    }
    printf("%s �� ���� �Ͻðڽ��ϱ�? (Y/N) \n", ride->name);
    char answer;
    scanf_s(" %c", &answer);
    if (answer == 'Y' || answer == 'y') {
        reserveRide(myTicket->pinNumber, rideId);
        printf("%s�� �����Ͽ����ϴ�. \n", ride->name);
    }
}

void inputReserveRide() {
    int rideId;
    printRideInfos();
    printf("������ ���̱ⱸ ID�� �Է��ϼ���: \n");
    scanf_s("%d", &rideId);
    inputReservePage(rideId);
}

void startCLI() {
    inputEnterAmusementPark();

    while (1) {
        inputReserveRide();
    }
}

