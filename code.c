#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// ----------------- Patient Structure (Linked List) -----------------
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient* next;
};

// Head pointer for linked list
struct Patient* head = NULL;

// Function to register a patient
void registerPatient(int id, char name[], int age, char disease[]) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    newPatient->id = id;
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->disease, disease);
    newPatient->next = head;
    head = newPatient;
    printf("✅ Patient %s registered successfully!\n", name);
}

// Function to display all patients
void displayPatients() {
    struct Patient* temp = head;
    if (temp == NULL) {
        printf("No patients registered yet.\n");
        return;
    }
    printf("\n--- Patient List ---\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s\n", temp->id, temp->name, temp->age, temp->disease);
        temp = temp->next;
    }
}

// ----------------- Appointment Scheduling (Queue) -----------------
struct AppointmentQueue {
    int patients[MAX];
    int front, rear;
} queue = {.front = -1, .rear = -1};

// Function to add patient to queue
void scheduleAppointment(int patientID) {
    if (queue.rear == MAX - 1) {
        printf("❌ Appointment queue is full!\n");
        return;
    }
    if (queue.front == -1) queue.front = 0;
    queue.patients[++queue.rear] = patientID;
    printf("✅ Appointment scheduled for patient ID: %d\n", patientID);
}

// Function to process the next patient in queue
void processAppointment() {
    if (queue.front == -1 || queue.front > queue.rear) {
        printf("❌ No appointments to process.\n");
        return;
    }
    printf("🩺 Processing appointment for patient ID: %d\n", queue.patients[queue.front++]);
}

// ----------------- Emergency Handling (Priority Queue - Min Heap) -----------------
struct EmergencyPatient {
    int severity;
    int patientID;
};

struct EmergencyPatient heap[MAX];
int heapSize = 0;

// Function to insert patient in priority queue
void insertEmergency(int patientID, int severity) {
    heap[heapSize].patientID = patientID;
    heap[heapSize].severity = severity;
    int i = heapSize++;
    
    // Heapify up
    while (i > 0 && heap[i].severity < heap[(i - 1) / 2].severity) {
        struct EmergencyPatient temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    printf("🚨 Emergency patient %d added with severity %d.\n", patientID, severity);
}

// Function to process highest priority emergency case
void processEmergency() {
    if (heapSize == 0) {
        printf("❌ No emergency patients.\n");
        return;
    }
    printf("⚠ Processing emergency patient %d with severity %d.\n", heap[0].patientID, heap[0].severity);
    heap[0] = heap[--heapSize];

    // Heapify down
    int i = 0;
    while ((2 * i + 1) < heapSize) {
        int smallest = (2 * i + 1);
        if ((2 * i + 2) < heapSize && heap[2 * i + 2].severity < heap[smallest].severity)
            smallest = 2 * i + 2;
        if (heap[i].severity <= heap[smallest].severity) break;

        struct EmergencyPatient temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
}

// ----------------- Doctor’s Last Visited Patients (Stack) -----------------
struct Stack {
    int patientIDs[10];
    int top;
} patientHistory = {.top = -1};

// Function to push patient ID onto stack
void pushHistory(int patientID) {
    if (patientHistory.top == 9) {
        printf("❌ History full!\n");
        return;
    }
    patientHistory.patientIDs[++patientHistory.top] = patientID;
    printf("📋 Doctor visited patient ID: %d\n", patientID);
}

// Function to pop last visited patient
void popHistory() {
    if (patientHistory.top == -1) {
        printf("❌ No patient history.\n");
        return;
    }
    printf("🔄 Last visited patient ID: %d\n", patientHistory.patientIDs[patientHistory.top--]);
}

// ----------------- Main Menu -----------------
void menu() {
    int choice, id, age, severity;
    char name[50], disease[50];

    while (1) {
        printf("\n🏥 Hospital Patient Management System\n");
        printf("1. Register Patient\n");
        printf("2. Display Patients\n");
        printf("3. Schedule Appointment\n");
        printf("4. Process Appointment\n");
        printf("5. Add Emergency Case\n");
        printf("6. Process Emergency Case\n");
        printf("7. Record Doctor Visit\n");
        printf("8. Show Last Visited Patient\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Age: ");
                scanf("%d", &age);
                printf("Enter Disease: ");
                scanf("%s", disease);
                registerPatient(id, name, age, disease);
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                printf("Enter Patient ID for appointment: ");
                scanf("%d", &id);
                scheduleAppointment(id);
                break;

            case 4:
                processAppointment();
                break;

            case 5:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                printf("Enter Severity (1-10): ");
                scanf("%d", &severity);
                insertEmergency(id, severity);
                break;

            case 6:
                processEmergency();
                break;

            case 7:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                pushHistory(id);
                break;

            case 8:
                popHistory();
                break;

            case 9:
                printf("Exiting...\n");
                return;

            default:
                printf("❌ Invalid choice! Try again.\n");
        }
    }
}

// ----------------- Main Function -----------------
int main() {
    menu();
    return 0;
}
