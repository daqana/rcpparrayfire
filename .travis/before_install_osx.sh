brew install fontconfig glfw
curl -O http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-v3.5.1_OSX.pkg
sudo installer -pkg ArrayFire-v3.5.1_OSX.pkg -target /
rm ArrayFire-v3.5.1_OSX.pkg

cat <<EOF > minimal.cpp
#include <arrayfire.h>
int main() {
    af_info();
}
EOF

clang++ minimal.cpp -laf -o minimal
./minimal
