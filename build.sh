cmake -Wdev -Wdeprecated -S $(pwd) -B "$(pwd)/build" -DCMAKE_BUILD_TYPE=Debug


if [[ $? -eq 0 ]]
then
    echo "Executing generated Makefile..."
    cd build
    make
    cd ..
fi
