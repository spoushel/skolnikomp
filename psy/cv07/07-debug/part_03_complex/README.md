# Systém správy studentských známek

Komplexní multi-file program pro správu studentů, kurzů a hodnocení. Program obsahuje **6 záměrných chyb** různých typů.

## Struktura projektu

```
part_03_complex/
├── src/                   # Zdrojové soubory
│   ├── config.h           # Konstanty systému
│   ├── student.h/c        # Správa databáze studentů
│   ├── course.h/c         # Správa kurzů a zápisů
│   ├── grades.h/c         # Operace s hodnocením
│   ├── stats.h/c          # Statistické výpočty
│   ├── file_io.h/c        # Načítání/ukládání souborů
│   ├── utils.h/c          # Pomocné funkce
│   └── main.c             # Hlavní program s menu
├── build/                 # Objektové soubory a executable (vytvoří se automaticky)
├── Makefile               # Build systém s podporou závislostí
├── BUGS.md                # Hlášené chyby k vyšetření
├── students.txt           # Testovací data
└── README.md              # Tento soubor
```

**Důležité**: Kód je záměrně dlouhý (~700 řádků). **Nečtěte celý kód**. Použijte debugger a nástroje k pozorování chování za běhu a nalezení pouze té cesty programem, která vede k chybě.

## Rychlý start

```bash
make                    # Kompilace (vytvoří build/ adresář automaticky)
make run                # Spuštění programu
```

Program se bude nacházet v `build/main`.

**POZOR**: V tomto projektu pro vás nejsou připraveny testovací cíle pro `Valgrind` nebo `Address Sanitizer` ani důsledně compiler flagy. Budete si je muset nastavit sami podle potřeby. Inspirujte se z předchozích částí.

## Cíl cvičení

V tomto programu je **záměrně** implementováno 6 různých typů chyb. V souboru `BUGS.md` naleznete bug reporty od uživatelů programu, kterí potkali neočekávané chování. Vaším úkolem je:

1. **Reprodukovat** hlášené chyby ze souboru `BUGS.md`
2. **Identifikovat** vhodné diagnostické nástroje pro každý typ problému
3. **Lokalizovat** přesné místo v kódu (soubor, řádky, funkce)
4. **Analyzovat** příčinu problému
5. **Zdokumentovat** své zjištění podle šablony

Pro jednodušší hledání dalších chyb může být někdy užitečné chybu opravit, pokud je to triviální. Nicméně hlavním cílem je **nalezení a analýza** chyb, nikoliv jejich oprava.

**Používejte dostupné nástroje jako compiler, Valgrind a Address Sanitizer.**