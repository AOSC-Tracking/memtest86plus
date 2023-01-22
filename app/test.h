// SPDX-License-Identifier: GPL-2.0
#ifndef TEST_H
#define TEST_H
/**
 * \file
 *
 * Provides types and variables used when performing the memory tests.
 *
 *//*
 * Copyright (C) 2020-2022 Martin Whitaker.
 */

#include <stdbool.h>
#include <stdint.h>

#include "pmem.h"
#include "smp.h"

#include "barrier.h"
#include "spinlock.h"

/**
 * A mapping from a CPU core number to the index number of the memory chunk
 * it operates on when performing a memory test in parallel across all the
 * enabled cores (in the current proximity domain, when NUMA awareness is
 * enabled).
 */
extern uint8_t chunk_index[MAX_CPUS];
/**
 * An array where the count of used CPUs in the current proximity domain.
 */
extern uint8_t used_cpus_in_proximity_domain[MAX_PROXIMITY_DOMAINS];

 /*
  * The number of CPU cores being used for the current test. This is always
  * either 1 or the full number of enabled CPU cores.
  */
extern int num_active_cpus;

/**
 * The current master CPU core.
 */
extern int master_cpu;

/**
 * A barrier used when running tests.
 */
extern barrier_t *run_barrier;

/**
 * A mutex used when reporting errors or printing trace information.
 */
extern spinlock_t *error_mutex;

#ifdef __x86_64__
/**
 * The word width (in bits) used for memory testing.
 */
#define TESTWORD_WIDTH       64
/**
 * The number of hex digits needed to display a memory test word.
 */
#define TESTWORD_DIGITS      16
/**
 * The string representation of TESTWORDS_DIGITS
 */
#define TESTWORD_DIGITS_STR "16"
#else
/**
 * The word width (in bits) used for memory testing.
 */
#define TESTWORD_WIDTH      32
/**
 * The number of hex digits needed to display a memory test word.
 */
#define TESTWORD_DIGITS      8
/**
 * The string representation of TESTWORDS_DIGITS
 */
#define TESTWORD_DIGITS_STR "8"
#endif

/**
 * The word type used for memory testing.
 */
typedef uintptr_t testword_t;

/**
 * A virtual memory segment descriptor.
 */
typedef struct {
    uintptr_t   pm_base_addr;
    testword_t  *start;
    testword_t  *end;
    uint32_t    proximity_domain_idx;
} vm_map_t;

/**
 * The list of memory segments currently mapped into virtual memory.
 */
extern vm_map_t vm_map[MAX_MEM_SEGMENTS];
/**
 * The number of memory segments currently mapped into virtual memory.
 */
extern int vm_map_size;

/**
 * The number of completed test passes.
 */
extern int pass_num;
/**
 * The current test number.
 */
extern int test_num;
/**
 * The current window number.
 */
extern int window_num;

/**
 * A flag indicating that testing should be restarted due to a configuration
 * change.
 */
extern bool restart;
/**
 * A flag indicating that the current test should be aborted.
 */
extern bool bail;

/**
 * The base address of the block of memory currently being tested.
 */
extern uintptr_t test_addr[MAX_CPUS];

#endif // TEST_H
