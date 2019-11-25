//Michael Karlsson, 1601924, Ti16SPeli, Programming and algorithms, Syksy 2018 HARJOITUSTYÖ

Yleisesti:
Joka koordinaatista voi liikkua enintään kahdeksaan suuntaan. Kartan reunan yli ei voi liikkua
Ohjelma lukee Map.txt nimisen tiedoston projektikansiosta

Koordinaatisto:
x,y koordinaatisto jonka origo on vasemmassa ylänurkassa.
1 2 3
4 5 6
7 8 9
Esim. (1,1) = 1 ja (3,3) = 9

Kartan tulkinta:
0 = este
1-9 = koordinaattiin liikumisen hinta

Enqueue:
Jos sama node lisätään pienemällä prioriteetilla niin vanha poistetaan jonosta.
Samaa nodea ei lisätä samalla/suuremmalla prioriteetilla

A*:
Tutkitaan ensin pohjoinen ja sitten kellonsuuntaan käyden läpi 8 ilmansuuntaa.
Aloitus pisteen painoarvolla ei merkitystä
Kartalla oleva numero kertoo paljonko ruutuun siirtyminen "maksaa"
Algoritmi löytää yhden nopeimmista reiteistä. Nopeampia reittejä kuin löydetty reitti ei pitäisi olla mutta reittejä jotka ovat yhtä
nopeita mutta joissa on vähemmän vaiheita voi olla.

Tuloste:
1- Kuljettu ruutu
5- Start
6- Goal
0- ei kuljettu ruutu
