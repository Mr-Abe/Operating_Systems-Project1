# Operating_Systems-Project1
A C++ program that meets the requirements of Project_1 in Operating Systems (IUPUI)


You will write a C++ program to create a double-type array, x^0, of size N. The elements in the array are
initialized by random numbers that follows a normal distribution N(μ, o), whereμ is the mean of the
random numbers and u is their standard deviation.

You will create another array X1 whose elements are the average of three numbers (left, ego, and right)
from the previous array.

Where L(k) and R(k) are the indices of k's left and right elements, respectively. The array is considered as
wrapped-around. The left of k is k - 1 except O (zero) whose left side is N - 1. Likewise, the right of k is
k + 1 except N - 1 whose right side is O (zero).

Continue the iteration by incrementing t, then an array will eventually have all same value. It is called as
the consensus. You are asked to answer the following questions:

a) How long (how many iteration) does it take to reach the consensus (consensus time)?

b) What are the major factors affecting the consensus time? The number of elements (N), the
magnitude of values(μ), or the variance of values (u)? What are the relationship between the
major factor and the consensus time?

c) How can you determine that many values are all same when they are in floating-point variables?
