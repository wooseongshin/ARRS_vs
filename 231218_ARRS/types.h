//
// Created by sure on 2023-12-14.
//

#ifndef ARRS_TYPES_H
#define ARRS_TYPES_H

#include <stdio.h>
#include <time.h>
#include <windows.h>

typedef enum {
    Daily,       // ���ϱ�
    Afternoon    // ���ı�
} PassType;

typedef enum {
    Inspection,  // ������
    Available,   // �̿밡��
    Closed       // ���
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
    char name[50];           // ���̱ⱸ �̸�
    int maxRiders;        // �ִ� ž�� �ο�
    int reservedRiders;   // ���� �ο�
    RideStatus status;    // ���̱ⱸ ����
} Ride;




#endif //ARRS_TYPES_H
