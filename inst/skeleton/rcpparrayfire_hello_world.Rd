\name{RcppArrayFire-Functions}
\alias{rcpparrayfire_hello_world}
\alias{rcpparrayfire_innerproduct}
\alias{rcpparrayfire_outerproduct}
\alias{rcpparrayfire_bothproducts}
\title{Set of functions in example RcppArrayFire package}
\description{
  These four functions are created when
  \code{RcppArrayFire.package.skeleton()} is invoked to create a
  skeleton packages.
}
\usage{
rcpparrayfire_hello_world()
rcpparrayfire_outerproduct(x)
rcpparrayfire_innerproduct(x)
rcpparrayfire_bothproducts(x)
}
\arguments{
  \item{x}{a numeric vector}
}
\value{
  \code{rcpparrayfire_hello_world()} returns a numeric matrix computed
  by some simple array operations.

  \code{rcpparrayfire_outerproduct()} returns a numeric matrix computed as the
  outer (vector) product of \code{x}.

  \code{rcpparrayfire_innerproduct()} returns a double value computed as the inner
  (vector) product of \code{x}.

  \code{rcpparrayfire_bothproducts()} returns a list with both the outer and
  inner products.

}
\details{
  These are example functions which should be largely
  self-explanatory. Their main benefit is to demonstrate how to write a
  function using the ArrayFire and RcppArrayFire classes, and to have such a
  function accessible from R.
}
\references{
  See the documentation for ArrayFire and RcppArrayFire, for more details.
}
\examples{
  x <- sqrt(1:4)
  rcpparrayfire_innerproduct(x)
  rcpparrayfire_outerproduct(x)
}
\author{Kazuki Fukui}
