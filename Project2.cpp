//Riyasat Rashid
//7-25-24

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

const int NUM_PHILOSOPHERS = 7;
const int INITIAL_RESOURCE = 30;

std::mutex forks[NUM_PHILOSOPHERS]; // Mutex locks for each fork
std::mutex cout_mutex; // Mutex for controlling access to std::cout

int shared_resource = INITIAL_RESOURCE; // Shared resource
std::vector<int> think_duration(NUM_PHILOSOPHERS, 0); // Think durations for each philosopher
std::vector<int> eat_duration(NUM_PHILOSOPHERS, 0); // Eat durations for each philosopher
std::vector<int> cycle_count(NUM_PHILOSOPHERS, 0); // Cycle counts for each philosopher

std::vector<std::vector<std::pair<int, int>>> cycles(NUM_PHILOSOPHERS); // Store each cycle's think and eat time

// Function to generate a random number in a given range
int get_random_duration(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void philosopher(int id) {
    while (true) {
        cycle_count[id]++; // Increment cycle count at the beginning of the cycle

        // Philosopher is thinking
        int think_time = get_random_duration(2, 4);
        std::this_thread::sleep_for(std::chrono::seconds(think_time));
        think_duration[id] += think_time;

        // Attempt to pick up forks
        std::unique_lock<std::mutex> left_fork(forks[id]);
        std::unique_lock<std::mutex> right_fork(forks[(id + 1) % NUM_PHILOSOPHERS]);

        // Check if there is enough resource to eat
        if (shared_resource > 0) {
            // Start eating
            shared_resource--;

            // Eating
            int eat_time = get_random_duration(1, 3);
            std::this_thread::sleep_for(std::chrono::seconds(eat_time));
            eat_duration[id] += eat_time;

            // Store cycle information
            cycles[id].emplace_back(think_time, eat_time);

            // Release forks
            left_fork.unlock();
            right_fork.unlock();
        } else {
            // No more resources, print final results and exit
            cycles[id].emplace_back(think_time, 0); // No eating time for the last cycle
            break;
        }
    }
}

int main() {
    // Create philosopher threads
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    // Join philosopher threads
    for (auto& phil : philosophers) {
        phil.join();
    }

    // Print final results
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        std::cout << "\nHello, my name is Philosopher " << i << " and my number is " << i << std::endl;
        std::cout << "My tummy is full of yummy food and my head is full of wonderful knowledge\n";
        std::cout << "---------------------------------------------------------\n";
        
        for (int j = 0; j < cycles[i].size(); ++j) {
            std::cout << "Cycle " << j + 1 << ": Pondered the universe for " << cycles[i][j].first 
                      << " seconds, Consumed food for " << cycles[i][j].second << " seconds.\n";
        }

        std::cout << "Total time spent pondering the universe: " << think_duration[i] << " seconds\n";
        std::cout << "Total time devouring delicious food: " << eat_duration[i] << " seconds\n";
        std::cout << "Total food devoured: " << cycle_count[i] << "\n";
    }

    return 0;
}
