# mBot - Arduino
# Matériel & Sources


## Avant Propos
Lors de nos réunions feedback après plusieurs évènements Devoxx4Kids, nous avons remarqué que de façon régulière, certains enfants de l’atelier mBots s’ennuient après avoir terminé le tutoriel prévu par l’atelier.


L’atelier est estimé à deux heures, et parfois au bout de 1h30, voir parfois moins d’une heure, certains enfants ont terminé, pour plusieurs raisons:
* l’enfant est plus rapide que les autres
* l’enfant est déjà habitué au monde de la programmation et de la robotique, il n’a pas eu besoin d’aide
* l’enfant est déjà venu, n’avait pas terminé le tutoriel la fois d’avant et reprend les bases rapidement pour passer un peu plus de temps sur les dernières questions

Nous avons discutés des options possibles pour occuper ses enfants, qui la plupart du temps se voient attribuer des challenges de labyrinthes avec les boites des robots, mais n’apprennent pas vraiment beaucoup plus, il leur faudrait un enfant avec un adulte pour leur montrer des cas pratiques, ce qui n’est pas possible, nous ne sommes pas assez de bénévoles.

Nous nous sommes aussi demandé s’il est possible de les envoyer dans l’atelier des enfants plus âgés, mais, souvent, l’atelier est complet.

Alors, nous avons pensé à une autre solution, qui serait de permettre aux enfants de faire leurs tous premiers pas en programmation. L’étape juste après la programmation en scratch, la programmation sur ordinateur/clavier.
Toujours sur les robots mBots, mais cette fois-ci avec l’application Arduino.

## Sources
* MakeBlock installation tutorial: https://support.makeblock.com/hc/en-us/articles/4419572961943-Program-mBot-in-Arduino-IDE
* Arduino software: https://www.arduino.cc/en/software
* mCore https://support.makeblock.com/hc/en-us/articles/4412894402967-mCore-Main-Control-Board-of-mBot

## Matériel Nécessaire
* 1 mBot complet
  * 1 Câble USB Type B vers USB Type A (ou dongle USB sans fil)
* 1 ordinateur (portable de préférence)
  * l’application Arduino installée
    * Les librairies installées: https://github.com/Makeblock-official/Makeblock-Libraries
      * driver USB: https://www.wch-ic.com/downloads/CH341SER_EXE.html
* 1 casque pour écouter la vidéo (1 seul pour tous les robots est suffisant)


## Tutoriel Bénévole
* Suivre ce tutoriel d’installation, si l’ordinateur n’est pas installé
  * https://support.makeblock.com/hc/en-us/articles/4419572961943-Program-mBot-in-Arduino-IDE
* Télécharger Makeblock library
  * https://codeload.github.com/Makeblock-official/Makeblock-Libraries/zip/master
* Apparemment pas nécessaire (à confirmer)
  * à chaque programme, utiliser: #include <MeMCore.h>
* trouver dans le Device Manager, le port USB nommé `USB-SERIAL CH340`
* Sélectionner la board dans le port trouvé, par exemple le COM10
  * board: arduino uno
  * com3
* Sélectionner un exemple dans 
  * files > examples > makeblock drive
* Compiler en cliquant sur VERIFY
* envoyer au robot en cliquant sur UPLOAD


## Tutoriel Enfant
* Face au logiciel
* File > Examples > MakeBlockDrive > me_RGBLed > ColorLoopTest
