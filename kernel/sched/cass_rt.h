// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2024 Sultan Alsawaf <sultan@kerneltoast.com>.
 */

#ifdef CONFIG_SCHED_CASS
int cass_select_task_rq_rt(struct task_struct *p, int prev_cpu, int sd_flag,
			   int wake_flags);

/* Use CASS. A dummy wrapper ensures the replaced function is still "used". */
static inline void *select_task_rq_rt_dummy(void)
{
	return (void *)select_task_rq_rt;
}
static int cass_select_task_rq_rt_hooked(struct task_struct *p, int prev_cpu,
					 int sd_flag, int wake_flags)
{
	/* Vendor placement hooks live in the original path, so use it */
	if (trace_android_rvh_select_task_rq_rt_enabled() ||
	    trace_android_rvh_find_lowest_rq_enabled())
		return select_task_rq_rt(p, prev_cpu, sd_flag, wake_flags);

	return cass_select_task_rq_rt(p, prev_cpu, sd_flag, wake_flags);
}
#define select_task_rq_rt cass_select_task_rq_rt_hooked
#endif /* CONFIG_SCHED_CASS */
