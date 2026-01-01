#include "../headers/xmltemplates.h"
#include <cctype>
#include <algorithm>

string getXMLTemplate(const string &skeletonName, const string &style) {
    // Normalize style to lowercase
    string normalizedStyle = style;
    std::transform(normalizedStyle.begin(), normalizedStyle.end(), normalizedStyle.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if (normalizedStyle.empty()) normalizedStyle = "standard";

    // ==================== ITEMS ====================
    if (skeletonName == "items") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Items Modlet -->
<configs>
    <append xpath="/items">
        <item name="myItem">
            <property name="Extends" value="resourceWood"/>
            <property name="CustomIcon" value="resourceWood"/>
        </item>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE ITEMS TEMPLATE                 -->
<!-- ================================================================ -->
<configs>
    <!-- EXTEND AN EXISTING ITEM -->
    <append xpath="/items">
        <item name="myCustomItem">
            <property name="Extends" value="meleeToolRepairT0StoneAxe"/>
            <property name="CustomIcon" value="meleeToolRepairT0StoneAxe"/>
            <property name="CustomIconTint" value="255,200,100"/>

            <!-- DISPLAY -->
            <property name="DescriptionKey" value="myCustomItemDesc"/>
            <property name="DisplayType" value="melee"/>
            <property name="Group" value="Tools/Traps"/>

            <!-- STATS -->
            <property name="DegradationMax" value="200" param1="Category"/>
            <property name="DegradationPerUse" value="1"/>
            <property name="EconomicValue" value="150"/>
            <property name="Weight" value="5"/>
            <property name="Stacknumber" value="1"/>

            <!-- ACTIONS -->
            <property name="Tags" value="tool,melee,axe,light,canHaveCosmetic,weapon"/>
            <property name="CraftingIngredientTime" value="1"/>

            <!-- EFFECTS -->
            <effect_group>
                <passive_effect name="EntityDamage" operation="base_set" value="15"/>
                <passive_effect name="BlockDamage" operation="base_set" value="25"/>
                <passive_effect name="DegradationPerUse" operation="base_set" value="1"/>
            </effect_group>
        </item>
    </append>

    <!-- MODIFY EXISTING ITEM -->
    <set xpath="/items/item[@name='resourceWood']/property[@name='Stacknumber']/@value">10000</set>

    <!-- ADD PROPERTY TO EXISTING ITEM -->
    <append xpath="/items/item[@name='resourceWood']">
        <property name="CustomIconTint" value="200,150,100"/>
    </append>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Items Template -->
<configs>
    <append xpath="/items">
        <item name="myCustomItem">
            <property name="Extends" value="resourceWood"/>
            <property name="CustomIcon" value="resourceWood"/>
            <property name="CustomIconTint" value="255,255,255"/>
            <property name="DescriptionKey" value="myCustomItemDesc"/>
            <property name="Group" value="Resources"/>
            <property name="EconomicValue" value="10"/>
            <property name="Stacknumber" value="500"/>
        </item>
    </append>
</configs>)";
        }
    }

    // ==================== BLOCKS ====================
    if (skeletonName == "blocks") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Blocks Modlet -->
<configs>
    <append xpath="/blocks">
        <block name="myBlock">
            <property name="Extends" value="woodBlock"/>
        </block>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE BLOCKS TEMPLATE                -->
<!-- ================================================================ -->
<!-- Shape Groups: frameShapes, woodShapes, cobblestoneShapes,        -->
<!--               concreteShapes, steelShapes, awningShapes,         -->
<!--               brickShapes, corrugatedMetalShapes                 -->
<!-- ================================================================ -->
<configs>
    <!-- DECORATIVE BLOCK -->
    <append xpath="/blocks">
        <block name="myCustomBlock">
            <property name="Extends" value="woodBlock"/>
            <property name="CreativeMode" value="Player"/>

            <!-- VISUAL -->
            <property name="CustomIcon" value="woodBlock"/>
            <property name="Material" value="Mwood"/>
            <property name="Shape" value="Cube"/>
            <property name="Mesh" value="cutoutcube"/>
            <property name="Texture" value="435"/>
            <property name="Model" value=""/>
            <property name="ImposterExchange" value="imposterBlock"/>
            <property name="Map.Color" value="139,90,43"/>

            <!-- STATS -->
            <property name="MaxDamage" value="400"/>
            <property name="StabilitySupport" value="true"/>
            <property name="Mass" value="10"/>
            <property name="Weight" value="10"/>
            <property name="EconomicValue" value="25"/>

            <!-- PLACEMENT -->
            <property name="Place" value="TowardsPlacerInverted"/>
            <property name="AllowedRotations" value="0,0,0,0"/>
            <property name="IsTerrainDecoration" value="false"/>
            <property name="CanPlayersSpawnOn" value="true"/>
            <property name="CanMobsSpawnOn" value="false"/>

            <!-- INTERACTION -->
            <property name="SoundPickup" value="woodblock_grab"/>
            <property name="SoundPlace" value="woodblock_place"/>
            <property name="SoundDestroy" value="wood_destroy"/>

            <!-- SORTING -->
            <property name="SortOrder1" value="0070"/>
            <property name="SortOrder2" value="0000"/>
            <property name="FilterTags" value="MC_building,SC_wood"/>
            <property name="DisplayType" value="blockMulti"/>

            <!-- UPGRADES -->
            <property name="UpgradeBlock" value="myCustomBlockUpgraded,resourceWood,4"/>
            <property name="DowngradeBlock" value="frameShapes:VariantHelper"/>

            <!-- DROPS -->
            <drop event="Harvest" name="resourceWood" count="2" tag="allToolsHarvest"/>
            <drop event="Destroy" name="resourceWood" count="1"/>
            <drop event="Fall" name="resourceWood" count="1" prob="0.5" stick_chance="0"/>
        </block>
    </append>

    <!-- MODIFY EXISTING BLOCK -->
    <set xpath="/blocks/block[@name='woodBlock']/property[@name='MaxDamage']/@value">800</set>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Blocks Template -->
<configs>
    <append xpath="/blocks">
        <block name="myCustomBlock">
            <property name="Extends" value="woodBlock"/>
            <property name="CreativeMode" value="Player"/>
            <property name="CustomIcon" value="woodBlock"/>
            <property name="Material" value="Mwood"/>
            <property name="MaxDamage" value="400"/>
            <property name="EconomicValue" value="25"/>
            <property name="FilterTags" value="MC_building,SC_wood"/>
            <drop event="Destroy" name="resourceWood" count="2"/>
        </block>
    </append>
</configs>)";
        }
    }

    // ==================== RECIPES ====================
    if (skeletonName == "recipes") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Recipes Modlet -->
<configs>
    <append xpath="/recipes">
        <recipe name="myItem" count="1" craft_time="2" craft_area="workbench">
            <ingredient name="resourceWood" count="10"/>
        </recipe>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE RECIPES TEMPLATE               -->
<!-- ================================================================ -->
<!-- craft_area values: none, campfire, forge, workbench, cementMixer,-->
<!--                    chemistryStation, player, tablesaw            -->
<!-- ================================================================ -->
<configs>
    <!-- BASIC RECIPE -->
    <append xpath="/recipes">
        <recipe name="myCustomItem" count="1" craft_time="5" craft_area="workbench"
                tags="learnable,workbenchCrafting" craft_exp_gain="10">
            <ingredient name="resourceWood" count="20"/>
            <ingredient name="resourceForgedIron" count="5"/>
            <ingredient name="resourceScrapPolymers" count="3"/>
        </recipe>
    </append>

    <!-- RECIPE WITH UNLOCK -->
    <append xpath="/recipes">
        <recipe name="myAdvancedItem" count="1" craft_time="10" craft_area="workbench"
                tags="learnable,perkAdvancedEngineering">
            <ingredient name="resourceForgedSteel" count="10"/>
            <ingredient name="resourceElectricParts" count="5"/>
        </recipe>
    </append>

    <!-- CAMPFIRE RECIPE (COOKING) -->
    <append xpath="/recipes">
        <recipe name="myFoodItem" count="1" craft_time="3" craft_area="campfire"
                tags="learnable,campfireCrafting" tooltip_key="rcpMyFoodItemTT">
            <ingredient name="foodRawMeat" count="2"/>
            <ingredient name="foodCropCorn" count="1"/>
        </recipe>
    </append>

    <!-- FORGE RECIPE (SMELTING) -->
    <append xpath="/recipes">
        <recipe name="resourceForgedIron" count="1" craft_time="30" craft_area="forge"
                material_based="true" tags="forgeCrafting">
            <ingredient name="resourceScrapIron" count="5"/>
            <ingredient name="resourceClay" count="2"/>
        </recipe>
    </append>

    <!-- CHEMISTRY STATION -->
    <append xpath="/recipes">
        <recipe name="drugPainkillers" count="2" craft_time="15" craft_area="chemistryStation"
                tags="learnable,chemistryStationCrafting">
            <ingredient name="resourceMoldyBread" count="3"/>
            <ingredient name="drugNitratePowder" count="2"/>
        </recipe>
    </append>

    <!-- MODIFY EXISTING RECIPE -->
    <set xpath="/recipes/recipe[@name='resourceWood']/ingredient[@name='resourceLog']/@count">1</set>

    <!-- REMOVE RECIPE -->
    <remove xpath="/recipes/recipe[@name='ammo9mmBulletBall']"/>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Recipes Template -->
<configs>
    <append xpath="/recipes">
        <recipe name="myCustomItem" count="1" craft_time="5" craft_area="workbench"
                tags="learnable,workbenchCrafting">
            <ingredient name="resourceWood" count="20"/>
            <ingredient name="resourceForgedIron" count="5"/>
        </recipe>
    </append>
</configs>)";
        }
    }

    // ==================== BUFFS ====================
    if (skeletonName == "buffs") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Buffs Modlet -->
<configs>
    <append xpath="/buffs">
        <buff name="myBuff" duration="30">
            <stack_type value="replace"/>
        </buff>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE BUFFS TEMPLATE                 -->
<!-- ================================================================ -->
<!-- stack_type: ignore, replace, duration, stack                     -->
<!-- Common passive_effects: HealthMax, StaminaMax, SpeedModifier,    -->
<!--   EntityDamage, BlockDamage, DamageResist, HealthChangeOT, etc.  -->
<!-- ================================================================ -->
<configs>
    <!-- STAT BUFF -->
    <append xpath="/buffs">
        <buff name="myStatBuff" duration="60" name_key="buffMyStatBuff"
              description_key="buffMyStatBuffDesc" icon="ui_game_symbol_map_bed"
              icon_color="0,200,100">
            <stack_type value="replace"/>
            <update_rate value="1"/>

            <effect_group>
                <passive_effect name="HealthMax" operation="perc_add" value=".10"/>
                <passive_effect name="StaminaMax" operation="perc_add" value=".10"/>
                <passive_effect name="SpeedModifier" operation="perc_add" value=".05"/>
            </effect_group>
        </buff>
    </append>

    <!-- HEALING OVER TIME -->
    <append xpath="/buffs">
        <buff name="myHealingBuff" duration="30" name_key="buffMyHeal" icon="ui_game_symbol_medical">
            <stack_type value="replace"/>
            <update_rate value="1"/>

            <effect_group>
                <passive_effect name="HealthChangeOT" operation="base_add" value="2" tags="heal"/>
            </effect_group>
        </buff>
    </append>

    <!-- DAMAGE OVER TIME -->
    <append xpath="/buffs">
        <buff name="myDotDebuff" duration="15" name_key="buffMyDot" icon="ui_game_symbol_poison"
              icon_color="0,255,0" cures="drugAntibiotics">
            <stack_type value="duration"/>
            <update_rate value="1"/>

            <effect_group>
                <passive_effect name="HealthChangeOT" operation="base_add" value="-1"/>
            </effect_group>
        </buff>
    </append>

    <!-- TRIGGERED EFFECTS -->
    <append xpath="/buffs">
        <buff name="myTriggeredBuff" duration="0" name_key="buffMyTriggered">
            <stack_type value="ignore"/>

            <effect_group>
                <triggered_effect trigger="onSelfPrimaryActionEnd" action="ModifyCVar"
                                  target="self" cvar="myCustomVar" operation="add" value="1"/>
                <triggered_effect trigger="onSelfBuffStart" action="PlaySound"
                                  target="self" sound="twitch_action_spawn"/>
            </effect_group>
        </buff>
    </append>

    <!-- CONDITIONAL EFFECTS -->
    <append xpath="/buffs">
        <buff name="myConditionalBuff" duration="0">
            <stack_type value="ignore"/>

            <effect_group>
                <requirement name="CVarCompare" cvar="$waterAmountCurrent" operation="LTE" value="20"/>
                <passive_effect name="StaminaChangeOT" operation="base_add" value="-1"/>
            </effect_group>
        </buff>
    </append>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Buffs Template -->
<configs>
    <append xpath="/buffs">
        <buff name="myBuff" duration="60" name_key="buffMyBuff"
              description_key="buffMyBuffDesc" icon="ui_game_symbol_add">
            <stack_type value="replace"/>
            <update_rate value="1"/>

            <effect_group>
                <passive_effect name="HealthChangeOT" operation="base_add" value="1"/>
                <passive_effect name="StaminaMax" operation="perc_add" value=".05"/>
            </effect_group>
        </buff>
    </append>
</configs>)";
        }
    }

    // ==================== TRADERS ====================
    if (skeletonName == "traders") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Traders Modlet -->
<configs>
    <append xpath="/traders/trader_info[@id='1']/trader_items">
        <item name="myItem" count="1,3"/>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE TRADERS TEMPLATE               -->
<!-- ================================================================ -->
<!-- Trader IDs: 1=Trader Joel, 2=Trader Rekt, 3=Trader Bob,          -->
<!--             4=Trader Hugh, 5=Trader Jen                          -->
<!-- ================================================================ -->
<configs>
    <!-- ADD ITEM TO SPECIFIC TRADER -->
    <append xpath="/traders/trader_info[@id='1']/trader_items">
        <item group="myCustomGroup"/>
        <item name="myCustomItem" count="1,3" price="100,200"/>
    </append>

    <!-- CREATE ITEM GROUP FOR TRADERS -->
    <append xpath="/traders">
        <trader_item_group name="myCustomGroup" count="1,2">
            <item name="myCustomItem1" prob="0.5"/>
            <item name="myCustomItem2" prob="0.3"/>
            <item name="myCustomItem3" prob="0.2"/>
        </trader_item_group>
    </append>

    <!-- ADD TO ALL TRADERS (loop example) -->
    <append xpath="/traders/trader_info[@id='1']/trader_items"><item name="myGlobalItem"/></append>
    <append xpath="/traders/trader_info[@id='2']/trader_items"><item name="myGlobalItem"/></append>
    <append xpath="/traders/trader_info[@id='3']/trader_items"><item name="myGlobalItem"/></append>
    <append xpath="/traders/trader_info[@id='4']/trader_items"><item name="myGlobalItem"/></append>
    <append xpath="/traders/trader_info[@id='5']/trader_items"><item name="myGlobalItem"/></append>

    <!-- MODIFY TRADER RESTOCK TIME -->
    <set xpath="/traders/trader_info[@id='1']/@reset_interval">3</set>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Traders Template -->
<configs>
    <!-- Add item to Trader Joel -->
    <append xpath="/traders/trader_info[@id='1']/trader_items">
        <item name="myCustomItem" count="1,3"/>
    </append>

    <!-- Add item group -->
    <append xpath="/traders">
        <trader_item_group name="myGroup" count="1,2">
            <item name="myCustomItem" prob="1"/>
        </trader_item_group>
    </append>
</configs>)";
        }
    }

    // ==================== ITEM_MODIFIERS ====================
    if (skeletonName == "item_modifiers") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Item Modifiers Modlet -->
<configs>
    <append xpath="/item_modifiers">
        <item_modifier name="modMyMod" installable_tags="weapon">
            <property name="Extends" value="modGeneralGripGrasping"/>
        </item_modifier>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE ITEM_MODIFIERS TEMPLATE        -->
<!-- ================================================================ -->
<configs>
    <append xpath="/item_modifiers">
        <item_modifier name="modMyCustomMod" modifier_tags="damage"
                       installable_tags="gun,weapon" blocked_tags="noMods"
                       type="attachment">
            <property name="CustomIcon" value="modGunScopeLarge"/>
            <property name="CustomIconTint" value="100,200,255"/>
            <property name="DescriptionKey" value="modMyCustomModDesc"/>
            <property name="Group" value="Mods"/>
            <property name="EconomicValue" value="200"/>

            <effect_group>
                <passive_effect name="EntityDamage" operation="perc_add" value=".15"/>
                <passive_effect name="DamageFalloffRange" operation="perc_add" value=".1"/>
            </effect_group>
        </item_modifier>
    </append>

    <!-- COSMETIC MOD -->
    <append xpath="/item_modifiers">
        <item_modifier name="modMyCosmeticMod" modifier_tags="cosmetic"
                       installable_tags="meleeCanHaveCosmetic" type="cosmetic">
            <property name="CustomIcon" value="modMeleeClubBurningMan"/>
            <effect_group>
                <triggered_effect trigger="onSelfPrimaryActionEnd" action="AddBuff"
                                  target="selfAOE" range="3" buff="buffMyEffect"/>
            </effect_group>
        </item_modifier>
    </append>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Item Modifiers Template -->
<configs>
    <append xpath="/item_modifiers">
        <item_modifier name="modMyCustomMod" installable_tags="weapon">
            <property name="Extends" value="modGeneralGripGrasping"/>
            <property name="CustomIcon" value="modGeneralGripGrasping"/>
            <property name="DescriptionKey" value="modMyCustomModDesc"/>

            <effect_group>
                <passive_effect name="EntityDamage" operation="perc_add" value=".1"/>
            </effect_group>
        </item_modifier>
    </append>
</configs>)";
        }
    }

    // ==================== LOOT ====================
    if (skeletonName == "loot") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Loot Modlet -->
<configs>
    <append xpath="/lootcontainers/lootgroup[@name='groupGenericHelper']">
        <item name="myItem" prob="0.1" count="1,2"/>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE LOOT TEMPLATE                  -->
<!-- ================================================================ -->
<configs>
    <!-- ADD TO EXISTING LOOT GROUP -->
    <append xpath="/lootcontainers/lootgroup[@name='groupGenericHelper']">
        <item name="myCustomItem" prob="0.05" count="1,2" loot_prob_template="low"/>
    </append>

    <!-- CREATE CUSTOM LOOT GROUP -->
    <append xpath="/lootcontainers">
        <lootgroup name="myCustomLootGroup" count="1,3">
            <item name="myCustomItem1" prob="0.5" count="1,2"/>
            <item name="myCustomItem2" prob="0.3" count="1"/>
            <item name="resourceScrapIron" prob="0.2" count="5,10"/>
        </lootgroup>
    </append>

    <!-- CREATE LOOT CONTAINER -->
    <append xpath="/lootcontainers">
        <lootcontainer id="myCustomContainer" count="5,10" size="8,5"
                       sound_open="UseActions/open_chest" sound_close="UseActions/close_chest"
                       loot_quality_template="qualBaseTemplate">
            <item group="myCustomLootGroup"/>
            <item group="groupAmmo" count="1"/>
        </lootcontainer>
    </append>

    <!-- ADD GROUP TO EXISTING CONTAINER -->
    <append xpath="/lootcontainers/lootcontainer[@id='31']">
        <item group="myCustomLootGroup" force_prob="true"/>
    </append>

    <!-- ADD TO ZOMBIE DROPS -->
    <append xpath="/lootcontainers/lootgroup[@name='groupZombieSoldier']">
        <item name="myMilitaryItem" prob="0.02"/>
    </append>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Loot Template -->
<configs>
    <!-- Create custom loot group -->
    <append xpath="/lootcontainers">
        <lootgroup name="myCustomLootGroup" count="1,2">
            <item name="myCustomItem" prob="0.5" count="1,2"/>
        </lootgroup>
    </append>

    <!-- Add to generic loot -->
    <append xpath="/lootcontainers/lootgroup[@name='groupGenericHelper']">
        <item name="myCustomItem" prob="0.05" count="1"/>
    </append>
</configs>)";
        }
    }

    // ==================== PROGRESSION ====================
    if (skeletonName == "progression") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Progression Modlet -->
<configs>
    <set xpath="/progression/perks/perk[@name='perkLightArmor']/effect_group/passive_effect[@name='PhysicalDamageResist']/@value">.05,.1,.15,.2,.25</set>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE PROGRESSION TEMPLATE           -->
<!-- ================================================================ -->
<configs>
    <!-- MODIFY EXISTING PERK -->
    <set xpath="/progression/perks/perk[@name='perkLightArmor']/effect_group/passive_effect[@name='PhysicalDamageResist']/@value">.10,.15,.20,.25,.30</set>

    <!-- ADD EFFECT TO PERK LEVEL -->
    <append xpath="/progression/perks/perk[@name='perkMasterChef']/effect_group[@level='5']">
        <passive_effect name="RecipeCraftCount" operation="base_add" value="2" tags="campfire"/>
    </append>

    <!-- CREATE CUSTOM PERK -->
    <append xpath="/progression/perks">
        <perk name="perkMyCustomPerk" parent="skillPerceptionGeneral" name_key="perkMyCustomPerk"
              description_key="perkMyCustomPerkDesc" icon="ui_game_symbol_target"
              max_level="5" base_skill_point_cost="1">
            <requirement name="ProgressionLevel" progression_name="attPerception"
                         compare_type="GE" operation_type="or" required_skill_level="1,3,5,7,9"/>

            <effect_group level="1,2,3,4,5" tags="perkLevel1,perkLevel2,perkLevel3,perkLevel4,perkLevel5">
                <passive_effect name="EntityDamage" operation="perc_add" value=".05,.10,.15,.20,.25" tags="gun"/>
            </effect_group>

            <effect_group level="3,4,5">
                <passive_effect name="SpreadMultiplierAiming" operation="perc_add" value="-.05,-.1,-.15"/>
            </effect_group>
        </perk>
    </append>

    <!-- MODIFY ATTRIBUTE REQUIREMENTS -->
    <set xpath="/progression/perks/perk[@name='perkArchery']/@base_skill_point_cost">2</set>

    <!-- ADD BOOK UNLOCK -->
    <append xpath="/progression/perks/perk[@name='perkBetterBarter']/effect_group[@level='3']">
        <triggered_effect trigger="onSelfBuffStart" action="AddBuff" buff="buffMyTraderBuff"/>
    </append>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Progression Template -->
<configs>
    <!-- Modify perk effect values -->
    <set xpath="/progression/perks/perk[@name='perkLightArmor']/effect_group/passive_effect[@name='PhysicalDamageResist']/@value">.10,.15,.20,.25,.30</set>

    <!-- Add new effect to perk -->
    <append xpath="/progression/perks/perk[@name='perkMasterChef']/effect_group[@level='5']">
        <passive_effect name="CraftingTier" operation="base_add" value="1" tags="campfire"/>
    </append>
</configs>)";
        }
    }

    // ==================== ENTITYCLASSES ====================
    if (skeletonName == "entityclasses") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Entity Classes Modlet -->
<configs>
    <set xpath="/entity_classes/entity_class[@name='zombieMoe']/property[@name='MaxHealth']/@value">200</set>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE ENTITYCLASSES TEMPLATE         -->
<!-- ================================================================ -->
<configs>
    <!-- MODIFY ZOMBIE HEALTH -->
    <set xpath="/entity_classes/entity_class[@name='zombieMoe']/property[@name='MaxHealth']/@value">500</set>
    <set xpath="/entity_classes/entity_class[@name='zombieArlene']/property[@name='MaxHealth']/@value">500</set>

    <!-- CREATE CUSTOM ZOMBIE -->
    <append xpath="/entity_classes">
        <entity_class name="zombieMyCustom" extends="zombieMoe">
            <property name="MaxHealth" value="1000"/>
            <property name="HandItem" value="meleeHandZombie"/>
            <property name="MoveSpeed" value="0.1, 0.12"/>
            <property name="MoveSpeedAggro" value="1.0, 1.8"/>
            <property name="SightRange" value="80"/>
            <property name="SwimSpeed" value="0.8"/>
            <property name="JumpMaxDistance" value="3.5"/>
            <property name="Mass" value="200"/>
            <property name="Weight" value="180"/>

            <!-- EXPERIENCE -->
            <property name="ExperienceGain" value="500"/>
            <property name="LootListOnDeath" value="2"/>

            <!-- SOUNDS -->
            <property name="SoundRandom" value="Zombies/Moe/moe_idle"/>
            <property name="SoundSense" value="Zombies/Moe/moe_sense"/>
            <property name="SoundAlert" value="Zombies/Moe/moe_spotted"/>
            <property name="SoundAttack" value="Zombies/Moe/moe_attack"/>
            <property name="SoundHurt" value="Zombies/Moe/moe_hurt"/>
            <property name="SoundDeath" value="Zombies/Moe/moe_death"/>

            <!-- APPEARANCE -->
            <property name="Mesh" value="#Entities/Zombies?Prefabs/ZombieMoe.prefab"/>
            <property name="MapIcon" value="map_skull"/>
        </entity_class>
    </append>

    <!-- MODIFY ANIMAL -->
    <set xpath="/entity_classes/entity_class[@name='animalDoe']/property[@name='MaxHealth']/@value">300</set>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Entity Classes Template -->
<configs>
    <!-- Modify zombie health -->
    <set xpath="/entity_classes/entity_class[@name='zombieMoe']/property[@name='MaxHealth']/@value">500</set>

    <!-- Create custom entity extending existing -->
    <append xpath="/entity_classes">
        <entity_class name="zombieMyCustom" extends="zombieMoe">
            <property name="MaxHealth" value="1000"/>
            <property name="ExperienceGain" value="500"/>
        </entity_class>
    </append>
</configs>)";
        }
    }

    // ==================== ENTITYGROUPS ====================
    if (skeletonName == "entitygroups") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Entity Groups Modlet -->
<configs>
    <append xpath="/entitygroups/entitygroup[@name='ZombiesAll']">
        <entity name="zombieMyCustom" prob="0.1"/>
    </append>
</configs>)";
        } else if (normalizedStyle == "comprehensive") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- ================================================================ -->
<!-- 7 Days to Die V1.0+ COMPREHENSIVE ENTITYGROUPS TEMPLATE          -->
<!-- ================================================================ -->
<configs>
    <!-- ADD TO EXISTING GROUP -->
    <append xpath="/entitygroups/entitygroup[@name='ZombiesAll']">
        <entity name="zombieMyCustom" prob="0.05"/>
    </append>

    <!-- ADD TO BLOODMOON HORDE -->
    <append xpath="/entitygroups/entitygroup[@name='feralHordeStageGS1']">
        <entity name="zombieMyCustom" prob="0.1"/>
    </append>

    <!-- CREATE CUSTOM ENTITY GROUP -->
    <append xpath="/entitygroups">
        <entitygroup name="myCustomHorde">
            <entity name="zombieMyCustom" prob="0.5"/>
            <entity name="zombieMoe" prob="0.3"/>
            <entity name="zombieArlene" prob="0.2"/>
        </entitygroup>
    </append>

    <!-- REMOVE ENTITY FROM GROUP -->
    <remove xpath="/entitygroups/entitygroup[@name='ZombiesAll']/entity[@name='zombieSpider']"/>

    <!-- MODIFY ENTITY PROBABILITY -->
    <set xpath="/entitygroups/entitygroup[@name='ZombiesAll']/entity[@name='zombieFeral']/@prob">0.2</set>
</configs>)";
        } else {
            // standard
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Entity Groups Template -->
<configs>
    <!-- Add custom entity to spawn groups -->
    <append xpath="/entitygroups/entitygroup[@name='ZombiesAll']">
        <entity name="zombieMyCustom" prob="0.05"/>
    </append>

    <!-- Create custom group -->
    <append xpath="/entitygroups">
        <entitygroup name="myCustomGroup">
            <entity name="zombieMyCustom" prob="1"/>
        </entitygroup>
    </append>
</configs>)";
        }
    }

    // ==================== ARCHETYPES ====================
    if (skeletonName == "archetypes") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Archetypes Template -->
<!-- Archetypes define player character classes/presets -->
<configs>
    <append xpath="/archetypes">
        <archetype name="myCustomArchetype"
                   title_key="archetypeMyCustom" description_key="archetypeMyCustomDesc">
            <stat name="health" value="100"/>
            <stat name="stamina" value="100"/>
            <buff name="buffStarterKit"/>
        </archetype>
    </append>
</configs>)";
    }

    // ==================== BIOMES ====================
    if (skeletonName == "biomes") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Biomes Modlet -->
<configs>
    <set xpath="/biomes/biome[@name='pine_forest']/spawn[@entitygroup='ZombiesAll']/@maxcount">10</set>
</configs>)";
        } else {
            // standard and comprehensive
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Biomes Template -->
<configs>
    <!-- Modify spawn counts in biome -->
    <set xpath="/biomes/biome[@name='pine_forest']/spawn[@entitygroup='ZombiesAll']/@maxcount">10</set>
    <set xpath="/biomes/biome[@name='desert']/spawn[@entitygroup='ZombiesAll']/@maxcount">8</set>

    <!-- Add custom spawn to biome -->
    <append xpath="/biomes/biome[@name='pine_forest']">
        <spawn entitygroup="myCustomGroup" maxcount="5" respawndelay="3" time="Night"/>
    </append>

    <!-- Modify biome properties -->
    <set xpath="/biomes/biome[@name='wasteland']/@difficulty">5</set>
</configs>)";
        }
    }

    // ==================== LOADINGSCREEN ====================
    if (skeletonName == "loadingscreen") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Loading Screen Tips Template -->
<configs>
    <append xpath="/loading_screen_tips">
        <tip>My custom tip 1</tip>
        <tip>My custom tip 2 - helpful hint here!</tip>
        <tip>Pro tip: Use this mod for best results</tip>
    </append>
</configs>)";
    }

    // ==================== MATERIALS ====================
    if (skeletonName == "materials") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Materials Template -->
<configs>
    <!-- Modify existing material -->
    <set xpath="/materials/material[@id='Mwood']/property[@name='damage_category']/@value">wood</set>

    <!-- Create custom material -->
    <append xpath="/materials">
        <material id="MyCustomMaterial">
            <property name="damage_category" value="metal"/>
            <property name="forge_category" value="metal"/>
            <property name="Hardness" type="float" value="1.5"/>
            <property name="stepsound" value="metal"/>
            <property name="stability_glue" value="40"/>
            <property name="Mass" type="int" value="15"/>
            <property name="MaxDamage" value="500"/>
            <property name="Experience" value="5"/>
        </material>
    </append>
</configs>)";
    }

    // ==================== PARTICLES ====================
    if (skeletonName == "particles") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Particles Template -->
<configs>
    <!-- Particle effects are complex - typically reference existing -->
    <set xpath="/particle_effects/particle_effect[@name='p_impact_metal']/@lifetime">2</set>
</configs>)";
    }

    // ==================== RWGMIXER ====================
    if (skeletonName == "rwgmixer") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ RWG Mixer Template -->
<!-- Random World Generation configuration -->
<configs>
    <!-- Add custom POI to spawn in towns -->
    <append xpath="/rwgmixer/prefab_rules/prefab_rule[@name='townResidential']">
        <prefab name="myCustomPOI" prob="0.1"/>
    </append>

    <!-- Modify spawn probability -->
    <set xpath="/rwgmixer/prefab_rules/prefab_rule[@name='townCommercial']/prefab[@name='store_book_01']/@prob">0.5</set>
</configs>)";
    }

    // ==================== SOUNDS ====================
    if (skeletonName == "sounds") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Sounds Template -->
<configs>
    <!-- Reference custom sounds from Mods/MyMod/Resources folder -->
    <append xpath="/Sounds/SoundDataNode[@name='AudioData']">
        <SoundDataNode name="myCustomSound">
            <AudioSource name="Sounds/MyMod/mySound"/>
            <AudioClip ClipName="#Mods/MyMod/Resources/Sounds/mySound.wav"/>
            <LocalCrouchVolumeScale value="0.5"/>
            <CrouchNoiseScale value="0.5"/>
            <NoiseScale value="1"/>
            <MaxVoices value="5"/>
            <Channel value="SFX"/>
        </SoundDataNode>
    </append>
</configs>)";
    }

    // ==================== SPAWNING ====================
    if (skeletonName == "spawning") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Spawning Modlet -->
<configs>
    <set xpath="/spawning/append[@biome='pine_forest']/@maxcount">20</set>
</configs>)";
        } else {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Spawning Template -->
<configs>
    <!-- Modify biome spawning -->
    <set xpath="/spawning/biome[@name='pine_forest']/spawn[@entitygroup='ZombiesAll']/@maxcount">15</set>

    <!-- Add custom spawn rule -->
    <append xpath="/spawning/biome[@name='pine_forest']">
        <spawn entitygroup="myCustomGroup" maxcount="5" respawndelay="2"
               time="Night" deadzone="false"/>
    </append>
</configs>)";
        }
    }

    // ==================== UI_DISPLAY ====================
    if (skeletonName == "ui_display") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ UI Display Template -->
<configs>
    <!-- Modify UI display settings -->
    <set xpath="/ui_display/recipe_list/recipe_list[@name='campfire']/@header">My Campfire Recipes</set>

    <!-- Add custom UI category -->
    <append xpath="/ui_display/item_stack_grid">
        <item_stack_grid name="myCustomGrid" columns="8" rows="5"/>
    </append>
</configs>)";
    }

    // ==================== VEHICLE_PROPERTIES ====================
    if (skeletonName == "vehicle_properties") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Vehicle Properties Template -->
<configs>
    <!-- Modify existing vehicle -->
    <set xpath="/vehicles/vehicle[@name='vehicleBicycle']/property[@name='velocityMax']/@value">15</set>
    <set xpath="/vehicles/vehicle[@name='vehicleMinibike']/property[@name='velocityMax']/@value">18</set>

    <!-- Modify vehicle health -->
    <set xpath="/vehicles/vehicle[@name='vehicle4x4Truck']/property[@name='entityDamage']/@value">200</set>

    <!-- Create custom vehicle extending existing -->
    <append xpath="/vehicles">
        <vehicle name="vehicleMyCustom" extends="vehicleMinibike">
            <property name="velocityMax" value="25"/>
            <property name="motorTorque" value="2000"/>
            <property name="entityDamage" value="150"/>
        </vehicle>
    </append>
</configs>)";
    }

    // ==================== WORLDGLOBAL ====================
    if (skeletonName == "worldglobal") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ World Global Template -->
<configs>
    <!-- Modify global world settings -->
    <set xpath="/worldglobal/property[@name='DayNightLength']/@value">90</set>
    <set xpath="/worldglobal/property[@name='DayLightLength']/@value">18</set>

    <!-- Zombie settings -->
    <set xpath="/worldglobal/property[@name='ZombiesRun']/@value">2</set>
    <set xpath="/worldglobal/property[@name='BloodMoonRange']/@value">0</set>
</configs>)";
    }

    // ==================== QUESTS ====================
    if (skeletonName == "quests") {
        if (normalizedStyle == "minimal") {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Quests Modlet -->
<configs>
    <set xpath="/quests/quest[@id='quest_BasicSurvival1']/property[@name='reward_exp']/@value">1000</set>
</configs>)";
        } else {
            return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Quests Template -->
<configs>
    <!-- Modify existing quest rewards -->
    <set xpath="/quests/quest[@id='quest_BasicSurvival1']/property[@name='reward_exp']/@value">1000</set>

    <!-- Create custom quest -->
    <append xpath="/quests">
        <quest id="quest_myCustomQuest">
            <property name="name_key" value="quest_myCustomQuest"/>
            <property name="description_key" value="quest_myCustomQuestDesc"/>
            <property name="icon" value="ui_game_symbol_quest"/>
            <property name="category_key" value="challenge"/>
            <property name="reward_exp" value="500"/>

            <!-- Objectives -->
            <objective type="Craft" id="myCustomItem" value="5"/>

            <!-- Rewards -->
            <reward type="Item" id="resourceCoin" value="100"/>
            <reward type="Exp" value="500"/>
        </quest>
    </append>
</configs>)";
        }
    }

    // ==================== DIALOGS ====================
    if (skeletonName == "dialogs") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ Dialogs Template -->
<configs>
    <!-- Add response to existing dialog -->
    <append xpath="/dialogs/dialog[@id='trader']/response_entry[@id='topic_jobs']">
        <response_entry id="myCustomResponse" text="myCustomResponseKey" next_dialog="myCustomDialog"/>
    </append>

    <!-- Create custom dialog -->
    <append xpath="/dialogs">
        <dialog id="myCustomDialog">
            <statement id="start" text="myCustomDialogStart"/>
            <response_entry id="resp1" text="myCustomResp1" next_dialog="trader"/>
        </dialog>
    </append>
</configs>)";
    }

    // ==================== NPC ====================
    if (skeletonName == "npc") {
        return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ NPC Template -->
<configs>
    <!-- Modify existing NPC -->
    <set xpath="/npc/npc[@id='npcTraderJoel']/property[@name='TraderID']/@value">1</set>

    <!-- Create custom NPC extending existing -->
    <append xpath="/npc">
        <npc id="npcMyCustomTrader" extends="npcTraderJoel">
            <property name="TraderID" value="99"/>
            <property name="Faction" value="trader"/>
            <property name="Dialog" value="myCustomDialog"/>
        </npc>
    </append>
</configs>)";
    }

    // ==================== DEFAULT FALLBACK ====================
    return R"(<?xml version="1.0" encoding="UTF-8"?>
<!-- 7 Days to Die V1.0+ )" + skeletonName + R"( Template -->
<configs>
    <!-- Add your )" + skeletonName + R"( modifications here -->
    <append xpath="/)" + skeletonName + R"(">
        <!-- Your content -->
    </append>
</configs>)";
}
