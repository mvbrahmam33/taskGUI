run:
	./task-GUI
build:
	g++ -o task-cli src/main.cpp src/task_manager.cpp -I"C:/dev/vcpkg/packages/nlohmann-json_x64-windows/include"
	

