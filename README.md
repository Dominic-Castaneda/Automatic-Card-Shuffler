## Overview
This project is a fully functional, Arduino-controlled card shuffler designed to mix decks of playing cards. The entire casing was 3D modeled and printed by me, including internal ramps and compartments that guide the cards down into the center collection zone.
        
## Design & CAD Modeling
Using Fusion 360, I designed a multi-piece shell that snaps together and aligns the cards perfectly. The two card holders are shaped to angle slightly inward, helping gravity feed the cards into the motor-driven slot. This part took several iterations to get right.

## Electronics
At the heart of the project is an Arduino Uno with a motor driver and IR receiver. The IR remote controls activation. Two motors alternate pulling cards from each side, triggered via a remote command and timed intervals

## Progress So Far
Right now, the electronics and code work well, motors spin, cards move, and the IR remote gives full control. The mechanical design is about 90% done. Some parts still need fitting tolerances adjusted and the final motor mounts integrated cleanly.

## What I Learned
This project taught me how to combine CAD and embedded programming into one cohesive physical product. I learned how important tolerances are in 3D printing, how to drive motors via Arduino.
