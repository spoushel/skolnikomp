# Hlášené chyby - Systém správy studentských známek

Tento dokument obsahuje seznam všech známých problémů v systému. Každá chyba je popsána z pohledu uživatele - co dělal, co očekával a co se skutečně stalo.

Vaším úkolem je **vyšetřit** tyto chyby pomocí diagnostických nástrojů, **lokalizovat** jejich příčinu v kódu a **zdokumentovat** své zjištění.

## Bug #1: Duplicitní zápis studenta do kurzu

### Popis
Systém umožňuje zapsat stejného studenta do jednoho kurzu vícekrát bez varování. Student se pak v seznamu kurzu objeví duplicitně.

### Kroky k reprodukci
```bash
1                       # Načíst studenty
students.txt
5                       # Zapsat studenta do kurzu
101                     # Student ID
1                       # Course ID
5                       # Zkusit zapsat stejného studenta znovu
101                     # Stejný student
1                       # Stejný kurz
9                       # Zobrazit seznam kurzů
```

### Očekávané chování
Druhý pokus o zápis by měl být odmítnut s chybovou hláškou:
```
Student 101 is already enrolled in this course.
Failed to enroll student
```

Program by tuto funkci již měl obsahovat! Není třeba nic implementovat.

### Skutečné chování
Program umožní duplicitní zápis bez varování. Student se v kurzu objeví vícekrát:
```
Course 1:
=== Programování v C/C++ (B0B36PSY) - 6 credits ===
Enrolled: 2 students
  - Anna Novakova (ID: 101)
  - Anna Novakova (ID: 101)
```

## Bug #2: Program padá při výpočtu statistik s hodnocením 100

### Popis
Program má buffer overflow chybu při výpočtu histogramu, pokud data obsahují známku 100. Chyba existuje vždy, ale projeví se náhodně.

### Kroky k reprodukci
```bash
1                       # Načíst studenty
students.txt
10                      # Vypočítat statistiky
# Program spadne
```

### Očekávané chování
Histogram správně zobrazí rozložení všech známek včetně hodnoty 100:
```
Grade Distribution:
[  0- 9]: 0
[10-19]: 0
...
[90-99]: 5
[ 100]: 2
```

## Bug #3: Směrodatná odchylka je nesprávná

### Popis
Výpočet směrodatné odchylky neodpovídá manuálnímu výpočtu. Hodnota je konzistentně nižší než by měla být.

### Kroky k reprodukci
```bash
1                       # Načíst studenty
students.txt
10                      # Vypočítat statistiky
```

### Očekávané chování
Pro 14 známek v souboru `students.txt`:
```
Známky: 85, 90, 88, 75, 80, 82, 95, 92, 89, 78, 100, 85, 100, 80
Průměr: 87.07
Směrodatná odchylka (výběrová): 8.24
```

### Skutečné chování
Program zobrazuje nižší hodnotu:
```
Standard Deviation: 7.71
```

### Výpočet (pro referenci)
Výběrová směrodatná odchylka:
```
s = √[Σ(xi - μ)² / (n-1)]    // Bessel's correction
```

Pro vzorek (sample) dat používáme **výběrovou** vzorec s dělitelem `(n-1)`.

## Bug #4: Nesprávné statistiky při prvním spuštění

### Popis
Při prvním spuštění programu (nebo náhodně) jsou statistiky nesprávné - obrovská čísla nebo NaN.

### Kroky k reprodukci
```bash
1                       # Načíst studenty
students.txt
10                      # Vypočítat statistiky
```

## Bug #5: Buffer overflow při dlouhých jménech

### Popis
Přidání studenta s velmi dlouhým jménem způsobí pád programu nebo poškození dat.

### Kroky k reprodukci
```bash
2                       # Přidat nového studenta
999
VeryLongFirstNameThatExceedsTheInternalBufferLimit
VeryLongLastNameThatAlsoExceedsTheInternalBufferLimit
2
8                       # Zobrazit všechny studenty
```

### Očekávané chování
Program bezpečně zkrátí vstup nebo odmítne příliš dlouhý vstup s chybovou hláškou.

### Skutečné chování
Program padá s chybou segmentace (segmentation fault) nebo zobrazuje poškozená data.

## Bug #6: Program spotřebovává hodně paměti (Memory Leak)

### Popis
Program uniká paměť při inicializaci kurzů. Při ukončení programu zůstávají alokované názvy kurzů v paměti.

### Kroky k reprodukci
```bash
1                       # Načíst studenty
students.txt
12                      # Uložit a ukončit
```
