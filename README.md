## Lecteur MP3 avec ESP32

english below

Petit lecteur mp3 avec port jack + Bluetooth

# Architecture du repo

```
.
├── 00_photos/          images du montage, du banc de test et du produit final
├── 01_code/
│   └── player/
│       ├── player.ino  fichier principal : setup, loop, gestion des boutons
│       ├── menu.ino    affichage OLED et navigation dans le menu
│       └── audio.ino   pilotage du DFPlayer (lecture, pause, volume, piste)
└── README.md
```

# Matériel

### Affichage
- ESP32
- Ecran OLED 0.91''

### Alimentation
- Lipo Batterie 3.7V
- TP4056

### Son
- DFPlayer + haut-parleur 2Ohms
- Carte SD

### Autres
- connecteur Jack
- PCB
- Interrupteur à Bascule
- Bouton

### Alimentation

![Alimentation](00_photos/supply_test.PNG)

Le TP4056 gère la charge de la Lipo en USB. L'interrupteur à bascule coupe la sortie batterie vers l'ESP32 et le DFPlayer.

### Banc de test

![Banc de test](00_photos/bench_test.PNG)

Montage sur breadboard pour valider avant le passage sur PCB/Breadboard universel.

# Software

### Librairies
DFRobotDFPlayerMini
Wire
U8g2lib

### Etape 1 : Faire marcher DFPlayer + haut-parleur
### Etape 2 : Faire marcher DFPlayer + haut-parleur + boutons
### Etape 3 : Faire marcher OLED

Sites pratiques : lopaka, pour le design de l'interface et la génération plus rapide de code avec u8g2

### Etape 4 : Faire marcher OLED + boutons
### Etape 5 : Faire marcher DFPlayer + OLED + haut-parleur + boutons

Le code est disponible dans 01_code

# Produit final

![Produit final](00_photos/produit_final.jpg)

---

## MP3 player with ESP32

Small mp3 player with jack output + Bluetooth

# Repo structure

```
.
├── 00_photos/          pictures of the build, test bench and final product
├── 01_code/
│   └── player/
│       ├── player.ino  main file: setup, loop, button handling
│       ├── menu.ino    OLED display and menu navigation
│       └── audio.ino   DFPlayer control (play, pause, volume, track)
└── README.md
```

# Hardware

### Display
- ESP32
- OLED screen 0.91''

### Power supply
- Lipo battery 3.7V
- TP4056

### Audio
- DFPlayer + 2Ohms speaker
- SD card

### Others
- Jack connector
- PCB
- Toggle switch
- Button

### Power supply

![Power supply](00_photos/supply_test.PNG)

The TP4056 handles Lipo charging over USB. The toggle switch cuts the battery output to the ESP32 and the DFPlayer.

### Test bench

![Test bench](00_photos/bench_test.PNG)

Breadboard setup used to validate each block before moving to the PCB.

# Software

### Libraries
DFRobotDFPlayerMini
Wire
U8g2lib

### Step 1 : Get DFPlayer + speaker working
### Step 2 : Get DFPlayer + speaker + buttons working
### Step 3 : Get OLED working

Useful sites : lopaka, for interface design and faster u8g2 code generation

### Step 4 : Get OLED + buttons working
### Step 5 : Get DFPlayer + OLED + speaker + buttons working

The code is available in 01_code

# Final product

![Final product](00_photos/produit_final.jpg)
