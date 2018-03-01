context("rng")

seed <- 12345678901234567890

test_that("setting and getting the random seed works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    arrayfire_set_seed(seed)
    expect_equal(seed, arrayfire_get_seed())
})

test_that("setting seed produces identical uniformly distributed numbers", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    arrayfire_set_seed(seed)
    u1 <- fastRunif(10)
    arrayfire_set_seed(seed)
    u2 <- fastRunif(10)
    expect_equal(u1, u2)
})

test_that("setting seed produces identical normaly distributed numbers", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    arrayfire_set_seed(seed)
    n1 <- fastRnorm(10)
    arrayfire_set_seed(seed)
    n2 <- fastRnorm(10)
    expect_equal(n1, n2)
})

test_that("numbers are generated in the correct range", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    arrayfire_set_seed(seed)
    u <- fastRunif(1e4, min = 10, max = 12)
    expect_true(all(u >= 10) && all(u < 12))
})
