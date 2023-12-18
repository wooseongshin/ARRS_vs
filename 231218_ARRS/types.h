//
// Created by sure on 2023-12-14.
//

#ifndef ARRS_TYPES_H
#define ARRS_TYPES_H

#include <stdio.h>
#include <time.h>
#include <windows.h>

typedef enum {
    Daily,       // 일일권
    Afternoon    // 오후권
} PassType;

typedef enum {
    Inspection,  // 점검중
    Available,   // 이용가능
    Closed       // 폐쇄
} RideStatus;

typedef struct {
    int pinNumber;
    char userName[50];
    time_t usageDate;
    PassType passType;
    int magicPassUsageCount;
} Ticket;

typedef struct {
    int id;
    char name[50];           // 놀이기구 이름
    int maxRiders;        // 최대 탑승 인원
    int reservedRiders;   // 예약 인원
    RideStatus status;    // 놀이기구 상태
} Ride;




#endif //ARRS_TYPES_H
