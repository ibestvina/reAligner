Here included are input files for testing. Every folder contains an original sequence, FASTA file with fragments and MHAP file with initial layout. All tests are generated with 1% insertion, 1% deletion, and 1% substitution error rates.

Synthetic tests are randomly generated. Original genome length is specified by its folder name (e.g. synthetic2k -> genome length is 2000).
Genome length (G), number of sequences (N), sequence length (L) and depth (D = NxL/G) is specified below:

G		N		L		D

500		60		50		6
1k		60		100		6
2k		100		200		10
5k		200		300		12
10k		400		300		12
20k		800		300		12
50k		2000	300		12
100k	3000	300		9
200k	4000	400		8
500k	10000	400		8
1m		20000	400		8



Ecoli test is based on ecoli genome which is 4.6m bases long and consists of 50k sequences, each 500 bases long (D = 5.4).
