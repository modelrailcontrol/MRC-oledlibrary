````
 __  __ ___  ___
|  \/  | _ \/ __|
| |\/| |   / (__
|_|  |_|_|_\\___| - OLED library
````

Model Rail Control - Controlling your model railroad the modern way

## Översikt
Detta är ett bibliotek (library) som hanterar en 128x64 pixels OLED-skärm för MRC-enheter.

Biblioteket kan idag hantera följande saker:
 - Visa titelrad på 15-20 tecken
 - Visa symbol för nätstatus (wifi/MQTT)
 - Visa en 3-vägsväxels alla lägen
 
 Titelrad och nätstatus kan valfritt visas eller döljas och titeln kan ha tre olika storlekar på texten.

 För alla växelindikeringar kan följande lägen visas:
  - Unknown (när enheten just har startat)
  - Left, Right, Closed, Thrown (beroende på typ av växel)
  - Moving (medan växeln slår om)
