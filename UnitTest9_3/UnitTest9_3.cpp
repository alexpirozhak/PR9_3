#include "pch.h"
#include "CppUnitTest.h"
#include "../PR9_3/PR9_3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const int N = 2;
            Student students[N];

            // Встановлення підробленого потоку вводу
            std::stringstream fakeInput;
            fakeInput << "Ivanov\nI.I.\n5 4 3 4 5\n";
            fakeInput << "Petrov\nP.P.\n4 3 4 5 3\n";
            std::streambuf* originalInput = std::cin.rdbuf(fakeInput.rdbuf());

            // Встановлення підробленого потоку виводу
            std::stringstream fakeOutput;
            std::streambuf* originalOutput = std::cout.rdbuf(fakeOutput.rdbuf());

            // Act
            Create(students, N);

            // Restore original cin and cout
            std::cin.rdbuf(originalInput);
            std::cout.rdbuf(originalOutput);

            // Assert
            Assert::AreEqual(std::string("vanov"), students[0].surname, L"Creating student failed", LINE_INFO());
            Assert::AreEqual(std::string("I.I."), students[0].initials, L"Creating student failed", LINE_INFO());
            Assert::AreEqual(5, students[0].marks[0], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(4, students[0].marks[1], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(3, students[0].marks[2], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(4, students[0].marks[3], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(5, students[0].marks[4], L"Creating student failed", LINE_INFO());

            Assert::AreEqual(std::string("Petrov"), students[1].surname, L"Creating student failed", LINE_INFO());
            Assert::AreEqual(std::string("P.P."), students[1].initials, L"Creating student failed", LINE_INFO());
            Assert::AreEqual(4, students[1].marks[0], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(3, students[1].marks[1], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(4, students[1].marks[2], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(5, students[1].marks[3], L"Creating student failed", LINE_INFO());
            Assert::AreEqual(3, students[1].marks[4], L"Creating student failed", LINE_INFO());
		}
	};
}
