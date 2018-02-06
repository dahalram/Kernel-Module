#include <linux/module.h> // Needed for all modules
#include <linux/init.h>	  // Needed for macros
#include <linux/types.h>   // Needed for list macros
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/list.h>    // Needed for linked list
#include <linux/types.h>   // Needed for list macros
#include <linux/slab.h>    // Needed for kernel
#include <linux/hashtable.h> // Needed for hashtable

//#define NUM_OF_BIRTHDAYS 5
#define BITS 3

// Birthday struct
struct birthday {
	char name[100];
	int day;
	int month;
	int year;
	struct hlist_node my_hash_list;
};

/*
struct bucket {
	struct hlist_head *head;
	int len = 2;
};

struct HashTable {
	unsigned int size;
	bucket *b_head; // Head of the bucket/doubly linked list
} HashTab;

HashTab *make_HashTable (unsigned int size) {

}
*/
/*#define HASH_TABLE(birthday_hash, BITS)\
	struct hlist_head birthday_hash[1 << (BITS)] =\ 
		{ [0 ... ((1 << (BITS)) -1)] = HLIST_HEAD_INIT}
*/
DEFINE_HASHTABLE(a, BITS);

/*
#define hash_add_rcu(hashtable, node, key)\
	hlist_add_head_rcu(node, &hashtable[hash_min(key, HASH_BITS(hashtable))])

*/
/*
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
*/


static int birthday_hash_init (void) {
	struct birthday *first, *second, *third, *fourth, *fifth, *tmp;

	first = kmalloc(sizeof *first, GFP_KERNEL);
	if (!first) { printk("can't allocate memory"); return -ENOMEM; }

	second = kmalloc(sizeof *second, GFP_KERNEL);
	third = kmalloc(sizeof *third, GFP_KERNEL);
	fourth = kmalloc(sizeof *fourth, GFP_KERNEL);
	fifth = kmalloc(sizeof *fifth, GFP_KERNEL);

	//memcpy(first->name, "a", 1);
	first->name = "a";
	first->day = 1;
	first->month = 1;
	first->year = 2001;

	//memcpy(second->name, "ba", 2);
	second->name = "ba";
	second->day = 2;
	second->month = 2;
	second->year = 2002;

	//memcpy(third->name, "cbc", 3);
	third->name = "cba";
	third->day = 3;
	third->month = 3;
	third->year = 2003;

	//memcpy(fourth->name, "dbcd", 4);
	fourth->name = "dcba";	
	fourth->day = 4;
	fourth->month = 4;
	fourth->year = 2004;

	//memcpy(fifth->name, "ebcde", 5);
	fifth->name = "edcba";
	fifth->day = 5;
	fifth->month = 5;
	fifth->year = 2005;

	hash_add(a, &first->my_hash_list, first->name);
	hash_add(a, &second->my_hash_list, second->name);
	hash_add(a, &third->my_hash_list, third->name);
	hash_add(a, &fourth->my_hash_list, fourth->name);
	hash_add(a, &fifth->my_hash_list, fifth->name);

	int i = 0;

	hash_for_each(a, i, tmp, my_hash_list) {
		printk(KERN_INFO "name=%s is in bucket %d\n", first->name, i);
	}

	return 0;
}

static void birthday_hash_clean(void) {
	printk(KERN_INFO "Removing module\n");
}

// Macros for registering module entry and exit points
module_init(birthday_hash_init);
module_exit(birthday_hash_clean);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module for Hashtable");
MODULE_AUTHOR("Ram D");
