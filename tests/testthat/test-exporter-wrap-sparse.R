context("export and wrap sparse array")

library(Matrix)
library(Rcpp)

create.src <- function(dtype, storage){
    src.template <- '
    af::array asis%s_%s(const RcppArrayFire::typed_array<%s, AF_STORAGE_%s>& x) {
          return x;
    }'
    fill.template <- function(d, s){
      sprintf(src.template, s, d, d, s)
    }

    return(outer(dtype, storage, FUN = fill.template))
}

# NOTE: Matrix package <= 1.2-14 does not support integer and complex matrices
# NOTE: Arrayfire v3.6.1 only supports f64/f32/c64/c32
# TODO: Add some tests for other data types(complex, bool, etc.) when they are supported.
for (src in create.src(c('f64', 'f32'), c('CSR', 'CSC', 'COO'))){
    Rcpp::cppFunction(code = src, depends = "RcppArrayFire")
}

test_that("export and wrap CSR array", {
    x <- as(matrix(c(1, 0, 0, 2, 3,
                     0, 0, 1, 0, 2), 2, 5),
            'dgRMatrix')
    invalid.x <- new('dgCMatrix')

    expect_equal(x, asisCSR_f64(x))
    expect_equal(x, asisCSR_f32(x))
    expect_error(asisCSR_f64(invalid.x))
})


test_that("export and wrap CSC array", {
    x <- as(matrix(c(1, 0, 0, 2, 3,
                     0, 0, 1, 0, 2), 2, 5),
            'dgCMatrix')
    invalid.x <- new('dgRMatrix')

    expect_equal(x, asisCSC_f64(x))
    expect_equal(x, asisCSC_f32(x))
    expect_error(asisCSC_f64(invalid.x))
})


test_that("export and wrap COO array", {
    x <- as(matrix(c(1, 0, 0, 2, 3,
                     0, 0, 1, 0, 2), 2, 5),
            'dgTMatrix')
    invalid.x <- new('dgCMatrix')

    expect_equal(x, asisCOO_f64(x))
    expect_equal(x, asisCOO_f32(x))
    expect_error(asisCOO_f64(invalid.x))

})

