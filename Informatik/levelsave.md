# Level saving

1. File header
2. Tiles
3. Buildings
4. Required files
5. Events

### File Header

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Version | Loader Version | 4 |
| Level width | The width of the level in tiles | 4 |
| Level height | The height of the level in tiles | 4 |

### Tiles
For each tile (width * height tiles):

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Tile number | The tile number |2|
| Tile Z | The height of the tile in the level |1|
| Variant | the variant of this tile |1|

### Buildings

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Building count | Number of buildings | 4 |

For each building:

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Building number | ID of the building | 2 |
| Building width | Width of the building in tiles | 1 |
| Building height | Height of the building in tiles | 1 |
| Building X | The x position of this building in tiles | 4 |
| Building Y | The y position of this building in tiles | 4 |
| Building Hitbox X (float) | The x position of this building's hitbox in tiles | 4 |
| Building Hitbox Y (float) | The y position of this building's hitbox in tiles | 4 |
| Building Hitbox width (float) | The width of this building's hitbox in tiles | 4 |
| Building Hitbox height (float) | The height of this building's hitbox in tiles | 4 |
| Building Hitbox behind X (float) | The x position of this building's behind hitbox in tiles | 4 |
| Building Hitbox behind Y (float) | The y position of this building's behind hitbox in tiles | 4 |
| Building Hitbox behind width (float) | The width of this building's behind hitbox in tiles | 4 |
| Building Hitbox behind height (float) | The height  of this building's behind hitbox in tiles | 4 |

# TODO: ASK WHY SO MUCH MEMORY FOR BUILDINGS

### Required Files
Current paths:
1. Audio file
2. Text file (For NPCs)
3. Tile map

For each path

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Len | The length of the string | 4 |
| Str | The Path itself (not null terminated) | Len |

### Events

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Len | The number of stored events | 4 |

For each event

| Name | Description | Required Bytes |
| ---- | ----------- | -------------- |
| Event X | The X position of the event | 4 |
| Event Y | The Y position of the event | 4 |
| Event Width | The width of the event | 4 |
| Event Height | The height of the event | 4 |
| Triggeramount | How many times the event should be triggered | 4 |
| Event ID dependency | Which event needs to be executed for this to be unlocked | 4 |
| Event ID | The ID of the event | 4 |
| Event Type | The type of the event (When is it executed) | 4 |
| Event Action | The action of the event (What happens when it's executed) | 4 |
| Event Args | The args of the event | depending on event action |






