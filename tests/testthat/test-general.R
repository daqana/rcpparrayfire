context("general")

test_that("info message is produced", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    expect_output(arrayfire_info(), regex = "^ArrayFire v.*")
})

test_that("getting and setting the device works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    device_count <- arrayfire_count_device()
    for (i in 1:device_count) {
        arrayfire_set_device(i)
        expect_equal(i, arrayfire_get_device())
    }
})

test_that("getting device info works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    device_info <- arrayfire_device_info()
    expect_type(device_info, "list")
    expect_type(device_info$name, "character")
    expect_type(device_info$platform, "character")
    expect_type(device_info$toolkit, "character")
    expect_type(device_info$compute, "character")
})


test_that("getting and setting the backend works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    backends <- arrayfire_get_available_backends()
    for (backend in backends) {
        arrayfire_set_backend(backend)
        expect_equal(backend, arrayfire_get_active_backend())
    }
})

test_that("set_backend w/o argument uses DEFAULT", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    skip_on_os("mac")
    arrayfire_set_backend("DEFAULT")
    default_backend <- arrayfire_get_active_backend()
    arrayfire_set_backend("")
    expect_equal(default_backend, arrayfire_get_active_backend())
})
