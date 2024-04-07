# Live-Flower: Interactive Arduino Project
In collaboration with a partner, we brought to life a captivating project called "Live-Flower." This creative endeavor utilized the capabilities of Arduino Uno and various complementary components. Our dynamic creation featured a fusion between technology and nature in the form of a sunflower-inspired design.

Components:
For our project, we integrated the following components with the Arduino:
- Servo Motor
- Neopixel Lights
- Photosensor
- Motion Sensor
- Homemade Capacitive Touch Sensor

Design Concept:
Our artistic vision centered around emulating the behavior of a sunflower, capturing two distinctive states: "sleep" and "awake." This transition was orchestrated by the photosensor's responsiveness to ambient light changes. Notably, two additional sensors, the motion sensor and capacitive touch sensor, played pivotal roles with varying functionalities, contingent on the flower's current state.

**Functionalities:**
Night Time/Flower Sleeping (Lights Off):
- (Photosensor) Upon detecting low light levels, the (Servo Motor) retracts the flower petals, symbolizing sleep.
- (Neopixel) Stem slowly pulses light on and off showing that it is resting. (Not clearly visible in video unfortunately)
- (Motion sensor) As you get closer to the flower, it displays red flashing lights through the (Neopixel) as if the flower's slumber was disrupted.
- (Touch sensor) Interaction with the leaves through the simulated a watering effect, visualized by a blue light pulse moving up the stem.

Day Time/Flower is Awake(Lights On):
- (Photosensor) Upon detecting higher light levels, the (Servo Motor) opens the flower petals, signalling that the flower is now awake.
- (Servo motor/Photosensor) Flower petals sprout back up after sensing light, becomes awake
- (Neopixel) Green light pulses down the stem showing that it is getting its nutrients from the sun
- (Touch sensor) Touching the leaves will tickle it, causing it to emit colorful lights (through neopixel)
- (Motion sensor) Getting closer to the flower will get it scared causing the petals to retract as you get closer

https://github.com/MohammedMawi/Live-Flower/assets/90345617/ac411540-b6c7-417c-aad2-a7d50eb2bccf

