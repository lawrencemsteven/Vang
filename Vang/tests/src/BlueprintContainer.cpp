#include <catch2/catch_test_macros.hpp>

#include "Vang/Items/Item.h"
#include "Vang/Items/Usability/Placeable.h"

TEST_CASE("First Test Case") {
	SECTION("Test Case 1") {
		Vang::Item test("Test Item");
		test.use();

		Vang::Item test2("Test Item 2", std::make_unique<Vang::Placeable>());
		test2.use();
	}
}