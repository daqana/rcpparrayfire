library(RcppArrayFire)

arrayfire_get_active_backend()
backends <- arrayfire_get_available_backends()

for (backend in backends) {
    arrayfire_set_backend(backend)
    print(arrayfire_get_active_backend())
}

arrayfire_set_backend("DEFAULT")
arrayfire_get_active_backend()

arrayfire_set_backend()
arrayfire_get_active_backend()
