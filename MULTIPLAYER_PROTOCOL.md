# TODO

1. Assign IDs to all the entities - ✅
2. Server sends data about entities -> ✅
3. Cheksum --> No other packets misinterpreted (Instead using start & end packets ✅)

## Server protocol

TCP:
  &lt;cmd:word>[args]
  word = two chars --> here all lowercase?

# Commands:
## Player --> Player ID
### ✅ &lt;pj>: Player Join --> Additional data (Name, ...) 
### ✅ &lt;pn>: Player name --> Set the name of the player 
### ✅ &lt;pl>: Player Leave 
### ✅ &lt;pm>: Player move --> new pos or direction 
### &lt;pa>: Player action --> (Attack or something) 

### &lt;pc>: Player chat --> Player Chat

## Entities --> Entity ID
### ✅ &lt;ej>: Entity join (Spawn) 
### ✅ &lt;el>: Entity leave (Die) 
### ✅ &lt;em>: Entity move 
### &lt;ea>: Entity action (Attack or something) 

## Level (Welcome message)
### ✅ &lt;li>: Send Serialized level (Level init)
### &lt;lc>: Change level (Same as level init, just no setup stuff --> Players are the same)

## Control
### ❎ &lt;cc>: TCP Packet with length (only needed if length > normal max length) (Replaced, not needed)
### ✅ &lt;co>: Packet received. More data can be received

