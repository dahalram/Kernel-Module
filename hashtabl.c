#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

#define NUM_OF_BIRTHDAYS 6
 

struct birthday {
	char name[100];
	int day;
	int month;
	int year;
	struct list_head list;
}

static LIST_HEAD (birthday_list);

struct birthday *person;

static int birthday_hash_init (void) {

	return 0;
}

static void birthday_hash_clean(void) {

}

module_init(birthday_hash_init);
module_exit(birthday_hash_clean);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module for Hashtable");
MODULE_AUTHOR("Ram D");
