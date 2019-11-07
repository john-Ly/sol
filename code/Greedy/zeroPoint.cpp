#include <iostream>
#include <cmath>

// 具体的数值分析 在后面补充

double f(double x);

// 实现二分法
double bisection(double lo, double hi) {
	// 强制执行循环不变式
	if(f(lo) > 0)
		swap(lo, hi);
	// 循环不变式 f(lo) <= 0 < f(hi)

	while(fabs(hi-lo) > 2e-7) {
		double mid = (lo + hi) / 2;
		double fmid = f(mid); //

		if(fmid <= 0) lo = mid;
		else hi = mid;
	}

	return (lo + hi ) / 2;
}
