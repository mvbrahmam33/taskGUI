#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Task {
    int id;
    std::string description;
    std::string status;  // "todo", "in-progress", "done"
    std::string createdAt;
    std::string updatedAt;

    // Convert Task to JSON
    json toJson() const {
        return json{{"id", id}, {"description", description}, {"status", status},
                    {"createdAt", createdAt}, {"updatedAt", updatedAt}};
    }

    // Create Task from JSON
    static Task fromJson(const json& j) {
        return {j["id"], j["description"], j["status"], j["createdAt"], j["updatedAt"]};
    }
};

// Task Manager class
class TaskManager {
public:
    TaskManager(const std::string& filename);
    void addTask(const std::string& description);
    void updateTask(int id, const std::string& newDescription);
    void deleteTask(int id);
    void markTask(int id, const std::string& status);
    void listTasks(const std::string& status = "all");
private:
    std::string filename;
    std::vector<Task> tasks;
    void loadTasks();
    void saveTasks();
};

#endif
