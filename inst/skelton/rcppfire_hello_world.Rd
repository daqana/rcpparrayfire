\name{RcppFire-Functions}
\alias{rcppfire_hello_world}
\alias{rcppfire_innerproduct}
\alias{rcppfire_outerproduct}
\alias{rcppfire_bothproducts}
\title{Set of functions in example RcppFire package}
\description{
  These four functions are created when
  \code{RcppFire.package.skeleton()} is invoked to create a
  skeleton packages.
}
\usage{
rcppfire_hello_world()
rcppfire_outerproduct(x)
rcppfire_innerproduct(x)
rcppfire_bothproducts(x)
}
\arguments{
  \item{x}{a numeric vector}
}
\value{
  \code{rcppfire_hello_world()} does not return a value, but displays a
  message to the console.

  \code{rcppfire_outerproduct()} returns a numeric matrix computed as the
  outer (vector) product of \code{x}.

  \code{rcppfire_innerproduct()} returns a double computer as the inner
  (vector) product of \code{x}.

  \code{rcppfire_bothproducts()} returns a list with both the outer and
  inner products.
  
}
\details{
  These are example functions which should be largely
  self-explanatory. Their main benefit is to demonstrate how to write a
  function using the Arrayfire and RcppFire classes, and to have to such a
  function accessible from R.
}
\references{
  See the documentation for Arrayfire, and RcppFire, for more details.
}
\examples{
  x <- sqrt(1:4)
  rcppfire_innerproduct(x)
  rcppfire_outerproduct(x)
}
\author{Kazuki Fukui}

