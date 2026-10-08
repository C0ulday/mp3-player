## Lecteur MP3 avec ESP32 mini C3

english below

Petit lecteur mp3 avec port jack + bluethooth

# Matériel
### Affichage 
- ESP32 C3 mini
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

#Software

### Librairies
DFRobotDFPlayerMini
Wire
U8g2lib

### Etape 1 : Faire marcher DFPlayer + haut-parleur
### Etape 2 : Faire marcher DFPlayer + haut-parleur + boutons
### Etape 3 : Faire marcher OLED

Important : les GPIO 8 et GPIO 9 pour le I2C ne sont pas utilisés car ils sont déjà liés au bouton BOOT qui crée des problèmes d'afficchage.
Sites pratiques : lopaka, pour le design de l'interface et la génération plus rapide de code avec u8g2

### Etape 4 : Faire marcher OLED + boutons
### Etape 5 : Faire marcher DFPlayer + OLED + haut-parleur + boutons


Le code est disponibble dans 01_code



