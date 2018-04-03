#include "NewGameProjectTests.h"
//#include "Test/WorldReaderTest.h"
//#include "Test/DialogueTranslationTest.h"
#include "Logger.h"

void NewGameProjectTests::runTests() {
	//runTest<WorldReaderTest>();
	//runTest<DialogueTranslationTest>();
}

template<typename T>
void NewGameProjectTests::runTest() {
	T wlTest;
	TestResult tr = wlTest.runTest();

	g_logger->logWarning("NewGameProjectTests", tr.testName + ": " +
		std::to_string(tr.testsSucceeded) + " / " + std::to_string(tr.testsSucceeded) +
		" tests passed.");
}