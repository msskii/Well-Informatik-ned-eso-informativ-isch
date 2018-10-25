# TODO

1. Assign IDs to all the entities - ✅
2. Server sends data about entities -> ✅
3. Cheksum --> No other packets misinterpreted (Instead using start & end packets ✅)

## Server protocol

TCP:
  &ltcmd:word>[args]
  word = two chars --> here all lowercase?

# Commands:
## Player --> Player ID
### ✅ &ltpj>: Player Join --> Additional data (Name, ...) 
### ✅ &ltpn>: Player name --> Set the name of the player 
### ✅ &ltpl>: Player Leave 
### ✅ &ltpm>: Player move --> new pos or direction 
### &ltpa>: Player action --> (Attack or something) 

### &ltpc>: Player chat --> Player Chat

## Entities --> Entity ID
### ✅ &ltej>: Entity join (Spawn) 
### ✅ &ltel>: Entity leave (Die) 
### ✅ &ltem>: Entity move 
### &ltea>: Entity action (Attack or something) 

## Level (Welcome message)
### ✅ &ltli>: Send Serialized level (Level init)
### &ltlc>: Change level (Same as level init, just no setup stuff --> Players are the same)

## Control
### ❎ &ltcc>: TCP Packet with length (only needed if length > normal max length) (Replaced, not needed)
### ✅ &ltco>: Packet received. More data can be received

