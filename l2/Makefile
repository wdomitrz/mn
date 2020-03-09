OPTIM_OPTIONS = -march=native -mtune=native -ftree-vectorize -msse2 -ftree-vectorizer-verbose=5 -O3

.PHONY = all clean

DLOG_N = 9
DSTEP_NUM = 12
DSTEP_SIZE = 4

all: julias_set_naive julias_set_vectorized

clean:
	rm julias_set_naive julias_set_vectorized

julias_set_naive:
	g++ julias_set_naive.cpp -o julias_set_naive ${OPTIM_OPTIONS} -DLOG_N=${DLOG_N} -DSTEP_NUM=${DSTEP_NUM}

julias_set_vectorized:
	g++ julias_set_vectorized.cpp -o julias_set_vectorized ${OPTIM_OPTIONS} -DLOG_N=${DLOG_N} -DSTEP_NUM=${DSTEP_NUM} -DSTEP_SIZE=${DSTEP_SIZE}

