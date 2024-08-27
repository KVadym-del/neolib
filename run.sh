if [ ! -d "./build" ]; then
    mkdir build
fi

cmake -B./build/ -S . -DCMAKE_GENERATOR:INTERNAL="Ninja Multi-Config"
if [ $? -ne 0 ]; then
    echo "cmake failed"
    exit 1
fi

if [ "$1" == "debug" ] || [ "$1" == "" ]; then
    echo "building debug"
    cmake --build ./build/ --config Debug
else
    echo "building release"
    cmake --build ./build/ --config Release
fi
if [ $? -ne 0 ]; then
    echo "build failed"
    exit 1
fi

if [ "$1" == "debug" ] || [ "$1" == "" ]; then
	./build/test/Debug/neolib_test
else
	./build/test/Release/neolib_test
fi
if [ $? -ne 0 ];then echo "run failed"
    exit 1
fi
