# reAligner
Implementation of reAligner algorithm for refining DNA sequence multi-alignments (Anson EL &amp; Myers EW, 1997).
Project by Zrinka Gavran, Karlo Fodor and Ivan Bestvina, for Bioinformatics course at FER, Zagreb, Croatia (http://www.fer.unizg.hr/en/course/bio)

Command line arguments:
```
<fasta input> <mhap input> <epsilon value> <max number of iterations> <output directory> <output filename>
```



ReAligner uses CPPUnit for testing important methods.

To compile, use:
```
c++ *.cpp -std=c++11 -lcppunit -O3 -o realigner
```
