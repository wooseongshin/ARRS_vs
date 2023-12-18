#include <stdbool.h>
#include "types.h"
#include "repository.h"
#include "service.h"
#include "controller.h"

Repository* repository;

void initService() {
    repository = getRepository();
}

void printRideInfos() {
    Ride* rides = getAllRides();

    for (int i = 1; i <= repository->rideId; i++) {
        printf("���̱ⱸ ID: %d \n", rides[i].id);
        printf("���̱ⱸ �̸�: %s \n", rides[i].name);
        char* statusString = rides[i].status == Available ? "���" : "������";
        if (rides[i].status != Available) {
            printf("���̱ⱸ ����: %s \n", statusString);
            printf("\n");
            continue;
        }
        printf("�����н� �ο�: %d / %d \n", rides[i].reservedRiders, rides[i].maxRiders);
        printf("���� ���ð�: %d�� \n", rides[i].reservedRiders * 5);

        printf("���̱ⱸ ����: %s \n", statusString);
        printf("\n");
    }
}

bool enterAmusementPark(int pinNumber) {
    Ticket* ticket = getTicketByPin(pinNumber);
    if (ticket != NULL && isValidDateTicket(ticket)) {
        return true;
    }
    else {
        return false;
    }
}

bool isValidDateTicket(Ticket* ticket) {
    time_t now = time(NULL);
    struct tm* now_tm = localtime(&now);
    struct tm* usageDate_tm = localtime(&(ticket->usageDate));

    // ��¥�� �´��� ��
    if (now_tm->tm_year == usageDate_tm->tm_year &&
        now_tm->tm_mon == usageDate_tm->tm_mon &&
        now_tm->tm_mday == usageDate_tm->tm_mday) {

        // passType�� ���� �ð� ���� Ȯ��
        if (ticket->passType == Daily) {
            // ���� 8�ú��� ���� 10�� �������� Ȯ��
            if (now_tm->tm_hour >= 8 && now_tm->tm_hour < 22) {
                return true;
            }
        }
        else if (ticket->passType == Afternoon) {
            // ���� 2�ú��� ���� 10�� �������� Ȯ��
            if (now_tm->tm_hour >= 14 && now_tm->tm_hour < 22) {
                return true;
            }
        }
    }
    return false;
}

void reserveRide(int pinNumber, int rideId) {
    Ride* ride = getRideById(rideId);
    Ticket* ticket = getTicketByPin(pinNumber);
    if (ride == NULL) {
        printf("�ش� ID�� ���̱ⱸ�� �����ϴ�. \n");
        return;
    }

    if (ticket->magicPassUsageCount > 0) {
        if (ride->status != Available) {
            printf("���� ���̱ⱸ�� ����� �ƴմϴ�. \n");
            return;
        }

        if (ride->reservedRiders >= ride->maxRiders) {
            printf("������ �ʰ��Ǿ� ������ �� �����ϴ�. \n");

            return;
        }
        httpReserveRide(pinNumber, rideId);
        ride->reservedRiders++;
    }
    else {
        printf("�����н��� �����ϴ�. \n");
    }
}

void rideDone(int rideId, int pinNumber) {
    Ticket* ticket = getTicketByPin(pinNumber);
    Ride* ride = getRideById(rideId);
    ticket->magicPassUsageCount--;
    ride->reservedRiders--;
    printf("ž�� �Ϸ��Ͽ����ϴ�. �����н��� %d�� ���ҽ��ϴ�.\n", ticket->magicPassUsageCount);
}




