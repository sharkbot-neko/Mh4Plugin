#pragma once
#include "cheats.hpp"
#include <variant>

namespace CTRPluginFramework
{
	// ここにチート一覧
	void ModMenu_test(void);

	// ここにBoolのチート一覧
	bool zoom = false;

	struct ModMenuItems;

	struct CheatFolder {
		const char* name;
		std::vector<ModMenuItems> items;
	};

	using VoidNoArgFunctionPointer = void(*)();

	enum class ItemType {
		Function,   // 通常の関数
		Folder,     // フォルダ
		Toggle      // ON/OFF チート
	};


	struct ModMenuItems {
		int count;
		const char* name;
		ItemType type;
		VoidNoArgFunctionPointer function; // type == Function のとき
		CheatFolder folder;               // type == Folder のとき
		bool* toggle;                     // type == Toggle のとき

		// コンストラクタ（フォルダ用）
		ModMenuItems(int c, const char* n, CheatFolder f)
			: count(c), name(n), type(ItemType::Folder), function(nullptr), folder(f), toggle(nullptr) {}

		// コンストラクタ（関数用）
		ModMenuItems(int c, const char* n, VoidNoArgFunctionPointer fn)
			: count(c), name(n), type(ItemType::Function), function(fn), toggle(nullptr) {}

		// コンストラクタ（トグル用）
		ModMenuItems(int c, const char* n, bool* t)
			: count(c), name(n), type(ItemType::Toggle), function(nullptr), toggle(t) {}
	};

	const ModMenuItems AllModMenuItems[] = {
		{0, "Camera", CheatFolder{
			"Camera",
			{
				{0, "Zoom", &zoom},
			}
		}},
		{1, "Test", ModMenu_test}
	};

}