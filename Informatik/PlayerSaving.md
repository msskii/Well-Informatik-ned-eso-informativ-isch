# Player data

1. Inventory data
2. Location data
3. Cooldown / Health data

### TODO: Encryption, so users can't edit their life easily

# Inventory data

For each inventory slot (Number To be determined):

| Name | Description | Size |
|---|---|---|
| nameLen | The length of the name-string | 4 |
| name | The name of the item | nameLen |
| amount | How many items of that type the player has | 1 |
| sid | Special data about the item | ? * amount |

# Location Data

| Name | Description | Size |
|---|---|---|
| locX | The x-position of the player | 4 |
| locY | The y-position of the player | 4 |
| zheight | The z-height the player is on | 1 |
| levelID | The id of the map the player is in | 4 |

# Cooldown & Health data

| Name | Description | Size |
|---|---|---|
| playerLevel | The level of the player | 4 |
| playerHealth | The health of the player | 4 |
| hotbarCooldowns | How many items the player has in the hotbar that require a cooldown | 4 |
| cooldowns | The id of the map the player is in | 4 * hotbarCooldowns |

