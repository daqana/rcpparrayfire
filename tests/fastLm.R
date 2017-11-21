library(RcppArrayFire)

# create some random data
set.seed(42)
n <- 100000
p <- 40
X <- matrix(rnorm(n*p), ncol=p)
y <- X %*% c(rep(0.5, p)) + rnorm(n)

# fit model with R and AF
modelR <- lm.fit(X, y)
modelAF <- fastLmPure(X, y)

# compare results
deviation <- mean(abs(modelR$coefficients - modelAF$coefficients))
stopifnot(deviation < 10^-5)
stopifnot(modelAF$intercept == FALSE)

# include intercept
X <- cbind(1, X)
modelAF <- fastLmPure(X, y)
stopifnot(modelAF$intercept == TRUE)
stopifnot(length(modelAF$coefficients) == p + 1)
