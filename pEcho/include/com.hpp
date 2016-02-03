#pragma once
// Standard Library Includes
#include <vector>
#include <cmath>
#include <iostream>
#include <mutex>

namespace com {
	typedef std::vector<body> bodyVector;
	typedef std::vector<std::vector<double>> double2DVector;
  typedef std::vector<std::vector<int>> int2DVector;
  typedef std::lock_guard<std::mutex> lockGuard;
}
