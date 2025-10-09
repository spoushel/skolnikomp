## notes
rg a fd

## ukoly
1. grep "neco" file.txt 
2. grep "neco" file.txt -q
3. find . -name "*.txt" -exec cat {} \; -exec du -b {} \; | cut -f 1
4. cut -d',' -f1< autori.csv | awk '{print $2}' | sort -u
5. 