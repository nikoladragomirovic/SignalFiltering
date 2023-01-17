# ADOZ Project

Projekat se sastojao iz 2 dela: </br>
- Pronalaženje frekvencije željenog signala.
- Otkljanjanje neželjenih frekvencija i smetnji unutar željene u vidu sinusa visoke amplitude implementacijom FIR i IIR filtra u C jeziku.

Pronalaženje frekvencije željenog signala i neželjenih sinusa ostvareno je pomoću analize "Plot Spectrum" alata programa "Audacity". </br>
Implementirani su circular FIR filtri 35og, 77og i 129og reda, kao i IIR filtri drugog, četvrtog i šestog reda na ulazni signal.

Nakon filtriranja, output signal sadrži samo željene frekvencije.
# English
The project consisted of two parts:</br>
- Finding the frequency of the desired signal.
- Removing unwanted frequencies and interference within the desired signal in the form of high amplitude sine waves by implementing FIR and IIR filters in C language.

Finding the frequency of the desired signal and unwanted sine waves was achieved using the "Plot Spectrum" tool of the "Audacity" program.
Circular FIR filters of 35th, 77th and 129th order, as well as IIR filters of second, fourth and sixth order were implemented on the input signal.

After filtering, the output signal only contains the desired frequencies.
