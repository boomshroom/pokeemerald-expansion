#ifndef GUARD_SHOP_CRITERIA_H
#define GUARD_SHOP_CRITERIA_H

void TryBuildDynamicShopItemList(const u16 **ogItemList, u16 *resultingTotal);
void TryFreeDynamicShopItemList(const u16 **ogItemList);

// Add new Criterias below!

bool32 ShopCriteriaStarted(enum Item item);
bool32 ShopCriteriaBadges1(enum Item item);
bool32 ShopCriteriaBadges2(enum Item item);
bool32 ShopCriteriaBadges3(enum Item item);
bool32 ShopCriteriaBadges4(enum Item item);
bool32 ShopCriteriaBadges5(enum Item item);
bool32 ShopCriteriaBadges6(enum Item item);
bool32 ShopCriteriaBadges7(enum Item item);
bool32 ShopCriteriaBadges8(enum Item item);

#endif // GUARD_SHOP_CRITERIA_H
