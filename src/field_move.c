#include "global.h"
#include "event_data.h"
#include "field_move.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "party_menu.h"
#include "constants/field_move.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "item.h"
#include "script.h"
#include "event_scripts.h"

static u8 sFieldMoveSource = FIELD_MOVE_SOURCE_POKEMON;

static bool32 IsFieldMoveUnlocked_Cut(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE02_GET);

    return FlagGet(FLAG_BADGE01_GET);
}

static bool32 IsFieldMoveUnlocked_Flash(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE01_GET);

    return FlagGet(FLAG_BADGE02_GET);
}

static bool32 IsFieldMoveUnlocked_RockSmash(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE06_GET);

    return FlagGet(FLAG_BADGE03_GET);
}

static bool32 IsFieldMoveUnlocked_Strength(void)
{
    return FlagGet(FLAG_BADGE04_GET);
}

static bool32 IsFieldMoveUnlocked_Surf(void)
{
    return FlagGet(FLAG_BADGE05_GET);
}

static bool32 IsFieldMoveUnlocked_Fly(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE03_GET);

    return FlagGet(FLAG_BADGE06_GET);
}

static bool32 IsFieldMoveUnlocked_Dive(void)
{
    return FlagGet(FLAG_BADGE07_GET);
}

static bool32 IsFieldMoveUnlocked_Waterfall(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE07_GET);

    return FlagGet(FLAG_BADGE08_GET);
}

static bool32 IsFieldMoveUnlocked_RockClimb(void)
{
    return OW_ROCK_CLIMB_FIELD_MOVE;
}

static bool32 IsFieldMoveUnlocked_Teleport(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_Dig(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_SecretPower(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_MilkDrink(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_SoftBoiled(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_SweetScent(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_Defog(void)
{
    return OW_DEFOG_FIELD_MOVE;
}

const struct FieldMoveInfo gFieldMoveInfo[FIELD_MOVES_COUNT] =
{
    [FIELD_MOVE_CUT] =
    {
        .fieldMoveFunc = SetUpFieldMove_Cut,
        .isUnlockedFunc = IsFieldMoveUnlocked_Cut,
        .moveID = MOVE_CUT,
        .partyMsgID = PARTY_MSG_NOTHING_TO_CUT,
        .hm = ITEM_HM_CUT,
        .tool = ITEM_CUT_TOOL,
    },

    [FIELD_MOVE_FLASH] =
    {
        .fieldMoveFunc = SetUpFieldMove_Flash,
        .isUnlockedFunc = IsFieldMoveUnlocked_Flash,
        .moveID = MOVE_FLASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_HM_FLASH,
        .tool = ITEM_FLASH_TOOL,
    },

    [FIELD_MOVE_ROCK_SMASH] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockSmash,
        .isUnlockedFunc = IsFieldMoveUnlocked_RockSmash,
        .moveID = MOVE_ROCK_SMASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_HM_ROCK_SMASH,
        .tool = ITEM_ROCK_SMASH_TOOL,
    },

    [FIELD_MOVE_STRENGTH] =
    {
        .fieldMoveFunc = SetUpFieldMove_Strength,
        .isUnlockedFunc = IsFieldMoveUnlocked_Strength,
        .moveID = MOVE_STRENGTH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_HM_STRENGTH,
        .tool = ITEM_STRENGTH_TOOL,
    },

    [FIELD_MOVE_SURF] =
    {
        .fieldMoveFunc = SetUpFieldMove_Surf,
        .isUnlockedFunc = IsFieldMoveUnlocked_Surf,
        .moveID = MOVE_SURF,
        .partyMsgID = PARTY_MSG_CANT_SURF_HERE,
        .hm = ITEM_HM_SURF,
        .tool = ITEM_SURF_TOOL,
    },

    [FIELD_MOVE_FLY] =
    {
        .fieldMoveFunc = SetUpFieldMove_Fly,
        .isUnlockedFunc = IsFieldMoveUnlocked_Fly,
        .moveID = MOVE_FLY,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_HM_FLY,
        .tool = ITEM_FLY_TOOL,
    },

    [FIELD_MOVE_DIVE] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dive,
        .isUnlockedFunc = IsFieldMoveUnlocked_Dive,
        .moveID = MOVE_DIVE,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_HM_DIVE,
        .tool = ITEM_DIVE_TOOL,
    },

    [FIELD_MOVE_WATERFALL] =
    {
        .fieldMoveFunc = SetUpFieldMove_Waterfall,
        .isUnlockedFunc = IsFieldMoveUnlocked_Waterfall,
        .moveID = MOVE_WATERFALL,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_HM_WATERFALL,
        .tool = ITEM_WATERFALL_TOOL,
    },

    [FIELD_MOVE_TELEPORT] =
    {
        .fieldMoveFunc = SetUpFieldMove_Teleport,
        .isUnlockedFunc = IsFieldMoveUnlocked_Teleport,
        .moveID = MOVE_TELEPORT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_DIG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dig,
        .isUnlockedFunc = IsFieldMoveUnlocked_Dig,
        .moveID = MOVE_DIG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_TM_DIG,
    #if I_KEY_ESCAPE_ROPE >= GEN_8
        .tool = ITEM_ESCAPE_ROPE,
    #endif
    },

    [FIELD_MOVE_SECRET_POWER] =
    {
        .fieldMoveFunc = SetUpFieldMove_SecretPower,
        .isUnlockedFunc = IsFieldMoveUnlocked_SecretPower,
        .moveID = MOVE_SECRET_POWER,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
        .hm = ITEM_TM_SECRET_POWER,
    },

    [FIELD_MOVE_MILK_DRINK] =
    {
        .fieldMoveFunc = SetUpFieldMove_SoftBoiled,
        .isUnlockedFunc = IsFieldMoveUnlocked_MilkDrink,
        .moveID = MOVE_MILK_DRINK,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SOFT_BOILED] =
    {
        .fieldMoveFunc = SetUpFieldMove_SoftBoiled,
        .isUnlockedFunc = IsFieldMoveUnlocked_SoftBoiled,
        .moveID = MOVE_SOFT_BOILED,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SWEET_SCENT] =
    {
        .fieldMoveFunc = SetUpFieldMove_SweetScent,
        .isUnlockedFunc = IsFieldMoveUnlocked_SweetScent,
        .moveID = MOVE_SWEET_SCENT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
    [FIELD_MOVE_ROCK_CLIMB] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockClimb,
        .isUnlockedFunc = IsFieldMoveUnlocked_RockClimb,
        .moveID = MOVE_ROCK_CLIMB,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
    [FIELD_MOVE_DEFOG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Defog,
        .isUnlockedFunc = IsFieldMoveUnlocked_Defog,
        .moveID = MOVE_DEFOG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
};

u8 GetFieldMoveSource(void)
{
    return sFieldMoveSource;
}

void SetFieldMoveSource(u8 source)
{
    sFieldMoveSource = source;
}

bool32 CanUseFieldMove(enum FieldMove fieldMove, bool32 doUnlockedCheck, u16 *idxPtr, u16 *speciesPtr) {
    u32 i;
    enum Species party[PARTY_SIZE];
    enum Move move = FieldMove_GetMoveId(fieldMove);

    // Check if the player has the required badge.
    if (doUnlockedCheck && !IsFieldMoveUnlocked(fieldMove))
        return FALSE;

    // Filter for eligible mon
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        enum Species species = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES);
        if (species && !GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG)) {
            party[i] = species;
        } else {
            party[i] = SPECIES_NONE;
        }
    }

    // 1. Check for Pokémon that already knows the move
    for (u32 i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
    {
        if (party[i] != SPECIES_NONE && MonKnowsMove(&gParties[B_TRAINER_PLAYER][i], move)) {
            if (idxPtr) *idxPtr = i;
            if (speciesPtr) *speciesPtr = party[i];
            sFieldMoveSource = FIELD_MOVE_SOURCE_POKEMON;
            return TRUE;
        }
    }

    // 2. Check for Pokémon that can learn and HM is obtained
    if (FieldMove_HaveHM(fieldMove)) {
        for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
        {
            if (party[i] != SPECIES_NONE && CanLearnTeachableMove(party[i], move))
            {
                if (idxPtr) *idxPtr = i;
                if (speciesPtr) *speciesPtr = party[i];
                sFieldMoveSource = FIELD_MOVE_SOURCE_POKEMON;
                return TRUE;
            }
        }
    }

    // 3. Check for tool
    if (FieldMove_HaveTool(fieldMove))
    {
        if (idxPtr) *idxPtr = PARTY_SIZE + 1;
        if (speciesPtr) *speciesPtr = SPECIES_NONE;
        sFieldMoveSource = FIELD_MOVE_SOURCE_ITEM;
        return TRUE; // Found the item
    }

    // If all checks fail, return FALSE.
    if (idxPtr) *idxPtr = PARTY_SIZE;
    if (speciesPtr) *speciesPtr = SPECIES_NONE;
    return FALSE;
}

void FieldCallback_Surf(void)
{
    ScriptContext_SetupScript(EventScript_UseSurf);
}
