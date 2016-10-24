/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
	/* Base cases */
	if(n==0)
		return 0;
	else if(n==1)
		return 1;
	else 	return fib(n-1)+fib(n-2);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
	static map<unsigned long, unsigned long> memo = {{0,0},{1,1},};
	auto lookup = memo.find(n);
	/* If key is in map */
	if(lookup != memo.end())
		return lookup->second;
	/* Else add (key,value) pair to map */
	else {
		unsigned long ret = memoized_fib(n-1) + memoized_fib(n-2);
		memo[n] = ret;
		return ret;
	}
}
