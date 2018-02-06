#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

#define NUM_OF_BIRTHDAYS 5
#define BITS 3

struct birthday {
	char name[100];
	int day;
	int month;
	int year;
	struct hlist_node my_hash_list;
};

#define HASH_TABLE(birthday_hash, BITS)	\
	struct hlist_head birthday_hash[1 << (BITS)] =	\ 
		{ [0 ... ((1 << (BITS)) -1)] = HLIST_HEAD_INIT}

#define hash_add_rcu(hashtable, node, key)	\
	hlist_add_head_rcu(node, &hashtable[hash_min(key, HASH_BITS(hashtable))])

struct birthday first = {
	.name = "abcd",
	.day = 1,
	.month = 12,
	.year = 1990,
	.my_hash_list = 0
};

struct birthday second = {
	.name = "abcde",
	.day = 15,
	.month = 12,
	.year = 1995,
	.my_hash_list = 0
};

struct birthday third = {
	.name = "abcd",
	.day = 12,
	.month = 12,
	.year = 1990,
	.my_hash_list = 0
};

struct birthday fourth = {
	.name = "abcdef",
	.day = 15,
	.month = 1,
	.year = 1996,
	.my_hash_list = 0
};

struct birthday fifth = {
	.name = "abcdef",
	.day = 21,
	.month = 2,
	.year = 1990,
	.my_hash_list = 0
};

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
