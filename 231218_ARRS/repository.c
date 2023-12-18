#include <string.h>
#include <stdlib.h>
#include "repository.h"
#include "constants.h"
static Repository repository;

Repository* getRepository() {
    return &repository;
}

void initRepository() {
    repository.tickets = (Ticket*)malloc(sizeof(Ticket) * MAX_TICKET_COUNT);
    repository.rides = (Ride*)malloc(sizeof(Ride) * DEFAULT_RIDE_COUNT);
    repository.rideId = 0;
    repository.pinNumber = 0;
    repository.size = 0;
    repository.capacity = REPOSITORY_INITIAL_CAPACITY;

    getTicketsFromFile();
    getRidesFromFile();
}

Ticket createTicket(char* userName, time_t usageDate, PassType passType, int magicPassUsageCount) {
    Ticket ticket;
    strcpy(ticket.userName, userName);
    ticket.pinNumber = repository.pinNumber++;
    ticket.usageDate = usageDate;
    ticket.passType = passType;
    ticket.magicPassUsageCount = magicPassUsageCount;
    saveTicket(ticket);
    return ticket;
}

void saveTicket(Ticket ticket) {
    repository.tickets[repository.pinNumber] = ticket;
}

Ticket* getTicketByPin(int pinNumber) {
    for (int i = 0; i < MAX_TICKET_COUNT; i++) {
        if (repository.tickets[i].pinNumber == pinNumber) {
            return &repository.tickets[i];
        }
    }
    return NULL;
}

Ride createRide(char* name, int maxRiders, RideStatus status) {
    Ride ride = { 0, };
    if (repository.rideId == DEFAULT_RIDE_COUNT) {
        printf("���̱ⱸ�� �� �̻� �߰��� �� �����ϴ�. \n");
        return ride;
    }

    strcpy(ride.name, name);
    ride.id = repository.rideId++;
    ride.maxRiders = maxRiders;
    ride.reservedRiders = 0;
    ride.status = status;
    saveRide(ride);
    return ride;
}

void saveRide(Ride ride) {
    repository.rides[repository.rideId] = ride;
}

Ride* getRideById(int rideId) {
    for (int i = 0; i < DEFAULT_RIDE_COUNT; i++) {
        if (repository.rides[i].id == rideId) {
            return &repository.rides[i];
        }
    }


    return NULL;
}

Ride* getAllRides() {
    return repository.rides;
}

void saveTicketsToFile(const char* filename, Ticket* tickets, size_t size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("���� ���� ����");
        return;
    }

    for (size_t i = 1; i <= size; ++i) {
        fprintf(file, "%d %s %lld %d %d\n", tickets[i].pinNumber, tickets[i].userName,
            tickets[i].usageDate, tickets[i].passType, tickets[i].magicPassUsageCount);
    }

    fclose(file);
}

void saveRidesToFile(const char* filename, Ride* rides, size_t size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("���� ���� ����");
        return;
    }

    for (size_t i = 1; i <= size; ++i) {
        fprintf(file, "%d %s %d %d %d\n", rides[i].id, rides[i].name, rides[i].maxRiders,
            rides[i].reservedRiders, rides[i].status);
    }

    fclose(file);
}

void saveRepositoryToFile() {
    saveTicketsToFile(TICKET_FILE_PATH, repository.tickets, repository.pinNumber);
    saveRidesToFile(RIDE_FILE_PATH, repository.rides, repository.rideId);
}

void getTicketsFromFile() {
    FILE* file = fopen("../ticket.txt", "r");
    if (file == NULL) {
        perror("���� ���� ����");
        return;
    }

    while (!feof(file)) {
        Ticket ticket;
        fscanf(file, "%d %s %lld %d %d\n", &ticket.pinNumber, ticket.userName,
            &ticket.usageDate, &ticket.passType, &ticket.magicPassUsageCount);
        createTicket(ticket.userName, ticket.usageDate, ticket.passType, ticket.magicPassUsageCount);
    }
    fclose(file);
}

void getRidesFromFile() {
    FILE* file = fopen("../ride.txt", "r");
    if (file == NULL) {
        perror("���� ���� ����");
        return;
    }

    while (!feof(file)) {
        Ride ride;
        fscanf(file, "%d %s %d %d %d\n", &ride.id, ride.name, &ride.maxRiders,
            &ride.reservedRiders, &ride.status);
        createRide(ride.name, ride.maxRiders, ride.status);
    }

    fclose(file);
}

void saveRideToDB(Ride ride) {
    char* query = (char*)malloc(sizeof(char) * 100);
    sprintf(query, "INSERT INTO rides (name, max_riders, reserved_riders, status) VALUES ('%s', %d, %d, %d);",
        ride.name, ride.maxRiders, ride.reservedRiders, ride.status);
}

void saveTicketToDB(Ticket ticket) {
    char* query = (char*)malloc(sizeof(char) * 100);
    sprintf(query, "INSERT INTO tickets (pin_number, user_name, usage_date, pass_type, magic_pass_usage_count) VALUES (%d, '%s', %lld, %d, %d);",
        ticket.pinNumber, ticket.userName, ticket.usageDate, ticket.passType, ticket.magicPassUsageCount);
}


