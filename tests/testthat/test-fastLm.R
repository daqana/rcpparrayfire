context("fastLm")

# create some random data
set.seed(42)
n <- 100000
p <- 40
X <- matrix(rnorm(n*p), ncol=p)
y <- X %*% c(rep(0.5, p)) + rnorm(n)

test_that("models from R and AF are similar", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    # fit model with R and AF
    modelR <- lm.fit(X, y)
    modelAF <- fastLmPure(X, y)

    # compare results
    deviation <- mean(abs(modelR$coefficients - modelAF$coefficients))
    expect_lt(deviation, 10^-5)
    expect_false(modelAF$intercept)
})

test_that("including intercept works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    X <- cbind(1, X)
    modelAF <- fastLmPure(X, y)
    expect_true(modelAF$intercept)
    expect_equal(length(modelAF$coefficients), p + 1)
})

test_that("models from R and AF on CPU are very similar", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    skip_on_os("mac")
    arrayfire_set_backend("CPU")
    # fit model with R and AF
    modelR <- lm.fit(X, y)
    modelAF <- fastLmPure(X, y, useDouble = TRUE)

    # compare results
    deviation <- mean(abs(modelR$coefficients - modelAF$coefficients))
    expect_lt(deviation, 10^-10)
    expect_false(modelAF$intercept)
})

