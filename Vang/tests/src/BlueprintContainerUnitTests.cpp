#include <catch2/catch_test_macros.hpp>

#include "Vang/Utility/BlueprintContainer/BlueprintContainer.h"
#include "Vang/Items/ItemBlueprint.h"
#include "Vang/Modding/Mod.h"

using namespace Vang;

TEST_CASE("BlueprintContainer.addBlueprint()") {
	SECTION("addBlueprint() with many blueprints") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};

		itemBlueprintContainer.addBlueprint({mod, "Test_Item", "Test Item"});
		CHECK(itemBlueprintContainer.size() == 1);

		itemBlueprintContainer.addBlueprint({mod, "Test_Item2", "Test Item 2"});
		CHECK(itemBlueprintContainer.size() == 2);

		itemBlueprintContainer.addBlueprint({mod, "Test_Item3", "Test Item 3"});
		CHECK(itemBlueprintContainer.size() == 3);
	}

	SECTION("addBlueprint() with same name") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};

		itemBlueprintContainer.addBlueprint({mod, "Test_Item", "Test Item"});
		CHECK(itemBlueprintContainer.size() == 1);

		bool success = false;
		try {
			itemBlueprintContainer.addBlueprint({mod, "Test_Item", "Test Item"});
		}
		catch (...) {
			success = true;
		}

		CHECK(success);
		CHECK(itemBlueprintContainer.size() == 1);
	}

	SECTION("addBlueprint() with same name but different mod name") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		Mod mod2{"Default2"};

		itemBlueprintContainer.addBlueprint({mod, "Test_Item", "Test Item"});
		CHECK(itemBlueprintContainer.size() == 1);

		itemBlueprintContainer.addBlueprint({mod2, "Test_Item", "Test Item"});
		CHECK(itemBlueprintContainer.size() == 2);
	}
}

TEST_CASE("BlueprintContainer.getBlueprint()") {
	SECTION("getBlueprint() with id") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		uint32_t numItems = 10;

		for (uint32_t i = 0; i < numItems; i++) {
			itemBlueprintContainer.addBlueprint(
				{mod, "Test_Item_" + std::to_string(i), "Test Item " + std::to_string(i)});
		}

		CHECK(itemBlueprintContainer.size() == numItems);

		for (uint32_t i = 0; i < numItems; i++) {
			ItemBlueprint& blueprint = itemBlueprintContainer.getBlueprint(i);
			CHECK(blueprint.getDisplayName() == "Test Item " + std::to_string(i));
		}
	}

	SECTION("getBlueprint() with id backwards") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		uint32_t numItems = 10;

		for (uint32_t i = numItems; i > 0; i--) {
			itemBlueprintContainer.addBlueprint(
				{mod, "Test_Item_" + std::to_string(i), "Test Item " + std::to_string(i)});
		}

		CHECK(itemBlueprintContainer.size() == numItems);

		for (uint32_t i = 0; i < numItems; i++) {
			ItemBlueprint& blueprint = itemBlueprintContainer.getBlueprint(i);
			CHECK(blueprint.getDisplayName() == "Test Item " + std::to_string(numItems - i));
		}
	}

	SECTION("getBlueprint() with mixed positions") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		std::vector blueprintDisplayNames{"Test Item 0", "Test Item 10", "Test Item 3",
										  "Test Item 7", "Test Item 94", "Test Item 5"};
		std::vector blueprintTechnicalNames{"Test_Item_0", "Test_Item_10", "Test_Item_3",
											"Test_Item_7", "Test_Item_94", "Test_Item_5"};
		uint32_t numItems = blueprintDisplayNames.size();

		for (uint32_t i = 0; i < numItems; i++) {
			itemBlueprintContainer.addBlueprint(
				{mod, blueprintTechnicalNames[i], blueprintDisplayNames[i]});
		}

		CHECK(itemBlueprintContainer.size() == numItems);

		for (uint32_t i = 0; i < numItems; i++) {
			CHECK(itemBlueprintContainer.getBlueprint(i).getDisplayName() ==
				  blueprintDisplayNames[i]);
		}
	}

	SECTION("getBlueprint() with invalid id") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};

		bool success = false;
		try {
			itemBlueprintContainer.getBlueprint(0);
		}
		catch (...) {
			success = true;
		}
		CHECK(success);

		itemBlueprintContainer.addBlueprint({mod, "Test_Item", "Test Item"});

		auto& testBlueprint = itemBlueprintContainer.getBlueprint(0);
		CHECK(testBlueprint.getDisplayName() == "Test Item");

		success = false;
		try {
			itemBlueprintContainer.getBlueprint(1);
		}
		catch (...) {
			success = true;
		}
		CHECK(success);
	}
}

TEST_CASE("BlueprintContainer.getBlueprintId()") {
	SECTION("getBlueprintId()") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		uint32_t numItems = 10;

		for (uint32_t i = 0; i < numItems; i++) {
			itemBlueprintContainer.addBlueprint(
				{mod, "Test_Item_" + std::to_string(i), "Test Item " + std::to_string(i)});
		}

		for (uint32_t i = 0; i < numItems; i++) {
			std::string displayName		   = "Test Item " + std::to_string(i);
			std::string technicalName	   = mod.getName() + "::Test_Item_" + std::to_string(i);
			const auto blueprintIdOptional = itemBlueprintContainer.getBlueprintId(technicalName);
			REQUIRE(blueprintIdOptional.has_value());
			ItemBlueprint& blueprint =
				itemBlueprintContainer.getBlueprint(blueprintIdOptional.value());
			CHECK(blueprint.getDisplayName() == displayName);
		}
	}

	SECTION("getBlueprintId() backwards") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		uint32_t numItems = 10;

		for (uint32_t i = numItems; i > 0; i--) {
			itemBlueprintContainer.addBlueprint(
				{mod, "Test_Item_" + std::to_string(i), "Test Item " + std::to_string(i)});
		}

		for (uint32_t i = 0; i < numItems; i++) {
			std::string displayName		   = "Test Item " + std::to_string(i + 1);
			std::string technicalName	   = mod.getName() + "::Test_Item_" + std::to_string(i + 1);
			const auto blueprintIdOptional = itemBlueprintContainer.getBlueprintId(technicalName);
			REQUIRE(blueprintIdOptional.has_value());
			ItemBlueprint& blueprint =
				itemBlueprintContainer.getBlueprint(blueprintIdOptional.value());
			CHECK(blueprint.getDisplayName() == displayName);
		}
	}

	SECTION("getBlueprintId() with mixed positions") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		std::vector blueprintDisplayNames{"Test Item 0", "Test Item 10", "Test Item 3",
										  "Test Item 7", "Test Item 94", "Test Item 5"};
		std::vector blueprintTechnicalNames{"Test_Item_0", "Test_Item_10", "Test_Item_3",
											"Test_Item_7", "Test_Item_94", "Test_Item_5"};
		uint32_t numItems = blueprintDisplayNames.size();

		for (uint32_t i = 0; i < numItems; i++) {
			itemBlueprintContainer.addBlueprint(
				{mod, blueprintTechnicalNames[i], blueprintDisplayNames[i]});
		}

		CHECK(itemBlueprintContainer.size() == numItems);

		for (uint32_t i = 0; i < numItems; i++) {
			auto blueprintIdOptional = itemBlueprintContainer.getBlueprintId(
				mod.getName() + "::" + blueprintTechnicalNames[i]);
			REQUIRE(blueprintIdOptional.has_value());
			ItemBlueprint& blueprint =
				itemBlueprintContainer.getBlueprint(blueprintIdOptional.value());
			CHECK(blueprint.getDisplayName() == blueprintDisplayNames[i]);
		}
	}

	SECTION("getBlueprintId() with invalid id") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};

		auto blueprintIdOptional = itemBlueprintContainer.getBlueprintId("NON_EXISTANT_ITEM");
		CHECK(!blueprintIdOptional.has_value());

		itemBlueprintContainer.addBlueprint({mod, "Test_Item", "Test Item"});

		blueprintIdOptional = itemBlueprintContainer.getBlueprintId(mod.getName() + "::Test_Item");
		CHECK(blueprintIdOptional.has_value());

		blueprintIdOptional =
			itemBlueprintContainer.getBlueprintId(mod.getName() + "::NOT_REAL_ITEM");
		CHECK(!blueprintIdOptional.has_value());
	}
}

TEST_CASE("BlueprintContainer.setBlueprintId()") {
	SECTION("setBlueprintId()") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		uint32_t numItems = 10;

		std::cout << "Test0\n";
		for (uint32_t i = 0; i < numItems; i++) {
			itemBlueprintContainer.addBlueprint(
				{mod, "Test_Item_" + std::to_string(i), "Test Item " + std::to_string(i)});
		}
		std::cout << "Test1\n";

		CHECK(itemBlueprintContainer.setBlueprintId(mod.getName() + "::Test_Item_0", numItems - 1));
		CHECK(itemBlueprintContainer.getBlueprintId(mod.getName() + "::Test_Item_0").value() ==
			  numItems - 1);

		std::cout << "Test\n";
		for (uint32_t i = 1; i < numItems; i++) {
			CHECK(itemBlueprintContainer.setBlueprintId(
				mod.getName() + "::Test_Item_" + std::to_string(i), i - 1));
			CHECK(itemBlueprintContainer
					  .getBlueprintId(mod.getName() + "::Test_Item_" + std::to_string(i))
					  .value() == i - 1);
		}
		std::cout << "Test2\n";
	}
}

TEST_CASE("BlueprintContainer.size()") {
	SECTION("size()") {
		BlueprintContainer<ItemBlueprint> itemBlueprintContainer{};
		Mod mod{"Default"};
		uint32_t numItems = 10;

		for (uint32_t i = 0; i < numItems; i++) {
			itemBlueprintContainer.addBlueprint(
				{mod, "Test_Item_" + std::to_string(i), "Test Item " + std::to_string(i)});
			CHECK(itemBlueprintContainer.size() == i + 1);
		}
	}
}