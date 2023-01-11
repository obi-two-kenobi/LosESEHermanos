
FILE=./TrafficLightThreads
if [[ -f "$FILE" ]]; then
    echo "Removing old file..."
    rm TrafficLightThreads
fi


    echo "Compiling new file..."
g++ -std=c++17 ./*.cpp  -o TrafficLightThreads
    echo "Launching..."
./TrafficLightThreads
