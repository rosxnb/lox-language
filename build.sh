cmake -Wdev -Wdeprecated -S $(pwd) -B "$(pwd)/build"


if [[ $? -eq 0 ]]
then
    echo "Executing generated Makefile..."
    cd build
    make
    cd ..
fi
