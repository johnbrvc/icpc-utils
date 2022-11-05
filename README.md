# icpc-utils
Tools used for ICPC contests.  Mostly shell scripts.

For WF type contests, you would copy / create the CDS config folder that contains
all the required CDS files.  Then:
1) Get johnbrvc/icpc-utils repo from git
2) Copy the following files from the repo to the config folder:
	a) icpc-utils/interactive-problem-gny/pc2-exe-wrapper
	b) icpc-utils/interactive-problem-gny/copy_xml_result
	c) icpc-utils/interactive-problem-gny/intrunner (the source is in that folder if it has to be rebuilt)
3) Fix the problem.yaml files by running icpc-utils/bin/djprob2pc2 from the copied config folder
4) Create/rename the sample and secret data for each problem by running fix_judgedata from the copied config folder
5) Edit pc2-exe-wrapper and modify the interactive problem letter list.  Use "X" if no interactive problems
6) Create a accounts_load.tsv file from the CMS data or "other" tsv/csv type data.  There are scripts in icpc-utils/bin
	for doing this.  You have to determine what format input file you have and what script(s) to use to convert it to
	the pc2 accounts import tsv file.  This is, perhaps, the hardest part.  
	Note: For WF2021 in Dhaka, the DOMJudge folks provided an accounts.tsv file AND a teams2.tsv file.  Both were needed
	to generate an appropriate accounts_load.tsv file, andthe djacct2pc2 script was created to do this.

