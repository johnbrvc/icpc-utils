/*
 * R - Guessing Game
 * One and done version
 *
 * Control program - interactively grades user submission.
 *
 * Sends response to user on "stderr"  (NOT stdout).
 * Accepts input on "stdin"
 * Sends (optional) diagnostic messages to "stdout" for debugging
 * We switched stdout/stderr to ensure there are no buffering issues.
 *
 * To use this program on Linux:
 * 1) Create 2 fifos  (fin, fout)
 * 2) Run this program:  rjudge r.in dummy dummy result.xml 2>fin <fout
 *      r.in is the list of input values.  Use the sample data file (sample/r.in) for
 *      for "test" button.  Use the judge data file (judge/r.out) for judged submissions.
 *      The "dummy" args are unused.
 *      rjudge places the validator XML output in result.xml
 * 3) Start student submission in another process:  r <fin >fout
 *
 */
#include <stdio.h>
#include <stdlib.h>

//#define	DEBUG
//#define	DEBUG1

#define	MAX_VAL		1024
#define	MAX_GUESS	10
#define MAX_PROB	1
int nTestCases[MAX_VAL];
int nProb = 0;

char *szResultFile;
int bSentXML = 0;
char szErr[256];
#ifdef WIN32
#define	snprintf	_snprintf
#endif
void GenXML(const char *szMsg1, const char *szMsg2)
{
	FILE *fp;

	if(szResultFile != NULL && *szResultFile != '\0'){
		fp = fopen(szResultFile, "wt");
		if(fp != NULL){
			fprintf(fp, "<?xml version=\"1.0\"?>\n");
			fprintf(fp, "<result outcome=\"%s\" security=\"%s\">%s</result>\n", szMsg1, szResultFile, szMsg2 == NULL ? "" : szMsg2);
			bSentXML = 1;
			fclose(fp);
		} else {
			fprintf(stdout, "Can't open result file %s\n", szResultFile);
		}
	} else {
		fprintf(stdout, "No result file: %s - %s\n", szMsg1, szMsg2 == NULL ? "" : szMsg2);
	}
}

int
main(int argc, char **argv)
{
	int i, nProb, val, guess, ntry;
	char ibuf[512];
	char *szJudge;
	FILE *fp;

	if(argc < 5)
	{
		snprintf(&(szErr[0]), sizeof(szErr)-1, 
			"USAGE: %s prob_file judge_file stud_file result_file\n", argv[0]);
		GenXML("Other - Contact Staff", &(szErr[0]));
		return -1;
	}
#ifdef DEBUG
	fprintf(stdout, "%s: arg1='%s' arg2='%s' arg3='%s' arg4='%s' arg5='%s'\n",
		argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
#endif
	szResultFile = argv[4];
	szJudge = argv[1];
	fp = fopen(szJudge, "rt");
	if(fp == NULL){
		snprintf(&(szErr[0]), sizeof(szErr)-1, 
			"Can not open judge data %s\n", szJudge);
		GenXML("Other - Contact Staff", &(szErr[0]));
		return -1;
	}
	nProb = 0;
	while(fgets(&(ibuf[0]), sizeof(ibuf), fp) != NULL && nProb < MAX_PROB){
		i = atoi(&(ibuf[0]));
		if(i >= 1 && i <= MAX_VAL){
			nTestCases[nProb++] = i;
		}
	}
	fclose(fp);
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);
#ifdef DEBUG1
	fprintf(stdout, "There are %d problems in file %s.\n", nProb, szJudge);
#endif
	for(i = 0; i < nProb; i++){
		val = nTestCases[i];
#ifdef DEBUG1
		fprintf(stdout, "Value is %d\n", val);
#endif
		for(ntry = 1; ntry <= MAX_GUESS; ntry++){
			if(fgets(&(ibuf[0]), sizeof(ibuf), stdin) == NULL){
#ifdef DEBUG
				fprintf(stdout, "EOF from submission\n");
#endif
				GenXML("Wrong Answer", "EOF from submission program");
				goto done;
			}
			guess = atoi(&(ibuf[0]));
#ifdef DEBUG
			fprintf(stdout, "Guess: %d\n", guess);
#endif
			if(guess < val){
				fprintf(stderr, "higher\n");
#ifdef DEBUG
				fprintf(stdout, "higher\n");
#endif
			} else if(guess > val){
				fprintf(stderr, "lower\n");
#ifdef DEBUG
				fprintf(stdout, "lower\n");
#endif
			} else {
#ifdef DEBUG1
				fprintf(stdout, "correctly guessed it using %d tries\n", ntry);
#endif
				fprintf(stderr, "correct\n");
#ifdef DEBUG
				fprintf(stdout, "correct\n");
#endif
				break;
			}
		} 
		if(ntry > MAX_GUESS){
#ifdef DEBUG1
			fprintf(stdout, "Too many guesses (%d)\n", ntry);
#endif
			snprintf(&(szErr[0]), sizeof(szErr)-1, "Too many guesses (%d)", ntry);
			GenXML("Wrong Answer", &(szErr[0]));

			break;
#ifdef DEBUG
		} else {
			fprintf(stdout, "Got %d in %d guesses\n", val, ntry);
#endif
		}
		
	}
done:
	if(!bSentXML){
		GenXML("Accepted", "");
	}
	exit(0);
}
