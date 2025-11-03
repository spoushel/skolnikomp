Tato úloha slouží k procvičení práce s polem, kontrole načítání vstupu a práci se znakovými literály. Zájemci mohou využit funkce z knihovny ctype.h jako jsou isalpha(), isspace() nebo tolower().
Povinné zadání
Program ze standardního vstupu načtěte text (větu) znak po znaku (např. funkcí getchar() a vypíše počty výskytu písmen abecedy 'a'–'z' a 'A'–'Z', přičemž nerozlišuje malá a velká písmena, viz níže uvedené příklady.
Vstupní text (věta) může obsahovat mezery a může být zakončena tečkou '.'
V případě, že vstupní text obsahuje jiné znaky, program končí návratovou hodnotou 100 vypíše na standardní chybový výstup zprávu: “Chyba vstupu!”.
V případě, že výskyt některého písmene překročí počet 9, program končí návratovou hodnotou 101 a vypíše na stderr chybové hlášení Error: Prilis mnoho stejnych znaku!.
V obou případech chybového výstupu je text zakončen znakem nového řádku \n.
V případě chyby, první výskyt chyby ukončuje program.
V případě úspěšného zpracování vstupu vrací program hodnotu 0.
Četnost výskytu znaku je vypsána na dvou řádcích zakončených znakem nového řádku. Před každým znakem je mezera

0;
100; “Chyba vstupu!” → stderr
101; “Error: Prilis mnoho stejnych znaku!” → stderr