#include <stdio.h>
#include <string.h>

#define MAX_SEATS 15
#define MAX_BUSES 10   // 🔥 Increased buses
#define MAX_NAME 50

// Passenger structure
typedef struct {
    int id;
    char name[MAX_NAME];
} Passenger;

// Circular Queue structure
typedef struct {
    Passenger passengers[MAX_SEATS];
    int front, rear, count;
} CircularQueue;

// Bus structure
typedef struct {
    char route[100];
    CircularQueue queue;
} Bus;

Bus buses[MAX_BUSES];

// Initialize buses
void initBuses() {
    strcpy(buses[0].route, "Haliyal -> Dharwad");
    strcpy(buses[1].route, "Haliyal -> Dandeli");
    strcpy(buses[2].route, "Haliyal -> Goa");
    strcpy(buses[3].route, "Haliyal -> Hubli");
    strcpy(buses[4].route, "Haliyal -> Bangalore");
    strcpy(buses[5].route, "Haliyal -> Belgaum");
    strcpy(buses[6].route, "Haliyal -> Karwar");
    strcpy(buses[7].route, "Haliyal -> Sirsi");
    strcpy(buses[8].route, "Haliyal -> Yellapur");
    strcpy(buses[9].route, "Haliyal -> Ankola");

    for(int i = 0; i < MAX_BUSES; i++) {
        buses[i].queue.front = 0;
        buses[i].queue.rear = -1;
        buses[i].queue.count = 0;
    }
}

// Add passenger (Enqueue)
void addPassenger(int busIndex) {
    if(buses[busIndex].queue.count == MAX_SEATS) {
        printf("❌ Bus is FULL! Added to waiting list.\n");
        return;
    }

    Passenger p;
    printf("Enter Passenger ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    CircularQueue *q = &buses[busIndex].queue;

    q->rear = (q->rear + 1) % MAX_SEATS;
    q->passengers[q->rear] = p;
    q->count++;

    printf("✅ Passenger Added Successfully!\n");
}

// Remove passenger (Dequeue)
void removePassenger(int busIndex) {
    CircularQueue *q = &buses[busIndex].queue;

    if(q->count == 0) {
        printf("❌ No passengers in bus.\n");
        return;
    }

    Passenger p = q->passengers[q->front];
    q->front = (q->front + 1) % MAX_SEATS;
    q->count--;

    printf("🟢 Passenger Removed: %s (ID: %d)\n", p.name, p.id);
}

// Display passengers
void displayPassengers(int busIndex) {
    CircularQueue *q = &buses[busIndex].queue;

    if(q->count == 0) {
        printf("No passengers in this bus.\n");
        return;
    }

    int i, idx = q->front;

    printf("\n👥 Passenger List:\n");
    for(i = 0; i < q->count; i++) {
        Passenger p = q->passengers[idx];
        printf("ID: %d | Name: %s\n", p.id, p.name);
        idx = (idx + 1) % MAX_SEATS;
    }
}

// Show bus info
void showBuses() {
    printf("\n🚍 Available Buses:\n");
    for(int i = 0; i < MAX_BUSES; i++) {
        printf("%d. %s (Seats filled: %d/%d)\n",
               i + 1,
               buses[i].route,
               buses[i].queue.count,
               MAX_SEATS);
    }
}

// Simulated tracking
void trackBus(int busIndex) {
    printf("📍 Bus on route: %s\n", buses[busIndex].route);
    printf("🛰️ Current Location: Near City Center (Simulated)\n");
    printf("⏱️ ETA: 10 minutes (Simulated)\n");
}

// Main menu
int main() {
    int choice, busChoice;

    initBuses();

    while(1) {
        printf("\n====== 🚍 RADAR BUS TRACKER ======\n");
        printf("1. Show Buses\n");
        printf("2. Add Passenger\n");
        printf("3. Remove Passenger\n");
        printf("4. Show Passengers\n");
        printf("5. Track Bus\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 6) break;

        if(choice >= 2 && choice <= 5) {   // 🔥 FIX: show buses only when needed
            showBuses();
            printf("Select Bus: ");
            scanf("%d", &busChoice);
            busChoice--;
        }

        switch(choice) {
            case 1:
                showBuses();
                break;

            case 2:
                addPassenger(busChoice);
                break;

            case 3:
                removePassenger(busChoice);
                break;

            case 4:
                displayPassengers(busChoice);
                break;

            case 5:
                trackBus(busChoice);
                break;

            default:
                printf("❌ Invalid choice!\n");
        }
    }

    printf("👋 Exiting system...\n");
    return 0;
}
