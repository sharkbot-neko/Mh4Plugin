#include "Item.hpp"
#include "items.h"

namespace CTRPluginFramework
{
    void GetItemPocket(u16 itemid, u8 count, int basho) {
        u32 offset = 0x00000000;
        Process::Read32(offset + 0x0E1CFE4, offset);
        u16 i = 4 * (basho - 1);
        Process::Write32(offset + 0x000100C + i, itemid * 0x10000);
        Process::Write8(offset + 0x0001010 + i, count);
    }

    constexpr size_t ITEMS_PER_PAGE = 20;

    ITEM_MAP* SelectItemWithPagination()
    {
        size_t totalItems = sizeof(AllItems) / sizeof(ITEM_MAP);
        size_t currentPage = 0;
        size_t totalPages = (totalItems + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;

        while (true)
        {
            Keyboard keyboard("アイテムを選択 (ページ " + std::to_string(currentPage + 1) + " / " + std::to_string(totalPages) + ")");
            std::vector<std::string> itemNames;

            // 現在のページに表示するアイテムを追加
            size_t start = currentPage * ITEMS_PER_PAGE;
            size_t end = std::min(start + ITEMS_PER_PAGE, totalItems);

            for (size_t i = start; i < end; ++i)
            {
                itemNames.push_back(AllItems[i].name1);
            }

            // 「次のページ」や「前のページ」をオプションとして追加
            if (currentPage > 0)
                itemNames.push_back("前のページ");
            if (currentPage < totalPages - 1)
                itemNames.push_back("次のページ");

            // Populateでリストを設定
            keyboard.Populate(itemNames);

            // キーボードを表示して、選択されたインデックスを取得
            int selectedIndex = keyboard.Open();

            // キャンセルされた場合は nullptr を返す
            if (selectedIndex < 0)
                return nullptr;

            // ページング操作
            if (currentPage > 0 && selectedIndex == (int)itemNames.size() - 2) // 「前のページ」
            {
                currentPage--;
                continue;
            }
            if (currentPage < totalPages - 1 && selectedIndex == (int)itemNames.size() - 1) // 「次のページ」
            {
                currentPage++;
                continue;
            }

            // 選択されたアイテムを返す
            return const_cast<ITEM_MAP*>(&AllItems[start + selectedIndex]);
        }
    }
}
