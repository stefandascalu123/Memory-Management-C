        Tema 1 IOCLA
Dascalu Stefan-Teodor

---------------------------------------
    Implementare add_last

Functia primeste ca parametru **arr, 
len(numarul de bytes ocupati) si structura
data. Daca len = 0, se aloca memorie pentru
structura data, iar daca nu e este realocata
pt cat avem nevoie. Copiem memoria din data 
in ordine(tipul,lungimea,data). Si marim
lungimea *arr cu memoria pe care am adaugat-o.

----------------------------------------

    Implementare add_at

Functia primeste ca parametru **arr, len,
data si index. Daca index este mai mare
decat numaru de elemente(returbat de Functia
CountElem) valorile vor fi adaugate la
capatul lui *arr. Daca  nu, se parcurge lungimea,
pana la index, se salveaza lungimea si se muta,
memoria deja stocata la dreapta, la adresa curenta +
memoria care urmeaza sa fie adaugata. In final,
se adauga memoria din structra data. Si marim
len cu cat am adaugat, apoi realocam *arr cu noua
lungime.

-----------------------------------------

    Implementare find

Functia primeste *arr, len si index. Parcurgem
pana la index si se salveaza aceasta in len_gen_cur
(da, am facut-o intentionat). Si se afiseaza datele sub
formatul cerut de tipul de data.

------------------------------------------

    Implementare delete_at

Analog functiei insert_at, se parcurge pana la index,
se salveaza memoria structurii care urmeaza sa fie stearsa,
si se muta memoria de la len_del(memoria de stergere) bytes 
distanta la index, se scade len cu len_del si se realoca memoria.

-------------------------------------------

    Implementare print

Functia printeaza date fiecarei structuri din *arr precum
este precizat pt fiecare tip in parte.

-------------------------------------------

    Functia GetData

Functia citeste de la tastatura tipul structurii, si intra in
if-ul corespunzator si citeste restul randului. Se salveaza,
valorile in n1, n2, b1,b2(numele1, numele2, bancnota1, bancnota2),
se salveaza memoria ocupata de acestea si se muta in zona, 
data.data. Apoi, functia returneaza data_structure data.

------------------------------------------

    Main

In main se aloca un buffer unde se for citi comenzile,
intra in functia corespunzatoare si executa functiile, pana
la citirea comenzii exit, unde se va iesi din program dupa
ce se elibereaza memoria.

