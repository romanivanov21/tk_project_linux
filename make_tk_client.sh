rm -R build
mkdir build
cd build/
cmake -DBOOST_ROOT:STRING=/home/roman/Диплом/boost_1_57_0/ -DBOOST_LIBRARYDIR:STRING=/home/roman/Диплом/boost_1_57_0/libs/ /home/roman/Диплом/tk_project_linux/network_client/
make