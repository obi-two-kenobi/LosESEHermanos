
FILE=./TrafficLightDemo
if [[ -f "$FILE" ]]; then
    echo "Removing old file..."
    rm TrafficLightDemo
fi


    echo "Compiling new file..."
g++ -std=c++17 ./*.cpp ./utils/*.cpp -o TrafficLightDemo
    echo "Launching..."
./TrafficLightDemo
