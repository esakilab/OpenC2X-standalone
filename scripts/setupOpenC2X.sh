#!/bin/sh

apt-get install libzmq3-dev libboost-all-dev protobuf-compiler libprotobuf-dev libgps-dev gpsd gpsd-clients libnl-3-200 libnl-3-dev libnl-genl-3-200 libnl-genl-3-dev sqlite3 libsqlite3-dev tmux asn1c build-essential cmake doxygen libnl-route-3-dev
grep https://dl.bintray.com/fynnh/debian /etc/apt/sources.list
if [ $? = 0 ]; then
	echo "there is https://dl.bintray.com/fynnh/debian"
else
	echo "deb [trusted=yes] https://dl.bintray.com/fynnh/debian xenial main" | sudo tee -a /etc/apt/sources.list
fi
apt-get update
apt-get install openc2x
cd $HOME/AutoC2X-OC
-u mizu mkdir $HOME/AutoC2X-OC/sources
cd $HOME/AutoC2X-OC/sources
-u mizu git clone https://github.com/ppianpak/rosbridgecpp.git
-u mizu git clone https://github.com/nlohmann/json.git
-u mizu mkdir build
cd $HOME/AutoC2X-OC/build
cmake ..
make all