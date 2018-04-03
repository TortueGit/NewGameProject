#pragma once

#include "global.h"

/// Static class for testing
class NewGameProjectTests final {
private:
	NewGameProjectTests() {};

public:
	static void runTests();

private:
	template<typename T>
	static void runTest();
};