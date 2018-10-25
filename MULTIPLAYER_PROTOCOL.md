# TODO

1. Assign IDs to all the entities - ✅
2. Server sends data about entities -> ✅
3. Cheksum --> No other packets misinterpreted (Instead using start & end packets ✅)

## Server protocol

TCP:
  <cmd:word>[args]
  word = two chars --> here all lowercase?

# Commands:
## Player --> Player ID
### ✅ <pj>: Player Join --> Additional data (Name, ...) 
### ✅ <pn>: Player name --> Set the name of the player 
### ✅ <pl>: Player Leave 
### ✅ <pm>: Player move --> new pos or direction 
### <pa>: Player action --> (Attack or something) 

### <pc>: Player chat --> Player Chat

## Entities --> Entity ID
### ✅ <ej>: Entity join (Spawn) 
### ✅ <el>: Entity leave (Die) 
### ✅ <em>: Entity move 
### <ea>: Entity action (Attack or something) 

## Level (Welcome message)
### ✅ <li>: Send Serialized level (Level init)
### <lc>: Change level (Same as level init, just no setup stuff --> Players are the same)

## Control
### ❎ <cc>: TCP Packet with length (only needed if length > normal max length) (Replaced, not needed)
### ✅ <co>: Packet received. More data can be received

