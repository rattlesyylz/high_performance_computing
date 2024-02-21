#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <vector>
#include <queue>
#include <random>

using namespace std;

// This section defines constants and variables for an elevator simulation.

const int TOTLE_MAX = 10;     // Maximum number of passengers allowed in each elevator
const int MAX_TIME = 1000;    // Maximum simulation time in milliseconds
const int TOTLE_FLOOR = 20;   // Total number of floors in the building
const int TOTLE_ELEVATOR = 3; // Total number of elevators in the building

mutex find_count;
mutex find_elevator[TOTLE_ELEVATOR];
queue<int> floor_elevator[TOTLE_ELEVATOR];
vector<int> people_take_elev[TOTLE_ELEVATOR];
int array_elev[TOTLE_ELEVATOR] = {0, 0, 0};  // Array to store current positions of each elevator
int up_or_down[TOTLE_ELEVATOR] = {0, 0, 0}; // Array to store current directions of each elevator
int current_position = 0;
int current_num_people[TOTLE_ELEVATOR] = {0, 0, 0};  // Array to store the current number of people in each elevator

int find_which_eleva(int current_floor, int destination_floor)
{
  int start_eleva = -1;
  int minimum = TOTLE_FLOOR + 1;

  // Lambda function to check each elevator
  auto check_elevator = [&](int i)
  {
    lock_guard<mutex> lock(find_elevator[i]);

    int find_distance = abs(array_elev[i] - current_floor);
    int find_up_or_down = up_or_down[i];

    // Check if the elevator is on the way to the destination
    if ((destination_floor - current_floor) * find_up_or_down < 0) // on the way
    {
      find_distance += TOTLE_FLOOR;
    }

    // Check if the elevator is closer and has available capacity
    if (find_distance < minimum && people_take_elev[i].size() < TOTLE_MAX)
    {
      minimum = find_distance;
      start_eleva = i;
    }
  };

  // Iterate over each elevator and check its suitability
  for (int i = 0; i < TOTLE_ELEVATOR; i++)
  {
    check_elevator(i);
  }

  return start_eleva;
}

void logicEleva(int personId, int current_floor, int destination_floor)
{
    int get_elevator = find_which_eleva(current_floor, destination_floor);
    if (get_elevator == -1)
    return;

    // Add the person's current floor and destination floor to the selected elevator
    {
    lock_guard<mutex> lock(find_elevator[get_elevator]);
    floor_elevator[get_elevator].push(current_floor);
    floor_elevator[get_elevator].push(destination_floor);
    people_take_elev[get_elevator].push_back(personId);
    }

    // Print a message indicating that the person entered the elevator
    {
    lock_guard<mutex> count_lock(find_count);
    cout << "Person " << personId << " entered elevator " << get_elevator << endl;
    }
}

void peopleInEleva(int personId)
{
    // Generate random current floor and destination floor for the person
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_int_distribution<int> dist_floor(1, TOTLE_FLOOR);
    int current_floor = dist_floor(gen);
    int destination_floor;
    do
    {
    destination_floor = dist_floor(gen);
    } while (current_floor == destination_floor);

    // Print a message indicating the person's desired floors
    {
    std::lock_guard<mutex> lock(find_count);
    cout << "Person " << personId << " wants to go from floor " << current_floor << " to floor " << destination_floor << endl;
    }

    // Call the logicEleva function to handle the person's elevator request
    logicEleva(personId, current_floor, destination_floor);
}

void enterEleva(int personID, int numPeople)
{
  while (true)
  {
    unique_lock<mutex> lock(find_elevator[personID]);

    if (!floor_elevator[personID].empty())
    {
      int destination_floor = floor_elevator[personID].front();
      up_or_down[personID] = destination_floor > array_elev[personID] ? 1 : -1;
      floor_elevator[personID].pop();
      int current_floor = array_elev[personID];
      while (array_elev[personID] != destination_floor)
      {
        array_elev[personID] += up_or_down[personID];
      }

      {
        lock_guard<mutex> cout_lock(find_count);
        cout << "Elevator " << personID << " moving from floor " << current_floor << " to floor " << destination_floor << endl;
      }
      current_position++;

      if (!floor_elevator[personID].empty())
      {
        int front_floor = floor_elevator[personID].front();
        up_or_down[personID] = front_floor > array_elev[personID] ? 1 : -1;
        floor_elevator[personID].pop();
        int new_current_floor = array_elev[personID];
        while (array_elev[personID] != front_floor)
        {
          array_elev[personID] += up_or_down[personID];
        }

        {
          lock_guard<mutex> cout_lock(find_count);
          cout << "Elevator " << personID << " moving from floor " << new_current_floor << " to floor " << front_floor << endl;
        }
      }
    }

    if (current_position >= numPeople)
    {
      break;
    }

    this_thread::yield();
  }

  {
    lock_guard<mutex> lock(find_count);
    cout << "Elevator " << personID << " has finished servicing all people." << endl;
  }
}

int main()
{
  // Get the number of people to service
  int numPeople;
  std::cout << "Enter the number of people to service: ";
  cin >> numPeople;

  // Create an array of elevator threads
  thread elevators[TOTLE_ELEVATOR];

  // Start elevator threads and initialize elevator array
  for (int i = 0; i < TOTLE_ELEVATOR; i++)
  {
    elevators[i] = std::thread(enterEleva, i, numPeople);
    array_elev[i] = 0;
  }

  // Randomly generate wait times for each person
  default_random_engine gen;
  uniform_int_distribution<int> dist(0, MAX_TIME);

  // Create threads for each person and detach them
  for (int i = 0; i < numPeople; i++)
  {
    int wait_time = dist(gen);
    this_thread::sleep_for(chrono::milliseconds(wait_time));
    std::thread t(peopleInEleva, i);
    t.detach();
  }

  // Wait until all people have been serviced
  while (current_position < numPeople)
  {
    this_thread::yield();
  }

  // Print job completion message
  {
    lock_guard<mutex> lock(find_count);
    cout << "Job completed!" << endl;
  }

  // Join all elevator threads
  for (int i = 0; i < TOTLE_ELEVATOR; i++)
  {
    elevators[i].join();
  }

  return 0;
}
