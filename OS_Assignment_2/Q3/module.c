#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>  // Required for task_struct
#include <linux/unistd.h> // Required for __NR_cs3753_add

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module to count running processes");
MODULE_VERSION("0.1");

static int __init proc_count_init(void)
{
    struct task_struct *task;
    int count = 0;

    printk(KERN_INFO "proc_count: Module loaded\n");

    // Traverse the list of processes
    for_each_process(task)
    {
        count++;
    }

    printk(KERN_INFO "proc_count: Currently running processes: %d\n", count);

    return 0;
}

static void __exit proc_count_exit(void)
{
    printk(KERN_INFO "proc_count: Module unloaded\n");
}

module_init(proc_count_init);
module_exit(proc_count_exit);
