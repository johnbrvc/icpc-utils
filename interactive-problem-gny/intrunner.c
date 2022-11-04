/*
 * Usage: intrunner interactive-validator result-tmp.xml command < secret_input_data
 *
 * interactive-validator is the executable of the interactive validator
 *	invoked as: interactive-validator secret_input_data_file dummy dummy result-tmp.xml
 *
 * secret_input_data_file is created by reading stdin and writing it that file.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* This sends messages to stderr, which will appear in estderr.pc2 in the execute folder */
#define	DEBUG

/* These are the fifos for communication between the interactive validator and contestant program */
#define	INFIFO				"fin"
#define	OUTFIFO				"fout"
#define FIFOMODE			(S_IFIFO | 0600)

/* Validator exit codes */
#define EXITCODE_AC	42
#define EXITCODE_WA	43

/* Argument lists for execv */
#define	MAX_CONTESTANT_ARGS	32
#define	MAX_VAL_ARGS		10

char *intv_args[MAX_VAL_ARGS];
char *contestant_args[MAX_CONTESTANT_ARGS];
char *szResultFile;
int bSentXML = 0;
char szErr[256];
#ifdef WIN32
#define	snprintf	_snprintf
#endif

static void GenXML(const char *szMsg1, const char *szMsg2);
static char *ReadLastLine(char *szFile);

pid_t intv_pid = 0, contestant_pid = 0;

const char *MakeTimeStamp()
{
	static char szTimeBuf[64];
	size_t n;
	struct tm *tp;
	struct timeval tv;

	gettimeofday(&(tv), NULL);
	tp = localtime(&(tv.tv_sec));
	tv.tv_sec += (tv.tv_usec/1000000);
	tv.tv_usec %= 1000000;
	n = strftime(&(szTimeBuf[0]), sizeof(szTimeBuf), "%Y-%m-%d %H:%M:%S.", tp);
	if(n != 0){
		snprintf(&(szTimeBuf[n-1]), sizeof(szTimeBuf)-n, "%03d", (int)(tv.tv_usec/1000)%1000);
	}
	return(&(szTimeBuf[0]));
}

void sig_handler(int signo)
{
#ifdef DEBUG
	fprintf(stderr, "%s: Signal %d caught by intrunner\n", MakeTimeStamp(), signo);
#endif
	if(intv_pid > 0){
		kill(intv_pid, SIGTERM);
	}
	if(contestant_pid > 0){
		kill(contestant_pid, SIGTERM);
	}
	unlink(INFIFO);
	unlink(OUTFIFO);
	exit(signo);
}

int main(int argc, char **argv)
{
	char *val, *judgein, *judgeout, *feedback;
	int c, i, j, wstat, wSubStat, bContestantFinished;
	FILE *fp;
	char szFeedBackFile[512], szRTEBuf[64];

	if(argc < 7){
		fprintf(stderr, "%s: interactive-validator judgein judgeout feedbackdir result.xml command ...\n", argv[0]);
		return(1);
	}
	signal(SIGTERM, sig_handler);
	signal(SIGKILL, sig_handler);
	/* Interactive validator executable */
	val = argv[1];
	judgein = argv[2];
	judgeout = argv[3];
	feedback = argv[4];

	/* result XML file */
	szResultFile = argv[5];

	/* Set up for contestant execv: this is all args after and including argv[3] */
	for(i = 0, j = 6; j < argc && i < MAX_CONTESTANT_ARGS-1; j++, i++){
		contestant_args[i] = argv[j];
	}
	contestant_args[i] = NULL;

	snprintf(&(szFeedBackFile[0]), sizeof(szFeedBackFile), "%s/judgemessage.txt",
		feedback);

	(void) unlink(INFIFO);
	(void) unlink(OUTFIFO);
	if(mknod(INFIFO, FIFOMODE, 0) == -1 ||
		mknod(OUTFIFO, FIFOMODE, 0) == -1){
		perror("Can not create fifos\n");
		return(2);
	}
#ifdef DEBUG
	fprintf(stderr, "%s: Fifos created\n", MakeTimeStamp());
#endif
	/* Have to execute interactive validtor now */
	intv_args[0] = val;
	intv_args[1] = judgein;
	intv_args[2] = judgeout;
	intv_args[3] = feedback;
	intv_args[4] = NULL;
	/* Spawn off the interactive validator */
	intv_pid = fork();
	if(intv_pid == 0){
		/* Child */
		/* stdout (1) becomes fin and 0 becomes fout */
		close(0);
		close(1);

		j = open(OUTFIFO, O_RDONLY);
		if(j != 0){
			fprintf(stderr, "%s: can not open %s to channel 0, got %d\n",
				intv_args[0], OUTFIFO, j);
			return(6);
		}
		j = open(INFIFO, O_RDWR);
		if(j != 1){
			fprintf(stderr, "%s: can not open %s to channel 1, got %d\n",
				intv_args[0], INFIFO, j);
			return(6);
		}
#ifdef DEBUG
		fprintf(stderr, "%s: Executing %s\n", MakeTimeStamp(), intv_args[0]);
#endif
		if(execv(intv_args[0], intv_args) == -1){
			fprintf(stderr, "execv on interactive validator fails\n");
			return(5);
		}
		fprintf(stderr, "Oops! %s could not execve!\n", intv_args[0]);
		/* Not reached */
		return(0);
	}
#ifdef DEBUG
	fprintf(stderr, "%s: Interactive validator pid is %d\n", MakeTimeStamp(), intv_pid);
#endif
	/* Now, spawn off and execute contestant program like normal */
	contestant_pid = fork();
	if(contestant_pid == 0){
		/* Child - set up stdin and stdout to be fifos */
		close(0);
		close(1);
		j = open(INFIFO, O_RDWR);
		if(j != 0){
			fprintf(stderr, "%s: can not open %s to channel 0, got %d\n",
				contestant_args[0], INFIFO, j);
			return(6);
		}
		j = open(OUTFIFO, O_RDWR);
		if(j != 1){
			fprintf(stderr, "%s: can not open %s to channel 1, got %d\n",
				contestant_args[0], OUTFIFO, j);
			return(6);
		}
#ifdef DEBUG
		fprintf(stderr, "%s: Executing %s\n", MakeTimeStamp(), contestant_args[0]);
#endif
		if(execv(contestant_args[0], contestant_args) == -1){
			perror("execve fails for contestant program\n");
			return(8);
		}
		/* Not reached */
		return(0);
	}	
	/* And now, we wait */
#ifdef DEBUG
	fprintf(stderr, "%s: Contestant PID is %d\n", MakeTimeStamp(), contestant_pid);
#endif
	bContestantFinished = 0;
	wSubStat = -1;
	for(;;){
		/*
		 * Wait for either process to finish (interactive validator) or contestant submission.
		 * If interactive validator finishes first, then we use its exit status for the result.
		 * If submission finishes first with an exception (non-normal exit), it's an RTE and
		 * we kill off the judge since we don't care about its result.
		 */
		j = wait(&(wstat));
		if(j == intv_pid){
			/*
			 * Once the interactive validator finishes, it's all over, no matter WHAT
			 * if the contestant program hasn't finished, kill it
			 */
			if(bContestantFinished == 0){
#ifdef DEBUG
				fprintf(stderr, "%s: Interactive validator finishes with status 0x%x - killing submission pid %d\n",
					MakeTimeStamp(), wstat, contestant_pid);
#endif
				kill(contestant_pid, 9);
#ifdef DEBUG
			} else {
				fprintf(stderr, "%s: Interactive validator finishes with status 0x%x - contestant submission finished earlier with status 0x%x\n",
					MakeTimeStamp(), wstat, wSubStat);
#endif
			}

			if(WEXITSTATUS(wstat) == EXITCODE_AC){
				GenXML("Accepted", "");
			} else if(WEXITSTATUS(wstat) == EXITCODE_WA){
				GenXML("No - Wrong answer", ReadLastLine(&(szFeedBackFile[0])));
			} else {
				/* If the judge dies abnormally, something is probably really bad */
				snprintf(&(szErr[0]), sizeof(szErr), "bad return code %d (0x%x)",
					WEXITSTATUS(wstat), wstat);
				GenXML("Other - contact staff", &(szErr[0]));
			}
			break;
		}
		if(j == contestant_pid){
#ifdef DEBUG
			fprintf(stderr, "%s: Contestant finishes with status 0x%x\n", MakeTimeStamp(), wstat);
#endif
			wSubStat = wstat;
			bContestantFinished = 1;
			if(wstat != 0){
				/* This is an RTE since it terminated abbynormally or non-zero exit code.  Kill validator */
#ifdef DEBUG
				fprintf(stderr, "%s: Contestant finished abnormally - killing interactive validator - RTE\n", MakeTimeStamp());
#endif
				kill(intv_pid, 9);
				snprintf(&(szRTEBuf[0]), sizeof(szRTEBuf)-1, "Exit status 0x%x", wstat);
				GenXML("No - Run-time Error", &(szRTEBuf[0]));
				break;
			}
		}
	}
#ifdef DEBUG
	fprintf(stderr, "%s: All done!\n", MakeTimeStamp());
#endif
	unlink(INFIFO);
	unlink(OUTFIFO);
	if(bSentXML == 0){
		GenXML("Other - contact staff", "unexpected runner exit");
	}
	return(0);
}

static void GenXML(const char *szMsg1, const char *szMsg2)
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
			fprintf(stderr, "Can't open result file %s\n", szResultFile);
		}
	} else {
		fprintf(stderr, "No result file: %s - %s\n", szMsg1, szMsg2 == NULL ? "" : szMsg2);
	}
}

static char *ReadLastLine(char *szFile)
{
	static char szLine[512];
	char *s;

	FILE *fp = fopen(szFile, "rt");
	if(fp != NULL){
		while(fgets(&(szLine[0]), sizeof(szLine)-2, fp) != NULL){
			;
		}
		s = &(szLine[strlen(szLine)]);
		while(--s >= &(szLine[0]) && (isspace(*s) != 0) ){
			;
		}
		*++s = '\0';
		
	} else {
		snprintf(&(szLine[0]), sizeof(szLine), "Can not read  %s", szFile);
	}
	return(&(szLine[0]));
}

