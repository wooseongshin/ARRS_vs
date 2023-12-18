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

    for(int i = 1; i <= repository->rideId; i++) {
        printf("놀이기구 ID: %d \n", rides[i].id);
        printf("놀이기구 이름: %s \n", rides[i].name);
        char* statusString = rides[i].status == Available ? "운영중" : "점검중";
        if (rides[i].status != Available){
            printf("놀이기구 상태: %s \n", statusString);
            printf("\n");
            continue;
        }
        printf("매직패스 인원: %d / %d \n",rides[i].reservedRiders ,rides[i].maxRiders);
        printf("예상 대기시간: %d분 \n", rides[i].reservedRiders * 5);

        printf("놀이기구 상태: %s \n", statusString);
        printf("\n");
    }
}

bool enterAmusementPark(int pinNumber) {
    Ticket* ticket = getTicketByPin(pinNumber);
    if(ticket != NULL && isValidDateTicket(ticket)) {
        return true;
    } else {
        return false;
    }
}

bool isValidDateTicket(Ticket* ticket) {
    time_t now = time(NULL);
    struct tm* now_tm = localtime(&now);
    struct tm* usageDate_tm = localtime(&(ticket->usageDate));

    // 날짜가 맞는지 비교
    if (now_tm->tm_year == usageDate_tm->tm_year &&
        now_tm->tm_mon == usageDate_tm->tm_mon &&
        now_tm->tm_mday == usageDate_tm->tm_mday) {

        // passType에 따라 시간 범위 확인
        if (ticket->passType == Daily) {
            // 오전 8시부터 오후 10시 사이인지 확인
            if (now_tm->tm_hour >= 8 && now_tm->tm_hour < 22) {
                return true;
            }
        } else if (ticket->passType == Afternoon) {
            // 오후 2시부터 오후 10시 사이인지 확인
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
    if(ride == NULL) {
        printf("해당 ID의 놀이기구가 없습니다. \n");
        return;
    }

    if(ticket->magicPassUsageCount > 0) {
        if (ride->status != Available) {
            printf("현재 놀이기구가 운영중이 아닙니다. \n");
            return;
        }

        if(ride->reservedRiders >= ride->maxRiders) {
            printf("정원이 초과되어 예약할 수 없습니다. \n");

            return;
        }
        httpReserveRide(pinNumber, rideId);
        ride->reservedRiders++;
    } else {
        printf("매직패스가 없습니다. \n");
    }
}

void rideDone(int rideId, int pinNumber) {
    Ticket* ticket = getTicketByPin(pinNumber);
    Ride* ride = getRideById(rideId);
    ticket->magicPassUsageCount--;
    ride->reservedRiders--;
    printf("탑승 완료하였습니다. 매직패스가 %d번 남았습니다.\n", ticket->magicPassUsageCount);
}




