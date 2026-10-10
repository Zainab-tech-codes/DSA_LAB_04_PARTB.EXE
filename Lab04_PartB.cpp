#include <iostream>
#include <string>
using namespace std;

// ==========================================
// Vehicle Node
// ==========================================
struct VehicleNode
{
    int ticketID;
    string plateNumber;
    string ownerName;
    string vehicleType;
    int priority;
    VehicleNode* next;
};

// ==========================================
// Priority Queue Class
// ==========================================
class PriorityQueue
{
private:
    VehicleNode* front;
    VehicleNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add vehicle according to priority
    void Add(VehicleNode* vehicle)
    {
        vehicle->next = nullptr;

        // Case 1: Queue is empty
        if (front == nullptr)
        {
            front = vehicle;
            rear = vehicle;
        }
        // Case 2: New vehicle has higher priority than front
        else if (vehicle->priority < front->priority)
        {
            vehicle->next = front;
            front = vehicle;
        }
        // Case 3: Insert after vehicles of same or higher priority
        else
        {
            VehicleNode* current = front;
            while (current->next != nullptr &&
                   current->next->priority <= vehicle->priority)
            {
                current = current->next;
            }
            vehicle->next = current->next;
            current->next = vehicle;

            if (vehicle->next == nullptr)
            {
                rear = vehicle;
            }
        }
        count++;
    }

    // Remove highest-priority vehicle
    VehicleNode* Remove()
    {
        if (front == nullptr)
        {
            return nullptr;
        }

        VehicleNode* vehicle = front;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        vehicle->next = nullptr;
        count--;
        return vehicle;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    int GetCount()
    {
        return count;
    }

    void PrintQueue()
    {
        VehicleNode* current = front;
        while (current != nullptr)
        {
            cout << "Ticket ID    : " << current->ticketID << endl;
            cout << "Plate Number : " << current->plateNumber << endl;
            cout << "Owner Name   : " << current->ownerName << endl;
            cout << "Vehicle Type : " << current->vehicleType << endl;
            cout << "Priority     : " << current->priority << endl;
            cout << "-----------------------------" << endl;
            current = current->next;
        }
    }

    // Copy Constructor
    PriorityQueue(const PriorityQueue& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;

        VehicleNode* current = other.front;
        while (current != nullptr)
        {
            VehicleNode* newNode = new VehicleNode;
            newNode->ticketID = current->ticketID;
            newNode->plateNumber = current->plateNumber;
            newNode->ownerName = current->ownerName;
            newNode->vehicleType = current->vehicleType;
            newNode->priority = current->priority;
            newNode->next = nullptr;
            Add(newNode);
            current = current->next;
        }
    }

    // Assignment Operator
    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (front != nullptr)
        {
            VehicleNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;

        VehicleNode* current = other.front;
        while (current != nullptr)
        {
            VehicleNode* newNode = new VehicleNode;
            newNode->ticketID = current->ticketID;
            newNode->plateNumber = current->plateNumber;
            newNode->ownerName = current->ownerName;
            newNode->vehicleType = current->vehicleType;
            newNode->priority = current->priority;
            newNode->next = nullptr;
            Add(newNode);
            current = current->next;
        }
        return *this;
    }

    // Destructor
    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            VehicleNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

// ==========================================
// Create Vehicle
// ==========================================
VehicleNode* CreateVehicle(int ticketID, string plateNumber,
                           string ownerName, string vehicleType, int priority)
{
    VehicleNode* vehicle = new VehicleNode;
    vehicle->ticketID = ticketID;
    vehicle->plateNumber = plateNumber;
    vehicle->ownerName = ownerName;
    vehicle->vehicleType = vehicleType;
    vehicle->priority = priority;
    vehicle->next = nullptr;
    return vehicle;
}

// ==========================================
// Main (Demo)
// ==========================================
int main()
{
    PriorityQueue parkingQueue;

    // Vehicles arrive at the full parking lot in this order
    parkingQueue.Add(CreateVehicle(1, "LEA-1234", "Ali", "Car", 3));
    parkingQueue.Add(CreateVehicle(2, "LHR-5678", "Rescue 1122", "Ambulance", 1));
    parkingQueue.Add(CreateVehicle(3, "LEB-4321", "Bilal", "Disabled Permit Car", 2));
    parkingQueue.Add(CreateVehicle(4, "LEC-8765", "Hamza", "Motorcycle", 3));
    parkingQueue.Add(CreateVehicle(5, "PFS-1122", "Fire Brigade", "Fire Truck", 1));

    cout << "===== Vehicles Waiting for Parking =====" << endl << endl;
    parkingQueue.PrintQueue();

    cout << endl << "Total waiting: " << parkingQueue.GetCount() << endl;

    // A parking slot becomes free: serve highest-priority vehicle
    cout << endl << "===== Parking Slot Available: Allowing Vehicle =====" << endl;
    VehicleNode* allowed = parkingQueue.Remove();
    if (allowed != nullptr)
    {
        cout << "Ticket ID    : " << allowed->ticketID << endl;
        cout << "Plate Number : " << allowed->plateNumber << endl;
        cout << "Owner Name   : " << allowed->ownerName << endl;
        cout << "Vehicle Type : " << allowed->vehicleType << endl;
        cout << "Priority     : " << allowed->priority << endl;
        delete allowed;
    }

    cout << endl << "===== Remaining Vehicles =====" << endl << endl;
    parkingQueue.PrintQueue();

    cout << "Queue Status: ";
    if (parkingQueue.IsEmpty())
        cout << "EMPTY" << endl;
    if (parkingQueue.IsNotEmpty())
        cout << "NOT EMPTY (" << parkingQueue.GetCount() << " waiting)" << endl;

    return 0;
}