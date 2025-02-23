#include "task_manager.h"
#include <iostream>
#include <fstream>
#include <ctime>

TaskManager::TaskManager(const std::string& filename) : filename(filename) {
    loadTasks();
}

// Load tasks from JSON file
void TaskManager::loadTasks() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    json j;
    file >> j;
    for (const auto& item : j) {
        tasks.push_back(Task::fromJson(item));
    }
}

// Save tasks to JSON file
void TaskManager::saveTasks() {
    json j = json::array();
    for (const auto& task : tasks) {
        j.push_back(task.toJson());
    }
    std::ofstream file(filename);
    file << j.dump(4);  // Pretty-print JSON
}

// Get current timestamp
std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// Add a new task
void TaskManager::addTask(const std::string& description) {
    int id = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.push_back({id, description, "todo", getCurrentTime(), getCurrentTime()});
    saveTasks();
    std::cout << "Task added successfully (ID: " << id << ")\n";
}

// Update task description
void TaskManager::updateTask(int id, const std::string& newDescription) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.description = newDescription;
            task.updatedAt = getCurrentTime();
            saveTasks();
            std::cout << "Task updated successfully!\n";
            return;
        }
    }
    std::cout << "Task not found!\n";
}

// Delete a task
void TaskManager::deleteTask(int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        saveTasks();
        std::cout << "Task deleted successfully!\n";
    } else {
        std::cout << "Task not found!\n";
    }
}

// Mark task as in-progress or done
void TaskManager::markTask(int id, const std::string& status) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.status = status;
            task.updatedAt = getCurrentTime();
            saveTasks();
            std::cout << "Task marked as " << status << "!\n";
            return;
        }
    }
    std::cout << "Task not found!\n";
}

// List tasks
void TaskManager::listTasks(const std::string& status) {
    for (const auto& task : tasks) {
        if (status == "all" || task.status == status) {
            std::cout << "[" << task.id << "] " << task.description << " - " << task.status 
                      << " (Created: " << task.createdAt << ", Updated: " << task.updatedAt << ")\n";
        }
    }
}
