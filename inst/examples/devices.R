library(RcppArrayFire)

device_count <- arrayfire_count_device()
for(i in 1:device_count) {
    arrayfire_set_device(1)
    arrayfire_info()
}

