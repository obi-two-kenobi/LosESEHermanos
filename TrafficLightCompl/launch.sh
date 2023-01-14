
FILE=./TrafficLightThreads
if [[ -f "$FILE" ]]; then
    echo "Removing old file..."
    rm TrafficLightThreads
fi


    echo "Compiling new file..."
g++ -std=c++20 ./*.cpp  -o TrafficLightThreads
    echo "Launching..."
./TrafficLightThreads
