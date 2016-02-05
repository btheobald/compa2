#pragma once
// Standard Library Includes
#include <vector>
#include <mutex>
// Custom Typedefs
namespace com {
	typedef std::vector<body> bodyVector;
	typedef std::vector<std::vector<double>> double2DVector;
  typedef std::lock_guard<std::mutex> lockGuard;

  // Color Arrays
  const float white[3] = { 1.0f, 1.0f, 1.0f };
  const float red[3] = { 1.0f, 0.0f, 0.0f };
  const float green[3] = { 0.0f, 1.0f, 0.0f };
  const float blue[3] = { 0.0f, 0.0f, 1.0f };
}
