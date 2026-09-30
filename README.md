> simple firmware to flood 2.4ghz airwaves with custom beacon frames. built for testing ONLY!.

## 🛠️ hardware requirements

- **esp32 dev board** (wroom-32, node_mcu, or whatever cheap clone you have lying around)
- **usb cable** (data capable, not just charge)

## 💻 software stack

- **arduino ide** (v2.x or legacy v1.8.x)
- **esp32 board package** (installed via arduino ide  ) (espressif)

## 🚀 quick start

1. clone the repo or copy the code into a new arduino sketch.
2. drop your custom ssid names right at the top:
   ```cpp
   String ssidList[] = {   //-- 3 ssids = int ssidCount = 3;
     "meow1",
     "meow2",
     "meow3"
   };
   int ssidCount = 3;    //- depends on how many ssids your using blah blah yk.
