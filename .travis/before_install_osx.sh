brew install fontconfig glfw
curl -O https://arrayfire.s3.amazonaws.com/3.6.4/ArrayFire-v3.6.4_OSX_x86_64.pkg
sudo installer -pkg ArrayFire-v3.6.4_OSX.pkg -target /
rm ArrayFire-v3.6.4_OSX.pkg

cat <<EOF > minimal.cpp
#include <arrayfire.h>
#include <stdio.h>

int main() {
  unsigned int count;
  af_get_backend_count(&count);
  printf("backends: %d\n", count);
  af_info();
  return 0;
}
EOF

echo "With afopencl"
clang++ minimal.cpp -lafopencl -o minimal
./minimal
otool -L minimal
echo "With af"
clang++ minimal.cpp -laf -o minimal
./minimal
otool -L minimal
echo "Removing temp files"
rm -f minimal minimal.cpp
otool -L /opt/arrayfire/lib/libaf.3.dylib
otool -L /opt/arrayfire/lib/libafopencl.3.dylib
otool -L /opt/arrayfire/lib/libafcpu.3.dylib
