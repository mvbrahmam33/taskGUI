#include "task_manager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    TaskManager manager("tasks.json");

    if (argc < 2) {
        std::cout << "Usage: task-cli <command> [args]\n";
        return 1;
    }
    std::cout<<"argc: "<<argc<<"hiiii\n";
    std::string command = argv[1];

    if (command == "add" && argc >= 3) {
        manager.addTask(argv[2]);
    } else if (command == "update" && argc >= 4) {
        manager.updateTask(std::stoi(argv[2]), argv[3]);
    } else if (command == "delete" && argc >= 3) {
        manager.deleteTask(std::stoi(argv[2]));
    } else if (command == "mark-in-progress" && argc >= 3) {
        manager.markTask(std::stoi(argv[2]), "in-progress");
    } else if (command == "mark-done" && argc >= 3) {
        manager.markTask(std::stoi(argv[2]), "done");
    } else if (command == "list") {
        std::string filter = argc >= 3 ? argv[2] : "all";
        manager.listTasks(filter);
    } else {
        std::cout << "Invalid command!\n";
    }

    return 0;
}
