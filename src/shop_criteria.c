#include "global.h"
#include "item.h"
#include "script.h"
#include "event_data.h"
#include "malloc.h"
#include "shop_criteria.h"

static EWRAM_DATA const u16 *sDynamicShopItemListRef = NULL;

// Remove the UNUSED if you'll use the functions!
static bool32 ShopCriteriaByBadgeCount(u32 count);
static bool32 ShopCriteriaByFlag(u32 flagId);
static UNUSED bool32 ShopCriteriaByVar(u32 varId, u32 varValue);

void TryBuildDynamicShopItemList(const u16 **ogItemList, u16 *resultingTotal)
{
    sDynamicShopItemListRef = *ogItemList;

    u16 *list = AllocZeroed((*resultingTotal + 1) * sizeof(u16));
    u32 overallIdx = 0, idx = 0;

    while (idx < *resultingTotal)
    {
        enum Item item = sDynamicShopItemListRef[idx];

        if (IsItemShopCriteriaFulfilled(item))
        {
            list[overallIdx] = item;
            overallIdx++;
        }

        idx++;
    }

    list[overallIdx] = ITEM_NONE;

    *ogItemList = list;
    *resultingTotal = overallIdx;
}

void TryFreeDynamicShopItemList(const u16 **ogItemList)
{
    Free((u16 *)*ogItemList);
    *ogItemList = sDynamicShopItemListRef;
}

// Add new Criterias below!

static bool32 ShopCriteriaByBadgeCount(u32 count)
{
    u32 badgeCount = 0;

    for (u32 badgeFlag = FLAG_BADGE01_GET; badgeFlag < FLAG_BADGE01_GET + NUM_BADGES; badgeFlag++)
    {
        if (FlagGet(badgeFlag))
            badgeCount++;
    }

    if (badgeCount >= count)
        return TRUE;

    return FALSE;
}

// These two below are somewhat identical to ShopCriteriaByBadgeCount
// but uses only one specific event var/flag check. Useful if you need
// a specific badge flag instead of just the badge total.

static bool32 ShopCriteriaByFlag(u32 flagId)
{
    if (FlagGet(flagId))
        return TRUE;

    return FALSE;
}

static UNUSED bool32 ShopCriteriaByVar(u32 varId, u32 varValue)
{
    if (VarGet(varId) >= varValue)
        return TRUE;

    return FALSE;
}

bool32 ShopCriteriaStarted(enum Item item) { return ShopCriteriaByFlag(FLAG_ADVENTURE_STARTED); }
bool32 ShopCriteriaBadges1(enum Item item) { return ShopCriteriaByBadgeCount(1); }
bool32 ShopCriteriaBadges2(enum Item item) { return ShopCriteriaByBadgeCount(2); }
bool32 ShopCriteriaBadges3(enum Item item) { return ShopCriteriaByBadgeCount(3); }
bool32 ShopCriteriaBadges4(enum Item item) { return ShopCriteriaByBadgeCount(4); }
bool32 ShopCriteriaBadges5(enum Item item) { return ShopCriteriaByBadgeCount(5); }
bool32 ShopCriteriaBadges6(enum Item item) { return ShopCriteriaByBadgeCount(6); }
bool32 ShopCriteriaBadges7(enum Item item) { return ShopCriteriaByBadgeCount(7); }
bool32 ShopCriteriaBadges8(enum Item item) { return ShopCriteriaByBadgeCount(8); }
