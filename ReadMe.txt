//Michael Karlsson, 1601924, Ti16SPeli, Programming and algorithms, Syksy 2018 HARJOITUSTY�

Yleisesti:
Joka koordinaatista voi liikkua enint��n kahdeksaan suuntaan. Kartan reunan yli ei voi liikkua
Ohjelma lukee Map.txt nimisen tiedoston projektikansiosta

Koordinaatisto:
x,y koordinaatisto jonka origo on vasemmassa yl�nurkassa.
1 2 3
4 5 6
7 8 9
Esim. (1,1) = 1 ja (3,3) = 9

Kartan tulkinta:
0 = este
1-9 = koordinaattiin liikumisen hinta

Enqueue:
Jos sama node lis�t��n pienem�ll� prioriteetilla niin vanha poistetaan jonosta.
Samaa nodea ei lis�t� samalla/suuremmalla prioriteetilla

A*:
Tutkitaan ensin pohjoinen ja sitten kellonsuuntaan k�yden l�pi 8 ilmansuuntaa.
Aloitus pisteen painoarvolla ei merkityst�
Kartalla oleva numero kertoo paljonko ruutuun siirtyminen "maksaa"
Algoritmi l�yt�� yhden nopeimmista reiteist�. Nopeampia reittej� kuin l�ydetty reitti ei pit�isi olla mutta reittej� jotka ovat yht�
nopeita mutta joissa on v�hemm�n vaiheita voi olla.

Tuloste:
1- Kuljettu ruutu
5- Start
6- Goal
0- ei kuljettu ruutu
