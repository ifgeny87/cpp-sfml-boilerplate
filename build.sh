# create build dir and go into
mkdir -p $(dirname $0)/build && cd $_
echo Current dir: $(pwd)

#cmake -DCMAKE_BUILD_TYPE=Debug ..
#cmake -DCMAKE_BUILD_TYPE=Release ..
cmake ..
cmake --build . --target hellosfml -- -j 4