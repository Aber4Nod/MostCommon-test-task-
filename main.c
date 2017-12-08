#include "./deps.h"

/* building and proceding priority queue function 
 * (based on a binary min-heap -> insertion/removal operations ~O(logN))
 * [Program Base Library is used]*/
void buildQueue(const Static* st)
{
	if (fseek(st->fp, 0, SEEK_SET)) {
		perror("fseek");
		exit(ERROR_INTERNAL);
	}
    char* strPr = (char*)malloc(st->maxlength*sizeof(char));
    if (fgets(strPr, st->maxlength, st->fp) == NULL){
        exit(ERROR_INTERNAL);
    }
    char* strC = (char*)malloc(st->maxlength*sizeof(char));
    int cnt=1;
    int size=0;
    int lines=1;

    PblPriorityQueue* priorityQueue;
    priorityQueue = pblPriorityQueueNew();
    while (lines < st->numlines){
        if (fgets(strC, st->maxlength, st->fp) == NULL){
            exit(ERROR_INTERNAL);
        }
        if (!strcmp(strPr, strC)){
            cnt++;
        } else {
            if (size != 10) {
                pblPriorityQueueInsert(priorityQueue, cnt, strPr);
                size++;
            } else {
                int prior=0;
                pblPriorityQueueGetFirst(priorityQueue,&prior);
                if (prior < cnt) {
                    pblPriorityQueueRemoveFirst(priorityQueue,NULL);
                    pblPriorityQueueInsert(priorityQueue,cnt,strPr);
                }
            }
            strPr = (char*)malloc(st->maxlength*sizeof(char));
            strcpy(strPr,strC);
            cnt=1;
        }
        lines++;
    }
    if (size != 10) {
        pblPriorityQueueInsert(priorityQueue, cnt, strPr);
        size++;
    } else {
        int prior=0;
        pblPriorityQueueGetFirst(priorityQueue,&prior);
        if (prior < cnt) {
            pblPriorityQueueRemoveFirst(priorityQueue,NULL);
            pblPriorityQueueInsert(priorityQueue,cnt,strPr);
        }
    }
    char bufR[size][st->maxlength];
    int bufPrior[size];
    for(int i=size-1;i>=0;--i){
        strcpy(bufR[i],(char*)pblPriorityQueueGetFirst(priorityQueue,&bufPrior[i]));
        pblPriorityQueueRemoveFirst(priorityQueue,NULL);
    }
    char name[PATH_MAX];
    snprintf(name,PATH_MAX,"%s%s%s","./res/",basename(st->sname),".XXXXXX");
    int fdR = mkstemp(name);
	FILE* fdtmpR = fdopen(fdR,"r+");

    printf("#\tfrequency\tpasswd\n");
    for(int i = 0; i < size; ++i) {
        printf("%d.\t%9d\t%7s",i+1,bufPrior[i],bufR[i]);
        fprintf(fdtmpR,"%d.\t%d\t%s",i+1,bufPrior[i],bufR[i]);
    }
    pblPriorityQueueFree(priorityQueue);
}

/* MergeSort function */
void MergeSort(Args* args)
{
    int chLeft = args->chLeft;
    int l = args->l;
    int r = args->r;

    /* Trivial cases (bottom of the tree) */
	if (r == l)
		return;

	char* fst = (char*)malloc(args->st->maxlength*sizeof(char));
	char* scnd = (char*)malloc(args->st->maxlength*sizeof(char));


	if (r - l == 1)
	{
        pthread_mutex_lock(&args->st->lock);
        if (fseek(args->st->fp, chLeft, SEEK_SET)) {
            exit(ERROR_INTERNAL);
        }
		if (fgets(fst, args->st->maxlength, args->st->fp) == NULL){
            exit(ERROR_INTERNAL);
        }
        if (fgets(scnd, args->st->maxlength, args->st->fp) == NULL){
            exit(ERROR_INTERNAL);
        }

		if (strcmp(fst, scnd)<0) {
			if (fseek(args->st->fp, chLeft, SEEK_SET)) {
				exit(ERROR_INTERNAL);
			}
			fputs(scnd, args->st->fp);
			fputs(fst, args->st->fp);
		}
        pthread_mutex_unlock(&args->st->lock);
		free(fst);
		free(scnd);
		return;
	}
    /* / Trivial cases */

	char name[] = {"/tmp/123XXXXXX"};
    int fdt = -1;
    do {
       fdt = mkstemp(name);
    } while (fdt == -1);
	FILE* fdtmp = fdopen(fdt,"r+");
	if (fseek(fdtmp, 0, SEEK_SET)) {
		exit(ERROR_INTERNAL);
	}

	int cnt = l;
	int chMiddle = chLeft;
    int base = args->crNumber/2;
    double divider = args->crNumber > 1 ? (double)args->crNumber/base : 2;

    FILE* bfp;
    if ((bfp = fopen(args->st->sname, "r+"))==NULL){
        exit(ERROR_INTERNAL);
    }
	if (fseek(bfp, chLeft, SEEK_SET)) {
		exit(ERROR_INTERNAL);
	}

    /* getting an optimal division of the rest interval between threads */
	while (cnt != r) {
		if (fgetc(bfp) == '\n') {
			if (cnt <= (r - l - 1) / divider + l)
				chMiddle++;
			cnt++;
		} else
		if (cnt <= (r - l - 1) / divider + l)
			chMiddle++;
	}
	int m = (r - l - 1) / divider + l;

    Args* argsL = (Args*)malloc(sizeof(Args));
    argsL->chLeft = chLeft;
    argsL->l = l;
    argsL->r = m;
    argsL->st = args->st;
    pthread_t thr1;

    if (args->crNumber > 1){ // if: more than one thread is obtainable at this
                             // moment -> divide the subproblem
        argsL->crNumber = base;
    
        if (pthread_create(&thr1,NULL,(void*)(*MergeSort),(void*)argsL)){
            exit(ERROR_INTERNAL);
        }
    } else { // else: current thread is working as a stand alone one
        argsL->crNumber = 1;
        MergeSort(argsL);
    }

    /* current thread is strating at another branch */
    Args* argsR = (Args*)malloc(sizeof(Args));
    argsR->chLeft = chMiddle;
    argsR->l = m+1;
    argsR->r = r;
    argsR->crNumber = args->crNumber - base;
    argsR->st = args->st;

	MergeSort(argsR);
    free(argsR);

    if (args->crNumber > 1){ // waiting for another branch thread be completed
        if (pthread_join(thr1, NULL)){
            exit(ERROR_INTERNAL);
        }
        close(thr1);
    }
    free(argsL);

	int lnLeft = l;
	int lnRight = m + 1;
	int xl = chLeft;
	int xr = chMiddle;
	int cur = 0;

	if (fseek(fdtmp, 0, SEEK_SET)) {
		exit(ERROR_INTERNAL);
	}

    /* merging phase */
    pthread_mutex_lock(&args->st->lock);
	while (r - l + 1 != cur)
	{
		if (lnLeft > m) {
			if (fseek(args->st->fp, xr, SEEK_SET)) {
				exit(ERROR_INTERNAL);
			}
			if (fgets(fst, args->st->maxlength, args->st->fp) == NULL){
                exit(ERROR_INTERNAL);
            }
			fputs(fst,fdtmp);
			cur++;
			lnRight++;
			xr += strlen(fst);
		}
		else if (lnRight>r) {
			if (fseek(args->st->fp, xl, SEEK_SET)) {
				exit(ERROR_INTERNAL);
			}
			if (fgets(scnd,args->st->maxlength, args->st->fp) == NULL){
                exit(ERROR_INTERNAL);
            }
			fputs(scnd, fdtmp);
			cur++;
			lnLeft++;
			xl += strlen(scnd);
		}
		else {
			if (fseek(args->st->fp, xl, SEEK_SET)) {
				exit(ERROR_INTERNAL);
			}
			if (fgets(fst, args->st->maxlength, args->st->fp) == NULL){
                exit(ERROR_INTERNAL);
            }
			if (fseek(args->st->fp, xr, SEEK_SET)) {
				exit(ERROR_INTERNAL);
			}
			if (fgets(scnd, args->st->maxlength, args->st->fp) == NULL){
                exit(ERROR_INTERNAL);
            }
			if (strcmp(fst, scnd)<0) {
				fputs(scnd, fdtmp);
				cur++;
				lnRight++;
				xr += strlen(scnd);
			}
			else {
				fputs(fst, fdtmp);
				cur++;
				lnLeft++;
				xl += strlen(fst);
			}
		}
	}
	if (fseek(args->st->fp, chLeft, SEEK_SET)) {
		exit(ERROR_INTERNAL);
	}
	if (fseek(fdtmp, 0, SEEK_SET)) {
		exit(ERROR_INTERNAL);
	}
	for (int i = 0; i<cur; i++)
	{
		if(fgets(fst, args->st->maxlength, fdtmp) == NULL){
            exit(ERROR_INTERNAL);
        }
		fputs(fst, args->st->fp);
	}
    pthread_mutex_unlock(&args->st->lock);
    fclose(fdtmp);
}

int main(int argc, char *argv[])
{
    /* checking the correctness of input data */
    if (argc == 1 || argc > 3) {
        printf("Invalid number of argumnets...\nUsage %s pathname cores_number\n",argv[0]);
       exit(ERROR_ARG_NUMBER); 
    }
    if (access(argv[1], F_OK) == -1){
        printf("err13123123\n");
        exit(ERROR_ARG_PATH);
    } 
    int thrNum=0;
    if (argc==3){
    char* str = "^[0-9]*$";
    regex_t regex;
    if(regcomp(&regex,str,0)){
        exit(ERROR_INTERNAL);
    }

    int ret=0;
    if (!(ret = regexec(&regex,argv[2],0,NULL,0))){
        thrNum=atoi(argv[2]);
    } else if (ret == REG_NOMATCH){
        exit(ERROR_ARG_NCORES);
    } else {
        exit(ERROR_INTERNAL);
    }
    if (!thrNum){
        exit(ERROR_ARG_NCORES);
    }
    regfree(&regex);
    } else {
        thrNum=4;   //May be more optimal to look in /proc/cpuinfo,
                    //which is specific for certain distribution
    }
    
    Static* st = (Static*)malloc(sizeof(Static));
	st->sname = argv[1];
    st->numlines=0;
    st->maxlength=0;
	if ((st->fp = fopen(st->sname, "r+"))==NULL){
        exit(ERROR_INTERNAL);
    }
    /* getting maximum length of the certain line and the total lines number */
	int curlength = 0;
	while (!feof(st->fp)) {
		if (fgetc(st->fp) == '\n') {
			if (curlength >= st->maxlength)
				st->maxlength = curlength+1;
			curlength = 0;
			st->numlines++;
		} else
			curlength++;
	}
	st->maxlength++;
	rewind(st->fp);

    if (st->numlines == 0){
        exit(ERROR_EMPTY_FILE);
    }
    if (thrNum > st->numlines){
        thrNum=st->numlines;
    }

    if (pthread_mutex_init(&st->lock,NULL) != 0){
        exit(ERROR_INTERNAL);
    }
    /* initialising main structure */
    Args* args = (Args*)malloc(sizeof(Args));
    args->chLeft = 0;
    args->l = 0;
    args->r = st->numlines-1;
    args->crNumber = thrNum;
    args->st=st;

    /* starting mergesort */
	MergeSort(args);

    /* proceding queue for getting top 10 */ 
    buildQueue(st);

    /* final clean up */
	fclose(st->fp);
    pthread_mutex_destroy(&st->lock);
    free(st);
    free(args);
}

